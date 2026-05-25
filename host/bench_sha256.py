#!/usr/bin/env python3
"""
bench_sha256.py — end-to-end CPU vs FPGA SHA-256 benchmark.

Workload: hash N independent 64-byte messages, each producing a 32-byte
SHA-256 digest.

Three benchmarks are run for each size N:

  1. CPU baseline — uses the C tool `cpu_sha256_bench` (libcrypto/EVP).
     Best-of-K iterations. This is a fair, hardware-accelerated CPU number;
     modern x86 cores use the SHA-NI instruction set automatically.

  2. FPGA via raw Python  — opens /dev/xdma0_h2c_0 + /dev/xdma0_c2h_0 from
     Python, reader thread first then writer. Includes ALL syscall +
     Python overhead. Same harness as `host/test_sha256.py`.

  3. FPGA via C tools     — runs Xilinx `dma_from_device` + `dma_to_device`
     from `dma_ip_drivers/.../tools/`. This is the closest you can get
     from a host process to "raw PCIe DMA cost".

Results are timed end-to-end (wall clock from "start of work" to
"all output received"). For repeatable numbers, each size is run RUNS
times and the best (= least system-noise) wall-clock is reported.

This script must run on the host that has the LiteFury attached (i.e.
where /dev/xdma0_* exist).
"""
import argparse
import hashlib
import os
import re
import shutil
import statistics
import subprocess
import sys
import tempfile
import threading
import time


H2C = "/dev/xdma0_h2c_0"
C2H = "/dev/xdma0_c2h_0"


# ----------------------------------------------------------------------
# Helpers shared with test_sha256.py
# ----------------------------------------------------------------------
def write_all(fd, buf):
    mv = memoryview(buf)
    n = 0
    while n < len(mv):
        n += os.write(fd, mv[n:])


def read_all(fd, mv):
    # Use os.read (NOT os.readv). The OOT xdma driver crashes in
    # async_io_handler on the readv path under kernel >=6.x.
    n = 0
    total = len(mv)
    while n < total:
        chunk = os.read(fd, total - n)
        if not chunk:
            raise IOError(f"short read at {n}")
        mv[n:n + len(chunk)] = chunk
        n += len(chunk)


# ----------------------------------------------------------------------
# CPU baseline (C tool)
# ----------------------------------------------------------------------
def bench_cpu(cpu_tool, n_msgs, iters):
    """Returns (MB/s, us_per_hash) — best-of-iters from the C tool."""
    r = subprocess.run([cpu_tool, str(n_msgs), str(iters)],
                       check=True, capture_output=True, text=True)
    # stdout: "CPU_MBPS=xxx CPU_US_PER_HASH=yyy"
    line = r.stdout.strip().splitlines()[-1]
    mbps = float(re.search(r"CPU_MBPS=([\d.eE+-]+)", line).group(1))
    us   = float(re.search(r"CPU_US_PER_HASH=([\d.eE+-]+)", line).group(1))
    return mbps, us


# ----------------------------------------------------------------------
# FPGA path 1: Python / raw os.read/write
# ----------------------------------------------------------------------
def bench_fpga_py(n_msgs, runs, verify=False):
    in_bytes  = n_msgs * 64
    out_bytes = n_msgs * 32
    inp = bytes((i * 31 + 7) & 0xFF for i in range(in_bytes))
    times = []
    last_out = None
    for _ in range(runs):
        out = bytearray(out_bytes)
        ready = threading.Event()

        def reader():
            fd = os.open(C2H, os.O_RDONLY)
            ready.set()
            try:
                read_all(fd, memoryview(out))
            finally:
                os.close(fd)

        t = threading.Thread(target=reader)
        t.start()
        ready.wait()

        t0 = time.perf_counter_ns()
        fd = os.open(H2C, os.O_WRONLY)
        try:
            write_all(fd, inp)
        finally:
            os.close(fd)
        t.join()
        times.append((time.perf_counter_ns() - t0) / 1e9)
        last_out = out

    ok = True
    if verify:
        for i in range(n_msgs):
            exp = hashlib.sha256(inp[i * 64:(i + 1) * 64]).digest()
            got = bytes(last_out[i * 32:(i + 1) * 32])
            if got != exp:
                ok = False
                break
    best = min(times)
    mean = statistics.mean(times)
    in_mbps = (in_bytes / best) / (1024 * 1024)
    us_per_hash = (best * 1e6) / n_msgs
    return in_mbps, us_per_hash, mean, ok


