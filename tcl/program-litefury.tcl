# Program LiteFury SPI flash over remote hw_server
open_hw_manager
connect_hw_server -url pdevarasetti:3121 -allow_non_jtag
puts "Targets:"
foreach t [get_hw_targets] { puts "  $t" }
open_hw_target [lindex [get_hw_targets] 0]

set dev [lindex [get_hw_devices xc7a*] 0]
puts "Device: $dev"
current_hw_device $dev
refresh_hw_device $dev

# Attach SPI flash (LiteFury: Spansion S25FL256S, x1/x2/x4)
create_hw_cfgmem -hw_device $dev [lindex [get_cfgmem_parts {s25fl256sxxxxxx0-spi-x1_x2_x4}] 0]
set cfg [get_property PROGRAM.HW_CFGMEM $dev]

set_property PROGRAM.ADDRESS_RANGE          {use_file}      $cfg
set_property PROGRAM.FILES                  [list "/home/pavand96/NiteFury-and-LiteFury/Sample-Projects/Project-0/FPGA/LiteFury/mcs/sha256.mcs"] $cfg
set_property PROGRAM.PRM_FILE               {}              $cfg
set_property PROGRAM.UNUSED_PIN_TERMINATION {pull-none}     $cfg
set_property PROGRAM.BLANK_CHECK            0               $cfg
set_property PROGRAM.ERASE                  1               $cfg
set_property PROGRAM.CFG_PROGRAM            1               $cfg
set_property PROGRAM.VERIFY                 1               $cfg
set_property PROGRAM.CHECKSUM               0               $cfg

# Load helper bitstream into FPGA if needed, then program flash
if {![string equal \
        [get_property PROGRAM.HW_CFGMEM_TYPE $dev] \
        [get_property MEM_TYPE [get_property CFGMEM_PART $cfg]]]} {
    create_hw_bitstream -hw_device $dev [get_property PROGRAM.HW_CFGMEM_BITFILE $dev]
    program_hw_devices $dev
}
program_hw_cfgmem -hw_cfgmem $cfg

puts "PROGRAM DONE"
close_hw_target
disconnect_hw_server
exit
