// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(aclk,0,0);
        VL_IN8(aresetn,0,0);
        VL_IN8(s_axis_tvalid,0,0);
        VL_OUT8(s_axis_tready,0,0);
        VL_IN8(s_axis_tlast,0,0);
        VL_OUT8(m_axis_tvalid,0,0);
        VL_IN8(m_axis_tready,0,0);
        VL_OUT8(m_axis_tlast,0,0);
        CData/*0:0*/ sha256_stream__DOT__aclk;
        CData/*0:0*/ sha256_stream__DOT__aresetn;
        CData/*0:0*/ sha256_stream__DOT__s_axis_tvalid;
        CData/*0:0*/ sha256_stream__DOT__s_axis_tready;
        CData/*0:0*/ sha256_stream__DOT__s_axis_tlast;
        CData/*0:0*/ sha256_stream__DOT__m_axis_tvalid;
        CData/*0:0*/ sha256_stream__DOT__m_axis_tready;
        CData/*0:0*/ sha256_stream__DOT__m_axis_tlast;
        CData/*0:0*/ sha256_stream__DOT__core_start;
        CData/*0:0*/ sha256_stream__DOT__core_ready;
        CData/*0:0*/ sha256_stream__DOT__core_done;
        CData/*2:0*/ sha256_stream__DOT__rx_state_q;
        CData/*1:0*/ sha256_stream__DOT__beat_idx_q;
        CData/*0:0*/ sha256_stream__DOT__digest_valid_q;
        CData/*0:0*/ sha256_stream__DOT__start_pulse;
        CData/*0:0*/ sha256_stream__DOT__tx_consume_digest;
        CData/*1:0*/ sha256_stream__DOT__tx_state_q;
        CData/*0:0*/ sha256_stream__DOT__u_core__DOT__clk;
        CData/*0:0*/ sha256_stream__DOT__u_core__DOT__rstn;
        CData/*0:0*/ sha256_stream__DOT__u_core__DOT__start;
        CData/*0:0*/ sha256_stream__DOT__u_core__DOT__ready;
        CData/*0:0*/ sha256_stream__DOT__u_core__DOT__done;
        CData/*5:0*/ sha256_stream__DOT__u_core__DOT__t_q;
        CData/*0:0*/ sha256_stream__DOT__u_core__DOT__busy_q;
        CData/*0:0*/ sha256_stream__DOT__u_core__DOT__done_q;
        CData/*5:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__aclk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__aresetn__0;
        CData/*0:0*/ __VactContinue;
        VL_IN16(s_axis_tkeep,15,0);
        VL_OUT16(m_axis_tkeep,15,0);
        SData/*15:0*/ sha256_stream__DOT__s_axis_tkeep;
        SData/*15:0*/ sha256_stream__DOT__m_axis_tkeep;
        VL_INW(s_axis_tdata,127,0,4);
        VL_OUTW(m_axis_tdata,127,0,4);
        VlWide<4>/*127:0*/ sha256_stream__DOT__s_axis_tdata;
        VlWide<4>/*127:0*/ sha256_stream__DOT__m_axis_tdata;
        VlWide<16>/*511:0*/ sha256_stream__DOT__core_block;
        VlWide<8>/*255:0*/ sha256_stream__DOT__core_cv_in;
        VlWide<8>/*255:0*/ sha256_stream__DOT__core_cv_out;
        VlWide<16>/*511:0*/ sha256_stream__DOT__msg_q;
        VlWide<8>/*255:0*/ sha256_stream__DOT__digest_q;
        VlWide<16>/*511:0*/ sha256_stream__DOT__start_block;
        VlWide<8>/*255:0*/ sha256_stream__DOT__start_cv;
        VlWide<16>/*511:0*/ sha256_stream__DOT__u_core__DOT__block;
        VlWide<8>/*255:0*/ sha256_stream__DOT__u_core__DOT__cv_in;
        VlWide<8>/*255:0*/ sha256_stream__DOT__u_core__DOT__cv_out;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__a_q;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__b_q;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__c_q;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__d_q;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__e_q;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__f_q;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__g_q;
    };
    struct {
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__h_q;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__av_q;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__bv_q;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__cv_q;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__dv_q;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__ev_q;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__fv_q;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__gv_q;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__hv_q;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__Wt;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__Wt_from_block;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__T1;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__T2;
        IData/*31:0*/ sha256_stream__DOT__u_core__DOT__i;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__SmS1__0__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__SmS1__0__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__1__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__1__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__2__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__2__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__shr__3__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__shr__3__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__SmS0__4__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__SmS0__4__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__5__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__5__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__6__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__6__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__shr__7__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__shr__7__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__BigS1__8__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__BigS1__8__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__9__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__9__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__10__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__10__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__11__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__11__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__y;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__z;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__BigS0__14__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__BigS0__14__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__15__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__15__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__16__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__16__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__17__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__rotr__17__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__Vfuncout;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__x;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__y;
        IData/*31:0*/ __Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__z;
        IData/*31:0*/ __VactIterCount;
        VlUnpacked<IData/*31:0*/, 16> sha256_stream__DOT__u_core__DOT__W_q;
    };
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // PARAMETERS
    static constexpr IData/*31:0*/ sha256_stream__DOT__DATA_WIDTH = 0x00000080U;
    static constexpr IData/*31:0*/ sha256_stream__DOT__KEEP_WIDTH = 0x00000010U;
    static constexpr VlWide<8>/*255:0*/ sha256_stream__DOT__SHA256_IV = {{
        0x5be0cd19, 0x1f83d9ab, 0x9b05688c, 0x510e527f,
        0xa54ff53a, 0x3c6ef372, 0xbb67ae85, 0x6a09e667
    }};
    static constexpr VlWide<16>/*511:0*/ sha256_stream__DOT__PAD_BLOCK = {{
        0x00000200, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x80000000
    }};

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
