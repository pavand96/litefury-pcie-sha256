// sha256_compress.sv
//
// 2-way interleaved, 2-stage pipelined SHA-256 compression engine.
//
// One 512-bit block is consumed per job and the 256-bit chaining value (CV)
// is updated.  The user provides the IV (or previous CV) per job, so this
// module can be chained across blocks.
//
// Style: gearbox.  All combinational logic in `assign`; every register has
// its own small `always_ff` block driven from a pre-computed `*_next`
// signal.  Per-lane state is replicated via a `generate` over the 2 lanes.
//
// =============================================================================
// PIPELINE OVERVIEW (why two stages + two interleaved lanes)
// =============================================================================
// A naive SHA-256 round is a 6-input adder tree (h + BigSig1 + Ch + K + W +
// BigSig0 + Maj) that maps to ~10.7 ns on Artix-7 -2L — too slow for 8 ns
// (125 MHz).  We:
//   1) precompute kw_pre = K[t] + W[t] one round ahead, dropping T1 to a
//      4-input add (h + BigSig1 + Ch + kw_pre),
//   2) register T1, T2 into a pipe and do the final 1-add writeback the next
//      cycle (a_new = T1+T2, e_new = d + T1),
//   3) interleave two independent jobs ("lanes") through the same fabric so
//      stage A and stage B always operate on DIFFERENT lanes (no
//      read-after-write bubble).
//
// Aggregate throughput in steady state = 1 round / cycle.
// Per lane = 64 rounds * 2 cycles + 1 load + 1 emit  = 130 cycles / block.
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

