// sha256_pkg.sv
//
// Shared SHA-256 constants, parameters, and primitive functions for the
// 2-way pipelined compression engine and its AXI-Stream wrapper.
//
// Anything that is part of the algorithm (FIPS 180-4) or that defines the
// engine's *shape* lives here so the modules below stay free of magic
// numbers and copy-pasted helper functions.

`timescale 1ns/1ps

package sha256_pkg;

  // ===========================================================================
  // ALGORITHM SIZES  (FIPS 180-4)
  // ===========================================================================
  localparam int unsigned WORD_W           = 32;                 // bits / word
  localparam int unsigned HASH_W           = 8  * WORD_W;        // 256
  localparam int unsigned BLOCK_W          = 16 * WORD_W;        // 512
  localparam int unsigned ROUNDS           = 64;
  localparam int unsigned ROUND_IDX_W      = $clog2(ROUNDS);     // 6
  localparam int unsigned MSG_SCHED_DEPTH  = 16;                 // W-window
  localparam int unsigned BLOCK_BYTES      = BLOCK_W / 8;        // 64
  localparam int unsigned HASH_BYTES       = HASH_W  / 8;        // 32

  // ===========================================================================
  // ENGINE SHAPE  (currently fixed; documented as parameters for clarity)
  // ===========================================================================
  // NOTE on NUM_LANES: the engine's stage-A/stage-B scheduler and per-lane
  // index arithmetic are written for 2 lanes only.  Treat this as a
  // documentation constant, not a knob.
  localparam int unsigned NUM_LANES        = 2;
  localparam int unsigned LANE_IDX_W       = $clog2(NUM_LANES);  // 1

  // ===========================================================================
  // AXI-STREAM CARRIER  (sized to XDMA's 128-bit datapath @ 125 MHz)
  // ===========================================================================
  localparam int unsigned AXIS_DATA_W      = 128;
  localparam int unsigned AXIS_KEEP_W      = AXIS_DATA_W / 8;    // 16
  localparam int unsigned BEATS_PER_BLOCK  = BLOCK_W   / AXIS_DATA_W; // 4
  localparam int unsigned BEATS_PER_HASH   = HASH_W    / AXIS_DATA_W; // 2
  localparam int unsigned BEAT_IDX_BLOCK_W = $clog2(BEATS_PER_BLOCK); // 2
  localparam int unsigned BEAT_IDX_HASH_W  = $clog2(BEATS_PER_HASH);  // 1

  // ===========================================================================
  // TYPES
  // ===========================================================================
  // SHA-256 working state a..h.  Packed struct so it can be carried as one
  // signal, indexed by field name, AND implicitly packed/unpacked against
  // a HASH_W-bit vector at port boundaries.  Field order matches the
  // canonical bit layout: a = MSB word, h = LSB word.
  typedef struct packed {
    logic [WORD_W-1:0] a;
    logic [WORD_W-1:0] b;
    logic [WORD_W-1:0] c;
    logic [WORD_W-1:0] d;
    logic [WORD_W-1:0] e;
    logic [WORD_W-1:0] f;
    logic [WORD_W-1:0] g;
    logic [WORD_W-1:0] h;
  } sha_state_t;

  // ===========================================================================
  // INITIAL HASH VALUE H(0)         (FIPS 180-4 §5.3.3)
  // ===========================================================================
  localparam logic [HASH_W-1:0] IV = {
    32'h6a09e667, 32'hbb67ae85, 32'h3c6ef372, 32'ha54ff53a,
    32'h510e527f, 32'h9b05688c, 32'h1f83d9ab, 32'h5be0cd19
  };

  // ===========================================================================
  // PADDING BLOCK for a single full-block message (= BLOCK_BYTES = 64 B):
  //   0x80, (BLOCK_BYTES-1-8) zero bytes, 64-bit big-endian bit-length.
  // ===========================================================================
  localparam int unsigned PAD_ZERO_BYTES   = BLOCK_BYTES - 1 - 8;
  localparam int unsigned PAD_ZERO_BITS    = PAD_ZERO_BYTES * 8;
  localparam logic [BLOCK_W-1:0] PAD_BLOCK_1MSG = {
      8'h80,
      {PAD_ZERO_BITS{1'b0}},
      64'(BLOCK_W)
  };

  // ===========================================================================
  // PRIMITIVE FUNCTIONS             (FIPS 180-4 §4.1.2)
  // ===========================================================================
  function automatic logic [WORD_W-1:0] rotr32(input logic [WORD_W-1:0] x,
                                               input int                n);
    rotr32 = (x >> n) | (x << (WORD_W - n));
  endfunction

  function automatic logic [WORD_W-1:0] ch_efg(input logic [WORD_W-1:0] e,
                                               input logic [WORD_W-1:0] f,
                                               input logic [WORD_W-1:0] g);
    ch_efg = (e & f) ^ (~e & g);
  endfunction

  function automatic logic [WORD_W-1:0] maj_abc(input logic [WORD_W-1:0] a,
                                                input logic [WORD_W-1:0] b,
                                                input logic [WORD_W-1:0] c);
    maj_abc = (a & b) ^ (a & c) ^ (b & c);
  endfunction

  function automatic logic [WORD_W-1:0] big_sigma0(input logic [WORD_W-1:0] a);
    big_sigma0 = rotr32(a, 2) ^ rotr32(a, 13) ^ rotr32(a, 22);
  endfunction

  function automatic logic [WORD_W-1:0] big_sigma1(input logic [WORD_W-1:0] e);
    big_sigma1 = rotr32(e, 6) ^ rotr32(e, 11) ^ rotr32(e, 25);
  endfunction

  function automatic logic [WORD_W-1:0] sm_sigma0(input logic [WORD_W-1:0] w);
    sm_sigma0 = rotr32(w, 7) ^ rotr32(w, 18) ^ (w >> 3);
  endfunction

  function automatic logic [WORD_W-1:0] sm_sigma1(input logic [WORD_W-1:0] w);
    sm_sigma1 = rotr32(w, 17) ^ rotr32(w, 19) ^ (w >> 10);
  endfunction

  // ===========================================================================
  // ROUND CONSTANTS K[0..63]        (FIPS 180-4 §4.2.2)
  // ===========================================================================
  function automatic logic [WORD_W-1:0] k_round(input logic [ROUND_IDX_W-1:0] r);
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
      default: k_round = '0;
    endcase
  endfunction

endpackage : sha256_pkg
