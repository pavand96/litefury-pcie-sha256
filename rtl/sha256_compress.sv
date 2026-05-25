// sha256_compress.sv

`timescale 1ns/1ps

import sha256_pkg::*;

module sha256_compress
(
  input  logic     clk,
  input  logic     rstn,

  input  logic     job_valid,
  output logic     job_ready,
  input  eng_job_t job,

  output logic     res_valid,
  input  logic     res_ready,
  output eng_res_t res
);

  sha_state_t              work_q      [0:NUM_LANES-1];
  sha_state_t              iv_q        [0:NUM_LANES-1];

  logic [BLOCK_W-1:0]      raw_block_q [0:NUM_LANES-1];
  logic [WORD_W-1:0]       msg_sched_q [0:NUM_LANES-1][0:MSG_SCHED_DEPTH-1];
  logic [ROUND_IDX_W-1:0]  round_q     [0:NUM_LANES-1];
  logic                    lane_busy_q [0:NUM_LANES-1];
  logic                    lane_tag_q  [0:NUM_LANES-1];
  logic [WORD_W-1:0]       kw_pre_q    [0:NUM_LANES-1];

  logic                    pipe_valid_q;
  logic                    pipe_lane_q;
  logic [ROUND_IDX_W-1:0]  pipe_round_q;
  logic                    pipe_is_last_round_q;
  logic [WORD_W-1:0]       pipe_t1_q;
  logic [WORD_W-1:0]       pipe_t2_q;
  logic [WORD_W-1:0]       pipe_wt_q;

  logic                    res_valid_q;
  sha_state_t              res_state_q;
  logic                    res_tag_q;

  logic                   load_lane_w;
  logic                   load_w;
  sha_state_t             loaded_w;

  logic                   stage_a_lane_pref_w;
  logic                   stage_a_lane_w;
  logic                   stage_a_lane_busy_w;
  logic                   stage_a_skid_full_w;
  logic                   stage_a_run_w;

  sha_state_t             sa_state_w;
  logic [WORD_W-1:0]      kw_sa;
  logic [ROUND_IDX_W-1:0] round_sa;
  logic                   is_last_round_sa;
  logic                   round_lt_window_sa;
  logic [WORD_W-1:0]      wt_from_block_sa;
  logic [WORD_W-1:0]      wt_recurrence_sa;
  logic [WORD_W-1:0]      wt_sa;
  logic [WORD_W-1:0]      t1_sa;
  logic [WORD_W-1:0]      t2_sa;

  sha_state_t             wb_pre_w;
  sha_state_t             iv_w;
  logic [WORD_W-1:0]      wb_a_new_w;
  logic [WORD_W-1:0]      wb_e_new_w;
  sha_state_t             final_state_w;

  logic                   wb_final_w;
  logic                   res_pop_w;
  logic                   res_valid_next;
  sha_state_t             res_state_next;
  logic                   res_tag_next;

  assign loaded_w    = sha_state_t'(job.cv_in);
  assign load_lane_w = lane_busy_q[0];

  assign job_ready =
      ~lane_busy_q[0]
    | ~lane_busy_q[1];

  assign load_w =
      job_valid
    & job_ready;

  assign stage_a_lane_pref_w = ~lane_busy_q[0];

  assign stage_a_lane_w =
      pipe_valid_q
    ? ~pipe_lane_q
    :  stage_a_lane_pref_w;

  assign stage_a_lane_busy_w = lane_busy_q[stage_a_lane_w];

  assign stage_a_skid_full_w =
      (&round_q[stage_a_lane_w])
    & res_valid_q
    & ~res_ready;

  assign stage_a_run_w =
      stage_a_lane_busy_w
    & ~stage_a_skid_full_w;

  assign sa_state_w = work_q  [stage_a_lane_w];
  assign kw_sa      = kw_pre_q[stage_a_lane_w];
  assign round_sa   = round_q [stage_a_lane_w];

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
      sa_state_w.h
    + big_sigma1(sa_state_w.e)
    + ch_efg    (sa_state_w.e, sa_state_w.f, sa_state_w.g)
    + kw_sa;

  assign t2_sa =
      big_sigma0(sa_state_w.a)
    + maj_abc   (sa_state_w.a, sa_state_w.b, sa_state_w.c);

  always_ff @(posedge clk) begin
    if (~rstn) pipe_valid_q <= 1'b0;
    else       pipe_valid_q <= stage_a_run_w;
  end

  always_ff @(posedge clk) begin
    pipe_lane_q <= stage_a_lane_w;
  end

  always_ff @(posedge clk) begin
    pipe_round_q <= round_sa;
  end

  always_ff @(posedge clk) begin
    pipe_is_last_round_q <= is_last_round_sa;
  end

  always_ff @(posedge clk) begin
    pipe_t1_q <= t1_sa;
  end

  always_ff @(posedge clk) begin
    pipe_t2_q <= t2_sa;
  end

  always_ff @(posedge clk) begin
    pipe_wt_q <= wt_sa;
  end

  assign wb_pre_w = work_q[pipe_lane_q];
  assign iv_w     = iv_q  [pipe_lane_q];

  assign wb_a_new_w =
      pipe_t1_q
    + pipe_t2_q;

  assign wb_e_new_w =
      wb_pre_w.d
    + pipe_t1_q;

  assign final_state_w.a = wb_a_new_w + iv_w.a;
  assign final_state_w.b = wb_pre_w.a + iv_w.b;
  assign final_state_w.c = wb_pre_w.b + iv_w.c;
  assign final_state_w.d = wb_pre_w.c + iv_w.d;
  assign final_state_w.e = wb_e_new_w + iv_w.e;
  assign final_state_w.f = wb_pre_w.e + iv_w.f;
  assign final_state_w.g = wb_pre_w.f + iv_w.g;
  assign final_state_w.h = wb_pre_w.g + iv_w.h;

  assign wb_final_w =
      pipe_valid_q
    & pipe_is_last_round_q;

  assign res_pop_w =
      res_valid_q
    & res_ready;

  assign res_valid_next =
      wb_final_w
    | (res_valid_q & ~res_pop_w);

  assign res_state_next =
      wb_final_w
    ? final_state_w
    : res_state_q;

  assign res_tag_next =
      wb_final_w
    ? lane_tag_q[pipe_lane_q]
    : res_tag_q;

  always_ff @(posedge clk) begin
    if (~rstn) res_valid_q <= 1'b0;
    else       res_valid_q <= res_valid_next;
  end

  always_ff @(posedge clk) begin
    res_state_q <= res_state_next;
  end

  always_ff @(posedge clk) begin
    res_tag_q <= res_tag_next;
  end

  assign res_valid  = res_valid_q;
  assign res.cv_out = res_state_q;
  assign res.tag    = res_tag_q;

  for (genvar L = 0; L < NUM_LANES; L = L + 1) begin : g_lane

    logic                   load_active_w;
    logic                   wb_normal_w;
    logic                   wb_final_lane_w;
    logic                   lane_busy_next;
    logic [ROUND_IDX_W-1:0] round_next;
    sha_state_t             work_next;
    logic [WORD_W-1:0]      kw_pre_next;
    logic [ROUND_IDX_W-1:0] next_round_w;
    logic                   next_round_lt_window_w;
    logic [WORD_W-1:0]      wt_next_from_block_w;
    logic [WORD_W-1:0]      wt_next_from_rec_w;
    logic [WORD_W-1:0]      wt_next_w;

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

    assign lane_busy_next =
        load_active_w
      | (lane_busy_q[L] & ~wb_final_lane_w);

    always_ff @(posedge clk) begin
      if (~rstn) lane_busy_q[L] <= 1'b0;
      else       lane_busy_q[L] <= lane_busy_next;
    end

    always_ff @(posedge clk) begin
      if (load_active_w) raw_block_q[L] <= job.block;
    end

    always_ff @(posedge clk) begin
      if (load_active_w) iv_q[L] <= loaded_w;
    end

    always_ff @(posedge clk) begin
      if (load_active_w) lane_tag_q[L] <= job.tag;
    end

    assign round_next =
        load_active_w
      ? '0
      : wb_normal_w
        ? (pipe_round_q + 'd1)
        : round_q[L];

    always_ff @(posedge clk) begin
      round_q[L] <= round_next;
    end

    assign work_next.a =
        load_active_w
      ? loaded_w.a
      : wb_final_lane_w
        ? final_state_w.a
        : wb_normal_w
          ? wb_a_new_w
          : work_q[L].a;

    assign work_next.b =
        load_active_w
      ? loaded_w.b
      : wb_final_lane_w
        ? final_state_w.b
        : wb_normal_w
          ? wb_pre_w.a
          : work_q[L].b;

    assign work_next.c =
        load_active_w
      ? loaded_w.c
      : wb_final_lane_w
        ? final_state_w.c
        : wb_normal_w
          ? wb_pre_w.b
          : work_q[L].c;

    assign work_next.d =
        load_active_w
      ? loaded_w.d
      : wb_final_lane_w
        ? final_state_w.d
        : wb_normal_w
          ? wb_pre_w.c
          : work_q[L].d;

    assign work_next.e =
        load_active_w
      ? loaded_w.e
      : wb_final_lane_w
        ? final_state_w.e
        : wb_normal_w
          ? wb_e_new_w
          : work_q[L].e;

    assign work_next.f =
        load_active_w
      ? loaded_w.f
      : wb_final_lane_w
        ? final_state_w.f
        : wb_normal_w
          ? wb_pre_w.e
          : work_q[L].f;

    assign work_next.g =
        load_active_w
      ? loaded_w.g
      : wb_final_lane_w
        ? final_state_w.g
        : wb_normal_w
          ? wb_pre_w.f
          : work_q[L].g;

    assign work_next.h =
        load_active_w
      ? loaded_w.h
      : wb_final_lane_w
        ? final_state_w.h
        : wb_normal_w
          ? wb_pre_w.g
          : work_q[L].h;

    always_ff @(posedge clk) begin
      work_q[L] <= work_next;
    end

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
        load_active_w
      ? (k_round('0)           + job.block[BLOCK_W-1 -: WORD_W])
      : wb_normal_w
        ? (k_round(next_round_w) + wt_next_w)
        : kw_pre_q[L];

    always_ff @(posedge clk) begin
      kw_pre_q[L] <= kw_pre_next;
    end

  end : g_lane

endmodule
