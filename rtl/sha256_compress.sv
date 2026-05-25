// sha256_compress.sv
//
// 2-way interleaved, 2-stage pipelined SHA-256 compression engine.
// One 512-bit block per job; emits the updated 256-bit chaining value.
// IV / previous-CV is supplied per job so the module chains across blocks.
//
// PIPELINE
//   kw_pre = K[t] + W[t] precomputed one round ahead (drops T1 to a 4-input
//     add: h + BigSig1 + Ch + kw_pre).
//   Stage A : compute T1, T2, Wt for selected lane.        -> pipe regs
//   Stage B : a_new = T1+T2, e_new = d + T1, writeback.
//   Stages A and B always touch DIFFERENT lanes, so 1 round / cycle aggregate.
//   Per lane = ROUNDS*2 + 1 load + 1 emit = 130 cycles / block.
//   SHA-256(64B) = 2 blocks -> ~60 MB/s at 125 MHz.

`timescale 1ns/1ps

import sha256_pkg::*;

module sha256_compress
(
  input  logic                clk,
  input  logic                rstn,

  input  logic                job_valid,
  output logic                job_ready,
  input  logic [BLOCK_W-1:0]  job_block,
  input  logic [HASH_W-1:0]   job_cv_in,
  input  logic                job_tag,

  output logic                res_valid,
  input  logic                res_ready,
  output logic [HASH_W-1:0]   res_cv_out,
  output logic                res_tag
);

  //---------------------------------------------------------------------------
  // REGISTERS
  //---------------------------------------------------------------------------
  // Per-lane working state a..h
  logic [WORD_W-1:0]       work_a_q [0:NUM_LANES-1];
  logic [WORD_W-1:0]       work_b_q [0:NUM_LANES-1];
  logic [WORD_W-1:0]       work_c_q [0:NUM_LANES-1];
  logic [WORD_W-1:0]       work_d_q [0:NUM_LANES-1];
  logic [WORD_W-1:0]       work_e_q [0:NUM_LANES-1];
  logic [WORD_W-1:0]       work_f_q [0:NUM_LANES-1];
  logic [WORD_W-1:0]       work_g_q [0:NUM_LANES-1];
  logic [WORD_W-1:0]       work_h_q [0:NUM_LANES-1];

  // Per-lane IV snapshot a..h (for final IV-add)
  logic [WORD_W-1:0]       iv_a_q   [0:NUM_LANES-1];
  logic [WORD_W-1:0]       iv_b_q   [0:NUM_LANES-1];
  logic [WORD_W-1:0]       iv_c_q   [0:NUM_LANES-1];
  logic [WORD_W-1:0]       iv_d_q   [0:NUM_LANES-1];
  logic [WORD_W-1:0]       iv_e_q   [0:NUM_LANES-1];
  logic [WORD_W-1:0]       iv_f_q   [0:NUM_LANES-1];
  logic [WORD_W-1:0]       iv_g_q   [0:NUM_LANES-1];
  logic [WORD_W-1:0]       iv_h_q   [0:NUM_LANES-1];

  // Per-lane bookkeeping
  logic [BLOCK_W-1:0]      raw_block_q [0:NUM_LANES-1];
  logic [WORD_W-1:0]       msg_sched_q [0:NUM_LANES-1][0:MSG_SCHED_DEPTH-1];
  logic [ROUND_IDX_W-1:0]  round_q     [0:NUM_LANES-1];
  logic                    lane_busy_q [0:NUM_LANES-1];
  logic                    lane_tag_q  [0:NUM_LANES-1];
  logic [WORD_W-1:0]       kw_pre_q    [0:NUM_LANES-1];

  // Pipeline (stage A -> stage B)
  logic                    pipe_valid_q;
  logic                    pipe_lane_q;
  logic [ROUND_IDX_W-1:0]  pipe_round_q;
  logic                    pipe_is_last_round_q;
  logic [WORD_W-1:0]       pipe_t1_q;
  logic [WORD_W-1:0]       pipe_t2_q;
  logic [WORD_W-1:0]       pipe_wt_q;

  // 1-deep output skid
  logic                    res_valid_q;
  logic [HASH_W-1:0]       res_cv_q;
  logic                    res_tag_q;

  //---------------------------------------------------------------------------
  // Job intake
  //---------------------------------------------------------------------------
  logic load_lane_w;
  logic load_w;

  assign load_lane_w = lane_busy_q[0];

  assign job_ready =
      ~lane_busy_q[0]
    | ~lane_busy_q[1];

  assign load_w =
      job_valid
    & job_ready;

  //---------------------------------------------------------------------------
  // Stage A scheduling
  //   pipe full  -> must pick the lane the pipe does NOT own
  //   pipe empty -> pick the busy lane (stage_a_run_w gates if neither)
  //---------------------------------------------------------------------------
  logic stage_a_lane_pref_w;
  logic stage_a_lane_w;
  logic stage_a_lane_busy_w;
  logic stage_a_skid_full_w;
  logic stage_a_run_w;

  assign stage_a_lane_pref_w = ~lane_busy_q[0];

  assign stage_a_lane_w =
      pipe_valid_q
    ? ~pipe_lane_q
    :  stage_a_lane_pref_w;

  assign stage_a_lane_busy_w = lane_busy_q[stage_a_lane_w];

  // Stall final round when output skid is still holding a previous digest.
  assign stage_a_skid_full_w =
      (&round_q[stage_a_lane_w])
    & res_valid_q
    & ~res_ready;

  assign stage_a_run_w =
      stage_a_lane_busy_w
    & ~stage_a_skid_full_w;

  //---------------------------------------------------------------------------
  // Stage A datapath  --  T1, T2, Wt for selected lane
  //---------------------------------------------------------------------------
  logic [WORD_W-1:0]      a_sa, b_sa, c_sa, d_sa, e_sa, f_sa, g_sa, h_sa;
  logic [WORD_W-1:0]      kw_sa;
  logic [ROUND_IDX_W-1:0] round_sa;
  logic                   is_last_round_sa;
  logic                   round_lt_window_sa;
  logic [WORD_W-1:0]      wt_from_block_sa;
  logic [WORD_W-1:0]      wt_recurrence_sa;
  logic [WORD_W-1:0]      wt_sa;
  logic [WORD_W-1:0]      t1_sa;
  logic [WORD_W-1:0]      t2_sa;

  assign a_sa     = work_a_q [stage_a_lane_w];
  assign b_sa     = work_b_q [stage_a_lane_w];
  assign c_sa     = work_c_q [stage_a_lane_w];
  assign d_sa     = work_d_q [stage_a_lane_w];
  assign e_sa     = work_e_q [stage_a_lane_w];
  assign f_sa     = work_f_q [stage_a_lane_w];
  assign g_sa     = work_g_q [stage_a_lane_w];
  assign h_sa     = work_h_q [stage_a_lane_w];
  assign kw_sa    = kw_pre_q [stage_a_lane_w];
  assign round_sa = round_q  [stage_a_lane_w];

  assign is_last_round_sa   = &round_sa;
  assign round_lt_window_sa = round_sa < ROUND_IDX_W'(MSG_SCHED_DEPTH);

  assign wt_from_block_sa =
      raw_block_q[stage_a_lane_w][BLOCK_W-1 - WORD_W*round_sa -: WORD_W];

  assign wt_recurrence_sa =
      sm_sigma1(msg_sched_q[stage_a_lane_w][14])
    + msg_sched_q[stage_a_lane_w][ 9]
    + sm_sigma0 (msg_sched_q[stage_a_lane_w][ 1])
    + msg_sched_q[stage_a_lane_w][ 0];

  assign wt_sa =
      round_lt_window_sa
    ? wt_from_block_sa
    : wt_recurrence_sa;

  assign t1_sa =
      h_sa
    + big_sigma1(e_sa)
    + ch_efg    (e_sa, f_sa, g_sa)
    + kw_sa;

  assign t2_sa =
      big_sigma0(a_sa)
    + maj_abc   (a_sa, b_sa, c_sa);

  //---------------------------------------------------------------------------
  // Pipeline register updates
  //---------------------------------------------------------------------------
  always_ff @(posedge clk) begin
    if (~rstn) pipe_valid_q <= 1'b0;
    else       pipe_valid_q <= stage_a_run_w;
  end

  always_ff @(posedge clk) begin
    pipe_lane_q          <= stage_a_lane_w;
    pipe_round_q         <= round_sa;
    pipe_is_last_round_q <= is_last_round_sa;
    pipe_t1_q            <= t1_sa;
    pipe_t2_q            <= t2_sa;
    pipe_wt_q            <= wt_sa;
  end

  //---------------------------------------------------------------------------
  // Stage B writeback helpers (pre/new state on pipe_lane_q) + final CV
  //---------------------------------------------------------------------------
  logic [WORD_W-1:0] wb_a_pre, wb_b_pre, wb_c_pre, wb_d_pre;
  logic [WORD_W-1:0] wb_e_pre, wb_f_pre, wb_g_pre, wb_h_pre;
  logic [WORD_W-1:0] wb_a_new, wb_e_new;
  logic [HASH_W-1:0] final_cv_w;

  assign wb_a_pre = work_a_q[pipe_lane_q];
  assign wb_b_pre = work_b_q[pipe_lane_q];
  assign wb_c_pre = work_c_q[pipe_lane_q];
  assign wb_d_pre = work_d_q[pipe_lane_q];
  assign wb_e_pre = work_e_q[pipe_lane_q];
  assign wb_f_pre = work_f_q[pipe_lane_q];
  assign wb_g_pre = work_g_q[pipe_lane_q];
  assign wb_h_pre = work_h_q[pipe_lane_q];

  assign wb_a_new =
      pipe_t1_q
    + pipe_t2_q;

  assign wb_e_new =
      wb_d_pre
    + pipe_t1_q;

  assign final_cv_w = {
      wb_a_new + iv_a_q[pipe_lane_q],
      wb_a_pre + iv_b_q[pipe_lane_q],
      wb_b_pre + iv_c_q[pipe_lane_q],
      wb_c_pre + iv_d_q[pipe_lane_q],
      wb_e_new + iv_e_q[pipe_lane_q],
      wb_e_pre + iv_f_q[pipe_lane_q],
      wb_f_pre + iv_g_q[pipe_lane_q],
      wb_g_pre + iv_h_q[pipe_lane_q]
  };

  //---------------------------------------------------------------------------
  // Output skid  --  final-round writeback wins over consumer pop
  //---------------------------------------------------------------------------
  logic              wb_final_w;
  logic              res_pop_w;
  logic              res_valid_next;
  logic [HASH_W-1:0] res_cv_next;
  logic              res_tag_next;

  assign wb_final_w =
      pipe_valid_q
    & pipe_is_last_round_q;

  assign res_pop_w =
      res_valid_q
    & res_ready;

  assign res_valid_next =
      wb_final_w
    | (res_valid_q & ~res_pop_w);

  assign res_cv_next =
      wb_final_w
    ? final_cv_w
    : res_cv_q;

  assign res_tag_next =
      wb_final_w
    ? lane_tag_q[pipe_lane_q]
    : res_tag_q;

  always_ff @(posedge clk) begin
    if (~rstn) res_valid_q <= 1'b0;
    else       res_valid_q <= res_valid_next;
  end
  always_ff @(posedge clk) begin
    res_cv_q  <= res_cv_next;
    res_tag_q <= res_tag_next;
  end

  assign res_valid  = res_valid_q;
  assign res_cv_out = res_cv_q;
  assign res_tag    = res_tag_q;

  //---------------------------------------------------------------------------
  // Per-lane state updates
  //---------------------------------------------------------------------------
  for (genvar L = 0; L < NUM_LANES; L = L + 1) begin : g_lane

    logic load_active_w;
    logic wb_normal_w;
    logic wb_final_lane_w;

    assign load_active_w =
        load_w
      & (load_lane_w == LANE_IDX_W'(L));

    assign wb_normal_w =
        pipe_valid_q
      & (pipe_lane_q == LANE_IDX_W'(L))
      & ~pipe_is_last_round_q;

    assign wb_final_lane_w =
        pipe_valid_q
      & (pipe_lane_q == LANE_IDX_W'(L))
      &  pipe_is_last_round_q;

    logic lane_busy_next;
    assign lane_busy_next =
        load_active_w
      | (lane_busy_q[L] & ~wb_final_lane_w);
    always_ff @(posedge clk) begin
      if (~rstn) lane_busy_q[L] <= 1'b0;
      else       lane_busy_q[L] <= lane_busy_next;
    end

    always_ff @(posedge clk) begin
      if (load_active_w) lane_tag_q[L] <= job_tag;
    end

    logic [ROUND_IDX_W-1:0] round_next;
    assign round_next =
        load_active_w ? '0
      : wb_normal_w   ? (pipe_round_q + 'd1)
      :                  round_q[L];
    always_ff @(posedge clk) begin
      round_q[L] <= round_next;
    end

    always_ff @(posedge clk) begin
      if (load_active_w) raw_block_q[L] <= job_block;
    end

    always_ff @(posedge clk) begin
      if (load_active_w) begin
        iv_a_q[L] <= job_cv_in[HASH_W-1 - 0*WORD_W -: WORD_W];
        iv_b_q[L] <= job_cv_in[HASH_W-1 - 1*WORD_W -: WORD_W];
        iv_c_q[L] <= job_cv_in[HASH_W-1 - 2*WORD_W -: WORD_W];
        iv_d_q[L] <= job_cv_in[HASH_W-1 - 3*WORD_W -: WORD_W];
        iv_e_q[L] <= job_cv_in[HASH_W-1 - 4*WORD_W -: WORD_W];
        iv_f_q[L] <= job_cv_in[HASH_W-1 - 5*WORD_W -: WORD_W];
        iv_g_q[L] <= job_cv_in[HASH_W-1 - 6*WORD_W -: WORD_W];
        iv_h_q[L] <= job_cv_in[HASH_W-1 - 7*WORD_W -: WORD_W];
      end
    end

    // Working state a..h  --  priority: load > final-add > normal-round > hold
    logic [WORD_W-1:0] work_a_next, work_b_next, work_c_next, work_d_next;
    logic [WORD_W-1:0] work_e_next, work_f_next, work_g_next, work_h_next;

    assign work_a_next =
        load_active_w   ? job_cv_in [HASH_W-1 - 0*WORD_W -: WORD_W]
      : wb_final_lane_w ? final_cv_w[HASH_W-1 - 0*WORD_W -: WORD_W]
      : wb_normal_w     ? wb_a_new
      :                   work_a_q[L];

    assign work_b_next =
        load_active_w   ? job_cv_in [HASH_W-1 - 1*WORD_W -: WORD_W]
      : wb_final_lane_w ? final_cv_w[HASH_W-1 - 1*WORD_W -: WORD_W]
      : wb_normal_w     ? wb_a_pre
      :                   work_b_q[L];

    assign work_c_next =
        load_active_w   ? job_cv_in [HASH_W-1 - 2*WORD_W -: WORD_W]
      : wb_final_lane_w ? final_cv_w[HASH_W-1 - 2*WORD_W -: WORD_W]
      : wb_normal_w     ? wb_b_pre
      :                   work_c_q[L];

    assign work_d_next =
        load_active_w   ? job_cv_in [HASH_W-1 - 3*WORD_W -: WORD_W]
      : wb_final_lane_w ? final_cv_w[HASH_W-1 - 3*WORD_W -: WORD_W]
      : wb_normal_w     ? wb_c_pre
      :                   work_d_q[L];

    assign work_e_next =
        load_active_w   ? job_cv_in [HASH_W-1 - 4*WORD_W -: WORD_W]
      : wb_final_lane_w ? final_cv_w[HASH_W-1 - 4*WORD_W -: WORD_W]
      : wb_normal_w     ? wb_e_new
      :                   work_e_q[L];

    assign work_f_next =
        load_active_w   ? job_cv_in [HASH_W-1 - 5*WORD_W -: WORD_W]
      : wb_final_lane_w ? final_cv_w[HASH_W-1 - 5*WORD_W -: WORD_W]
      : wb_normal_w     ? wb_e_pre
      :                   work_f_q[L];

    assign work_g_next =
        load_active_w   ? job_cv_in [HASH_W-1 - 6*WORD_W -: WORD_W]
      : wb_final_lane_w ? final_cv_w[HASH_W-1 - 6*WORD_W -: WORD_W]
      : wb_normal_w     ? wb_f_pre
      :                   work_g_q[L];

    assign work_h_next =
        load_active_w   ? job_cv_in [HASH_W-1 - 7*WORD_W -: WORD_W]
      : wb_final_lane_w ? final_cv_w[HASH_W-1 - 7*WORD_W -: WORD_W]
      : wb_normal_w     ? wb_g_pre
      :                   work_h_q[L];

    always_ff @(posedge clk) begin
      work_a_q[L] <= work_a_next;
      work_b_q[L] <= work_b_next;
      work_c_q[L] <= work_c_next;
      work_d_q[L] <= work_d_next;
      work_e_q[L] <= work_e_next;
      work_f_q[L] <= work_f_next;
      work_g_q[L] <= work_g_next;
      work_h_q[L] <= work_h_next;
    end

    // msg_sched_q  --  16-deep shift, inject pipe_wt_q at the top on wb_normal_w
    for (genvar I = 0; I < MSG_SCHED_DEPTH; I = I + 1) begin : g_msg_sched
      logic [WORD_W-1:0] msg_sched_next;
      if (I == MSG_SCHED_DEPTH-1) begin : g_inject
        assign msg_sched_next =
            wb_normal_w
          ? pipe_wt_q
          : msg_sched_q[L][I];
      end
      else begin : g_shift
        assign msg_sched_next =
            wb_normal_w
          ? msg_sched_q[L][I+1]
          : msg_sched_q[L][I];
      end
      always_ff @(posedge clk) begin
        msg_sched_q[L][I] <= msg_sched_next;
      end
    end

    // kw_pre_q  --  K[t] + W[t] computed one round ahead.  Recurrence reads
    // POST-shift indices 14/9/1/0  ==  PRE-shift 15/10/2/1.
    logic [WORD_W-1:0]      kw_pre_next;
    logic [ROUND_IDX_W-1:0] next_round_w;
    logic                   next_round_lt_window_w;
    logic [WORD_W-1:0]      wt_next_from_block_w;
    logic [WORD_W-1:0]      wt_next_from_rec_w;
    logic [WORD_W-1:0]      wt_next_w;

    assign next_round_w           = pipe_round_q + 'd1;
    assign next_round_lt_window_w = next_round_w < ROUND_IDX_W'(MSG_SCHED_DEPTH);

    assign wt_next_from_block_w =
        raw_block_q[L][BLOCK_W-1 - WORD_W*next_round_w -: WORD_W];

    assign wt_next_from_rec_w =
        sm_sigma1(msg_sched_q[L][15])
      + msg_sched_q[L][10]
      + sm_sigma0 (msg_sched_q[L][ 2])
      + msg_sched_q[L][ 1];

    assign wt_next_w =
        next_round_lt_window_w
      ? wt_next_from_block_w
      : wt_next_from_rec_w;

    assign kw_pre_next =
        load_active_w ? (k_round('0)           + job_block[BLOCK_W-1 -: WORD_W])
      : wb_normal_w   ? (k_round(next_round_w) + wt_next_w)
      :                  kw_pre_q[L];

    always_ff @(posedge clk) begin
      kw_pre_q[L] <= kw_pre_next;
    end

  end : g_lane

endmodule
