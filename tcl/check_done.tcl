open_hw_manager
connect_hw_server -url pdevarasetti:3121 -allow_non_jtag
open_hw_target
puts "TARGET: [current_hw_target]"
puts "DEVICE: [get_hw_devices]"
foreach d [get_hw_devices] {
    current_hw_device $d
    refresh_hw_device $d
    puts "  $d  done=[get_property REGISTER.IR.BIT05_DONE $d]  status=[get_property STATUS.DONE_PIN $d]"
}
close_hw_target
disconnect_hw_server
exit
