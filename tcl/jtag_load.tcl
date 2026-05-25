# JTAG-load .bit directly into the FPGA fabric (does NOT touch SPI flash).
# Bitstream is volatile — lost on power cycle. Pair with a PCIe hot-reload on
# the host to re-enumerate without a cold boot.
open_hw_manager
connect_hw_server -url pdevarasetti:3121 -allow_non_jtag
open_hw_target [lindex [get_hw_targets] 0]

set dev [lindex [get_hw_devices xc7a*] 0]
current_hw_device $dev
refresh_hw_device -quiet $dev

set bit "/home/pavand96/NiteFury-and-LiteFury/Sample-Projects/Project-0/FPGA/LiteFury/project/project.runs/impl_1/Top_wrapper.bit"
set_property PROGRAM.FILE $bit $dev
program_hw_devices $dev
refresh_hw_device -quiet $dev

puts "JTAG LOAD DONE: $bit"
close_hw_target
disconnect_hw_server
exit
