# FPGA Reload Procedure

When you re-flash the LiteFury SPI with `tcl/program-litefury.tcl`, the new
bitstream is in flash but the FPGA is still running the *old* one and the
PCIe link to the host is still up against the old XDMA core. You must
re-load the FPGA from flash *and* convince the host kernel to re-enumerate.

## Escalation ladder (try cheapest first)

| Tier | Action | Time | When it works |
|---|---|---|---|
| 1 | `tools/reload-fpga.sh` — JTAG `boot_hw_device` + `pci remove` + `pci rescan` | ~30 s | Same IP layout; host root port is healthy; PCIe IP re-trains on its own |
| 2 | Warm reboot: `ssh root@pdevarasetti reboot` | ~60 s | Always — clears wedged root-port state and toggles `PERST#` |
| 3 | Cold boot (power off, wait, power on) | minutes | Last resort if firmware on the host gets into a weird state |

## Why tier 1 sometimes fails (and how to make it more reliable)

The XDMA PCIe hard-IP on Artix-7 watches the slot's `PERST#` line for its
master reset. A JTAG `boot_hw_device` re-loads the FPGA fabric but does
*not* physically toggle `PERST#`, so the PCIe IP's LTSSM may not fully
re-initialize. Symptoms:

- `lspci -t` shows the bus exists but `-[01]--` (no endpoint)
- Link trains physically (LinkSta DL Active set) but no config-space access
- Kernel reports "not ready N ms after bus reset; giving up" followed by
  `AER: Root Port link has been reset (-25)` — at that point the root
  port is wedged and only a warm reboot will recover it.

**Mitigation in RTL (future work):** wire a soft-PERST into the XDMA core
that fires for ~10 ms after `boot_hw_device` (use an SRL-based one-shot
clocked off the 100 MHz refclk; trigger on `prog_b` rising edge inferred
from a never-1 register that *is* reset by the dedicated GSR signal which
JTAG reconfig releases). Then JTAG reload behaves exactly like a slot
reset and tier 1 becomes 100% reliable.

## After any tier

```bash
ssh root@pdevarasetti '
  modprobe -r xdma 2>/dev/null
  modprobe xdma poll_mode=1
  ls /dev/xdma*
'
```

If `/dev/xdma*` appears, run the smoke test (`host/test_sha256.py 256`).
