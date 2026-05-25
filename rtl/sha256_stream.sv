// sha256_stream.sv
//
// AXI4-Stream wrapper around sha256_compress.
//
//   Spec:  hash(msg_64B) = SHA-256(msg_64B)   -- standard FIPS-180-4
//
//   Per request the host streams 64 bytes of message in, and the FPGA
//   streams back the 32-byte digest. A 64-byte SHA-256 message needs two
//   internal compression rounds (block 1 = the message; block 2 = the
//   standard padding 0x80 || 0*55 || length=512).
//
//   Wire format (matching XDMA AXI-Stream, DATA_WIDTH=128b, big-endian
//   byte order so it matches `dd`/`hexdump` semantics):
//
//     Input  beat 0 [127:0] = msg bytes 0..15
//     Input  beat 1 [127:0] = msg bytes 16..31
//     Input  beat 2 [127:0] = msg bytes 32..47
//     Input  beat 3 [127:0] = msg bytes 48..63  (with tlast=1)
//
//     Output beat 0 [127:0] = digest bytes  0..15
//     Output beat 1 [127:0] = digest bytes 16..31 (with tlast=1)
//
//   Throughput (1 engine, this file):
//       2 compressions × 66 cycles ≈ 132 cycles / 64B = ~2.07 cycles/byte
//       @ 125 MHz that's ~60.5 MB/s of input.
//   Scaling: replicate the engine N× and round-robin. The dispatcher and
//   collector are FIFO-ordered so output digests come out in the same order
//   as input messages. See README for the area/throughput trade.
//
// Style: matches gearbox.sv — named generates, _q/_next signals, async-low
// reset rstn for internal sigs; AXI uses aresetn (active-low sync).

