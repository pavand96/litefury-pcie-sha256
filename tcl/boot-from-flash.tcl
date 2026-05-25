# boot-from-flash.tcl
# Triggers the FPGA to reload its bitstream from the SPI flash by issuing
# JTAG boot (asserts PROG_B and re-reads the flash). This is the cheap
# alternative to a host cold-boot when re-flashing the same IP layout.
#
# Pre-req: hw_server is running on the target board, reachable over Tailscale.
#          The target host has done `echo 1 > /sys/bus/pci/devices/<BDF>/remove`
#          first, so Linux is not holding the PCIe BARs.

set HW_URL  "pdevarasetti:3121"
set TARGET  "*xc7a*"

open_hw_manager
connect_hw_server -url $HW_URL -allow_non_jtag
current_hw_target [lindex [get_hw_targets] 0]
open_hw_target

set dev [lindex [get_hw_devices $TARGET] 0]
puts "Booting device $dev from SPI flash..."
current_hw_device $dev

# boot_hw_device asserts PROG_B then releases — the FPGA fetches its
# new bitstream from the attached SPI flash and re-trains the PCIe link.
boot_hw_device $dev

close_hw_target
disconnect_hw_server
puts "BOOT-FROM-FLASH DONE"
exit
