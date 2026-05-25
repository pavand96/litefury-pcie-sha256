// sha256_stream.sv
//
// AXI4-Stream wrapper around the 2-way pipelined SHA-256 compress engine.
// Hashes back-to-back 64-byte messages from the AXI-Stream slave port and
// emits 32-byte digests on the AXI-Stream master port.
//
// One job = one 64-byte message  = 4 input beats   (128b)  on s_axis.
// One result = one 32-byte digest = 2 output beats (128b) on m_axis,
//              with tlast asserted on beat 1.
//
// Style: gearbox.  Only `assign` (combinational) and `always_ff` (one block
// per register or tightly related register group).  No FSMs, no always_comb.
//
// Two "slots" in flight at all times (matched to the engine's 2 lanes):
//   slot.busy            : occupied
//   slot.first_done      : first block compressed; intermediate CV captured
//   slot.second_issued   : second block (pad) accepted by the engine
//   slot.digest_ready    : final digest captured, awaiting emit
//
`timescale 1ns/1ps

module sha256_stream
(
  input  logic         aclk,
  input  logic         aresetn,

  // Slave AXI-Stream (message in) -------------------------------------------
  input  logic         s_axis_tvalid,
  output logic         s_axis_tready,
  input  logic [127:0] s_axis_tdata,
  input  logic [ 15:0] s_axis_tkeep,
  input  logic         s_axis_tlast,

  // Master AXI-Stream (digest out) ------------------------------------------
  output logic         m_axis_tvalid,
  input  logic         m_axis_tready,
  output logic [127:0] m_axis_tdata,
  output logic [ 15:0] m_axis_tkeep,
  output logic         m_axis_tlast
);

  // ===========================================================================
  // CONSTANTS  (FIPS 180-4)
  // ===========================================================================
  // Initial hash value H(0)
  localparam logic [255:0] SHA256_IV = {
    32'h6a09e667, 32'hbb67ae85, 32'h3c6ef372, 32'ha54ff53a,
    32'h510e527f, 32'h9b05688c, 32'h1f83d9ab, 32'h5be0cd19
  };
  // Padding block for a 64-byte (= 512-bit) message:
  //   0x80, 55 zero bytes, then 64-bit big-endian length = 512.
  localparam logic [511:0] PAD_BLOCK_64B = { 8'h80, 440'h0, 64'd512 };

  // ===========================================================================
  // RX  —  collect 4 input beats into one 512-bit message register
  // ===========================================================================
  logic [511:0] rx_msg_q;
  logic [1:0]   rx_beat_cnt_q;   // 0..3, next beat index to fill
  logic         rx_msg_full_q;   // set when 4 beats are in; cleared on issue

  // Handshake
  logic rx_beat_tfer_w;
  logic rx_msg_consume_w;        // wired below from dispatch_first_w

  assign s_axis_tready  = ~rx_msg_full_q;
  assign rx_beat_tfer_w =  s_axis_tvalid & s_axis_tready;

  // ---- rx_beat_cnt_q -------------------------------------------------------
  logic [1:0] rx_beat_cnt_next;
  assign rx_beat_cnt_next =
      rx_beat_tfer_w
    ? ( (rx_beat_cnt_q == 2'd3) ? 2'd0 : (rx_beat_cnt_q + 2'd1) )
    : rx_beat_cnt_q;

  always_ff @(posedge aclk or negedge aresetn) begin
    if (~aresetn) rx_beat_cnt_q <= 2'd0;
    else          rx_beat_cnt_q <= rx_beat_cnt_next;
  end

  // ---- rx_msg_full_q -------------------------------------------------------
  logic rx_msg_full_set_w;
  logic rx_msg_full_next;

  assign rx_msg_full_set_w = rx_beat_tfer_w & (rx_beat_cnt_q == 2'd3);
  assign rx_msg_full_next  =
      rx_msg_full_set_w
    ? 1'b1
    : ( rx_msg_consume_w
      ? 1'b0
      : rx_msg_full_q );

  always_ff @(posedge aclk or negedge aresetn) begin
    if (~aresetn) rx_msg_full_q <= 1'b0;
    else          rx_msg_full_q <= rx_msg_full_next;
  end

  // ---- rx_msg_q   (per-quarter write, gated by beat counter) ---------------
  always_ff @(posedge aclk) begin
    if (rx_beat_tfer_w) begin
      case (rx_beat_cnt_q)
        2'd0: rx_msg_q[511:384] <= s_axis_tdata;
        2'd1: rx_msg_q[383:256] <= s_axis_tdata;
        2'd2: rx_msg_q[255:128] <= s_axis_tdata;
        2'd3: rx_msg_q[127:  0] <= s_axis_tdata;
      endcase
    end
  end

  // ===========================================================================
  // SLOT STATE  (2 slots, one per compress engine lane)
  // ===========================================================================
  logic         slot_busy_q          [0:1];
  logic         slot_first_done_q    [0:1];
  logic         slot_second_issued_q [0:1];
  logic         slot_digest_ready_q  [0:1];
  logic [255:0] slot_cv_q            [0:1];   // intermediate CV
  logic [255:0] slot_digest_q        [0:1];   // final digest

  // ===========================================================================
  // ISSUE / DISPATCH SELECTION  (pure combinational)
  // ===========================================================================
  // Pick empty slot for new message admission (prefer slot 0).
  logic empty_slot_w;
  logic have_empty_slot_w;
  assign empty_slot_w      = slot_busy_q[0] ? 1'b1 : 1'b0;
  assign have_empty_slot_w = ~slot_busy_q[0] | ~slot_busy_q[1];

  // Pick slot ready for second-block dispatch (prefer slot 0).
  logic slot0_second_ready_w;
  logic slot1_second_ready_w;
  logic second_slot_w;
  logic have_second_w;

  assign slot0_second_ready_w =
      slot_busy_q          [0]
    &  slot_first_done_q    [0]
    & ~slot_second_issued_q [0]
    & ~slot_digest_ready_q  [0];

  assign slot1_second_ready_w =
      slot_busy_q          [1]
    &  slot_first_done_q    [1]
    & ~slot_second_issued_q [1]
    & ~slot_digest_ready_q  [1];

  assign second_slot_w = slot0_second_ready_w ? 1'b0 : 1'b1;
  assign have_second_w = slot0_second_ready_w |  slot1_second_ready_w;

  // ===========================================================================
  // COMPRESS ENGINE INSTANTIATION
  // ===========================================================================
  logic         eng_job_valid;
  logic         eng_job_ready;
  logic [511:0] eng_job_block;
  logic [255:0] eng_job_cv_in;
  logic         eng_job_tag;
  logic         eng_res_valid;
  logic         eng_res_ready;
  logic [255:0] eng_res_cv_out;
  logic         eng_res_tag;

  sha256_compress u_compress (
    .clk        (aclk),
    .rstn       (aresetn),
    .job_valid  (eng_job_valid),
    .job_ready  (eng_job_ready),
    .job_block  (eng_job_block),
    .job_cv_in  (eng_job_cv_in),
    .job_tag    (eng_job_tag),
    .res_valid  (eng_res_valid),
    .res_ready  (eng_res_ready),
    .res_cv_out (eng_res_cv_out),
    .res_tag    (eng_res_tag)
  );

  // Second-block dispatch wins over first-block dispatch.
  logic dispatch_second_w;
  logic dispatch_first_w;

  assign dispatch_second_w =
      have_second_w
    & eng_job_ready;

  assign dispatch_first_w =
      have_empty_slot_w
    & rx_msg_full_q
    & eng_job_ready
    & ~dispatch_second_w;

  // Engine port drivers
  assign eng_job_valid = dispatch_second_w | dispatch_first_w;
  assign eng_job_block = dispatch_second_w ? PAD_BLOCK_64B            : rx_msg_q;
  assign eng_job_cv_in = dispatch_second_w ? slot_cv_q[second_slot_w] : SHA256_IV;
  assign eng_job_tag   = dispatch_second_w ? second_slot_w            : empty_slot_w;

  // Always ready to take results (we only ever have 2 jobs in flight).
  assign eng_res_ready = 1'b1;

  // Wire back into rx-buffer free event.
  assign rx_msg_consume_w = dispatch_first_w;

  // ===========================================================================
  // RESULT CAPTURE
  // ===========================================================================
  logic         res_tfer_w;
  logic         res_first_w;   // result is the FIRST CV for tagged slot
  logic         res_final_w;   // result is the FINAL digest for tagged slot

  assign res_tfer_w  = eng_res_valid & eng_res_ready;
  assign res_first_w = res_tfer_w & ~slot_first_done_q[eng_res_tag];
  assign res_final_w = res_tfer_w &  slot_first_done_q[eng_res_tag];

  // ===========================================================================
  // TX  —  emit captured digest as 2 beats on master
  // ===========================================================================
  logic tx_slot_w;
  logic have_tx_w;
  assign tx_slot_w = slot_digest_ready_q[0] ? 1'b0 : 1'b1;
  assign have_tx_w = slot_digest_ready_q[0] | slot_digest_ready_q[1];

  logic tx_active_q;
  logic tx_active_slot_q;
  logic tx_beat_cnt_q;       // 0 = high half, 1 = low half + tlast

  // Combinational handshake events
  logic tx_start_w;          // begin emitting a new digest
  logic tx_beat_tfer_w;      // master accepts current beat
  logic tx_last_beat_w;      // beat 1 accepted (digest finished)

  assign tx_start_w     = ~tx_active_q &  have_tx_w;
  assign tx_beat_tfer_w =  tx_active_q &  m_axis_tready;
  assign tx_last_beat_w =  tx_beat_tfer_w & tx_beat_cnt_q;

  // Master port drivers
  assign m_axis_tvalid =  tx_active_q;
  assign m_axis_tkeep  = {16{tx_active_q}};
  assign m_axis_tlast  =  tx_active_q & tx_beat_cnt_q;
  assign m_axis_tdata  =
      ~tx_active_q
    ? 128'h0
    : ( tx_beat_cnt_q
      ? slot_digest_q[tx_active_slot_q][127:  0]
      : slot_digest_q[tx_active_slot_q][255:128] );

  // ---- tx_active_q ---------------------------------------------------------
  logic tx_active_next;
  assign tx_active_next =
      tx_start_w
    ? 1'b1
    : ( tx_last_beat_w
      ? 1'b0
      : tx_active_q );

  always_ff @(posedge aclk or negedge aresetn) begin
    if (~aresetn) tx_active_q <= 1'b0;
    else          tx_active_q <= tx_active_next;
  end

  // ---- tx_active_slot_q  (latched on start) -------------------------------
  always_ff @(posedge aclk) begin
    if (tx_start_w) tx_active_slot_q <= tx_slot_w;
  end

  // ---- tx_beat_cnt_q -------------------------------------------------------
  logic tx_beat_cnt_next;
  assign tx_beat_cnt_next =
      tx_start_w
    ? 1'b0
    : ( tx_last_beat_w
      ? 1'b0
      : ( tx_beat_tfer_w
        ? 1'b1
        : tx_beat_cnt_q ) );

  always_ff @(posedge aclk or negedge aresetn) begin
    if (~aresetn) tx_beat_cnt_q <= 1'b0;
    else          tx_beat_cnt_q <= tx_beat_cnt_next;
  end

  // ===========================================================================
  // PER-SLOT STATE UPDATES  (replicated via generate)
  // ===========================================================================
  for (genvar S = 0; S < 2; S = S + 1) begin : g_slot

    // Per-slot control events
    logic slot_load_w;     // accept new message into this slot
    logic slot_second_w;   // dispatch second block for this slot
    logic slot_capture_first_w;
    logic slot_capture_final_w;
    logic slot_emit_done_w; // TX finished this slot's digest

    assign slot_load_w          = dispatch_first_w  & (empty_slot_w  == 1'(S));
    assign slot_second_w        = dispatch_second_w & (second_slot_w == 1'(S));
    assign slot_capture_first_w = res_first_w       & (eng_res_tag   == 1'(S));
    assign slot_capture_final_w = res_final_w       & (eng_res_tag   == 1'(S));
    assign slot_emit_done_w     = tx_last_beat_w    & (tx_active_slot_q == 1'(S));

    // ---- busy --------------------------------------------------------------
    logic slot_busy_next;
    assign slot_busy_next =
        slot_load_w
      ? 1'b1
      : ( slot_emit_done_w
        ? 1'b0
        : slot_busy_q[S] );

    always_ff @(posedge aclk or negedge aresetn) begin
      if (~aresetn) slot_busy_q[S] <= 1'b0;
      else          slot_busy_q[S] <= slot_busy_next;
    end

    // ---- first_done --------------------------------------------------------
    logic slot_first_done_next;
    assign slot_first_done_next =
        slot_capture_first_w
      ? 1'b1
      : ( slot_emit_done_w
        ? 1'b0
        : ( slot_load_w
          ? 1'b0
          : slot_first_done_q[S] ) );

    always_ff @(posedge aclk or negedge aresetn) begin
      if (~aresetn) slot_first_done_q[S] <= 1'b0;
      else          slot_first_done_q[S] <= slot_first_done_next;
    end

    // ---- second_issued -----------------------------------------------------
    logic slot_second_issued_next;
    assign slot_second_issued_next =
        slot_second_w
      ? 1'b1
      : ( slot_emit_done_w
        ? 1'b0
        : ( slot_load_w
          ? 1'b0
          : slot_second_issued_q[S] ) );

    always_ff @(posedge aclk or negedge aresetn) begin
      if (~aresetn) slot_second_issued_q[S] <= 1'b0;
      else          slot_second_issued_q[S] <= slot_second_issued_next;
    end

    // ---- digest_ready ------------------------------------------------------
    logic slot_digest_ready_next;
    assign slot_digest_ready_next =
        slot_capture_final_w
      ? 1'b1
      : ( slot_emit_done_w
        ? 1'b0
        : ( slot_load_w
          ? 1'b0
          : slot_digest_ready_q[S] ) );

    always_ff @(posedge aclk or negedge aresetn) begin
      if (~aresetn) slot_digest_ready_q[S] <= 1'b0;
      else          slot_digest_ready_q[S] <= slot_digest_ready_next;
    end

    // ---- intermediate CV  --------------------------------------------------
    always_ff @(posedge aclk) begin
      if (slot_capture_first_w) slot_cv_q[S] <= eng_res_cv_out;
    end

    // ---- final digest  -----------------------------------------------------
    always_ff @(posedge aclk) begin
      if (slot_capture_final_w) slot_digest_q[S] <= eng_res_cv_out;
    end

  end : g_slot

endmodule