module sha256_compress
(
  input  logic           clk,
  input  logic           rstn,

  // Job input handshake ------------------------------------------------------
  input  logic           job_valid,
  output logic           job_ready,
  input  logic [511:0]   job_block,    // 16 big-endian 32-bit words, word0=MSB
  input  logic [255:0]   job_cv_in,    // {a,b,c,d,e,f,g,h}, a in MSBs
  input  logic           job_tag,

  // Result output handshake --------------------------------------------------
  output logic           res_valid,
  input  logic           res_ready,
  output logic [255:0]   res_cv_out,
  output logic           res_tag
);

  // ===========================================================================
  // SHA-256 round constants K[0..63]  (FIPS 180-4 §4.2.2)
  // ===========================================================================
  function automatic logic [31:0] k_round(input logic [5:0] r);
    case (r)
      6'd00: k_round = 32'h428a2f98; 6'd01: k_round = 32'h71374491;
      6'd02: k_round = 32'hb5c0fbcf; 6'd03: k_round = 32'he9b5dba5;
      6'd04: k_round = 32'h3956c25b; 6'd05: k_round = 32'h59f111f1;
      6'd06: k_round = 32'h923f82a4; 6'd07: k_round = 32'hab1c5ed5;
      6'd08: k_round = 32'hd807aa98; 6'd09: k_round = 32'h12835b01;
      6'd10: k_round = 32'h243185be; 6'd11: k_round = 32'h550c7dc3;
      6'd12: k_round = 32'h72be5d74; 6'd13: k_round = 32'h80deb1fe;
      6'd14: k_round = 32'h9bdc06a7; 6'd15: k_round = 32'hc19bf174;
      6'd16: k_round = 32'he49b69c1; 6'd17: k_round = 32'hefbe4786;
      6'd18: k_round = 32'h0fc19dc6; 6'd19: k_round = 32'h240ca1cc;
      6'd20: k_round = 32'h2de92c6f; 6'd21: k_round = 32'h4a7484aa;
      6'd22: k_round = 32'h5cb0a9dc; 6'd23: k_round = 32'h76f988da;
      6'd24: k_round = 32'h983e5152; 6'd25: k_round = 32'ha831c66d;
      6'd26: k_round = 32'hb00327c8; 6'd27: k_round = 32'hbf597fc7;
      6'd28: k_round = 32'hc6e00bf3; 6'd29: k_round = 32'hd5a79147;
      6'd30: k_round = 32'h06ca6351; 6'd31: k_round = 32'h14292967;
      6'd32: k_round = 32'h27b70a85; 6'd33: k_round = 32'h2e1b2138;
      6'd34: k_round = 32'h4d2c6dfc; 6'd35: k_round = 32'h53380d13;
      6'd36: k_round = 32'h650a7354; 6'd37: k_round = 32'h766a0abb;
      6'd38: k_round = 32'h81c2c92e; 6'd39: k_round = 32'h92722c85;
      6'd40: k_round = 32'ha2bfe8a1; 6'd41: k_round = 32'ha81a664b;
      6'd42: k_round = 32'hc24b8b70; 6'd43: k_round = 32'hc76c51a3;
      6'd44: k_round = 32'hd192e819; 6'd45: k_round = 32'hd6990624;
      6'd46: k_round = 32'hf40e3585; 6'd47: k_round = 32'h106aa070;
      6'd48: k_round = 32'h19a4c116; 6'd49: k_round = 32'h1e376c08;
      6'd50: k_round = 32'h2748774c; 6'd51: k_round = 32'h34b0bcb5;
      6'd52: k_round = 32'h391c0cb3; 6'd53: k_round = 32'h4ed8aa4a;
      6'd54: k_round = 32'h5b9cca4f; 6'd55: k_round = 32'h682e6ff3;
      6'd56: k_round = 32'h748f82ee; 6'd57: k_round = 32'h78a5636f;
      6'd58: k_round = 32'h84c87814; 6'd59: k_round = 32'h8cc70208;
      6'd60: k_round = 32'h90befffa; 6'd61: k_round = 32'ha4506ceb;
      6'd62: k_round = 32'hbef9a3f7; 6'd63: k_round = 32'hc67178f2;
      default: k_round = 32'h0;
    endcase
  endfunction

  // ===========================================================================
  // SHA-256 primitive functions  (FIPS 180-4 §4.1.2)
  // ===========================================================================
  function automatic logic [31:0] rotr32(input logic [31:0] x, input int n);
    rotr32 = (x >> n) | (x << (32 - n));
  endfunction
  function automatic logic [31:0] ch_efg     (input logic [31:0] e, f, g);
    ch_efg     = (e & f) ^ (~e & g);
  endfunction
  function automatic logic [31:0] maj_abc    (input logic [31:0] a, b, c);
    maj_abc    = (a & b) ^ (a & c) ^ (b & c);
  endfunction
  function automatic logic [31:0] big_sigma0 (input logic [31:0] a);
    big_sigma0 = rotr32(a, 2) ^ rotr32(a,13) ^ rotr32(a,22);
  endfunction
  function automatic logic [31:0] big_sigma1 (input logic [31:0] e);
    big_sigma1 = rotr32(e, 6) ^ rotr32(e,11) ^ rotr32(e,25);
  endfunction
  function automatic logic [31:0] sm_sigma0  (input logic [31:0] w);
    sm_sigma0  = rotr32(w, 7) ^ rotr32(w,18) ^ (w >> 3);
  endfunction
  function automatic logic [31:0] sm_sigma1  (input logic [31:0] w);
    sm_sigma1  = rotr32(w,17) ^ rotr32(w,19) ^ (w >>10);
  endfunction

  // ===========================================================================
  // PER-LANE STATE  (replicated via generate)
  // ===========================================================================
  logic [31:0] work_a_q   [0:1], work_b_q [0:1], work_c_q [0:1], work_d_q [0:1];
  logic [31:0] work_e_q   [0:1], work_f_q [0:1], work_g_q [0:1], work_h_q [0:1];
  logic [31:0] iv_a_q     [0:1], iv_b_q   [0:1], iv_c_q   [0:1], iv_d_q   [0:1];
  logic [31:0] iv_e_q     [0:1], iv_f_q   [0:1], iv_g_q   [0:1], iv_h_q   [0:1];
  logic [511:0] raw_block_q [0:1];
  logic [31:0] msg_sched_q [0:1][0:15];
  logic [5:0]  round_q     [0:1];
  logic        lane_busy_q [0:1];
  logic        lane_tag_q  [0:1];
  logic [31:0] kw_pre_q    [0:1];

  // ===========================================================================
  // PIPELINE REGISTERS  (stage A -> stage B)
  // ===========================================================================
  logic         pipe_valid_q;
  logic         pipe_lane_q;
  logic [5:0]   pipe_round_q;
  logic         pipe_is_last_round_q;
  logic [31:0]  pipe_t1_q;
  logic [31:0]  pipe_t2_q;
  logic [31:0]  pipe_wt_q;

  // ===========================================================================
  // OUTPUT SKID  (1 deep)
  // ===========================================================================
  logic         res_valid_q;
  logic [255:0] res_cv_q;
  logic         res_tag_q;

  // ===========================================================================
  // STAGE SCHEDULING  (pure combinational)
  // ===========================================================================
  // Pick the lane stage A operates on this cycle.  When the pipe is full,
  // we MUST pick the lane the pipe does not own (stage B will write that
  // lane on the same cycle).  When pipe is empty, prefer lane 0.
  logic stage_a_lane_pref_w;
  logic stage_a_lane_w;
  logic stage_a_lane_busy_w;
  logic stage_a_skid_full_w;
  logic stage_a_run_w;

  assign stage_a_lane_pref_w =
      lane_busy_q[0]
    ? 1'b0
    : 1'b1;

  assign stage_a_lane_w =
      pipe_valid_q
    ? ~pipe_lane_q
    :  stage_a_lane_pref_w;

  assign stage_a_lane_busy_w = lane_busy_q[stage_a_lane_w];

  // Block stage A on round 63 if the skid is still holding a previous
  // digest the consumer has not popped yet (would otherwise be clobbered).
  assign stage_a_skid_full_w =
      (round_q[stage_a_lane_w] == 6'd63)
    &  res_valid_q
    & ~res_ready;

  assign stage_a_run_w =
      stage_a_lane_busy_w
    & ~stage_a_skid_full_w;

  // ===========================================================================
  // STAGE A  —  T1, T2, Wt (looked up from the selected lane's state)
  // ===========================================================================
  logic [31:0] a_sa, b_sa, c_sa, d_sa, e_sa, f_sa, g_sa, h_sa;
  logic [31:0] kw_sa;
  logic [5:0]  round_sa;
  logic        is_last_round_sa;
  logic [31:0] wt_from_block_sa;
  logic [31:0] wt_recurrence_sa;
  logic [31:0] wt_sa;
  logic [31:0] t1_sa;
  logic [31:0] t2_sa;

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
  assign is_last_round_sa = (round_sa == 6'd63);

  assign wt_from_block_sa = raw_block_q[stage_a_lane_w][511 - 32*round_sa -: 32];
  assign wt_recurrence_sa =
      sm_sigma1(msg_sched_q[stage_a_lane_w][14])
    + msg_sched_q[stage_a_lane_w][ 9]
    + sm_sigma0 (msg_sched_q[stage_a_lane_w][ 1])
    + msg_sched_q[stage_a_lane_w][ 0];

  assign wt_sa =
      (round_sa < 6'd16)
    ? wt_from_block_sa
    : wt_recurrence_sa;

  // 4-input add for T1.
  assign t1_sa = h_sa + big_sigma1(e_sa) + ch_efg (e_sa, f_sa, g_sa) + kw_sa;
  assign t2_sa =        big_sigma0(a_sa) + maj_abc(a_sa, b_sa, c_sa);

  // ===========================================================================
  // STAGE B  —  writeback helpers (pre/new state on pipe_lane_q)
  // ===========================================================================
  logic [31:0] wb_a_pre, wb_b_pre, wb_c_pre, wb_d_pre;
  logic [31:0] wb_e_pre, wb_f_pre, wb_g_pre, wb_h_pre;
  logic [31:0] wb_a_new, wb_e_new;

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
  // JOB INTAKE  (combinational lane selection)
  // ===========================================================================
  logic load_lane_w;
  logic load_w;

  assign load_lane_w =
      lane_busy_q[0]
    ? 1'b1
    : 1'b0;

  assign load_w    = job_valid & job_ready;
  assign job_ready = ~lane_busy_q[0] | ~lane_busy_q[1];

  // ===========================================================================
  // FINAL DIGEST (after-the-final-round, IV-add applied)
  // ===========================================================================
  logic [255:0] final_cv_w;

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
  // PIPELINE REGISTER UPDATES  (one always_ff per register, gearbox style)
  // ===========================================================================
  always_ff @(posedge clk or negedge rstn) begin
    if (~rstn) pipe_valid_q         <= 1'b0;
    else       pipe_valid_q         <= stage_a_run_w;
  end
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
  // cycle — the skid is reloaded with the new digest immediately.
  logic         wb_final_w;
  logic         res_pop_w;
  logic         res_valid_next;
  logic [255:0] res_cv_next;
  logic         res_tag_next;

  assign wb_final_w = pipe_valid_q & pipe_is_last_round_q;
  assign res_pop_w  = res_valid_q  & res_ready;

  assign res_valid_next =
      wb_final_w
    ? 1'b1
    : ( res_pop_w
      ? 1'b0
      : res_valid_q );

  assign res_cv_next =
      wb_final_w
    ? final_cv_w
    : res_cv_q;

  assign res_tag_next =
      wb_final_w
    ? lane_tag_q[pipe_lane_q]
    : res_tag_q;

  always_ff @(posedge clk or negedge rstn) begin
    if (~rstn) res_valid_q <= 1'b0;
    else       res_valid_q <= res_valid_next;
  end
  always_ff @(posedge clk) begin
    res_cv_q  <= res_cv_next;
    res_tag_q <= res_tag_next;
  end

  // ===========================================================================
  // PER-LANE STATE UPDATES  (replicated via generate)
  // ===========================================================================
  for (genvar L = 0; L < 2; L = L + 1) begin : g_lane

    // ---- per-lane control events --------------------------------------------
    logic load_active_w;   // a fresh job is being loaded into THIS lane
    logic wb_normal_w;     // pipe writeback to THIS lane, not the final round
    logic wb_final_lane_w; // pipe writeback to THIS lane on round 63

    assign load_active_w   = load_w & (load_lane_w == 1'(L));
    assign wb_normal_w     = pipe_valid_q & (pipe_lane_q == 1'(L)) & ~pipe_is_last_round_q;
    assign wb_final_lane_w = pipe_valid_q & (pipe_lane_q == 1'(L)) &  pipe_is_last_round_q;

    // ---- lane occupancy + tag ----------------------------------------------
    logic lane_busy_next;
    logic lane_tag_next;

    assign lane_busy_next =
        load_active_w
      ? 1'b1
      : ( wb_final_lane_w
        ? 1'b0
        : lane_busy_q[L] );

    assign lane_tag_next =
        load_active_w
      ? job_tag
      : lane_tag_q[L];

    always_ff @(posedge clk or negedge rstn) begin
      if (~rstn) lane_busy_q[L] <= 1'b0;
      else       lane_busy_q[L] <= lane_busy_next;
    end
    always_ff @(posedge clk) begin
      lane_tag_q[L] <= lane_tag_next;
    end

    // ---- round counter ------------------------------------------------------
    logic [5:0] round_next;
    assign round_next =
        load_active_w
      ? 6'd0
      : ( wb_normal_w
        ? (pipe_round_q + 6'd1)
        : round_q[L] );

    always_ff @(posedge clk) begin
      round_q[L] <= round_next;
    end

    // ---- raw block ----------------------------------------------------------
    logic [511:0] raw_block_next;
    assign raw_block_next =
        load_active_w
      ? job_block
      : raw_block_q[L];

    always_ff @(posedge clk) begin
      raw_block_q[L] <= raw_block_next;
    end

    // ---- IV snapshot (8 words) ---------------------------------------------
    always_ff @(posedge clk) begin
      if (load_active_w) begin
        iv_a_q[L] <= job_cv_in[255:224];
        iv_b_q[L] <= job_cv_in[223:192];
        iv_c_q[L] <= job_cv_in[191:160];
        iv_d_q[L] <= job_cv_in[159:128];
        iv_e_q[L] <= job_cv_in[127: 96];
        iv_f_q[L] <= job_cv_in[ 95: 64];
        iv_g_q[L] <= job_cv_in[ 63: 32];
        iv_h_q[L] <= job_cv_in[ 31:  0];
      end
    end

    // ---- working state a..h -------------------------------------------------
    // Per-register _next: load > final-add > normal-round > hold.
    logic [31:0] work_a_next, work_b_next, work_c_next, work_d_next;
    logic [31:0] work_e_next, work_f_next, work_g_next, work_h_next;

    assign work_a_next =
        load_active_w   ? job_cv_in[255:224] :
        wb_final_lane_w ? final_cv_w[255:224] :
        wb_normal_w     ? wb_a_new            :
                          work_a_q[L];

    assign work_b_next =
        load_active_w   ? job_cv_in[223:192] :
        wb_final_lane_w ? final_cv_w[223:192] :
        wb_normal_w     ? wb_a_pre            :
                          work_b_q[L];

    assign work_c_next =
        load_active_w   ? job_cv_in[191:160] :
        wb_final_lane_w ? final_cv_w[191:160] :
        wb_normal_w     ? wb_b_pre            :
                          work_c_q[L];

    assign work_d_next =
        load_active_w   ? job_cv_in[159:128] :
        wb_final_lane_w ? final_cv_w[159:128] :
        wb_normal_w     ? wb_c_pre            :
                          work_d_q[L];

    assign work_e_next =
        load_active_w   ? job_cv_in[127: 96] :
        wb_final_lane_w ? final_cv_w[127: 96] :
        wb_normal_w     ? wb_e_new            :
                          work_e_q[L];

    assign work_f_next =
        load_active_w   ? job_cv_in[ 95: 64] :
        wb_final_lane_w ? final_cv_w[ 95: 64] :
        wb_normal_w     ? wb_e_pre            :
                          work_f_q[L];

    assign work_g_next =
        load_active_w   ? job_cv_in[ 63: 32] :
        wb_final_lane_w ? final_cv_w[ 63: 32] :
        wb_normal_w     ? wb_f_pre            :
                          work_g_q[L];

    assign work_h_next =
        load_active_w   ? job_cv_in[ 31:  0] :
        wb_final_lane_w ? final_cv_w[ 31:  0] :
        wb_normal_w     ? wb_g_pre            :
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

    // ---- message schedule window (16-deep shift, inject pipe_wt_q) ----------
    // On a normal-round writeback for THIS lane, shift entries 1..15 down
    // into 0..14 and inject pipe_wt_q at index 15.  On load or hold, keep
    // current contents (post-load contents are don't-care; round 0..15 uses
    // raw_block_q directly).
    for (genvar I = 0; I < 16; I = I + 1) begin : g_msg_sched
      logic [31:0] msg_sched_next;
      if (I == 15) begin : g_inject
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

    // ---- kw_pre = K[t] + W[t] one round ahead ------------------------------
    // On load:  preload for round 0           = K[0] + word0(block).
    // On normal writeback: precompute for round t+1.  W[t+1] is either
    //                     direct (t+1 < 16) or via the recurrence applied
    //                     to the POST-shift ring (= pre-shift indices 1, 2,
    //                     10, 15).
    logic [31:0] kw_pre_next;
    logic [5:0]  next_round_w;
    logic [31:0] wt_next_from_block_w;
    logic [31:0] wt_next_from_rec_w;
    logic [31:0] wt_next_w;

    assign next_round_w         = pipe_round_q + 6'd1;
    assign wt_next_from_block_w = raw_block_q[L][511 - 32*next_round_w -: 32];
    assign wt_next_from_rec_w   =
        sm_sigma1(msg_sched_q[L][15])   // post-shift index 14
      + msg_sched_q[L][10]              // post-shift index  9
      + sm_sigma0 (msg_sched_q[L][ 2])  // post-shift index  1
      + msg_sched_q[L][ 1];             // post-shift index  0
    assign wt_next_w =
        (next_round_w < 6'd16)
      ? wt_next_from_block_w
      : wt_next_from_rec_w;

    assign kw_pre_next =
        load_active_w
      ? (k_round(6'd0) + job_block[511:480])
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
