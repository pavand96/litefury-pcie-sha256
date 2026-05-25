// sha256_compress.sv
//
// Iterative SHA-256 compression function (FIPS 180-4 §6.2).
// One 512-bit message block is consumed and the 256-bit chaining value (CV)
// is updated. The user provides the initial chaining value (CV_in) so this
// module can be chained across multiple blocks.
//
// Latency  : 64 round cycles + 1 setup cycle + 1 done cycle = 66 cycles.
// Interface: ready/valid pulse-style job handshake
//              - on the cycle `start` is asserted, `block` and `cv_in` are
//                captured, `ready` falls.
//              - 66 cycles later `done` pulses high for 1 cycle with the new
//                CV on `cv_out`, and `ready` returns high.
//
// Style: SystemVerilog with explicit _q / _next signals, named generates,
// async-low reset (rstn) — matches the Generic_Parameterized_Modules
// gearbox coding conventions.
//

`timescale 1ns/1ps

module sha256_compress
(
  input  logic           clk,
  input  logic           rstn,

  // Job-input handshake
  input  logic           start,
  input  logic [511:0]   block,    // 16 × 32b big-endian words, word[0] in MSBs
  input  logic [255:0]   cv_in,    // {a,b,c,d,e,f,g,h} on entry, a in MSBs
  output logic           ready,

  // Job-output
  output logic           done,
  output logic [255:0]   cv_out
);

  // ---------------------------------------------------------------------------
  // K constants (FIPS 180-4 §4.2.2)
  // ---------------------------------------------------------------------------
  function automatic logic [31:0] K_const(input logic [5:0] t);
    case (t)
      6'd00: K_const = 32'h428a2f98; 6'd01: K_const = 32'h71374491;
      6'd02: K_const = 32'hb5c0fbcf; 6'd03: K_const = 32'he9b5dba5;
      6'd04: K_const = 32'h3956c25b; 6'd05: K_const = 32'h59f111f1;
      6'd06: K_const = 32'h923f82a4; 6'd07: K_const = 32'hab1c5ed5;
      6'd08: K_const = 32'hd807aa98; 6'd09: K_const = 32'h12835b01;
      6'd10: K_const = 32'h243185be; 6'd11: K_const = 32'h550c7dc3;
      6'd12: K_const = 32'h72be5d74; 6'd13: K_const = 32'h80deb1fe;
      6'd14: K_const = 32'h9bdc06a7; 6'd15: K_const = 32'hc19bf174;
      6'd16: K_const = 32'he49b69c1; 6'd17: K_const = 32'hefbe4786;
      6'd18: K_const = 32'h0fc19dc6; 6'd19: K_const = 32'h240ca1cc;
      6'd20: K_const = 32'h2de92c6f; 6'd21: K_const = 32'h4a7484aa;
      6'd22: K_const = 32'h5cb0a9dc; 6'd23: K_const = 32'h76f988da;
      6'd24: K_const = 32'h983e5152; 6'd25: K_const = 32'ha831c66d;
      6'd26: K_const = 32'hb00327c8; 6'd27: K_const = 32'hbf597fc7;
      6'd28: K_const = 32'hc6e00bf3; 6'd29: K_const = 32'hd5a79147;
      6'd30: K_const = 32'h06ca6351; 6'd31: K_const = 32'h14292967;
      6'd32: K_const = 32'h27b70a85; 6'd33: K_const = 32'h2e1b2138;
      6'd34: K_const = 32'h4d2c6dfc; 6'd35: K_const = 32'h53380d13;
      6'd36: K_const = 32'h650a7354; 6'd37: K_const = 32'h766a0abb;
      6'd38: K_const = 32'h81c2c92e; 6'd39: K_const = 32'h92722c85;
      6'd40: K_const = 32'ha2bfe8a1; 6'd41: K_const = 32'ha81a664b;
      6'd42: K_const = 32'hc24b8b70; 6'd43: K_const = 32'hc76c51a3;
      6'd44: K_const = 32'hd192e819; 6'd45: K_const = 32'hd6990624;
      6'd46: K_const = 32'hf40e3585; 6'd47: K_const = 32'h106aa070;
      6'd48: K_const = 32'h19a4c116; 6'd49: K_const = 32'h1e376c08;
      6'd50: K_const = 32'h2748774c; 6'd51: K_const = 32'h34b0bcb5;
      6'd52: K_const = 32'h391c0cb3; 6'd53: K_const = 32'h4ed8aa4a;
      6'd54: K_const = 32'h5b9cca4f; 6'd55: K_const = 32'h682e6ff3;
      6'd56: K_const = 32'h748f82ee; 6'd57: K_const = 32'h78a5636f;
      6'd58: K_const = 32'h84c87814; 6'd59: K_const = 32'h8cc70208;
      6'd60: K_const = 32'h90befffa; 6'd61: K_const = 32'ha4506ceb;
      6'd62: K_const = 32'hbef9a3f7; 6'd63: K_const = 32'hc67178f2;
      default: K_const = 32'h0;
    endcase
  endfunction

  // ---------------------------------------------------------------------------
  // SHA-256 primitive functions (FIPS 180-4 §4.1.2)
  // ---------------------------------------------------------------------------
  function automatic logic [31:0] rotr(input logic [31:0] x, input int n);
    rotr = (x >> n) | (x << (32 - n));
  endfunction
  function automatic logic [31:0] shr (input logic [31:0] x, input int n);
    shr  = (x >> n);
  endfunction
  function automatic logic [31:0] Ch (input logic [31:0] x,y,z);
    Ch  = (x & y) ^ (~x & z);
  endfunction
  function automatic logic [31:0] Maj(input logic [31:0] x,y,z);
    Maj = (x & y) ^ (x & z) ^ (y & z);
  endfunction
  function automatic logic [31:0] BigS0(input logic [31:0] x);
    BigS0 = rotr(x,2)  ^ rotr(x,13) ^ rotr(x,22);
  endfunction
  function automatic logic [31:0] BigS1(input logic [31:0] x);
    BigS1 = rotr(x,6)  ^ rotr(x,11) ^ rotr(x,25);
  endfunction
  function automatic logic [31:0] SmS0 (input logic [31:0] x);
    SmS0  = rotr(x,7)  ^ rotr(x,18) ^ shr(x,3);
  endfunction
  function automatic logic [31:0] SmS1 (input logic [31:0] x);
    SmS1  = rotr(x,17) ^ rotr(x,19) ^ shr(x,10);
  endfunction

  // ---------------------------------------------------------------------------
  // Working state
  // ---------------------------------------------------------------------------
  // Working variables a..h (a = MSB-side of cv).
  logic [31:0] a_q, b_q, c_q, d_q, e_q, f_q, g_q, h_q;

  // Initial chaining value snapshotted at start, used for the final add.
  logic [31:0] av_q, bv_q, cv_q, dv_q, ev_q, fv_q, gv_q, hv_q;

  // Sliding 16-deep message schedule window. W_q[0] = W[t-16] when computing
  // W[t]; W_q[15] = W[t-1]. We shift up on every round and inject the next W
  // value at index 15 (or the raw block for the first 16 rounds).
  logic [31:0] W_q [0:15];

  // Round counter 0..63. Valid while busy_q.
  logic [5:0]  t_q;
  logic        busy_q;
  logic        done_q;

  // ---------------------------------------------------------------------------
  // Combinational: compute next W and one round update
  // ---------------------------------------------------------------------------
  // Next W to use this round. For t<16 we pull a word directly from `block`.
  // For t>=16 we recompute Wt = SmS1(W_q[14]) + W_q[9] + SmS0(W_q[1]) + W_q[0].
  //   (because before the shift, W_q[15]=W[t-1], W_q[14]=W[t-2], W_q[9]=W[t-7],
  //    W_q[1]=W[t-15], W_q[0]=W[t-16].)
  logic [31:0] Wt;
  logic [31:0] Wt_from_block;
  // block is treated as 16 big-endian words: word 0 occupies bits [511:480].
  assign Wt_from_block = block[ 511 - 32*t_q -: 32 ];
  assign Wt = (t_q < 6'd16)
            ?  Wt_from_block
            :  (SmS1(W_q[14]) + W_q[9] + SmS0(W_q[1]) + W_q[0]);

  // T1, T2 use Wt and the current working state.
  logic [31:0] T1, T2;
  assign T1 = h_q + BigS1(e_q) + Ch(e_q,f_q,g_q) + K_const(t_q) + Wt;
  assign T2 = BigS0(a_q) + Maj(a_q,b_q,c_q);

  // ---------------------------------------------------------------------------
  // FSM
  // ---------------------------------------------------------------------------
  assign ready  = ~busy_q;
  assign done   = done_q;
  assign cv_out = {a_q,b_q,c_q,d_q,e_q,f_q,g_q,h_q};

  integer i;
  always_ff @(posedge clk or negedge rstn) begin
    if (!rstn) begin
      busy_q <= 1'b0;
      done_q <= 1'b0;
      t_q    <= 6'd0;
      a_q <= '0; b_q <= '0; c_q <= '0; d_q <= '0;
      e_q <= '0; f_q <= '0; g_q <= '0; h_q <= '0;
      av_q<= '0; bv_q<= '0; cv_q<= '0; dv_q<= '0;
      ev_q<= '0; fv_q<= '0; gv_q<= '0; hv_q<= '0;
      for (i = 0; i < 16; i = i + 1) W_q[i] <= '0;
    end
    else begin
      done_q <= 1'b0;

      if (!busy_q && start) begin
        // Load working variables from cv_in. cv_in is {a,b,c,d,e,f,g,h} packed
        // with a in the MSBs.
        a_q  <= cv_in[255:224]; av_q <= cv_in[255:224];
        b_q  <= cv_in[223:192]; bv_q <= cv_in[223:192];
        c_q  <= cv_in[191:160]; cv_q <= cv_in[191:160];
        d_q  <= cv_in[159:128]; dv_q <= cv_in[159:128];
        e_q  <= cv_in[127: 96]; ev_q <= cv_in[127: 96];
        f_q  <= cv_in[ 95: 64]; fv_q <= cv_in[ 95: 64];
        g_q  <= cv_in[ 63: 32]; gv_q <= cv_in[ 63: 32];
        h_q  <= cv_in[ 31:  0]; hv_q <= cv_in[ 31:  0];
        t_q    <= 6'd0;
        busy_q <= 1'b1;
        // W_q irrelevant on round 0 (Wt comes from block).
      end
      else if (busy_q) begin
        // One round per cycle: update a..h.
        h_q <= g_q;
        g_q <= f_q;
        f_q <= e_q;
        e_q <= d_q + T1;
        d_q <= c_q;
        c_q <= b_q;
        b_q <= a_q;
        a_q <= T1 + T2;

        // Shift the W window up and inject Wt at the top.
        for (i = 0; i < 15; i = i + 1) W_q[i] <= W_q[i+1];
        W_q[15] <= Wt;

        if (t_q == 6'd63) begin
          // Final add: a..h += av..hv, then signal done. Captured in the same
          // cycle that we'd otherwise advance to t=64; we use the snapshot.
          a_q <= (T1 + T2)       + av_q;
          b_q <= a_q             + bv_q;
          c_q <= b_q             + cv_q;
          d_q <= c_q             + dv_q;
          e_q <= (d_q + T1)      + ev_q;
          f_q <= e_q             + fv_q;
          g_q <= f_q             + gv_q;
          h_q <= g_q             + hv_q;
          busy_q <= 1'b0;
          done_q <= 1'b1;
        end
        else begin
          t_q <= t_q + 6'd1;
        end
      end
    end
  end

endmodule
