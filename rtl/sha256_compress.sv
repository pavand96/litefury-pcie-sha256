// sha256_compress.sv
//
// 2-way interleaved, 2-stage pipelined SHA-256 compression engine.
//
// Consumes one 512-bit block per job along with the 256-bit chaining value
// (CV) and emits the updated CV.  IV / previous-CV is supplied per job so
// this module can be chained across blocks.
//
// Style: gearbox.  See docs/CODING_STYLE.md.  All combinational logic in
// `assign`; every register has its own small `always_ff` block driven from
// a pre-computed `*_next` signal computed in the lines immediately above.
// Per-lane state is replicated via `generate` over NUM_LANES (=2).
//
// =============================================================================
// PIPELINE OVERVIEW (why two stages + two interleaved lanes)
// =============================================================================
// A naive SHA-256 round is a 6-input adder tree (h + BigSig1 + Ch + K + W +
// BigSig0 + Maj) that maps to ~10.7 ns on Artix-7 -2L -- too slow for 8 ns
// (125 MHz).  We:
//   1) precompute kw_pre = K[t] + W[t] one round ahead, dropping T1 to a
//      4-input add (h + BigSig1 + Ch + kw_pre),
//   2) register T1, T2 into a pipe and do the final 1-add writeback the
//      next cycle (a_new = T1+T2, e_new = d + T1),
//   3) interleave two independent jobs ("lanes") through the same fabric so
//      stage A and stage B always operate on DIFFERENT lanes (no
//      read-after-write bubble).
//
// Aggregate throughput in steady state = 1 round / cycle.
// Per lane = ROUNDS*2 cycles + 1 load + 1 emit  = 130 cycles / block.
// 64-byte SHA-256 message = 2 blocks, so ~60 MB/s at 125 MHz.
//
// =============================================================================
// HANDSHAKES
// =============================================================================
//   Input  : job_valid / job_ready.  Accepted whenever ANY lane is free.
//   Output : res_valid / res_ready.  A 1-deep skid parks the digest until
//            the consumer pops it.  res_tag echoes job_tag.
//
`timescale 1ns/1ps

import sha256_pkg::*;

module sha256_compress
(
  input  logic                clk,
  input  logic                rstn,

  // Job input handshake ------------------------------------------------------
  input  logic                job_valid,
  output logic                job_ready,
  input  logic [BLOCK_W-1:0]  job_block,    // 16 BE words, word0 = MSBs
  input  logic [HASH_W-1:0]   job_cv_in,    // {a,b,c,d,e,f,g,h}, a in MSBs
  input  logic                job_tag,

  // Result output handshake --------------------------------------------------
  output logic                res_valid,
  input  logic                res_ready,
  output logic [HASH_W-1:0]   res_cv_out,
  output logic                res_tag
);

  // ===========================================================================
  // PER-LANE STATE (replicated via generate over NUM_LANES)
  // ===========================================================================
  logic [WORD_W-1:0]       work_a_q [0:NUM_LANES-1];
  logic [WORD_W-1:0]       work_b_q [0:NUM_LANES-1];
  logic [WORD_W-1:0]       work_c_q [0:NUM_LANES-1];
  logic [WORD_W-1:0]       work_d_q [0:NUM_LANES-1];
  logic [WORD_W-1:0]       work_e_q [0:NUM_LANES-1];
  logic [WORD_W-1:0]       work_f_q [0:NUM_LANES-1];
  logic [WORD_W-1:0]       work_g_q [0:NUM_LANES-1];
  logic [WORD_W-1:0]       work_h_q [0:NUM_LANES-1];

  logic [WORD_W-1:0]       iv_a_q   [0:NUM_LANES-1];
  logic [WORD_W-1:0]       iv_b_q   [0:NUM_LANES-1];
  logic [WORD_W-1:0]       iv_c_q   [0:NUM_LANES-1];
  logic [WORD_W-1:0]       iv_d_q   [0:NUM_LANES-1];
  logic [WORD_W-1:0]       iv_e_q   [0:NUM_LANES-1];
  logic [WORD_W-1:0]       iv_f_q   [0:NUM_LANES-1];
  logic [WORD_W-1:0]       iv_g_q   [0:NUM_LANES-1];
  logic [WORD_W-1:0]       iv_h_q   [0:NUM_LANES-1];

  logic [BLOCK_W-1:0]      raw_block_q [0:NUM_LANES-1];
  logic [WORD_W-1:0]       msg_sched_q [0:NUM_LANES-1][0:MSG_SCHED_DEPTH-1];
  logic [ROUND_IDX_W-1:0]  round_q     [0:NUM_LANES-1];
  logic                    lane_busy_q [0:NUM_LANES-1];
  logic                    lane_tag_q  [0:NUM_LANES-1];
  logic [WORD_W-1:0]       kw_pre_q    [0:NUM_LANES-1];

  // ===========================================================================
  // PIPELINE REGISTERS (stage A -> stage B)
  // ===========================================================================
  logic                    pipe_valid_q;
  logic                    pipe_lane_q;
  logic [ROUND_IDX_W-1:0]  pipe_round_q;
  logic                    pipe_is_last_round_q;
  logic [WORD_W-1:0]       pipe_t1_q;
  logic [WORD_W-1:0]       pipe_t2_q;
  logic [WORD_W-1:0]       pipe_wt_q;

  // ===========================================================================
  // OUTPUT SKID (1-deep)
  // ===========================================================================
  logic                    res_valid_q;
  logic [HASH_W-1:0]       res_cv_q;
  logic                    res_tag_q;

  // ===========================================================================
  // STAGE SCHEDULING (pure combinational)
  // ===========================================================================
  // Pick the lane stage A operates on this cycle.  When the pipe is full,
  // we MUST pick the lane the pipe does not own (stage B writes that lane
  // on the same cycle).  When the pipe is empty, pick the busy lane,
  // biased toward lane 1 when both are free (stage_a_run_w gates anyway).
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

  // Block stage A on the final round if the skid is still holding a
  // previous digest the consumer hasn't popped yet (would clobber it).
  assign stage_a_skid_full_w =
      (&round_q[stage_a_lane_w])
    &  res_valid_q
    & ~res_ready;

  assign stage_a_run_w =
      stage_a_lane_busy_w
    & ~stage_a_skid_full_w;

  // ===========================================================================
  // STAGE A  --  T1, T2, Wt (looked up from the selected lane's state)
  // ===========================================================================
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

  assign a_sa             = work_a_q [stage_a_lane_w];
  assign b_sa             = work_b_q [stage_a_lane_w];
  assign c_sa             = work_c_q [stage_a_lane_w];
  assign d_sa             = work_d_q [stage_a_lane_w];
  assign e_sa             = work_e_q [stage_a_lane_w];
  assign f_sa             = work_f_q [stage_a_lane_w];
  assign g_sa             = work_g_q [stage_a_lane_w];
  assign h_sa             = work_h_q [stage_a_lane_w];
  assign kw_sa            = kw_pre_q [stage_a_lane_w];
  assign round_sa         = round_q  [stage_a_lane_w];
  assign is_last_round_sa = &round_sa;                       // all bits 1 = 63

  // round < MSG_SCHED_DEPTH  ==  top (ROUND_IDX_W - $clog2(DEPTH)) bits clear.
  assign round_lt_window_sa =
      round_sa < ROUND_IDX_W'(MSG_SCHED_DEPTH);

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

  // 4-input add for T1 (kw_sa carries K[t] + W[t] pre-summed last cycle).
  assign t1_sa = h_sa + big_sigma1(e_sa) + ch_efg (e_sa, f_sa, g_sa) + kw_sa;
  assign t2_sa =        big_sigma0(a_sa) + maj_abc(a_sa, b_sa, c_sa);

  // ===========================================================================
  // STAGE B  --  writeback helpers (pre/new state on pipe_lane_q)
  // ===========================================================================
  logic [WORD_W-1:0] wb_a_pre, wb_b_pre, wb_c_pre, wb_d_pre;
  logic [WORD_W-1:0] wb_e_pre, wb_f_pre, wb_g_pre, wb_h_pre;
  logic [WORD_W-1:0] wb_a_new, wb_e_new;

  assign wb_a_pre = work_a_q[pipe_lane_q];
  assign wb_b_pre = work_b_q[pipe_lane_q];
  assign wb_c_pre = work_c_q[pipe_lane_q];
  assign wb_d_pre = work_d_q[pipe_lane_q];
  assign wb_e_pre = work_e_q[pipe_lane_q];
  assign wb_f_pre = work_f_q[pipe_lane_q];
  assign wb_g_pre = work_g_q[pipe_lane_q];
  assign wb_h_pre = work_h_q[pipe_lane_q];

  assign wb_a_new = pipe_t1_q + pipe_t2_q;
  assign wb_e_new = wb_d_pre  + pipe_t1_q;

  // ===========================================================================
  // JOB INTAKE (combinational lane selection)
  // ===========================================================================
  // Pick the FREE lane (biased toward lane 0).  Accept a job whenever any
  // lane is free.
  logic load_lane_w;
  logic load_w;

  assign load_lane_w =  lane_busy_q[0];
  assign job_ready   = ~lane_busy_q[0] | ~lane_busy_q[1];
  assign load_w      =  job_valid & job_ready;

  // ===========================================================================
  // FINAL DIGEST (after the final round, IV-add applied)
  // ===========================================================================
  logic [HASH_W-1:0] final_cv_w;

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

  // ===========================================================================
  // PIPELINE REGISTER UPDATES (gearbox style, one always_ff per register)
  // ===========================================================================
  // ---- pipe_valid_q --------------------------------------------------------
  // Mirrors stage_a_run_w one cycle delayed; no separate set/clear.
  always_ff @(posedge clk) begin
    if (~rstn) pipe_valid_q <= 1'b0;
    else       pipe_valid_q <= stage_a_run_w;
  end

  // ---- pipe payload regs (no reset; safe under pipe_valid_q gating) -------
  always_ff @(posedge clk) begin
    pipe_lane_q          <= stage_a_lane_w;
    pipe_round_q         <= round_sa;
    pipe_is_last_round_q <= is_last_round_sa;
    pipe_t1_q            <= t1_sa;
    pipe_t2_q            <= t2_sa;
    pipe_wt_q            <= wt_sa;
  end

  // ===========================================================================
  // OUTPUT SKID UPDATES
  // ===========================================================================
  // A final-round writeback always wins over a consumer pop on the same
  // cycle -- the skid is reloaded with the new digest immediately.
  logic              wb_final_w;
  logic              res_pop_w;
  logic              res_valid_next;
  logic [HASH_W-1:0] res_cv_next;
  logic              res_tag_next;

  assign wb_final_w = pipe_valid_q & pipe_is_last_round_q;
  assign res_pop_w  = res_valid_q  & res_ready;

  // set = wb_final_w, clear = res_pop_w, set wins on collision.
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

  // ===========================================================================
  // PER-LANE STATE UPDATES (replicated via generate)
  // ===========================================================================
  for (genvar L = 0; L < NUM_LANES; L = L + 1) begin : g_lane

    // ---- per-lane control events --------------------------------------------
    logic load_active_w;   // a fresh job is being loaded into THIS lane
    logic wb_normal_w;     // pipe writeback to THIS lane, not the final round
    logic wb_final_lane_w; // pipe writeback to THIS lane on the final round

    assign load_active_w   = load_w        & (load_lane_w == LANE_IDX_W'(L));
    assign wb_normal_w     = pipe_valid_q  & (pipe_lane_q == LANE_IDX_W'(L)) & ~pipe_is_last_round_q;
    assign wb_final_lane_w = pipe_valid_q  & (pipe_lane_q == LANE_IDX_W'(L)) &  pipe_is_last_round_q;

    // ---- lane_busy_q --------------------------------------------------------
    // set = load_active_w, clear = wb_final_lane_w (set wins on collision).
    logic lane_busy_next;
    assign lane_busy_next =
        load_active_w
      | (lane_busy_q[L] & ~wb_final_lane_w);

    always_ff @(posedge clk) begin
      if (~rstn) lane_busy_q[L] <= 1'b0;
      else       lane_busy_q[L] <= lane_busy_next;
    end

    // ---- lane_tag_q  (latched at load) -------------------------------------
    always_ff @(posedge clk) begin
      if (load_active_w) lane_tag_q[L] <= job_tag;
    end

    // ---- round_q  (resets to 0 on load, ++ on normal writeback) ------------
    logic [ROUND_IDX_W-1:0] round_next;
    assign round_next =
        load_active_w
      ? '0
      : ( wb_normal_w
        ? (pipe_round_q + 'd1)
        : round_q[L] );

    always_ff @(posedge clk) begin
      round_q[L] <= round_next;
    end

    // ---- raw_block_q  (latched at load) ------------------------------------
    always_ff @(posedge clk) begin
      if (load_active_w) raw_block_q[L] <= job_block;
    end

    // ---- IV snapshot a..h  (latched at load) -------------------------------
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

    // ---- working state a..h ------------------------------------------------
    // Per-register _next priority: load > final-add > normal-round > hold.
    logic [WORD_W-1:0] work_a_next, work_b_next, work_c_next, work_d_next;
    logic [WORD_W-1:0] work_e_next, work_f_next, work_g_next, work_h_next;

    assign work_a_next =
        load_active_w   ? job_cv_in[HASH_W-1 - 0*WORD_W -: WORD_W] :
        wb_final_lane_w ? final_cv_w[HASH_W-1 - 0*WORD_W -: WORD_W] :
        wb_normal_w     ? wb_a_new                                  :
                          work_a_q[L];

    assign work_b_next =
        load_active_w   ? job_cv_in[HASH_W-1 - 1*WORD_W -: WORD_W] :
        wb_final_lane_w ? final_cv_w[HASH_W-1 - 1*WORD_W -: WORD_W] :
        wb_normal_w     ? wb_a_pre                                  :
                          work_b_q[L];

    assign work_c_next =
        load_active_w   ? job_cv_in[HASH_W-1 - 2*WORD_W -: WORD_W] :
        wb_final_lane_w ? final_cv_w[HASH_W-1 - 2*WORD_W -: WORD_W] :
        wb_normal_w     ? wb_b_pre                                  :
                          work_c_q[L];

    assign work_d_next =
        load_active_w   ? job_cv_in[HASH_W-1 - 3*WORD_W -: WORD_W] :
        wb_final_lane_w ? final_cv_w[HASH_W-1 - 3*WORD_W -: WORD_W] :
        wb_normal_w     ? wb_c_pre                                  :
                          work_d_q[L];

    assign work_e_next =
        load_active_w   ? job_cv_in[HASH_W-1 - 4*WORD_W -: WORD_W] :
        wb_final_lane_w ? final_cv_w[HASH_W-1 - 4*WORD_W -: WORD_W] :
        wb_normal_w     ? wb_e_new                                  :
                          work_e_q[L];

    assign work_f_next =
        load_active_w   ? job_cv_in[HASH_W-1 - 5*WORD_W -: WORD_W] :
        wb_final_lane_w ? final_cv_w[HASH_W-1 - 5*WORD_W -: WORD_W] :
        wb_normal_w     ? wb_e_pre                                  :
                          work_f_q[L];

    assign work_g_next =
        load_active_w   ? job_cv_in[HASH_W-1 - 6*WORD_W -: WORD_W] :
        wb_final_lane_w ? final_cv_w[HASH_W-1 - 6*WORD_W -: WORD_W] :
        wb_normal_w     ? wb_f_pre                                  :
                          work_g_q[L];

    assign work_h_next =
        load_active_w   ? job_cv_in[HASH_W-1 - 7*WORD_W -: WORD_W] :
        wb_final_lane_w ? final_cv_w[HASH_W-1 - 7*WORD_W -: WORD_W] :
        wb_normal_w     ? wb_g_pre                                  :
                          work_h_q[L];

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

    // ---- message schedule window (MSG_SCHED_DEPTH-deep shift register) -----
    // On a normal-round writeback for THIS lane, shift entries 1..15 down
    // into 0..14 and inject pipe_wt_q at index 15.  Otherwise hold.  Post-
    // load contents are don't-care -- rounds 0..15 read raw_block_q.
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

    // ---- kw_pre_q = K[t] + W[t] computed one round ahead --------------------
    // On load:             preload for round 0 = K[0] + word0(block).
    // On normal writeback: compute for round t+1.  W[t+1] is direct from
    //                      block (t+1 < MSG_SCHED_DEPTH) or via the
    //                      recurrence applied to the POST-shift ring
    //                      (= pre-shift indices 1, 2, 10, 15).
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
        sm_sigma1(msg_sched_q[L][15])   // post-shift index 14
      + msg_sched_q[L][10]              // post-shift index  9
      + sm_sigma0 (msg_sched_q[L][ 2])  // post-shift index  1
      + msg_sched_q[L][ 1];             // post-shift index  0

    assign wt_next_w =
        next_round_lt_window_w
      ? wt_next_from_block_w
      : wt_next_from_rec_w;

    assign kw_pre_next =
        load_active_w
      ? (k_round('0) + job_block[BLOCK_W-1 -: WORD_W])
      : ( wb_normal_w
        ? (k_round(next_round_w) + wt_next_w)
        : kw_pre_q[L] );

    always_ff @(posedge clk) begin
      kw_pre_q[L] <= kw_pre_next;
    end

  end : g_lane

  // ===========================================================================
  // OUTPUT DRIVERS
  // ===========================================================================
  assign res_valid  = res_valid_q;
  assign res_cv_out = res_cv_q;
  assign res_tag    = res_tag_q;

endmodule
