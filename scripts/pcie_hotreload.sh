#!/bin/bash
# Hot-reload LiteFury on pdevarasetti without a cold boot.
# Run order:
#   1) From dev host: vivado -mode batch -source tcl/jtag_load.tcl   (loads .bit)
#   2) ssh root@pdevarasetti bash /tmp/pcie_hotreload.sh             (this script)
#
# Sequence:
#   - rmmod xdma  (release the device cleanly)
#   - PCI remove the endpoint
#   - Pulse Secondary Bus Reset on the upstream bridge (forces PERST# on slot)
#   - Rescan the PCI bus -> root complex re-enumerates LiteFury
#   - modprobe xdma poll_mode=1
set -euo pipefail

BDF="0000:01:00.0"
BRIDGE="0000:00:01.0"

echo "[hot-reload] unbinding xdma..."
modprobe -r xdma 2>/dev/null || true

if [ -e "/sys/bus/pci/devices/${BDF}" ]; then
    echo "[hot-reload] removing ${BDF}..."
    echo 1 > "/sys/bus/pci/devices/${BDF}/remove"
fi

# Bridge control register is at config offset 0x3E (16-bit). Bit 6 = SBR.
echo "[hot-reload] asserting SBR on bridge ${BRIDGE}..."
BCTL=$(setpci -s "${BRIDGE#0000:}" BRIDGE_CONTROL)
echo "[hot-reload]   BRIDGE_CONTROL was 0x${BCTL}"
NEW=$(printf "%04x" $((0x${BCTL} | 0x40)))
setpci -s "${BRIDGE#0000:}" BRIDGE_CONTROL=${NEW}
sleep 0.2
setpci -s "${BRIDGE#0000:}" BRIDGE_CONTROL=${BCTL}
sleep 0.5

echo "[hot-reload] rescanning PCI..."
echo 1 > /sys/bus/pci/rescan
sleep 0.3

if [ ! -e "/sys/bus/pci/devices/${BDF}" ]; then
    echo "[hot-reload] ERROR: ${BDF} did not reappear" >&2
    lspci -nn | grep -i xilinx || true
    exit 1
fi

echo "[hot-reload] ${BDF} present:"
lspci -s "${BDF#0000:}" -nn

echo "[hot-reload] loading xdma..."
modprobe xdma poll_mode=1
sleep 0.3
ls -l /dev/xdma0_* 2>&1 | head -8 || true
echo "[hot-reload] OK"
