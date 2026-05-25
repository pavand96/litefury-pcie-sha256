# build_stream_sha256.tcl
#
# Adapts the existing add1_stream Vivado project to use sha256_stream instead.
# Re-uses the entire PCIe + XDMA + clock infrastructure already validated in
# the litefury-pcie-addone project.
#
# Steps:
#   1. Add SHA-256 RTL sources to the project.
#   2. In the BD, delete add1_stream_0 (if present), insert sha256_stream_0.
#   3. Re-route M_AXIS_H2C_0 → sha256_stream_0/s_axis → S_AXIS_C2H_0.
#   4. Re-validate, rewrap, re-synth, re-impl, re-bitstream, re-MCS.
#
# Run with:  vivado -mode batch -source build_stream_sha256.tcl

set proj      /home/pavand96/NiteFury-and-LiteFury/Sample-Projects/Project-0/FPGA/LiteFury/project
set bd        $proj/project.srcs/sources_1/bd/Top/Top.bd

set rtl_dir   /home/pavand96/litefury-pcie-sha256/rtl
set rtl_files [list \
    $rtl_dir/sha256_pkg.sv        \
    $rtl_dir/sha256_compress.sv   \
    $rtl_dir/sha256_stream.sv     \
    $rtl_dir/sha256_stream_top.v  \
]

open_project $proj/project.xpr

# Force AUTOMATIC compile order (module references need it).
set_property source_mgmt_mode All [current_project]

# Add SHA-256 sources (idempotent). Mark .sv files as SystemVerilog so Vivado
# parses them with the SV-2012 parser; .v files keep the default Verilog type.
foreach f $rtl_files {
    set bn [file tail $f]
    if {[llength [get_files -quiet $bn]] == 0} {
        puts "Adding source: $f"
        add_files -norecurse $f
        if {[string equal -nocase [file extension $f] ".sv"]} {
            set_property file_type SystemVerilog [get_files $bn]
        }
    }
}
update_compile_order -fileset sources_1

open_bd_design $bd
current_bd_design [get_bd_designs Top]

puts "--- Remove old add1_stream cell if present ---"
foreach cell {add1_stream_0} {
    set bc [get_bd_cells -quiet $cell]
    if {$bc ne ""} {
        puts "  deleting $bc"
        delete_bd_objs $bc
    }
}

puts "--- Insert sha256_stream_0 module reference (Verilog top wrapper) ---"
update_compile_order -fileset sources_1
if {[llength [get_bd_cells -quiet sha256_stream_0]] == 0} {
    create_bd_cell -type module -reference sha256_stream_top sha256_stream_0
} else {
    # Module-reference BD cells are packaged as out-of-context IPs.  Their
    # synth run does NOT re-trigger when underlying RTL changes (we just see
    # the cached .dcp).  Best-effort refresh here; the explicit `reset_run`
    # on Top_sha256_stream_0_0_synth_1 below is the real guarantor.
    puts "  refreshing module reference (RTL may have changed)"
    if {[catch {update_module_reference sha256_stream_top} msg]} {
        puts "  (update_module_reference skipped: $msg)"
    }
}

puts "--- Connect streams + clk/rst (idempotent) ---"
# Helper: connect an interface pin only if not already connected.
proc safe_connect_intf {a b} {
    set ap [get_bd_intf_pins $a]
    set bp [get_bd_intf_pins $b]
    set an [get_bd_intf_nets -of_objects $ap -quiet]
    set bn [get_bd_intf_nets -of_objects $bp -quiet]
    if {$an ne "" && $bn ne "" && $an eq $bn} {
        puts "  intf $a <-> $b already connected via $an"
        return
    }
    connect_bd_intf_net $ap $bp
}
proc safe_connect_net {a b} {
    set ap [get_bd_pins $a]
    set bp [get_bd_pins $b]
    set an [get_bd_nets -of_objects $ap -quiet]
    set bn [get_bd_nets -of_objects $bp -quiet]
    if {$an ne "" && $bn ne "" && $an eq $bn} {
        puts "  net $a <-> $b already connected via $an"
        return
    }
    connect_bd_net $ap $bp
}
safe_connect_intf xdma_0/M_AXIS_H2C_0       sha256_stream_0/s_axis
safe_connect_intf sha256_stream_0/m_axis    xdma_0/S_AXIS_C2H_0
safe_connect_net  xdma_0/axi_aclk           sha256_stream_0/aclk
safe_connect_net  xdma_0/axi_aresetn        sha256_stream_0/aresetn

puts "--- Validate + save BD ---"
regenerate_bd_layout
validate_bd_design
save_bd_design
close_bd_design [current_bd_design]

puts "--- Regenerate wrapper ---"
make_wrapper -files [get_files $bd] -top -force -import
set_property top_auto_set false [current_fileset]
set_property top Top_wrapper    [current_fileset]
update_compile_order -fileset sources_1

# Demote unconnected-IO DRCs that we know are harmless on this BD.
# These must be set both here (for any DRC the parent runs) AND as a
# pre-hook for write_bitstream because launch_runs spawns a subprocess
# that does NOT inherit these property changes.
set_property SEVERITY {Warning} [get_drc_checks NSTD-1]
set_property SEVERITY {Warning} [get_drc_checks UCIO-1]
set_property STEPS.WRITE_BITSTREAM.TCL.PRE \
    [file normalize tcl/drc_demote.tcl] [get_runs impl_1]

puts "--- Run synth + impl + bitstream ---"
# Always start fresh on the OOC IP run so RTL changes are picked up.
foreach r [get_runs -quiet -filter {NAME =~ "Top_sha256_stream_0_0_*"}] {
    puts "  reset_run $r"
    reset_run $r
}
reset_run synth_1
launch_runs synth_1 -jobs 16
wait_on_run  synth_1
launch_runs impl_1 -jobs 16 -to_step write_bitstream
wait_on_run  impl_1
puts "Implementation done!"

puts "--- Resource usage report ---"
open_run impl_1
report_utilization -file $proj/sha256_util.rpt
puts "Wrote utilization report to $proj/sha256_util.rpt"

puts "--- Generate MCS ---"
set bitfile $proj/project.runs/impl_1/Top_wrapper.bit
set mcs     /home/pavand96/NiteFury-and-LiteFury/Sample-Projects/Project-0/FPGA/LiteFury/mcs/sha256.mcs
set bin     /home/pavand96/NiteFury-and-LiteFury/Sample-Projects/Project-0/FPGA/LiteFury/mcs/sha256.bin
write_cfgmem -format mcs -size 16 -interface SPIx4 -force -loadbit "up 0 $bitfile" -file $mcs
write_cfgmem -format bin -size 16 -interface SPIx4 -force -loadbit "up 0 $bitfile" -file $bin
puts "BUILD COMPLETE  ->  bit: $bitfile   mcs: $mcs"
exit
