# sim/Makefile
SIM ?= verilator
TOPLEVEL_LANG ?= verilog

VERILOG_SOURCES  = $(PWD)/../rtl/sha256_pkg.sv
VERILOG_SOURCES += $(PWD)/../rtl/sha256_compress.sv
VERILOG_SOURCES += $(PWD)/../rtl/sha256_stream.sv

ifeq ($(SIM),verilator)
    COMPILE_ARGS += --timing
    COMPILE_ARGS += --assert
    COMPILE_ARGS += -Wno-WIDTHEXPAND -Wno-WIDTHTRUNC -Wno-UNOPTFLAT
    EXTRA_ARGS   += --trace --trace-structs
endif

TOPLEVEL = sha256_stream
COCOTB_TEST_MODULES = test_sha256_stream

include $(shell cocotb-config --makefiles)/Makefile.sim

.PHONY: clean
clean::
	@$(RM) -rf __pycache__ sim_build dump.vcd results.xml
