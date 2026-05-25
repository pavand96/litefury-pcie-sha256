# Pre-hook for write_bitstream: demote benign IO DRCs (SPI_0_ss_i[0] tie-off).
set_property SEVERITY {Warning} [get_drc_checks NSTD-1]
set_property SEVERITY {Warning} [get_drc_checks UCIO-1]