`timescale 1ns/1ps

module sha256_stream #(
    parameter integer DATA_WIDTH = 128,
    parameter integer KEEP_WIDTH = DATA_WIDTH/8
)(
    input  logic                   aclk,
    input  logic                   aresetn,

    // Slave (from XDMA M_AXIS_H2C)
    input  logic [DATA_WIDTH-1:0]  s_axis_tdata,
    input  logic [KEEP_WIDTH-1:0]  s_axis_tkeep,
    input  logic                   s_axis_tvalid,
    output logic                   s_axis_tready,
    input  logic                   s_axis_tlast,

    // Master (to XDMA S_AXIS_C2H)
    output logic [DATA_WIDTH-1:0]  m_axis_tdata,
    output logic [KEEP_WIDTH-1:0]  m_axis_tkeep,
    output logic                   m_axis_tvalid,
    input  logic                   m_axis_tready,
    output logic                   m_axis_tlast
);

  // ---------------------------------------------------------------------------
  // Constants
  // ---------------------------------------------------------------------------
  // SHA-256 initial hash values H0..H7 (FIPS 180-4 §5.3.3).
  localparam logic [255:0] SHA256_IV = {
    32'h6a09e667, 32'hbb67ae85, 32'h3c6ef372, 32'ha54ff53a,
    32'h510e527f, 32'h9b05688c, 32'h1f83d9ab, 32'h5be0cd19
  };

  // Padding block for a 64-byte (512-bit) message: 0x80 || 0*55 || length(64b BE).
  // Length in bits = 512 = 0x200, encoded in the LAST 64 bits (big-endian).
  // Bit accounting: 8 (0x80) + 55*8=440 (zeros) + 64 (length) = 512 ✓
  localparam logic [511:0] PAD_BLOCK = {
    8'h80,
    440'h0,
    64'd512
  };

  // ---------------------------------------------------------------------------
  // Local signals
  // ---------------------------------------------------------------------------
  // The internal compression core is async-reset; AXI gives us sync active-low
  // aresetn — wire them together.
  logic core_start;
  logic core_ready;
  logic core_done;
  logic [511:0] core_block;
  logic [255:0] core_cv_in;
  logic [255:0] core_cv_out;

  sha256_compress u_core (
    .clk   (aclk),
    .rstn  (aresetn),
    .start (core_start),
    .block (core_block),
    .cv_in (core_cv_in),
    .ready (core_ready),
    .done  (core_done),
    .cv_out(core_cv_out)
  );

  // ---------------------------------------------------------------------------
  // RX (input) FSM
  //
  // Collects 4 beats of 128b into a 512b message register, then dispatches
  // 2 compressions back-to-back (msg block, padding block).
  // ---------------------------------------------------------------------------
  typedef enum logic [2:0] {
    RX_COLLECT,   // accept 4 beats into msg_q
    RX_RUN_MSG,   // start core on msg block, wait done
    RX_RUN_PAD,   // start core on pad block, wait done
    RX_EMIT_WAIT  // wait for TX FSM to consume the digest
  } rx_state_e;

  rx_state_e rx_state_q;

  logic [511:0] msg_q;
  logic [1:0]   beat_idx_q;     // 0..3
  logic [255:0] digest_q;       // result, handed off to TX
  logic         digest_valid_q; // set when digest_q is ready; cleared by TX

  // Stage which compression to dispatch when core is ready.
  logic         start_pulse;
  logic [511:0] start_block;
  logic [255:0] start_cv;

  // Forward declaration: pulsed by the TX FSM, observed by RX.
  logic         tx_consume_digest;

  assign core_start = start_pulse;
  assign core_block = start_block;
  assign core_cv_in = start_cv;

  // Ready upstream only when we are actively collecting beats.
  assign s_axis_tready = (rx_state_q == RX_COLLECT) && !digest_valid_q;

  always_ff @(posedge aclk) begin
    if (!aresetn) begin
      rx_state_q     <= RX_COLLECT;
      msg_q          <= '0;
      beat_idx_q     <= 2'd0;
      digest_q       <= '0;
      digest_valid_q <= 1'b0;
      start_pulse    <= 1'b0;
      start_block    <= '0;
      start_cv       <= '0;
    end
    else begin
      start_pulse <= 1'b0;  // default: 1-cycle pulse

      // Hand-off: TX clears digest_valid_q indirectly via the wire below.
      if (tx_consume_digest) begin
        digest_valid_q <= 1'b0;
      end

      unique case (rx_state_q)
        // -------------------------------------------------------------------
        RX_COLLECT: begin
          if (s_axis_tvalid && s_axis_tready) begin
            // Shift the new 128b into the right slot (big-endian: beat 0 in
            // bits [511:384]).
            case (beat_idx_q)
              2'd0: msg_q[511:384] <= s_axis_tdata;
              2'd1: msg_q[383:256] <= s_axis_tdata;
              2'd2: msg_q[255:128] <= s_axis_tdata;
              2'd3: msg_q[127:  0] <= s_axis_tdata;
            endcase
            if (beat_idx_q == 2'd3) begin
              beat_idx_q <= 2'd0;
              // Dispatch the message-block compression.
              start_pulse <= 1'b1;
              start_block <= { msg_q[511:384], msg_q[383:256],
                               msg_q[255:128], s_axis_tdata };
              start_cv    <= SHA256_IV;
              rx_state_q  <= RX_RUN_MSG;
            end
            else begin
              beat_idx_q <= beat_idx_q + 2'd1;
            end
          end
        end

        // -------------------------------------------------------------------
        RX_RUN_MSG: begin
          if (core_done) begin
            // Latch intermediate CV; dispatch padding block.
            start_pulse <= 1'b1;
            start_block <= PAD_BLOCK;
            start_cv    <= core_cv_out;
            rx_state_q  <= RX_RUN_PAD;
          end
        end

        // -------------------------------------------------------------------
        RX_RUN_PAD: begin
          if (core_done) begin
            digest_q       <= core_cv_out;
            digest_valid_q <= 1'b1;
            rx_state_q     <= RX_EMIT_WAIT;
          end
        end

        // -------------------------------------------------------------------
        RX_EMIT_WAIT: begin
          // TX FSM clears digest_valid_q when it has consumed both beats.
          if (!digest_valid_q) begin
            rx_state_q <= RX_COLLECT;
          end
        end

        default: rx_state_q <= RX_COLLECT;
      endcase
    end
  end

  // ---------------------------------------------------------------------------
  // TX (output) FSM
  //
  // Emits the 32-byte digest as two 128b beats. Tells the RX FSM when it is
  // done so the next message can be accepted.
  // ---------------------------------------------------------------------------
  typedef enum logic [1:0] {
    TX_IDLE,
    TX_BEAT0,
    TX_BEAT1,
    TX_DONE
  } tx_state_e;

  tx_state_e tx_state_q;

  assign m_axis_tkeep = {KEEP_WIDTH{1'b1}};

  always_comb begin
    m_axis_tdata  = '0;
    m_axis_tvalid = 1'b0;
    m_axis_tlast  = 1'b0;
    case (tx_state_q)
      TX_BEAT0: begin
        m_axis_tdata  = digest_q[255:128];
        m_axis_tvalid = 1'b1;
        m_axis_tlast  = 1'b0;
      end
      TX_BEAT1: begin
        m_axis_tdata  = digest_q[127:  0];
        m_axis_tvalid = 1'b1;
        m_axis_tlast  = 1'b1;
      end
      default: ;
    endcase
  end

  always_ff @(posedge aclk) begin
    if (!aresetn) begin
      tx_state_q        <= TX_IDLE;
      tx_consume_digest <= 1'b0;
    end
    else begin
      tx_consume_digest <= 1'b0;

      unique case (tx_state_q)
        TX_IDLE: begin
          if (digest_valid_q) tx_state_q <= TX_BEAT0;
        end
        TX_BEAT0: begin
          if (m_axis_tready) tx_state_q <= TX_BEAT1;
        end
        TX_BEAT1: begin
          if (m_axis_tready) begin
            tx_state_q        <= TX_DONE;
            tx_consume_digest <= 1'b1;
          end
        end
        TX_DONE: begin
          // 1-cycle gap to let RX observe digest_valid_q go low.
          tx_state_q <= TX_IDLE;
        end
        default: tx_state_q <= TX_IDLE;
      endcase
    end
  end

endmodule
