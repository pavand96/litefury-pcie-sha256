// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__aclk__0 = vlSelfRef.aclk;
    vlSelfRef.__Vtrigprevexpr___TOP__aresetn__0 = vlSelfRef.aresetn;
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root___eval_initial__TOP(vlSelf);
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial__TOP\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.sha256_stream__DOT__m_axis_tkeep = 0xffffU;
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY(((0x64U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("/home/pavand96/litefury-pcie-sha256/sim/../rtl/sha256_stream.sv", 35, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vtop___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vtop___024root___eval_triggers__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtop___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vtop___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge aclk)\n");
    }
    if ((2ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(negedge aresetn)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge aclk)\n");
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(negedge aresetn)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->aclk = VL_RAND_RESET_I(1);
    vlSelf->aresetn = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, vlSelf->s_axis_tdata);
    vlSelf->s_axis_tkeep = VL_RAND_RESET_I(16);
    vlSelf->s_axis_tvalid = VL_RAND_RESET_I(1);
    vlSelf->s_axis_tready = VL_RAND_RESET_I(1);
    vlSelf->s_axis_tlast = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, vlSelf->m_axis_tdata);
    vlSelf->m_axis_tkeep = VL_RAND_RESET_I(16);
    vlSelf->m_axis_tvalid = VL_RAND_RESET_I(1);
    vlSelf->m_axis_tready = VL_RAND_RESET_I(1);
    vlSelf->m_axis_tlast = VL_RAND_RESET_I(1);
    vlSelf->sha256_stream__DOT__aclk = VL_RAND_RESET_I(1);
    vlSelf->sha256_stream__DOT__aresetn = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, vlSelf->sha256_stream__DOT__s_axis_tdata);
    vlSelf->sha256_stream__DOT__s_axis_tkeep = VL_RAND_RESET_I(16);
    vlSelf->sha256_stream__DOT__s_axis_tvalid = VL_RAND_RESET_I(1);
    vlSelf->sha256_stream__DOT__s_axis_tready = VL_RAND_RESET_I(1);
    vlSelf->sha256_stream__DOT__s_axis_tlast = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, vlSelf->sha256_stream__DOT__m_axis_tdata);
    vlSelf->sha256_stream__DOT__m_axis_tkeep = VL_RAND_RESET_I(16);
    vlSelf->sha256_stream__DOT__m_axis_tvalid = VL_RAND_RESET_I(1);
    vlSelf->sha256_stream__DOT__m_axis_tready = VL_RAND_RESET_I(1);
    vlSelf->sha256_stream__DOT__m_axis_tlast = VL_RAND_RESET_I(1);
    vlSelf->sha256_stream__DOT__core_start = VL_RAND_RESET_I(1);
    vlSelf->sha256_stream__DOT__core_ready = VL_RAND_RESET_I(1);
    vlSelf->sha256_stream__DOT__core_done = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(512, vlSelf->sha256_stream__DOT__core_block);
    VL_RAND_RESET_W(256, vlSelf->sha256_stream__DOT__core_cv_in);
    VL_RAND_RESET_W(256, vlSelf->sha256_stream__DOT__core_cv_out);
    vlSelf->sha256_stream__DOT__rx_state_q = VL_RAND_RESET_I(3);
    VL_RAND_RESET_W(512, vlSelf->sha256_stream__DOT__msg_q);
    vlSelf->sha256_stream__DOT__beat_idx_q = VL_RAND_RESET_I(2);
    VL_RAND_RESET_W(256, vlSelf->sha256_stream__DOT__digest_q);
    vlSelf->sha256_stream__DOT__digest_valid_q = VL_RAND_RESET_I(1);
    vlSelf->sha256_stream__DOT__start_pulse = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(512, vlSelf->sha256_stream__DOT__start_block);
    VL_RAND_RESET_W(256, vlSelf->sha256_stream__DOT__start_cv);
    vlSelf->sha256_stream__DOT__tx_consume_digest = VL_RAND_RESET_I(1);
    vlSelf->sha256_stream__DOT__tx_state_q = VL_RAND_RESET_I(2);
    vlSelf->sha256_stream__DOT__u_core__DOT__clk = VL_RAND_RESET_I(1);
    vlSelf->sha256_stream__DOT__u_core__DOT__rstn = VL_RAND_RESET_I(1);
    vlSelf->sha256_stream__DOT__u_core__DOT__start = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(512, vlSelf->sha256_stream__DOT__u_core__DOT__block);
    VL_RAND_RESET_W(256, vlSelf->sha256_stream__DOT__u_core__DOT__cv_in);
    vlSelf->sha256_stream__DOT__u_core__DOT__ready = VL_RAND_RESET_I(1);
    vlSelf->sha256_stream__DOT__u_core__DOT__done = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(256, vlSelf->sha256_stream__DOT__u_core__DOT__cv_out);
    vlSelf->sha256_stream__DOT__u_core__DOT__a_q = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__b_q = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__c_q = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__d_q = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__e_q = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__f_q = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__g_q = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__h_q = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__av_q = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__bv_q = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__cv_q = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__dv_q = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__ev_q = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__fv_q = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__gv_q = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__hv_q = VL_RAND_RESET_I(32);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->sha256_stream__DOT__u_core__DOT__W_q[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->sha256_stream__DOT__u_core__DOT__t_q = VL_RAND_RESET_I(6);
    vlSelf->sha256_stream__DOT__u_core__DOT__busy_q = VL_RAND_RESET_I(1);
    vlSelf->sha256_stream__DOT__u_core__DOT__done_q = VL_RAND_RESET_I(1);
    vlSelf->sha256_stream__DOT__u_core__DOT__Wt = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__Wt_from_block = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__T1 = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__T2 = VL_RAND_RESET_I(32);
    vlSelf->sha256_stream__DOT__u_core__DOT__i = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__SmS1__0__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__SmS1__0__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__1__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__1__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__2__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__2__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__shr__3__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__shr__3__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__SmS0__4__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__SmS0__4__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__5__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__5__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__6__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__6__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__shr__7__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__shr__7__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__BigS1__8__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__BigS1__8__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__9__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__9__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__10__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__10__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__11__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__11__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__y = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__z = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t = VL_RAND_RESET_I(6);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__BigS0__14__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__BigS0__14__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__15__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__15__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__16__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__16__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__17__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__17__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__Vfuncout = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__x = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__y = VL_RAND_RESET_I(32);
    vlSelf->__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__z = VL_RAND_RESET_I(32);
    vlSelf->__Vtrigprevexpr___TOP__aclk__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__aresetn__0 = VL_RAND_RESET_I(1);
}