# ----------------------------------------------------------------------
# FPGA path 2: Xilinx C dma tools
# ----------------------------------------------------------------------
def bench_fpga_c(dma_to, dma_from, n_msgs, runs):
    """Times one DMA transfer of N*64 bytes in + N*32 bytes out using the
    Xilinx C tools. Spawns dma_from_device first (reader), then dma_to_device
    (writer), and times the WRITER's wall clock end-to-end.
    """
    in_bytes  = n_msgs * 64
    out_bytes = n_msgs * 32
    inp = bytes((i * 31 + 7) & 0xFF for i in range(in_bytes))

    times = []
    with tempfile.TemporaryDirectory() as td:
        infile  = os.path.join(td, "in.bin")
        outfile = os.path.join(td, "out.bin")
        with open(infile, "wb") as f:
            f.write(inp)

        for _ in range(runs):
            # Start the reader first; it blocks waiting for OUT_BYTES.
            r = subprocess.Popen(
                [dma_from, "-d", C2H, "-s", str(out_bytes), "-c", "1",
                 "-f", outfile],
                stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
            )
            # Give the reader a moment to open C2H and arm the kernel.
            time.sleep(0.005)
            t0 = time.perf_counter_ns()
            w = subprocess.run(
                [dma_to, "-d", H2C, "-s", str(in_bytes), "-c", "1",
                 "-f", infile],
                stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                check=True,
            )
            r.wait()
            times.append((time.perf_counter_ns() - t0) / 1e9)

    best = min(times)
    mean = statistics.mean(times)
    in_mbps = (in_bytes / best) / (1024 * 1024)
    us_per_hash = (best * 1e6) / n_msgs
    return in_mbps, us_per_hash, mean


# ----------------------------------------------------------------------
# Driver
# ----------------------------------------------------------------------
def fmt_size(n_bytes):
    if n_bytes >= 1024 * 1024: return f"{n_bytes // (1024 * 1024)}MB"
    if n_bytes >= 1024:        return f"{n_bytes // 1024}KB"
    return f"{n_bytes}B"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--cpu-tool", default="./host/cpu_sha256_bench",
                    help="Path to compiled cpu_sha256_bench")
    ap.add_argument("--dma-tools",
                    default="/root/dma_ip_drivers/XDMA/linux-kernel/tools",
                    help="Directory with dma_to_device + dma_from_device")
    ap.add_argument("--sizes", default="1,4,16,64,256,1024,4096,16384",
                    help="Comma list of message counts (each msg = 64B)")
    ap.add_argument("--runs", type=int, default=5,
                    help="Wall-clock runs per FPGA test (min reported)")
    ap.add_argument("--cpu-iters", type=int, default=10,
                    help="Inner iterations for the CPU best-of timing")
    ap.add_argument("--verify-py", action="store_true",
                    help="Verify FPGA Python-path output vs hashlib (slower)")
    ap.add_argument("--skip-cpu", action="store_true")
    ap.add_argument("--skip-py",  action="store_true")
    ap.add_argument("--skip-c",   action="store_true")
    args = ap.parse_args()

    counts = [int(x) for x in args.sizes.split(",")]

    cpu_tool = args.cpu_tool
    if not args.skip_cpu and not os.path.isfile(cpu_tool):
        print(f"!! CPU tool not found at {cpu_tool}; build with 'make -C host'", file=sys.stderr)
        sys.exit(1)
    dma_to   = os.path.join(args.dma_tools, "dma_to_device")
    dma_from = os.path.join(args.dma_tools, "dma_from_device")
    if not args.skip_c and not (os.path.isfile(dma_to) and os.path.isfile(dma_from)):
        print(f"!! dma_to_device/dma_from_device not in {args.dma_tools}", file=sys.stderr)
        sys.exit(1)

    print(f"runs/size = {args.runs}   cpu iters = {args.cpu_iters}")
    print(f"{'msgs':>8} {'in':>8} {'out':>8} | "
          f"{'CPU MB/s':>9} {'CPU us/h':>9} | "
          f"{'PY MB/s':>8} {'PY us/h':>9} | "
          f"{'C MB/s':>8} {'C us/h':>9} | speedup")
    print("-" * 105)

    for n in counts:
        in_b  = n * 64
        out_b = n * 32

        cpu_mbps = cpu_us = float("nan")
        if not args.skip_cpu:
            cpu_mbps, cpu_us = bench_cpu(cpu_tool, n, args.cpu_iters)

        py_mbps = py_us = float("nan")
        if not args.skip_py:
            py_mbps, py_us, _, ok = bench_fpga_py(n, args.runs, verify=args.verify_py)
            if args.verify_py and not ok:
                print(f"{'!! python path output MISMATCH at n=' + str(n)}")

        c_mbps = c_us = float("nan")
        if not args.skip_c:
            try:
                c_mbps, c_us, _ = bench_fpga_c(dma_to, dma_from, n, args.runs)
            except subprocess.CalledProcessError as e:
                print(f"  !! C tool failed at n={n}: {e}")

        speedup = (c_mbps / cpu_mbps) if (cpu_mbps and not (cpu_mbps != cpu_mbps)) else float("nan")
        print(f"{n:8d} {fmt_size(in_b):>8} {fmt_size(out_b):>8} | "
              f"{cpu_mbps:9.1f} {cpu_us:9.3f} | "
              f"{py_mbps:8.1f} {py_us:9.3f} | "
              f"{c_mbps:8.1f} {c_us:9.3f} | {speedup:6.2f}x")


if __name__ == "__main__":
    main()
