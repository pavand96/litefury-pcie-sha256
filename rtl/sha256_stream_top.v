// sha256_stream_top.v
//
// Plain Verilog top-level wrapper around `sha256_stream` (SystemVerilog).
// Vivado IPI module-references require the TOP file to be Verilog, not
// SystemVerilog, even when the underlying implementation is SV.
// Functionally this is a 1:1 instantiation — see sha256_stream.sv for the
// actual logic.

`timescale 1ns/1ps

module sha256_stream_top #(
    parameter integer DATA_WIDTH = 128,
    parameter integer KEEP_WIDTH = DATA_WIDTH/8
)(
    input  wire                    aclk,
    input  wire                    aresetn,

    input  wire [DATA_WIDTH-1:0]   s_axis_tdata,
    input  wire [KEEP_WIDTH-1:0]   s_axis_tkeep,
    input  wire                    s_axis_tvalid,
    output wire                    s_axis_tready,
    input  wire                    s_axis_tlast,

    output wire [DATA_WIDTH-1:0]   m_axis_tdata,
    output wire [KEEP_WIDTH-1:0]   m_axis_tkeep,
    output wire                    m_axis_tvalid,
    input  wire                    m_axis_tready,
    output wire                    m_axis_tlast
);

    // Underlying sha256_stream hardcodes 128b data / 16b keep to match
    // XDMA AXI-Stream.  The DATA_WIDTH parameter on this wrapper exists
    // only to keep the BD module-reference signature stable.
    sha256_stream u_sha256_stream (
        .aclk         (aclk),
        .aresetn      (aresetn),
        .s_axis_tdata (s_axis_tdata),
        .s_axis_tkeep (s_axis_tkeep),
        .s_axis_tvalid(s_axis_tvalid),
        .s_axis_tready(s_axis_tready),
        .s_axis_tlast (s_axis_tlast),
        .m_axis_tdata (m_axis_tdata),
        .m_axis_tkeep (m_axis_tkeep),
        .m_axis_tvalid(m_axis_tvalid),
        .m_axis_tready(m_axis_tready),
        .m_axis_tlast (m_axis_tlast)
    );

endmodule
