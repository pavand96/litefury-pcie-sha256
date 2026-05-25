// sha256_stream.sv
//
// AXI4-Stream wrapper around the 2-way SHA-256 compress engine.
//   In:  64-byte messages, BEATS_PER_BLOCK beats per message on s_axis.
//   Out: 32-byte digests,  BEATS_PER_HASH  beats per digest  on m_axis.
//   TLAST passes through end-of-burst (XDMA C2H descriptor boundary).

`timescale 1ns/1ps

import sha256_pkg::*;

module sha256_stream
(
  input  logic                     aclk,
  input  logic                     aresetn,

  input  logic                     s_axis_tvalid,
  output logic                     s_axis_tready,
  input  logic [AXIS_DATA_W-1:0]   s_axis_tdata,
  input  logic [AXIS_KEEP_W-1:0]   s_axis_tkeep,
  input  logic                     s_axis_tlast,

  output logic                     m_axis_tvalid,
  input  logic                     m_axis_tready,
  output logic [AXIS_DATA_W-1:0]   m_axis_tdata,
  output logic [AXIS_KEEP_W-1:0]   m_axis_tkeep,
  output logic                     m_axis_tlast
);

  //---------------------------------------------------------------------------
  // REGISTERS  (every `_q` in this module)
  //---------------------------------------------------------------------------
  // RX message collector
  logic [BLOCK_W-1:0]          rx_msg_q;
  logic [BEAT_IDX_BLOCK_W-1:0] rx_beat_cnt_q;
  logic                        rx_msg_full_q;
  logic                        rx_msg_is_last_q;

  // Per-engine-lane slot bookkeeping
  logic              slot_busy_q          [0:NUM_LANES-1];
  logic              slot_first_done_q    [0:NUM_LANES-1];
  logic              slot_second_issued_q [0:NUM_LANES-1];
  logic              slot_digest_ready_q  [0:NUM_LANES-1];
  logic              slot_is_last_q       [0:NUM_LANES-1];
  logic [HASH_W-1:0] slot_cv_q            [0:NUM_LANES-1];
  logic [HASH_W-1:0] slot_digest_q        [0:NUM_LANES-1];

  // TX emitter
  logic                       tx_active_q;
  logic                       tx_active_slot_q;
  logic [BEAT_IDX_HASH_W-1:0] tx_beat_cnt_q;

  //---------------------------------------------------------------------------
  // WIRES  (every `_w` and `_next` in this module)
  //---------------------------------------------------------------------------
  // RX
  logic                        rx_beat_tfer_w;
  logic                        rx_beat_last_in_msg_w;
  logic                        rx_msg_consume_w;
  logic [BEAT_IDX_BLOCK_W-1:0] rx_beat_cnt_next;
  logic                        rx_msg_full_next;

  // Dispatch + engine ports
  logic     empty_slot_w;
  logic     have_empty_slot_w;
  logic     slot0_second_ready_w;
  logic     slot1_second_ready_w;
  logic     second_slot_w;
  logic     have_second_w;
  logic     dispatch_first_w;
  logic     dispatch_second_w;
  logic     eng_job_valid;
  logic     eng_job_ready;
  eng_job_t eng_job;
  logic     eng_res_valid;
  logic     eng_res_ready;
  eng_res_t eng_res;

  // Combinational bypass: forward this-cycle first-block capture into
  // dispatch_second so the second block fires the SAME cycle the first
  // result arrives.  Kills the otherwise-1-cycle dispatch bubble between
  // back-to-back blocks of the same message.
  logic              slot_first_done_w [0:NUM_LANES-1];
  logic [HASH_W-1:0] slot_cv_w         [0:NUM_LANES-1];

  // Result capture
  logic res_tfer_w;
  logic res_first_w;
  logic res_final_w;

  // TX
  logic tx_slot_w;
  logic have_tx_w;
  logic tx_start_w;
  logic tx_beat_tfer_w;
  logic tx_last_beat_w;
  logic tx_active_next;
  logic tx_beat_cnt_set_w;
  logic tx_beat_cnt_clear_w;
  logic tx_beat_cnt_next;

  //---------------------------------------------------------------------------
  // RX  --  s_axis -> rx_msg_q, rx_msg_full_q, rx_msg_is_last_q
  //---------------------------------------------------------------------------
  // XDMA presents tdata little-endian within each beat (byte N at
  // tdata[8N+:8]).  SHA-256 wants big-endian message words, so reverse
  // the 16 bytes inside every beat at the AXIS boundary.
  logic [AXIS_DATA_W-1:0] s_axis_tdata_be;
  for (genvar B = 0; B < AXIS_DATA_W/8; B = B + 1) begin : g_rx_bswap
    assign s_axis_tdata_be[8*B +: 8] =
      s_axis_tdata[8*(AXIS_DATA_W/8 - 1 - B) +: 8];
  end

  assign s_axis_tready = ~rx_msg_full_q;

  assign rx_beat_tfer_w =
      s_axis_tvalid
    & s_axis_tready;

  assign rx_beat_last_in_msg_w =
      rx_beat_tfer_w
    & (&rx_beat_cnt_q);

  assign rx_beat_cnt_next =
      rx_beat_tfer_w
    ? (rx_beat_cnt_q + 'd1)
    : rx_beat_cnt_q;

  assign rx_msg_full_next =
      rx_beat_last_in_msg_w
    | (rx_msg_full_q & ~rx_msg_consume_w);

  // All RX-domain flops in one process: reset-clearable counter/full bit,
  // beat-indexed message write, and end-of-burst tlast capture.
  always_ff @(posedge aclk) begin
    if (~aresetn) begin
      rx_beat_cnt_q <= '0;
      rx_msg_full_q <= 1'b0;
    end else begin
      rx_beat_cnt_q <= rx_beat_cnt_next;
      rx_msg_full_q <= rx_msg_full_next;
    end
    if (rx_beat_tfer_w) begin
      case (rx_beat_cnt_q)
        2'd0: rx_msg_q[BLOCK_W-1 - 0*AXIS_DATA_W -: AXIS_DATA_W] <= s_axis_tdata_be;
        2'd1: rx_msg_q[BLOCK_W-1 - 1*AXIS_DATA_W -: AXIS_DATA_W] <= s_axis_tdata_be;
        2'd2: rx_msg_q[BLOCK_W-1 - 2*AXIS_DATA_W -: AXIS_DATA_W] <= s_axis_tdata_be;
        2'd3: rx_msg_q[BLOCK_W-1 - 3*AXIS_DATA_W -: AXIS_DATA_W] <= s_axis_tdata_be;
      endcase
    end
    // Carry s_axis_tlast end-of-burst flag to m_axis_tlast so a single host
    // read() drains the whole digest burst in one XDMA C2H descriptor.
    if (rx_beat_last_in_msg_w) rx_msg_is_last_q <= s_axis_tlast;
  end

  //---------------------------------------------------------------------------
  // DISPATCH  --  pick slot + drive engine ports (second-block wins)
  //---------------------------------------------------------------------------
  assign empty_slot_w = slot_busy_q[0];

  assign have_empty_slot_w =
      ~slot_busy_q[0]
    | ~slot_busy_q[1];

  // Bypass: a first-block result captured THIS cycle counts as done.
  assign slot_first_done_w[0] =
      slot_first_done_q[0]
    | (res_first_w & (eng_res.tag == 1'b0));

  assign slot_first_done_w[1] =
      slot_first_done_q[1]
    | (res_first_w & (eng_res.tag == 1'b1));

  // Bypass: matching first-cycle CV forwards straight from the engine
  // output before slot_cv_q latches it next cycle.
  assign slot_cv_w[0] =
      (res_first_w & (eng_res.tag == 1'b0))
    ? eng_res.cv_out
    : slot_cv_q[0];

  assign slot_cv_w[1] =
      (res_first_w & (eng_res.tag == 1'b1))
    ? eng_res.cv_out
    : slot_cv_q[1];

  assign slot0_second_ready_w =
      slot_busy_q[0]
    &  slot_first_done_w[0]
    & ~slot_second_issued_q[0]
    & ~slot_digest_ready_q[0];

  assign slot1_second_ready_w =
      slot_busy_q[1]
    &  slot_first_done_w[1]
    & ~slot_second_issued_q[1]
    & ~slot_digest_ready_q[1];

  assign second_slot_w = ~slot0_second_ready_w;

  assign have_second_w =
      slot0_second_ready_w
    | slot1_second_ready_w;

  assign dispatch_second_w =
      have_second_w
    & eng_job_ready;

  assign dispatch_first_w =
      have_empty_slot_w
    & rx_msg_full_q
    & eng_job_ready
    & ~dispatch_second_w;

  assign eng_job_valid =
      dispatch_second_w
    | dispatch_first_w;

  assign eng_job.block =
      dispatch_second_w
    ? PAD_BLOCK_1MSG
    : rx_msg_q;

  assign eng_job.cv_in =
      dispatch_second_w
    ? slot_cv_w[second_slot_w]
    : IV;

  assign eng_job.tag =
      dispatch_second_w
    ? second_slot_w
    : empty_slot_w;

  assign eng_res_ready    = 1'b1;
  assign rx_msg_consume_w = dispatch_first_w;

  sha256_compress u_compress (
    .clk        (aclk),
    .rstn       (aresetn),
    .job_valid  (eng_job_valid),
    .job_ready  (eng_job_ready),
    .job        (eng_job),
    .res_valid  (eng_res_valid),
    .res_ready  (eng_res_ready),
    .res        (eng_res)
  );

  //---------------------------------------------------------------------------
  // Result capture events
  //---------------------------------------------------------------------------
  assign res_tfer_w =
      eng_res_valid
    & eng_res_ready;

  assign res_first_w =
      res_tfer_w
    & ~slot_first_done_q[eng_res.tag];

  assign res_final_w =
      res_tfer_w
    &  slot_first_done_q[eng_res.tag];

  //---------------------------------------------------------------------------
  // TX  --  slot_digest_q -> m_axis  (2 beats; tlast only at burst end)
  //---------------------------------------------------------------------------
  assign tx_slot_w = ~slot_digest_ready_q[0];

  assign have_tx_w =
      slot_digest_ready_q[0]
    | slot_digest_ready_q[1];

  assign tx_start_w =
      ~tx_active_q
    & have_tx_w;

  assign tx_beat_tfer_w =
      tx_active_q
    & m_axis_tready;

  assign tx_last_beat_w =
      tx_beat_tfer_w
    & tx_beat_cnt_q;

  assign tx_active_next =
      tx_start_w
    | (tx_active_q & ~tx_last_beat_w);

  assign tx_beat_cnt_set_w =
      tx_beat_tfer_w
    & ~tx_beat_cnt_q;

  assign tx_beat_cnt_clear_w =
      tx_start_w
    | tx_last_beat_w;

  assign tx_beat_cnt_next =
      tx_beat_cnt_set_w
    | (tx_beat_cnt_q & ~tx_beat_cnt_clear_w);

  // All TX-domain flops in one process: active flag, active-slot latch,
  // and 2-beat counter.
  always_ff @(posedge aclk) begin
    if (~aresetn) begin
      tx_active_q   <= 1'b0;
      tx_beat_cnt_q <= '0;
    end else begin
      tx_active_q   <= tx_active_next;
      tx_beat_cnt_q <= tx_beat_cnt_next;
    end
    if (tx_start_w) tx_active_slot_q <= tx_slot_w;
  end

  assign m_axis_tvalid = tx_active_q;
  assign m_axis_tkeep  = {AXIS_KEEP_W{tx_active_q}};

  assign m_axis_tlast =
      tx_active_q
    & tx_beat_cnt_q
    & slot_is_last_q[tx_active_slot_q];

  // Digest is BE-word internally; XDMA wants LE-within-beat on m_axis, so
  // reverse the 16 bytes inside each beat at the boundary.
  logic [AXIS_DATA_W-1:0] m_axis_tdata_be;
  assign m_axis_tdata_be =
      ~tx_active_q
    ? '0
    : ( tx_beat_cnt_q
      ? slot_digest_q[tx_active_slot_q][1*AXIS_DATA_W-1 : 0*AXIS_DATA_W]
      : slot_digest_q[tx_active_slot_q][2*AXIS_DATA_W-1 : 1*AXIS_DATA_W] );

  for (genvar B = 0; B < AXIS_DATA_W/8; B = B + 1) begin : g_tx_bswap
    assign m_axis_tdata[8*B +: 8] =
      m_axis_tdata_be[8*(AXIS_DATA_W/8 - 1 - B) +: 8];
  end

  //---------------------------------------------------------------------------
  // Per-slot bookkeeping updates
  //---------------------------------------------------------------------------
  for (genvar S = 0; S < NUM_LANES; S = S + 1) begin : g_slot

    // -- WIRES (every `_w` / `_next` in this generate scope) ----------------
    logic slot_load_w;
    logic slot_second_w;
    logic slot_capture_first_w;
    logic slot_capture_final_w;
    logic slot_emit_done_w;
    logic slot_reload_or_emit_w;
    logic slot_busy_next;
    logic slot_first_done_next;
    logic slot_second_issued_next;
    logic slot_digest_ready_next;

    // -- ASSIGNS / ALWAYS_FF ------------------------------------------------
    assign slot_load_w =
        dispatch_first_w
      & (empty_slot_w == LANE_IDX_W'(S));

    assign slot_second_w =
        dispatch_second_w
      & (second_slot_w == LANE_IDX_W'(S));

    assign slot_capture_first_w =
        res_first_w
      & (eng_res.tag == LANE_IDX_W'(S));

    assign slot_capture_final_w =
        res_final_w
      & (eng_res.tag == LANE_IDX_W'(S));

    assign slot_emit_done_w =
        tx_last_beat_w
      & (tx_active_slot_q == LANE_IDX_W'(S));

    assign slot_reload_or_emit_w =
        slot_load_w
      | slot_emit_done_w;

    assign slot_busy_next =
        slot_load_w
      | (slot_busy_q[S] & ~slot_emit_done_w);

    assign slot_first_done_next =
        slot_capture_first_w
      | (slot_first_done_q[S] & ~slot_reload_or_emit_w);

    assign slot_second_issued_next =
        slot_second_w
      | (slot_second_issued_q[S] & ~slot_reload_or_emit_w);

    assign slot_digest_ready_next =
        slot_capture_final_w
      | (slot_digest_ready_q[S] & ~slot_reload_or_emit_w);

    // Per-slot status bits: reset-clearable, all share the same next/reset
    // pattern and live in one process.
    always_ff @(posedge aclk) begin
      if (~aresetn) begin
        slot_busy_q          [S] <= 1'b0;
        slot_first_done_q    [S] <= 1'b0;
        slot_second_issued_q [S] <= 1'b0;
        slot_digest_ready_q  [S] <= 1'b0;
        slot_is_last_q       [S] <= 1'b0;
      end else begin
        slot_busy_q          [S] <= slot_busy_next;
        slot_first_done_q    [S] <= slot_first_done_next;
        slot_second_issued_q [S] <= slot_second_issued_next;
        slot_digest_ready_q  [S] <= slot_digest_ready_next;
        if (slot_load_w)          slot_is_last_q[S] <= rx_msg_is_last_q;
      end
    end

    // Payload captures: enable-only, no reset.
    always_ff @(posedge aclk) begin
      if (slot_capture_first_w) slot_cv_q[S] <= eng_res.cv_out;
    end

    always_ff @(posedge aclk) begin
      if (slot_capture_final_w) slot_digest_q[S] <= eng_res.cv_out;
    end

  end : g_slot

endmodule
