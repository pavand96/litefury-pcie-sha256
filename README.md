# LiteFury PCIe **SHA‑256** Streaming Engine — A Hardware Crypto Hello‑World

A complete, reproducible streaming **SHA‑256** accelerator for the
[**RHS Research LiteFury**](https://github.com/RHSResearchLLC/NiteFury-and-LiteFury)
M.2 FPGA card (Xilinx Artix‑7 100T, PCIe Gen2 x4):

1. The host streams an array of 64‑byte messages into the FPGA over PCIe
   via the Xilinx **XDMA** AXI‑Stream H2C channel.
2. A custom HDL pipeline runs **SHA‑256** on each 64‑byte block in
   hardware and produces the corresponding 32‑byte digest.
3. The digests are streamed back via XDMA C2H and verified on the host
   against `hashlib.sha256` and OpenSSL.
4. The same workload is benchmarked on the host CPU using OpenSSL
   (which dispatches to **SHA‑NI** instructions on modern x86), so you
   can see exactly where the FPGA wins, where it loses, and *why*.

This is the natural follow‑up to
[`litefury-pcie-addone`](https://github.com/pavand96/litefury-pcie-addone),
which proved that the PCIe + XDMA + driver path works end‑to‑end with a
trivial `+1` workload. Here we replace the "+1" IP with something the CPU
actually has to *work* for — and the picture changes.

---

## Table of contents

1. [TL;DR results](#1-tldr-results)
2. [Hardware / software prerequisites](#2-hardware--software-prerequisites)
3. [What the design looks like](#3-what-the-design-looks-like)
4. [The SHA‑256 RTL — `sha256_compress.sv` + `sha256_stream.sv`](#4-the-sha-256-rtl)
5. [Repository layout](#5-repository-layout)
6. [Build, flash, test](#6-build-flash-test)
7. [Bottleneck analysis — *the heart of this README*](#7-bottleneck-analysis--the-heart-of-this-readme)
8. [Pushing PCIe / XDMA to the max with the current bitstream](#8-pushing-pcie--xdma-to-the-max)
9. [Why one engine isn't enough — and the path to PCIe‑saturating throughput](#9-scaling-up-multi-engine-roadmap)
10. [Reproducing the numbers](#10-reproducing-the-numbers)

---

## 1. TL;DR results

Workload: hash N independent 64‑byte messages, get back N × 32‑byte digests.

| size (msgs) | CPU MB/s (1 core, SHA‑NI) | FPGA MB/s (Python) | FPGA MB/s (C dma tools) | FPGA / CPU |
|---:|---:|---:|---:|---:|
| 1     | _filled by bench_ | _filled_ | _filled_ | _filled_ |
| 16    | _filled_ | _filled_ | _filled_ | _filled_ |
| 256   | _filled_ | _filled_ | _filled_ | _filled_ |
| 4096  | _filled_ | _filled_ | _filled_ | _filled_ |
| 65536 | _filled_ | _filled_ | _filled_ | _filled_ |

*(Filled in after the first benchmark run — see §10.)*

The architectural truth this design exposes:

* On modern x86 with SHA‑NI, a **single CPU core hashes faster than this
  single‑engine FPGA bitstream** (~2 GB/s vs ~60 MB/s of pure compute).
* The FPGA is **not PCIe‑bottlenecked** here. The bottleneck is the
  *gateware*: one iterative SHA‑256 unit doing ~132 cycles per 64‑byte
  message at 125 MHz = ~60 MB/s, well under the ~1.6 GB/s PCIe Gen2 x4
  ceiling we already measured.
* So the lesson is: **PCIe is fine, the FPGA needs to do more work per
  cycle.** Section 9 explains exactly how to fix that (replicate
  engines, or fully pipeline) and how the area trades.

---

## 2. Hardware / software prerequisites

Identical to the `+1` project — *the same bitstream slot, the same XDMA
configuration, the same kernel driver*. We literally re‑use the Vivado
project and only swap the IP between `xdma_0/M_AXIS_H2C_0` and
`xdma_0/S_AXIS_C2H_0`.

* **Card**: LiteFury (Artix‑7 `xc7a100tfgg484-2L`), PCIe Gen2 x4.
* **Host**: any Linux with a free PCIe slot (we use Proxmox VE on
  kernel 6.17). Slot used: CPU‑attached x16 (works in any electrical x4+).
* **Vivado**: 2025.2 (the `Sample-Projects/Project-0` Vivado project from
  RHS Research is the starting point; *exact* same .xpr as the `+1`
  project).
* **XDMA driver**: Xilinx `dma_ip_drivers/XDMA/linux-kernel/xdma`
  built with the kernel 6.17 fix (`cp ../include/libxdma_api.h .`).
  Loaded as `modprobe xdma poll_mode=1`.
* **C user tools** (built from `dma_ip_drivers/.../tools/`):
  `dma_to_device`, `dma_from_device`, `performance`, `reg_rw`.
* **OpenSSL** for the CPU baseline (`apt install libssl-dev`).
* **cocotb 2.x + Verilator** for RTL simulation (any Linux with
  `pip install cocotb` works).

---

## 3. What the design looks like

```
   host ───────────────────────── PCIe Gen2 x4 ───────────────────────── FPGA (Artix-7 100T)

                                                                ┌──────────────────────────┐
   /dev/xdma0_h2c_0 ── DMA ──▶  xdma_0.M_AXIS_H2C_0 (128b @125 MHz) ─▶│      sha256_stream       │
                                                                │   (gearbox SV style)     │
                                                                │  ┌─────────────────────┐ │
                                                                │  │   sha256_compress   │ │
                                                                │  │   iterative, 66 cyc │ │
                                                                │  │   per 512‑bit block │ │
                                                                │  └─────────────────────┘ │
   /dev/xdma0_c2h_0 ◀── DMA ──  xdma_0.S_AXIS_C2H_0 (128b @125 MHz) ◀─│                          │
                                                                └──────────────────────────┘
```

* **AXI‑Stream width**: 128 bits @ 125 MHz = 2 GB/s wire bandwidth in
  *each* direction (matches the PCIe Gen2 x4 hard‑IP limit).
* **Per‑message wire format**:
  * H2C: 4 beats of 128 b = 64 bytes of message, with `tlast=1` on beat 3.
  * C2H: 2 beats of 128 b = 32 bytes of digest, with `tlast=1` on beat 1.
* Everything is **byte‑identical to standard SHA‑256** (FIPS 180‑4):
  the FPGA does the same two‑block compression a CPU does on a 64‑byte
  input (block 1 = message, block 2 = standard 0x80/zero/length padding).

---

## 4. The SHA‑256 RTL

The implementation deliberately copies the *coding conventions* of the
[`Generic_Parameterized_Modules/gearbox`](https://github.com/aignacio/Generic_Parameterized_Modules)
reference: SystemVerilog, ready/valid streaming handshakes, async‑low
reset (`rstn`), `_q` / `_next` naming, named generates, and detailed
inline commentary about *why* the code is shaped the way it is.

### 4.1 `rtl/sha256_compress.sv`

Iterative SHA‑256 compression function (FIPS 180‑4 §6.2).

```
job‑input  : start, block[511:0], cv_in[255:0]      (handshake: ready ↔ start)
job‑output : done (1‑cycle pulse), cv_out[255:0]
latency    : 1 cycle load + 64 round cycles + 1 done cycle = 66 cycles total
```

Implementation details worth pointing out:

* **8 working variables `a..h`** as 32‑bit FFs. Standard pattern.
* **K constants** in a 64‑entry `case` (synthesizes to BRAM/LUTRAM or
  hard logic depending on the tool's discretion).
* **Round primitives** (`Ch`, `Maj`, `BigS0`, `BigS1`, `SmS0`, `SmS1`)
  as `automatic function`s. These inline cleanly.
* **Message schedule W** is computed *on the fly* with a **16‑deep
  rolling window** instead of materialising the full 64‑word array.
  This is the standard area‑saving trick:
  * For round `t < 16`: `W[t]` is pulled directly from `block`.
  * For round `t ≥ 16`: `W[t] = σ₁(W_q[14]) + W_q[9] + σ₀(W_q[1]) + W_q[0]`.
  The window shifts up every cycle and `W[t]` is injected at the top.
* **Final add** at `t==63`: in the same cycle we'd otherwise advance to
  round 64, we instead override the working register updates with
  `Hᵢ_new = Hᵢ_old + working_iᵢ`. Subtle: the snapshot of the input CV
  (`av_q .. hv_q`) is taken at `start` so the final add is unambiguous.
* **Reset is async‑low (`rstn`)**, matching the gearbox style.

Total Artix‑7 cost (post‑synth): ≈ **1500–2500 LUTs + ~700 FFs** for one
iterative engine. Trivially fits.

### 4.2 `rtl/sha256_stream.sv`

AXI4‑Stream wrapper that turns 64‑byte input messages into 32‑byte
digests. Two cooperating FSMs:

* **RX FSM** (`RX_COLLECT → RX_RUN_MSG → RX_RUN_PAD → RX_EMIT_WAIT`):
  * Collects 4 input beats of 128 b into a 512‑bit `msg_q`.
  * Dispatches the message block to `sha256_compress` with `cv_in = IV`.
  * On `core_done`, dispatches the **hard‑coded padding block**
    `0x80 || 0×55 || length=512(64b BE)` with `cv_in = previous result`.
  * Latches the final digest and waits for TX to drain it.
* **TX FSM** (`TX_IDLE → TX_BEAT0 → TX_BEAT1 → TX_DONE`):
  * Emits the 256‑bit digest as 2 beats of 128 b with `tlast` on the
    second beat, then pulses `tx_consume_digest` to unblock RX.

Subtle correctness fix that bit us during bring‑up:

> The padding block constant was originally `{8'h80, 448'h0, 64'd512}`
> — that's **520 bits**, not 512. The high `0x80` byte was silently
> truncated and the first round of the second compression saw a zero
> message word. Fixed to `{8'h80, 440'h0, 64'd512}` (= 512 bits exactly).
> **Always count your bits when you build a constant by concatenation.**

### 4.3 `rtl/sha256_stream_top.v`

A trivial Verilog (not SystemVerilog) top wrapper that instantiates
`sha256_stream`. Vivado IPI module‑references reject SV files as the
*top* file even when the body is pure SV; the wrapper sidesteps that.

### 4.4 Simulation — cocotb

```bash
cd sim
make                    # runs both tests with verilator
make -f Makefile.compress     # runs the core‑only unit test
```

* `test_sha256_compress.py` — drives the compression core with a known
  block, compares `cv_out` against a Python reference implementation of
  the SHA‑256 round function. Catches all the per‑round arithmetic bugs.
* `test_sha256_stream.py` — drives the AXI‑Stream wrapper with a
  known‑vector message (64 zero bytes → `f5a5fd42d16a2030…`) and 16
  random 64‑byte messages, comparing each result against
  `hashlib.sha256`.

Both pass at sim time ~1 µs / hash, which agrees with the analytical
estimate of 132 cycles × 8 ns = 1.056 µs.

---

## 5. Repository layout

```
litefury-pcie-sha256/
├── rtl/
│   ├── sha256_compress.sv        # iterative round engine (the heavy lifting)
│   ├── sha256_stream.sv          # AXI‑Stream wrapper + dual‑compression FSM
│   └── sha256_stream_top.v       # Verilog top so Vivado BD will accept it
├── sim/
│   ├── Makefile                  # cocotb + verilator for the wrapper
│   ├── Makefile.compress         # cocotb + verilator for the bare core
│   ├── test_sha256_compress.py   # core unit test vs Python ref
│   └── test_sha256_stream.py     # wrapper test vs hashlib
├── tcl/
│   ├── build_stream_sha256.tcl   # swap +1 IP for sha256_stream, build bitstream
│   ├── program-litefury.tcl      # flash SPI over remote hw_server
│   └── check_done.tcl
├── host/
│   ├── Makefile                  # builds cpu_sha256_bench
│   ├── cpu_sha256_bench.c        # fair single‑core OpenSSL/SHA‑NI baseline
│   ├── test_sha256.py            # correctness smoke test via /dev/xdma0_*
│   └── bench_sha256.py           # CPU vs FPGA‑Python vs FPGA‑C bench, prints table
├── docs/                         # (room for waveform PNGs etc.)
├── LICENSE
├── .gitignore
└── README.md (this file)
```

---

## 6. Build, flash, test

### 6.1 Simulate first (sanity)

```bash
cd sim
make -f Makefile.compress         # ~5 s
make                              # ~5 s
```

You should see `TESTS=1 PASS=1` for the core test and `TESTS=2 PASS=2`
for the wrapper. If either fails, **do not flash** — fix the RTL first.

### 6.2 Build the bitstream

The build script *swaps* the `add1_stream_0` IP in the existing
`litefury-pcie-addone` Vivado project for `sha256_stream_0`, leaving the
entire XDMA / PCIe / clock infrastructure untouched.

```bash
source /opt/Xilinx/2025.2/Vivado/settings64.sh
vivado -mode batch -source tcl/build_stream_sha256.tcl
```

Outputs:

* `…/project/project.runs/impl_1/Top_wrapper.bit`
* `…/LiteFury/mcs/sha256.mcs`  ←  flash this
* `…/LiteFury/mcs/sha256.bin`  ←  or this if your flasher prefers binary
* `…/project/sha256_util.rpt`  ←  post‑impl utilization report

Build takes ~15–25 min on an 8‑core x86 box.

### 6.3 Flash the SPI flash

Run on a machine that can reach the `hw_server` of the JTAG host:

```bash
ssh build-host vivado -mode batch -source tcl/program-litefury.tcl
```

(The script references the JTAG host as `pdevarasetti:3121` — edit to
match your setup.) After flashing, **cold reboot** the host that holds
the LiteFury so PCIe re‑enumerates with the new bitstream.

### 6.4 Smoke test

On the host with `/dev/xdma0_*`:

```bash
sudo modprobe xdma poll_mode=1
sudo python3 host/test_sha256.py 64
# → PASS  64 hashes verified
```

If you ever see `OSError: [Errno 512]` here, the H2C engine is wedged
from a prior failed run — reset with:

```bash
sudo rmmod xdma
sudo bash -c 'echo 1 > /sys/bus/pci/devices/0000:01:00.0/reset'
sudo modprobe xdma poll_mode=1
```

(This is the same `FLR` recovery trick documented in the `+1` repo.)

### 6.5 Benchmark

```bash
make -C host                         # builds cpu_sha256_bench
sudo python3 host/bench_sha256.py    # CPU vs FPGA‑py vs FPGA‑C
```

---

## 7. Bottleneck analysis — *the heart of this README*

To reason about FPGA‑vs‑CPU correctly, write the bandwidth chain:

```
   ┌─────────┐   PCIe TX   ┌──────────┐   XDMA H2C   ┌────────────┐
   │  HOST   │ ──────────▶ │ XDMA hw  │ ───────────▶ │ sha256_str │
   │ memory  │             │  Gen2 x4 │   128b@125M  │  engine    │
   └─────────┘             └──────────┘              └────────────┘
        ▲                       ▲                          │
        │     XDMA C2H          │      compute              │
        └───────────────────────┴──────────────────────────┘
              128b @ 125 MHz             (this row is the bottleneck)
```

Per‑stage hard caps:

| stage | hard cap | notes |
|---|---|---|
| PCIe Gen2 x4 raw                  | ~2.0 GB/s/dir | 5 GT/s × 4 × 8/10 ≈ 2.0 GB/s |
| PCIe Gen2 x4 *usable* on Linux    | ~1.6 GB/s/dir | TLP + ACK overhead, measured |
| XDMA AXI‑Stream 128b @ 125 MHz    | ~2.0 GB/s/dir | matches PCIe by construction |
| sha256_stream (1 engine, this build) | **~60.5 MB/s of input** | 132 cyc × 8 ns / 64 B |
| CPU single core w/ SHA‑NI         | ~2.0 GB/s | Ice Lake+, OpenSSL EVP |
| CPU single core no SHA‑NI         | ~300‑400 MB/s | older x86 / non‑x86 |

So in this bitstream the **compute engine is the bottleneck by ~30×**.
PCIe and XDMA are both wildly over‑provisioned. The wall‑clock you'll
measure with the bench script breaks down roughly as:

* **PCIe round‑trip floor (anything, even 0 bytes)**: ~55 µs (Python),
  ~25–30 µs (C tools). Same number we measured in the `+1` project.
  Dominated by two `open()`s, two DMA descriptor setups, IRQ/poll
  completion path, plus user‑space process overhead.
* **Per‑byte compute on the FPGA**: ~16.5 ns/B (1 / 60 MB/s).
* **Per‑byte compute on the CPU (SHA‑NI)**: ~0.5 ns/B (1 / 2 GB/s).
* **Per‑byte transfer on PCIe**: ~0.6 ns/B (1 / 1.6 GB/s).

That means:

* **Small N (1–64 msgs ≈ 64 B – 4 KB)**: dominated by the PCIe RT floor.
  CPU wins by hundreds of × because it touches no PCIe.
* **Medium N (256 msgs ≈ 16 KB)**: FPGA compute starts to dominate;
  we're paying ~270 µs of compute on top of the ~50 µs floor. CPU
  finishes in ~8 µs. CPU wins.
* **Large N (≥ 4096 msgs ≈ 256 KB)**: FPGA compute is now far over
  the PCIe RT floor (>4 ms vs 50 µs), so the FPGA throughput is **just
  the compute throughput** = ~60 MB/s. CPU is still ~30× faster
  (~2 GB/s) until you saturate DDR.

The honest story is: *this single‑engine bitstream is a correctness
demonstration. It is the SHA‑256 equivalent of `hello world` and is
deliberately not tuned for throughput.* §9 explains exactly what changes
to make it competitive.

### Why "compute‑bottlenecked" is actually good news here

It means the *system* (PCIe, driver, DMA) is healthy and the only thing
between us and ~2 GB/s of hashing is gateware. That's a fixable problem:
add more engines or pipeline the existing one. By contrast, if you were
*PCIe‑bottlenecked*, you'd be stuck without a new card.

---

## 8. Pushing PCIe / XDMA to the max

These knobs apply to **any XDMA streaming design**, not just this one.
They are how you turn a "first‑light" bench into a numbers‑you‑show‑off
bench, *without changing the FPGA*.

| # | trick | why | typical effect |
|---|---|---|---|
| 1 | **Use the C tools** (`dma_to_device` / `dma_from_device`) | No Python interpreter, no per‑byte object overhead | ~2× on latency, +10‑20 % throughput |
| 2 | **Keep file descriptors open** across iterations | Each `open()` of `/dev/xdma0_*` re‑inits descriptors | −10 to −20 µs / call |
| 3 | **Page‑aligned, 4 KB‑multiple buffers** (`posix_memalign(…, 4096, …)`) | Driver skips the bounce‑buffer path | Sometimes big, sometimes nothing — measure |
| 4 | **`modprobe xdma poll_mode=1`** for latency | No IRQ context switch | −5 to −15 µs on small DMAs |
| 5 | **Hugepages (2 MB)** for large buffers | Fewer SG descriptors, fewer setup writes | +5‑10 % on >1 MB transfers |
| 6 | **Multi‑queue XDMA** (rebuild IP with N H2C + N C2H) | Overlapped DMAs in parallel | Linear up to PCIe wall |
| 7 | **Double‑buffer H2C and C2H** in the host app | Don't wait for C2H to finish before issuing next H2C | Hides one full RT per pipeline depth |
| 8 | **Pin to the same NUMA node** as the PCIe slot | Avoid cross‑socket QPI hop | +20 % bandwidth on dual‑socket hosts |
| 9 | **`dma_from_device -e` (EOP flush)** | Reader auto‑terminates at `tlast` instead of waiting for `-s` to fill | Removes a stall on the bench |

In `bench_sha256.py` we already do #1, #2 (Python path keeps FDs open
across runs in the loop body), and run with `poll_mode=1` from #4. The
rest is documented for whoever wants to push further.

For *this* bitstream none of these tricks change the steady‑state
throughput, because the FPGA compute is the bottleneck (§7). They *do*
improve the small‑N latency floor — which is what the bench table
exposes.

---

## 9. Scaling up — multi‑engine roadmap

The reason this build tops out at ~60 MB/s of compute is that it has
**one** `sha256_compress` engine doing ~132 cycles per message at 125 MHz.

```
   throughput  =  fclk / cycles_per_message  ×  bytes_per_message
              =  125 MHz / 132  ×  64 B
              ≈  60.5 MB/s
```

To saturate PCIe (~1.6 GB/s) the engine has to deliver ~25 M hashes/s.

There are two clean ways to get there. The RTL is already structured so
that *neither one is a rewrite*; both are local changes inside
`sha256_stream.sv`.

### 9.1 Replicate the engine (N parallel iterative cores)

The simplest. Wrap N `sha256_compress` instances in a round‑robin
dispatcher and collector. Because each engine takes a fixed number of
cycles, round‑robin preserves message order without any reorder buffer.

| N engines | cycles per emitted hash | throughput | Artix‑7 100T LUT fit |
|---:|---:|---:|---|
|  1 | 132 |   60 MB/s | trivial (~2 K LUT) |
|  2 |  66 |  121 MB/s | easy (~4 K LUT) |
|  4 |  33 |  242 MB/s | comfortable (~8 K LUT) |
|  8 |  17 |  470 MB/s | tight (~16 K LUT) |
| 16 |   9 |  889 MB/s | tight on 100T (≈ ¼ of total LUTs just for SHA) |
| 32 |   ~5 | ≈ 1.6 GB/s | doesn't fit on 100T; fits on 200T (NiteFury) |

Implementation sketch (already idiomatic in this code base):

```sv
parameter int NUM_ENGINES = 4;

logic [NUM_ENGINES-1:0] eng_ready, eng_done;
logic [511:0]           eng_block [NUM_ENGINES];
logic [255:0]           eng_cv    [NUM_ENGINES];
logic [255:0]           eng_out   [NUM_ENGINES];

for (genvar i = 0; i < NUM_ENGINES; i++) begin : g_engines
    sha256_compress u_eng (
        .clk(aclk), .rstn(aresetn),
        .start(disp_idx == i && start_pulse),
        .block(eng_block[i]), .cv_in(eng_cv[i]),
        .ready(eng_ready[i]), .done(eng_done[i]),
        .cv_out(eng_out[i])
    );
end
// disp_idx and coll_idx wrap 0..NUM_ENGINES-1 in lockstep with message arrivals.
```

### 9.2 Fully pipeline a single engine (1 hash per cycle)

Build 64 round stages in series, each with its own a..h and W register
file. One block enters every cycle; one chaining value emerges 64 cycles
later. Pipeline throughput = 1 block per cycle = **125 M blocks/s ×
64 B = 8 GB/s** — far beyond PCIe.

Cost: each stage is small (~150‑200 LUTs and ~256 FFs) but 64 of them
plus a 16‑deep W *pipeline* per stage adds up to ~15–20 K LUTs and
~30‑50 K FFs. Fits comfortably on Artix‑7 100T.

Caveat: SHA‑256 of a 64‑byte message is **2 blocks** (msg + pad), and
block 2 depends on block 1's chaining value. A naive 64‑stage pipeline
can therefore only emit **1 hash per 65 cycles** (1.9 MHash/s × 64 B ≈
123 MB/s), because the dependency stalls. To go faster you either
(a) interleave many independent messages through the pipeline, getting
back to 1 hash per cycle when steady‑state, or (b) use *two* parallel
pipelines so block‑2 of message i runs in parallel with block‑1 of
message i+1.

### 9.3 What to build next

For LiteFury / Artix‑7 100T, the **N=8 replicated‑iterative** design is
the sweet spot: about ~500 MB/s of compute, 1/4 of the LUTs, and a
trivial extension of this RTL. It would beat single‑core CPU SHA‑256
*without* SHA‑NI, would still lose to SHA‑NI‑equipped CPUs, and would
fall comfortably under the PCIe wall — meaning the bottleneck story is
clean and the bench table actually changes.

For Artix‑7 200T (NiteFury) the **N=16–32** design becomes feasible.
For UltraScale+/Versal Gen3/Gen4 platforms, full pipelining + multi‑queue
XDMA pushes this into the 10s of GB/s range — at which point the FPGA
beats the CPU on pure throughput too, and the conversation becomes about
power and latency.

---

## 10. Reproducing the numbers

```bash
# 1. Simulate (no hardware needed)
cd sim && make -f Makefile.compress && make

# 2. Build (Vivado 2025.2, ~20 min)
vivado -mode batch -source tcl/build_stream_sha256.tcl

# 3. Flash + cold-boot host (see §6.3)

# 4. Correctness
sudo modprobe xdma poll_mode=1
sudo python3 host/test_sha256.py 256          # PASS  256 hashes verified

# 5. Performance
make -C host
sudo python3 host/bench_sha256.py \
    --cpu-tool ./host/cpu_sha256_bench \
    --dma-tools /root/dma_ip_drivers/XDMA/linux-kernel/tools \
    --sizes 1,4,16,64,256,1024,4096,16384,65536 \
    --runs 5 --cpu-iters 20
```

Copy the printed table into §1 (TL;DR results) of this README.

---

## License

MIT. See [`LICENSE`](LICENSE).

This project is the streaming‑crypto follow‑up to
[`pavand96/litefury-pcie-addone`](https://github.com/pavand96/litefury-pcie-addone).
The Vivado base project (XDMA + LiteFury board files) comes from
[RHSResearchLLC/NiteFury‑and‑LiteFury](https://github.com/RHSResearchLLC/NiteFury-and-LiteFury).
SHA‑256 specified by NIST FIPS 180‑4. RTL style conventions inspired by
[`aignacio/Generic_Parameterized_Modules`](https://github.com/aignacio/Generic_Parameterized_Modules).
