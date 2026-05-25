#!/usr/bin/env bash
# reload-fpga.sh
# One-shot "hot reload" of the LiteFury FPGA without a host cold-boot.
#
# Sequence (all unattended):
#   1. SSH to target, rmmod xdma + remove PCIe device from kernel
#   2. From build host, drive JTAG boot_hw_device -> FPGA reloads from SPI
#   3. SSH to target, PCI rescan + modprobe xdma
#   4. SSH to target, verify /dev/xdma* nodes appeared
#
# Assumptions:
#   - hw_server is running on the target (port 3121)
#   - Flash already programmed with the new MCS (run program-litefury.tcl first)
#   - Same IP layout / BAR map / PCIe ID as before
#
# If this script ever fails to bring the link back, fall back to a *warm
# reboot* on the target (`ssh root@TARGET reboot`); a full cold boot is
# only needed if the host's PCIe root port latches a bad link state.

set -euo pipefail

TARGET=${TARGET:-pdevarasetti}
TARGET_USER=${TARGET_USER:-root}
BDF=${BDF:-0000:01:00.0}
VIVADO_INIT=${VIVADO_INIT:-/opt/Xilinx/2025.2/Vivado/settings64.sh}
HERE=$(cd "$(dirname "$0")/.." && pwd)

run_target() { ssh "${TARGET_USER}@${TARGET}" "$@"; }

echo "[1/4] target: rmmod xdma + PCIe remove $BDF"
run_target "rmmod xdma 2>/dev/null || true; \
  if [ -e /sys/bus/pci/devices/${BDF}/remove ]; then \
    echo 1 > /sys/bus/pci/devices/${BDF}/remove; \
  else \
    echo '(device already absent)'; \
  fi"

echo "[2/4] build host: JTAG boot_hw_device (FPGA reloads from SPI)"
source "$VIVADO_INIT" >/dev/null
( cd "$HERE" && vivado -mode batch -nojournal -nolog -source tcl/boot-from-flash.tcl 2>&1 ) | tail -15

echo "[3/4] target: pci rescan + modprobe xdma"
# Small delay so the PCIe link finishes training before we rescan
sleep 3
run_target "echo 1 > /sys/bus/pci/rescan; \
  sleep 1; \
  modprobe xdma poll_mode=1; \
  sleep 1"

echo "[4/4] target: verify"
run_target "lspci -nn | grep -i xilinx || true; \
  ls -l /dev/xdma* 2>/dev/null || echo 'NO /dev/xdma* nodes'; \
  dmesg | tail -20"

echo "OK: hot-reload complete"
