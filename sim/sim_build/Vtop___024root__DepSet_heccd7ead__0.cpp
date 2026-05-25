// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.sha256_stream__DOT__s_axis_tdata[0U] 
        = vlSelfRef.s_axis_tdata[0U];
    vlSelfRef.sha256_stream__DOT__s_axis_tdata[1U] 
        = vlSelfRef.s_axis_tdata[1U];
    vlSelfRef.sha256_stream__DOT__s_axis_tdata[2U] 
        = vlSelfRef.s_axis_tdata[2U];
    vlSelfRef.sha256_stream__DOT__s_axis_tdata[3U] 
        = vlSelfRef.s_axis_tdata[3U];
    vlSelfRef.sha256_stream__DOT__s_axis_tkeep = vlSelfRef.s_axis_tkeep;
    vlSelfRef.sha256_stream__DOT__s_axis_tvalid = vlSelfRef.s_axis_tvalid;
    vlSelfRef.sha256_stream__DOT__s_axis_tlast = vlSelfRef.s_axis_tlast;
    vlSelfRef.sha256_stream__DOT__m_axis_tready = vlSelfRef.m_axis_tready;
    vlSelfRef.m_axis_tkeep = vlSelfRef.sha256_stream__DOT__m_axis_tkeep;
    vlSelfRef.sha256_stream__DOT__core_done = vlSelfRef.sha256_stream__DOT__u_core__DOT__done_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__done 
        = vlSelfRef.sha256_stream__DOT__u_core__DOT__done_q;
    vlSelfRef.sha256_stream__DOT__aclk = vlSelfRef.aclk;
    vlSelfRef.sha256_stream__DOT__aresetn = vlSelfRef.aresetn;
    vlSelfRef.sha256_stream__DOT__m_axis_tvalid = 0U;
    vlSelfRef.sha256_stream__DOT__m_axis_tlast = 0U;
    vlSelfRef.sha256_stream__DOT__core_start = vlSelfRef.sha256_stream__DOT__start_pulse;
    vlSelfRef.sha256_stream__DOT__core_block[0U] = 
        vlSelfRef.sha256_stream__DOT__start_block[0U];
    vlSelfRef.sha256_stream__DOT__core_block[1U] = 
        vlSelfRef.sha256_stream__DOT__start_block[1U];
    vlSelfRef.sha256_stream__DOT__core_block[2U] = 
        vlSelfRef.sha256_stream__DOT__start_block[2U];
    vlSelfRef.sha256_stream__DOT__core_block[3U] = 
        vlSelfRef.sha256_stream__DOT__start_block[3U];
    vlSelfRef.sha256_stream__DOT__core_block[4U] = 
        vlSelfRef.sha256_stream__DOT__start_block[4U];
    vlSelfRef.sha256_stream__DOT__core_block[5U] = 
        vlSelfRef.sha256_stream__DOT__start_block[5U];
    vlSelfRef.sha256_stream__DOT__core_block[6U] = 
        vlSelfRef.sha256_stream__DOT__start_block[6U];
    vlSelfRef.sha256_stream__DOT__core_block[7U] = 
        vlSelfRef.sha256_stream__DOT__start_block[7U];
    vlSelfRef.sha256_stream__DOT__core_block[8U] = 
        vlSelfRef.sha256_stream__DOT__start_block[8U];
    vlSelfRef.sha256_stream__DOT__core_block[9U] = 
        vlSelfRef.sha256_stream__DOT__start_block[9U];
    vlSelfRef.sha256_stream__DOT__core_block[0xaU] 
        = vlSelfRef.sha256_stream__DOT__start_block[0xaU];
    vlSelfRef.sha256_stream__DOT__core_block[0xbU] 
        = vlSelfRef.sha256_stream__DOT__start_block[0xbU];
    vlSelfRef.sha256_stream__DOT__core_block[0xcU] 
        = vlSelfRef.sha256_stream__DOT__start_block[0xcU];
    vlSelfRef.sha256_stream__DOT__core_block[0xdU] 
        = vlSelfRef.sha256_stream__DOT__start_block[0xdU];
    vlSelfRef.sha256_stream__DOT__core_block[0xeU] 
        = vlSelfRef.sha256_stream__DOT__start_block[0xeU];
    vlSelfRef.sha256_stream__DOT__core_block[0xfU] 
        = vlSelfRef.sha256_stream__DOT__start_block[0xfU];
    vlSelfRef.sha256_stream__DOT__core_cv_in[0U] = 
        vlSelfRef.sha256_stream__DOT__start_cv[0U];
    vlSelfRef.sha256_stream__DOT__core_cv_in[1U] = 
        vlSelfRef.sha256_stream__DOT__start_cv[1U];
    vlSelfRef.sha256_stream__DOT__core_cv_in[2U] = 
        vlSelfRef.sha256_stream__DOT__start_cv[2U];
    vlSelfRef.sha256_stream__DOT__core_cv_in[3U] = 
        vlSelfRef.sha256_stream__DOT__start_cv[3U];
    vlSelfRef.sha256_stream__DOT__core_cv_in[4U] = 
        vlSelfRef.sha256_stream__DOT__start_cv[4U];
    vlSelfRef.sha256_stream__DOT__core_cv_in[5U] = 
        vlSelfRef.sha256_stream__DOT__start_cv[5U];
    vlSelfRef.sha256_stream__DOT__core_cv_in[6U] = 
        vlSelfRef.sha256_stream__DOT__start_cv[6U];
    vlSelfRef.sha256_stream__DOT__core_cv_in[7U] = 
        vlSelfRef.sha256_stream__DOT__start_cv[7U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__ready 
        = (1U & (~ (IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__busy_q)));
    vlSelfRef.sha256_stream__DOT__m_axis_tdata[0U] = 0U;
    vlSelfRef.sha256_stream__DOT__m_axis_tdata[1U] = 0U;
    vlSelfRef.sha256_stream__DOT__m_axis_tdata[2U] = 0U;
    vlSelfRef.sha256_stream__DOT__m_axis_tdata[3U] = 0U;
    if ((1U == (IData)(vlSelfRef.sha256_stream__DOT__tx_state_q))) {
        vlSelfRef.sha256_stream__DOT__m_axis_tvalid = 1U;
        vlSelfRef.sha256_stream__DOT__m_axis_tlast = 0U;
        vlSelfRef.sha256_stream__DOT__m_axis_tdata[0U] 
            = vlSelfRef.sha256_stream__DOT__digest_q[4U];
        vlSelfRef.sha256_stream__DOT__m_axis_tdata[1U] 
            = vlSelfRef.sha256_stream__DOT__digest_q[5U];
        vlSelfRef.sha256_stream__DOT__m_axis_tdata[2U] 
            = vlSelfRef.sha256_stream__DOT__digest_q[6U];
        vlSelfRef.sha256_stream__DOT__m_axis_tdata[3U] 
            = vlSelfRef.sha256_stream__DOT__digest_q[7U];
    } else if ((2U == (IData)(vlSelfRef.sha256_stream__DOT__tx_state_q))) {
        vlSelfRef.sha256_stream__DOT__m_axis_tvalid = 1U;
        vlSelfRef.sha256_stream__DOT__m_axis_tlast = 1U;
        vlSelfRef.sha256_stream__DOT__m_axis_tdata[0U] 
            = vlSelfRef.sha256_stream__DOT__digest_q[0U];
        vlSelfRef.sha256_stream__DOT__m_axis_tdata[1U] 
            = vlSelfRef.sha256_stream__DOT__digest_q[1U];
        vlSelfRef.sha256_stream__DOT__m_axis_tdata[2U] 
            = vlSelfRef.sha256_stream__DOT__digest_q[2U];
        vlSelfRef.sha256_stream__DOT__m_axis_tdata[3U] 
            = vlSelfRef.sha256_stream__DOT__digest_q[3U];
    }
    vlSelfRef.sha256_stream__DOT__s_axis_tready = (
                                                   (~ (IData)(vlSelfRef.sha256_stream__DOT__digest_valid_q)) 
                                                   & (0U 
                                                      == (IData)(vlSelfRef.sha256_stream__DOT__rx_state_q)));
    vlSelfRef.sha256_stream__DOT__core_cv_out[0U] = vlSelfRef.sha256_stream__DOT__u_core__DOT__h_q;
    vlSelfRef.sha256_stream__DOT__core_cv_out[1U] = vlSelfRef.sha256_stream__DOT__u_core__DOT__g_q;
    vlSelfRef.sha256_stream__DOT__core_cv_out[2U] = (IData)(
                                                            (((QData)((IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__e_q)) 
                                                              << 0x20U) 
                                                             | (QData)((IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__f_q))));
    vlSelfRef.sha256_stream__DOT__core_cv_out[3U] = (IData)(
                                                            ((((QData)((IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__e_q)) 
                                                               << 0x20U) 
                                                              | (QData)((IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__f_q))) 
                                                             >> 0x20U));
    vlSelfRef.sha256_stream__DOT__core_cv_out[4U] = vlSelfRef.sha256_stream__DOT__u_core__DOT__d_q;
    vlSelfRef.sha256_stream__DOT__core_cv_out[5U] = vlSelfRef.sha256_stream__DOT__u_core__DOT__c_q;
    vlSelfRef.sha256_stream__DOT__core_cv_out[6U] = (IData)(
                                                            (((QData)((IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__a_q)) 
                                                              << 0x20U) 
                                                             | (QData)((IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__b_q))));
    vlSelfRef.sha256_stream__DOT__core_cv_out[7U] = (IData)(
                                                            ((((QData)((IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__a_q)) 
                                                               << 0x20U) 
                                                              | (QData)((IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__b_q))) 
                                                             >> 0x20U));
    vlSelfRef.sha256_stream__DOT__u_core__DOT__T2 = 
        (([&]() {
                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS0__14__x 
                    = vlSelfRef.sha256_stream__DOT__u_core__DOT__a_q;
                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS0__14__Vfuncout 
                    = ((([&]() {
                                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__15__x 
                                    = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS0__14__x;
                                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__15__Vfuncout 
                                    = (VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__15__x, 2U) 
                                       | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__15__x, 0x1eU));
                            }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__15__Vfuncout) 
                        ^ ([&]() {
                                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__16__x 
                                    = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS0__14__x;
                                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__16__Vfuncout 
                                    = (VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__16__x, 0xdU) 
                                       | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__16__x, 0x13U));
                            }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__16__Vfuncout)) 
                       ^ ([&]() {
                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__17__x 
                                = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS0__14__x;
                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__17__Vfuncout 
                                = (VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__17__x, 0x16U) 
                                   | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__17__x, 0xaU));
                        }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__17__Vfuncout));
            }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS0__14__Vfuncout) 
         + ([&]() {
                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__z 
                    = vlSelfRef.sha256_stream__DOT__u_core__DOT__c_q;
                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__y 
                    = vlSelfRef.sha256_stream__DOT__u_core__DOT__b_q;
                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__x 
                    = vlSelfRef.sha256_stream__DOT__u_core__DOT__a_q;
                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__Vfuncout 
                    = (((vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__x 
                         & vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__y) 
                        ^ (vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__x 
                           & vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__z)) 
                       ^ (vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__y 
                          & vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__z));
            }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__Vfuncout));
    vlSelfRef.sha256_stream__DOT__u_core__DOT__Wt_from_block 
        = (((0U == (0x1fU & (((IData)(0x1ffU) - VL_SHIFTL_III(9,9,32, (IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q), 5U)) 
                             - (IData)(0x1fU)))) ? 0U
             : (vlSelfRef.sha256_stream__DOT__start_block[
                (((IData)(0x1fU) + (0x1ffU & (((IData)(0x1ffU) 
                                               - VL_SHIFTL_III(9,9,32, (IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q), 5U)) 
                                              - (IData)(0x1fU)))) 
                 >> 5U)] << ((IData)(0x20U) - (0x1fU 
                                               & (((IData)(0x1ffU) 
                                                   - 
                                                   VL_SHIFTL_III(9,9,32, (IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q), 5U)) 
                                                  - (IData)(0x1fU)))))) 
           | (vlSelfRef.sha256_stream__DOT__start_block[
              (0xfU & ((((IData)(0x1ffU) - VL_SHIFTL_III(9,9,32, (IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q), 5U)) 
                        - (IData)(0x1fU)) >> 5U))] 
              >> (0x1fU & (((IData)(0x1ffU) - VL_SHIFTL_III(9,9,32, (IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q), 5U)) 
                           - (IData)(0x1fU)))));
    vlSelfRef.sha256_stream__DOT__u_core__DOT__clk 
        = vlSelfRef.sha256_stream__DOT__aclk;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__rstn 
        = vlSelfRef.sha256_stream__DOT__aresetn;
    vlSelfRef.m_axis_tvalid = vlSelfRef.sha256_stream__DOT__m_axis_tvalid;
    vlSelfRef.m_axis_tlast = vlSelfRef.sha256_stream__DOT__m_axis_tlast;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__start 
        = vlSelfRef.sha256_stream__DOT__core_start;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[0U] 
        = vlSelfRef.sha256_stream__DOT__core_block[0U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[1U] 
        = vlSelfRef.sha256_stream__DOT__core_block[1U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[2U] 
        = vlSelfRef.sha256_stream__DOT__core_block[2U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[3U] 
        = vlSelfRef.sha256_stream__DOT__core_block[3U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[4U] 
        = vlSelfRef.sha256_stream__DOT__core_block[4U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[5U] 
        = vlSelfRef.sha256_stream__DOT__core_block[5U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[6U] 
        = vlSelfRef.sha256_stream__DOT__core_block[6U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[7U] 
        = vlSelfRef.sha256_stream__DOT__core_block[7U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[8U] 
        = vlSelfRef.sha256_stream__DOT__core_block[8U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[9U] 
        = vlSelfRef.sha256_stream__DOT__core_block[9U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[0xaU] 
        = vlSelfRef.sha256_stream__DOT__core_block[0xaU];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[0xbU] 
        = vlSelfRef.sha256_stream__DOT__core_block[0xbU];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[0xcU] 
        = vlSelfRef.sha256_stream__DOT__core_block[0xcU];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[0xdU] 
        = vlSelfRef.sha256_stream__DOT__core_block[0xdU];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[0xeU] 
        = vlSelfRef.sha256_stream__DOT__core_block[0xeU];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[0xfU] 
        = vlSelfRef.sha256_stream__DOT__core_block[0xfU];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in[0U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_in[0U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in[1U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_in[1U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in[2U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_in[2U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in[3U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_in[3U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in[4U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_in[4U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in[5U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_in[5U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in[6U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_in[6U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in[7U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_in[7U];
    vlSelfRef.sha256_stream__DOT__core_ready = vlSelfRef.sha256_stream__DOT__u_core__DOT__ready;
    vlSelfRef.m_axis_tdata[0U] = vlSelfRef.sha256_stream__DOT__m_axis_tdata[0U];
    vlSelfRef.m_axis_tdata[1U] = vlSelfRef.sha256_stream__DOT__m_axis_tdata[1U];
    vlSelfRef.m_axis_tdata[2U] = vlSelfRef.sha256_stream__DOT__m_axis_tdata[2U];
    vlSelfRef.m_axis_tdata[3U] = vlSelfRef.sha256_stream__DOT__m_axis_tdata[3U];
    vlSelfRef.s_axis_tready = vlSelfRef.sha256_stream__DOT__s_axis_tready;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out[0U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_out[0U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out[1U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_out[1U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out[2U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_out[2U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out[3U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_out[3U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out[4U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_out[4U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out[5U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_out[5U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out[6U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_out[6U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out[7U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_out[7U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__Wt = 
        ((0x10U > (IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q))
          ? vlSelfRef.sha256_stream__DOT__u_core__DOT__Wt_from_block
          : (((([&]() {
                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS1__0__x 
                                = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                                [0xeU];
                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS1__0__Vfuncout 
                                = ((([&]() {
                                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__1__x 
                                                = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS1__0__x;
                                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__1__Vfuncout 
                                                = (
                                                   VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__1__x, 0x11U) 
                                                   | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__1__x, 0xfU));
                                        }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__1__Vfuncout) 
                                    ^ ([&]() {
                                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__2__x 
                                                = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS1__0__x;
                                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__2__Vfuncout 
                                                = (
                                                   VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__2__x, 0x13U) 
                                                   | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__2__x, 0xdU));
                                        }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__2__Vfuncout)) 
                                   ^ ([&]() {
                                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__shr__3__x 
                                            = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS1__0__x;
                                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__shr__3__Vfuncout 
                                            = VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__shr__3__x, 0xaU);
                                    }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__shr__3__Vfuncout));
                        }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS1__0__Vfuncout) 
               + vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
               [9U]) + ([&]() {
                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS0__4__x 
                            = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                            [1U];
                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS0__4__Vfuncout 
                            = ((([&]() {
                                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__5__x 
                                            = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS0__4__x;
                                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__5__Vfuncout 
                                            = (VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__5__x, 7U) 
                                               | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__5__x, 0x19U));
                                    }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__5__Vfuncout) 
                                ^ ([&]() {
                                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__6__x 
                                            = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS0__4__x;
                                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__6__Vfuncout 
                                            = (VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__6__x, 0x12U) 
                                               | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__6__x, 0xeU));
                                    }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__6__Vfuncout)) 
                               ^ ([&]() {
                                    vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__shr__7__x 
                                        = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS0__4__x;
                                    vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__shr__7__Vfuncout 
                                        = VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__shr__7__x, 3U);
                                }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__shr__7__Vfuncout));
                    }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS0__4__Vfuncout)) 
             + vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
             [0U]));
    vlSelfRef.sha256_stream__DOT__u_core__DOT__T1 = 
        ((((vlSelfRef.sha256_stream__DOT__u_core__DOT__h_q 
            + ([&]() {
                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS1__8__x 
                                = vlSelfRef.sha256_stream__DOT__u_core__DOT__e_q;
                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS1__8__Vfuncout 
                                = ((([&]() {
                                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__9__x 
                                                = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS1__8__x;
                                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__9__Vfuncout 
                                                = (
                                                   VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__9__x, 6U) 
                                                   | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__9__x, 0x1aU));
                                        }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__9__Vfuncout) 
                                    ^ ([&]() {
                                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__10__x 
                                                = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS1__8__x;
                                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__10__Vfuncout 
                                                = (
                                                   VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__10__x, 0xbU) 
                                                   | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__10__x, 0x15U));
                                        }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__10__Vfuncout)) 
                                   ^ ([&]() {
                                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__11__x 
                                            = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS1__8__x;
                                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__11__Vfuncout 
                                            = (VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__11__x, 0x19U) 
                                               | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__11__x, 7U));
                                    }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__11__Vfuncout));
                        }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS1__8__Vfuncout)) 
           + ([&]() {
                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__z 
                            = vlSelfRef.sha256_stream__DOT__u_core__DOT__g_q;
                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__y 
                            = vlSelfRef.sha256_stream__DOT__u_core__DOT__f_q;
                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__x 
                            = vlSelfRef.sha256_stream__DOT__u_core__DOT__e_q;
                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__Vfuncout 
                            = ((vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__x 
                                & vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__y) 
                               ^ ((~ vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__x) 
                                  & vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__z));
                    }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__Vfuncout)) 
          + ([&]() {
                    vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t 
                        = vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q;
                    vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__Vfuncout 
                        = ((0x20U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                            ? ((0x10U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                ? ((8U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                    ? ((4U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                        ? ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xc67178f2U
                                                : 0xbef9a3f7U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xa4506cebU
                                                : 0x90befffaU))
                                        : ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x8cc70208U
                                                : 0x84c87814U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x78a5636fU
                                                : 0x748f82eeU)))
                                    : ((4U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                        ? ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x682e6ff3U
                                                : 0x5b9cca4fU)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x4ed8aa4aU
                                                : 0x391c0cb3U))
                                        : ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x34b0bcb5U
                                                : 0x2748774cU)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x1e376c08U
                                                : 0x19a4c116U))))
                                : ((8U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                    ? ((4U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                        ? ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x106aa070U
                                                : 0xf40e3585U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xd6990624U
                                                : 0xd192e819U))
                                        : ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xc76c51a3U
                                                : 0xc24b8b70U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xa81a664bU
                                                : 0xa2bfe8a1U)))
                                    : ((4U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                        ? ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x92722c85U
                                                : 0x81c2c92eU)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x766a0abbU
                                                : 0x650a7354U))
                                        : ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x53380d13U
                                                : 0x4d2c6dfcU)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x2e1b2138U
                                                : 0x27b70a85U)))))
                            : ((0x10U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                ? ((8U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                    ? ((4U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                        ? ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x14292967U
                                                : 0x6ca6351U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xd5a79147U
                                                : 0xc6e00bf3U))
                                        : ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xbf597fc7U
                                                : 0xb00327c8U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xa831c66dU
                                                : 0x983e5152U)))
                                    : ((4U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                        ? ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x76f988daU
                                                : 0x5cb0a9dcU)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x4a7484aaU
                                                : 0x2de92c6fU))
                                        : ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x240ca1ccU
                                                : 0xfc19dc6U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xefbe4786U
                                                : 0xe49b69c1U))))
                                : ((8U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                    ? ((4U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                        ? ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xc19bf174U
                                                : 0x9bdc06a7U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x80deb1feU
                                                : 0x72be5d74U))
                                        : ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x550c7dc3U
                                                : 0x243185beU)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x12835b01U
                                                : 0xd807aa98U)))
                                    : ((4U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                        ? ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xab1c5ed5U
                                                : 0x923f82a4U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x59f111f1U
                                                : 0x3956c25bU))
                                        : ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xe9b5dba5U
                                                : 0xb5c0fbcfU)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x71374491U
                                                : 0x428a2f98U))))));
                }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__Vfuncout)) 
         + vlSelfRef.sha256_stream__DOT__u_core__DOT__Wt);
}

void Vtop___024root___eval_triggers__ico(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vtop___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vtop___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf);
void Vtop___024root___nba_sequent__TOP__1(Vtop___024root* vlSelf);
void Vtop___024root___nba_sequent__TOP__2(Vtop___024root* vlSelf);
void Vtop___024root___nba_comb__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_sequent__TOP__1(vlSelf);
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_sequent__TOP__2(vlSelf);
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_comb__TOP__0(vlSelf);
    }
}

extern const VlWide<16>/*511:0*/ Vtop__ConstPool__CONST_h9a6efa96_0;
extern const VlWide<8>/*255:0*/ Vtop__ConstPool__CONST_ha51a22ca_0;
extern const VlWide<16>/*511:0*/ Vtop__ConstPool__CONST_h93e1b771_0;
extern const VlWide<8>/*255:0*/ Vtop__ConstPool__CONST_h9e67c271_0;
extern const VlUnpacked<CData/*0:0*/, 32> Vtop__ConstPool__TABLE_h8f853809_0;
extern const VlUnpacked<CData/*1:0*/, 32> Vtop__ConstPool__TABLE_he27f979f_0;
extern const VlUnpacked<CData/*1:0*/, 32> Vtop__ConstPool__TABLE_h78dc6dc1_0;

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*4:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*0:0*/ __Vdly__sha256_stream__DOT__digest_valid_q;
    __Vdly__sha256_stream__DOT__digest_valid_q = 0;
    CData/*2:0*/ __Vdly__sha256_stream__DOT__rx_state_q;
    __Vdly__sha256_stream__DOT__rx_state_q = 0;
    VlWide<16>/*511:0*/ __Vdly__sha256_stream__DOT__msg_q;
    VL_ZERO_W(512, __Vdly__sha256_stream__DOT__msg_q);
    CData/*1:0*/ __Vdly__sha256_stream__DOT__beat_idx_q;
    __Vdly__sha256_stream__DOT__beat_idx_q = 0;
    // Body
    __Vdly__sha256_stream__DOT__msg_q[0U] = vlSelfRef.sha256_stream__DOT__msg_q[0U];
    __Vdly__sha256_stream__DOT__msg_q[1U] = vlSelfRef.sha256_stream__DOT__msg_q[1U];
    __Vdly__sha256_stream__DOT__msg_q[2U] = vlSelfRef.sha256_stream__DOT__msg_q[2U];
    __Vdly__sha256_stream__DOT__msg_q[3U] = vlSelfRef.sha256_stream__DOT__msg_q[3U];
    __Vdly__sha256_stream__DOT__msg_q[4U] = vlSelfRef.sha256_stream__DOT__msg_q[4U];
    __Vdly__sha256_stream__DOT__msg_q[5U] = vlSelfRef.sha256_stream__DOT__msg_q[5U];
    __Vdly__sha256_stream__DOT__msg_q[6U] = vlSelfRef.sha256_stream__DOT__msg_q[6U];
    __Vdly__sha256_stream__DOT__msg_q[7U] = vlSelfRef.sha256_stream__DOT__msg_q[7U];
    __Vdly__sha256_stream__DOT__msg_q[8U] = vlSelfRef.sha256_stream__DOT__msg_q[8U];
    __Vdly__sha256_stream__DOT__msg_q[9U] = vlSelfRef.sha256_stream__DOT__msg_q[9U];
    __Vdly__sha256_stream__DOT__msg_q[0xaU] = vlSelfRef.sha256_stream__DOT__msg_q[0xaU];
    __Vdly__sha256_stream__DOT__msg_q[0xbU] = vlSelfRef.sha256_stream__DOT__msg_q[0xbU];
    __Vdly__sha256_stream__DOT__msg_q[0xcU] = vlSelfRef.sha256_stream__DOT__msg_q[0xcU];
    __Vdly__sha256_stream__DOT__msg_q[0xdU] = vlSelfRef.sha256_stream__DOT__msg_q[0xdU];
    __Vdly__sha256_stream__DOT__msg_q[0xeU] = vlSelfRef.sha256_stream__DOT__msg_q[0xeU];
    __Vdly__sha256_stream__DOT__msg_q[0xfU] = vlSelfRef.sha256_stream__DOT__msg_q[0xfU];
    __Vdly__sha256_stream__DOT__beat_idx_q = vlSelfRef.sha256_stream__DOT__beat_idx_q;
    __Vdly__sha256_stream__DOT__digest_valid_q = vlSelfRef.sha256_stream__DOT__digest_valid_q;
    __Vdly__sha256_stream__DOT__rx_state_q = vlSelfRef.sha256_stream__DOT__rx_state_q;
    if (vlSelfRef.aresetn) {
        vlSelfRef.sha256_stream__DOT__start_pulse = 0U;
        if (vlSelfRef.sha256_stream__DOT__tx_consume_digest) {
            __Vdly__sha256_stream__DOT__digest_valid_q = 0U;
        }
        if ((4U & (IData)(vlSelfRef.sha256_stream__DOT__rx_state_q))) {
            __Vdly__sha256_stream__DOT__rx_state_q = 0U;
        } else if ((2U & (IData)(vlSelfRef.sha256_stream__DOT__rx_state_q))) {
            if ((1U & (IData)(vlSelfRef.sha256_stream__DOT__rx_state_q))) {
                if ((1U & (~ (IData)(vlSelfRef.sha256_stream__DOT__digest_valid_q)))) {
                    __Vdly__sha256_stream__DOT__rx_state_q = 0U;
                }
            } else if (vlSelfRef.sha256_stream__DOT__core_done) {
                vlSelfRef.sha256_stream__DOT__digest_q[0U] 
                    = vlSelfRef.sha256_stream__DOT__core_cv_out[0U];
                vlSelfRef.sha256_stream__DOT__digest_q[1U] 
                    = vlSelfRef.sha256_stream__DOT__core_cv_out[1U];
                vlSelfRef.sha256_stream__DOT__digest_q[2U] 
                    = vlSelfRef.sha256_stream__DOT__core_cv_out[2U];
                vlSelfRef.sha256_stream__DOT__digest_q[3U] 
                    = vlSelfRef.sha256_stream__DOT__core_cv_out[3U];
                vlSelfRef.sha256_stream__DOT__digest_q[4U] 
                    = vlSelfRef.sha256_stream__DOT__core_cv_out[4U];
                vlSelfRef.sha256_stream__DOT__digest_q[5U] 
                    = vlSelfRef.sha256_stream__DOT__core_cv_out[5U];
                vlSelfRef.sha256_stream__DOT__digest_q[6U] 
                    = vlSelfRef.sha256_stream__DOT__core_cv_out[6U];
                vlSelfRef.sha256_stream__DOT__digest_q[7U] 
                    = vlSelfRef.sha256_stream__DOT__core_cv_out[7U];
                __Vdly__sha256_stream__DOT__digest_valid_q = 1U;
                __Vdly__sha256_stream__DOT__rx_state_q = 3U;
            }
        } else if ((1U & (IData)(vlSelfRef.sha256_stream__DOT__rx_state_q))) {
            if (vlSelfRef.sha256_stream__DOT__core_done) {
                vlSelfRef.sha256_stream__DOT__start_pulse = 1U;
                vlSelfRef.sha256_stream__DOT__start_block[0U] 
                    = Vtop__ConstPool__CONST_h9a6efa96_0[0U];
                vlSelfRef.sha256_stream__DOT__start_block[1U] 
                    = Vtop__ConstPool__CONST_h9a6efa96_0[1U];
                vlSelfRef.sha256_stream__DOT__start_block[2U] 
                    = Vtop__ConstPool__CONST_h9a6efa96_0[2U];
                vlSelfRef.sha256_stream__DOT__start_block[3U] 
                    = Vtop__ConstPool__CONST_h9a6efa96_0[3U];
                vlSelfRef.sha256_stream__DOT__start_block[4U] 
                    = Vtop__ConstPool__CONST_h9a6efa96_0[4U];
                vlSelfRef.sha256_stream__DOT__start_block[5U] 
                    = Vtop__ConstPool__CONST_h9a6efa96_0[5U];
                vlSelfRef.sha256_stream__DOT__start_block[6U] 
                    = Vtop__ConstPool__CONST_h9a6efa96_0[6U];
                vlSelfRef.sha256_stream__DOT__start_block[7U] 
                    = Vtop__ConstPool__CONST_h9a6efa96_0[7U];
                vlSelfRef.sha256_stream__DOT__start_block[8U] 
                    = Vtop__ConstPool__CONST_h9a6efa96_0[8U];
                vlSelfRef.sha256_stream__DOT__start_block[9U] 
                    = Vtop__ConstPool__CONST_h9a6efa96_0[9U];
                vlSelfRef.sha256_stream__DOT__start_block[0xaU] 
                    = Vtop__ConstPool__CONST_h9a6efa96_0[0xaU];
                vlSelfRef.sha256_stream__DOT__start_block[0xbU] 
                    = Vtop__ConstPool__CONST_h9a6efa96_0[0xbU];
                vlSelfRef.sha256_stream__DOT__start_block[0xcU] 
                    = Vtop__ConstPool__CONST_h9a6efa96_0[0xcU];
                vlSelfRef.sha256_stream__DOT__start_block[0xdU] 
                    = Vtop__ConstPool__CONST_h9a6efa96_0[0xdU];
                vlSelfRef.sha256_stream__DOT__start_block[0xeU] 
                    = Vtop__ConstPool__CONST_h9a6efa96_0[0xeU];
                vlSelfRef.sha256_stream__DOT__start_block[0xfU] 
                    = Vtop__ConstPool__CONST_h9a6efa96_0[0xfU];
                vlSelfRef.sha256_stream__DOT__start_cv[0U] 
                    = vlSelfRef.sha256_stream__DOT__core_cv_out[0U];
                vlSelfRef.sha256_stream__DOT__start_cv[1U] 
                    = vlSelfRef.sha256_stream__DOT__core_cv_out[1U];
                vlSelfRef.sha256_stream__DOT__start_cv[2U] 
                    = vlSelfRef.sha256_stream__DOT__core_cv_out[2U];
                vlSelfRef.sha256_stream__DOT__start_cv[3U] 
                    = vlSelfRef.sha256_stream__DOT__core_cv_out[3U];
                vlSelfRef.sha256_stream__DOT__start_cv[4U] 
                    = vlSelfRef.sha256_stream__DOT__core_cv_out[4U];
                vlSelfRef.sha256_stream__DOT__start_cv[5U] 
                    = vlSelfRef.sha256_stream__DOT__core_cv_out[5U];
                vlSelfRef.sha256_stream__DOT__start_cv[6U] 
                    = vlSelfRef.sha256_stream__DOT__core_cv_out[6U];
                vlSelfRef.sha256_stream__DOT__start_cv[7U] 
                    = vlSelfRef.sha256_stream__DOT__core_cv_out[7U];
                __Vdly__sha256_stream__DOT__rx_state_q = 2U;
            }
        } else if (((IData)(vlSelfRef.s_axis_tvalid) 
                    & (IData)(vlSelfRef.sha256_stream__DOT__s_axis_tready))) {
            if ((2U & (IData)(vlSelfRef.sha256_stream__DOT__beat_idx_q))) {
                if ((1U & (IData)(vlSelfRef.sha256_stream__DOT__beat_idx_q))) {
                    __Vdly__sha256_stream__DOT__msg_q[0U] 
                        = vlSelfRef.s_axis_tdata[0U];
                    __Vdly__sha256_stream__DOT__msg_q[1U] 
                        = vlSelfRef.s_axis_tdata[1U];
                    __Vdly__sha256_stream__DOT__msg_q[2U] 
                        = vlSelfRef.s_axis_tdata[2U];
                    __Vdly__sha256_stream__DOT__msg_q[3U] 
                        = vlSelfRef.s_axis_tdata[3U];
                } else {
                    __Vdly__sha256_stream__DOT__msg_q[4U] 
                        = vlSelfRef.s_axis_tdata[0U];
                    __Vdly__sha256_stream__DOT__msg_q[5U] 
                        = vlSelfRef.s_axis_tdata[1U];
                    __Vdly__sha256_stream__DOT__msg_q[6U] 
                        = vlSelfRef.s_axis_tdata[2U];
                    __Vdly__sha256_stream__DOT__msg_q[7U] 
                        = vlSelfRef.s_axis_tdata[3U];
                }
            } else if ((1U & (IData)(vlSelfRef.sha256_stream__DOT__beat_idx_q))) {
                __Vdly__sha256_stream__DOT__msg_q[8U] 
                    = vlSelfRef.s_axis_tdata[0U];
                __Vdly__sha256_stream__DOT__msg_q[9U] 
                    = vlSelfRef.s_axis_tdata[1U];
                __Vdly__sha256_stream__DOT__msg_q[0xaU] 
                    = vlSelfRef.s_axis_tdata[2U];
                __Vdly__sha256_stream__DOT__msg_q[0xbU] 
                    = vlSelfRef.s_axis_tdata[3U];
            } else {
                __Vdly__sha256_stream__DOT__msg_q[0xcU] 
                    = vlSelfRef.s_axis_tdata[0U];
                __Vdly__sha256_stream__DOT__msg_q[0xdU] 
                    = vlSelfRef.s_axis_tdata[1U];
                __Vdly__sha256_stream__DOT__msg_q[0xeU] 
                    = vlSelfRef.s_axis_tdata[2U];
                __Vdly__sha256_stream__DOT__msg_q[0xfU] 
                    = vlSelfRef.s_axis_tdata[3U];
            }
            if ((3U == (IData)(vlSelfRef.sha256_stream__DOT__beat_idx_q))) {
                __Vdly__sha256_stream__DOT__beat_idx_q = 0U;
                vlSelfRef.sha256_stream__DOT__start_pulse = 1U;
                vlSelfRef.sha256_stream__DOT__start_block[0U] 
                    = vlSelfRef.s_axis_tdata[0U];
                vlSelfRef.sha256_stream__DOT__start_block[1U] 
                    = vlSelfRef.s_axis_tdata[1U];
                vlSelfRef.sha256_stream__DOT__start_block[2U] 
                    = vlSelfRef.s_axis_tdata[2U];
                vlSelfRef.sha256_stream__DOT__start_block[3U] 
                    = vlSelfRef.s_axis_tdata[3U];
                vlSelfRef.sha256_stream__DOT__start_block[4U] 
                    = vlSelfRef.sha256_stream__DOT__msg_q[4U];
                vlSelfRef.sha256_stream__DOT__start_block[5U] 
                    = vlSelfRef.sha256_stream__DOT__msg_q[5U];
                vlSelfRef.sha256_stream__DOT__start_block[6U] 
                    = vlSelfRef.sha256_stream__DOT__msg_q[6U];
                vlSelfRef.sha256_stream__DOT__start_block[7U] 
                    = vlSelfRef.sha256_stream__DOT__msg_q[7U];
                vlSelfRef.sha256_stream__DOT__start_block[8U] 
                    = vlSelfRef.sha256_stream__DOT__msg_q[8U];
                vlSelfRef.sha256_stream__DOT__start_block[9U] 
                    = vlSelfRef.sha256_stream__DOT__msg_q[9U];
                vlSelfRef.sha256_stream__DOT__start_block[0xaU] 
                    = vlSelfRef.sha256_stream__DOT__msg_q[0xaU];
                vlSelfRef.sha256_stream__DOT__start_block[0xbU] 
                    = vlSelfRef.sha256_stream__DOT__msg_q[0xbU];
                vlSelfRef.sha256_stream__DOT__start_block[0xcU] 
                    = vlSelfRef.sha256_stream__DOT__msg_q[0xcU];
                vlSelfRef.sha256_stream__DOT__start_block[0xdU] 
                    = vlSelfRef.sha256_stream__DOT__msg_q[0xdU];
                vlSelfRef.sha256_stream__DOT__start_block[0xeU] 
                    = vlSelfRef.sha256_stream__DOT__msg_q[0xeU];
                vlSelfRef.sha256_stream__DOT__start_block[0xfU] 
                    = vlSelfRef.sha256_stream__DOT__msg_q[0xfU];
                vlSelfRef.sha256_stream__DOT__start_cv[0U] 
                    = Vtop__ConstPool__CONST_ha51a22ca_0[0U];
                vlSelfRef.sha256_stream__DOT__start_cv[1U] 
                    = Vtop__ConstPool__CONST_ha51a22ca_0[1U];
                vlSelfRef.sha256_stream__DOT__start_cv[2U] 
                    = Vtop__ConstPool__CONST_ha51a22ca_0[2U];
                vlSelfRef.sha256_stream__DOT__start_cv[3U] 
                    = Vtop__ConstPool__CONST_ha51a22ca_0[3U];
                vlSelfRef.sha256_stream__DOT__start_cv[4U] 
                    = Vtop__ConstPool__CONST_ha51a22ca_0[4U];
                vlSelfRef.sha256_stream__DOT__start_cv[5U] 
                    = Vtop__ConstPool__CONST_ha51a22ca_0[5U];
                vlSelfRef.sha256_stream__DOT__start_cv[6U] 
                    = Vtop__ConstPool__CONST_ha51a22ca_0[6U];
                vlSelfRef.sha256_stream__DOT__start_cv[7U] 
                    = Vtop__ConstPool__CONST_ha51a22ca_0[7U];
                __Vdly__sha256_stream__DOT__rx_state_q = 1U;
            } else {
                __Vdly__sha256_stream__DOT__beat_idx_q 
                    = (3U & ((IData)(1U) + (IData)(vlSelfRef.sha256_stream__DOT__beat_idx_q)));
            }
        }
    } else {
        __Vdly__sha256_stream__DOT__digest_valid_q = 0U;
        __Vdly__sha256_stream__DOT__rx_state_q = 0U;
        __Vdly__sha256_stream__DOT__msg_q[0U] = Vtop__ConstPool__CONST_h93e1b771_0[0U];
        __Vdly__sha256_stream__DOT__msg_q[1U] = Vtop__ConstPool__CONST_h93e1b771_0[1U];
        __Vdly__sha256_stream__DOT__msg_q[2U] = Vtop__ConstPool__CONST_h93e1b771_0[2U];
        __Vdly__sha256_stream__DOT__msg_q[3U] = Vtop__ConstPool__CONST_h93e1b771_0[3U];
        __Vdly__sha256_stream__DOT__msg_q[4U] = Vtop__ConstPool__CONST_h93e1b771_0[4U];
        __Vdly__sha256_stream__DOT__msg_q[5U] = Vtop__ConstPool__CONST_h93e1b771_0[5U];
        __Vdly__sha256_stream__DOT__msg_q[6U] = Vtop__ConstPool__CONST_h93e1b771_0[6U];
        __Vdly__sha256_stream__DOT__msg_q[7U] = Vtop__ConstPool__CONST_h93e1b771_0[7U];
        __Vdly__sha256_stream__DOT__msg_q[8U] = Vtop__ConstPool__CONST_h93e1b771_0[8U];
        __Vdly__sha256_stream__DOT__msg_q[9U] = Vtop__ConstPool__CONST_h93e1b771_0[9U];
        __Vdly__sha256_stream__DOT__msg_q[0xaU] = Vtop__ConstPool__CONST_h93e1b771_0[0xaU];
        __Vdly__sha256_stream__DOT__msg_q[0xbU] = Vtop__ConstPool__CONST_h93e1b771_0[0xbU];
        __Vdly__sha256_stream__DOT__msg_q[0xcU] = Vtop__ConstPool__CONST_h93e1b771_0[0xcU];
        __Vdly__sha256_stream__DOT__msg_q[0xdU] = Vtop__ConstPool__CONST_h93e1b771_0[0xdU];
        __Vdly__sha256_stream__DOT__msg_q[0xeU] = Vtop__ConstPool__CONST_h93e1b771_0[0xeU];
        __Vdly__sha256_stream__DOT__msg_q[0xfU] = Vtop__ConstPool__CONST_h93e1b771_0[0xfU];
        __Vdly__sha256_stream__DOT__beat_idx_q = 0U;
        vlSelfRef.sha256_stream__DOT__digest_q[0U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[0U];
        vlSelfRef.sha256_stream__DOT__digest_q[1U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[1U];
        vlSelfRef.sha256_stream__DOT__digest_q[2U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[2U];
        vlSelfRef.sha256_stream__DOT__digest_q[3U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[3U];
        vlSelfRef.sha256_stream__DOT__digest_q[4U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[4U];
        vlSelfRef.sha256_stream__DOT__digest_q[5U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[5U];
        vlSelfRef.sha256_stream__DOT__digest_q[6U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[6U];
        vlSelfRef.sha256_stream__DOT__digest_q[7U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[7U];
        vlSelfRef.sha256_stream__DOT__start_pulse = 0U;
        vlSelfRef.sha256_stream__DOT__start_block[0U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0U];
        vlSelfRef.sha256_stream__DOT__start_block[1U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[1U];
        vlSelfRef.sha256_stream__DOT__start_block[2U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[2U];
        vlSelfRef.sha256_stream__DOT__start_block[3U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[3U];
        vlSelfRef.sha256_stream__DOT__start_block[4U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[4U];
        vlSelfRef.sha256_stream__DOT__start_block[5U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[5U];
        vlSelfRef.sha256_stream__DOT__start_block[6U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[6U];
        vlSelfRef.sha256_stream__DOT__start_block[7U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[7U];
        vlSelfRef.sha256_stream__DOT__start_block[8U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[8U];
        vlSelfRef.sha256_stream__DOT__start_block[9U] 
            = Vtop__ConstPool__CONST_h93e1b771_0[9U];
        vlSelfRef.sha256_stream__DOT__start_block[0xaU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xaU];
        vlSelfRef.sha256_stream__DOT__start_block[0xbU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xbU];
        vlSelfRef.sha256_stream__DOT__start_block[0xcU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xcU];
        vlSelfRef.sha256_stream__DOT__start_block[0xdU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xdU];
        vlSelfRef.sha256_stream__DOT__start_block[0xeU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xeU];
        vlSelfRef.sha256_stream__DOT__start_block[0xfU] 
            = Vtop__ConstPool__CONST_h93e1b771_0[0xfU];
        vlSelfRef.sha256_stream__DOT__start_cv[0U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[0U];
        vlSelfRef.sha256_stream__DOT__start_cv[1U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[1U];
        vlSelfRef.sha256_stream__DOT__start_cv[2U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[2U];
        vlSelfRef.sha256_stream__DOT__start_cv[3U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[3U];
        vlSelfRef.sha256_stream__DOT__start_cv[4U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[4U];
        vlSelfRef.sha256_stream__DOT__start_cv[5U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[5U];
        vlSelfRef.sha256_stream__DOT__start_cv[6U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[6U];
        vlSelfRef.sha256_stream__DOT__start_cv[7U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[7U];
    }
    vlSelfRef.sha256_stream__DOT__msg_q[0U] = __Vdly__sha256_stream__DOT__msg_q[0U];
    vlSelfRef.sha256_stream__DOT__msg_q[1U] = __Vdly__sha256_stream__DOT__msg_q[1U];
    vlSelfRef.sha256_stream__DOT__msg_q[2U] = __Vdly__sha256_stream__DOT__msg_q[2U];
    vlSelfRef.sha256_stream__DOT__msg_q[3U] = __Vdly__sha256_stream__DOT__msg_q[3U];
    vlSelfRef.sha256_stream__DOT__msg_q[4U] = __Vdly__sha256_stream__DOT__msg_q[4U];
    vlSelfRef.sha256_stream__DOT__msg_q[5U] = __Vdly__sha256_stream__DOT__msg_q[5U];
    vlSelfRef.sha256_stream__DOT__msg_q[6U] = __Vdly__sha256_stream__DOT__msg_q[6U];
    vlSelfRef.sha256_stream__DOT__msg_q[7U] = __Vdly__sha256_stream__DOT__msg_q[7U];
    vlSelfRef.sha256_stream__DOT__msg_q[8U] = __Vdly__sha256_stream__DOT__msg_q[8U];
    vlSelfRef.sha256_stream__DOT__msg_q[9U] = __Vdly__sha256_stream__DOT__msg_q[9U];
    vlSelfRef.sha256_stream__DOT__msg_q[0xaU] = __Vdly__sha256_stream__DOT__msg_q[0xaU];
    vlSelfRef.sha256_stream__DOT__msg_q[0xbU] = __Vdly__sha256_stream__DOT__msg_q[0xbU];
    vlSelfRef.sha256_stream__DOT__msg_q[0xcU] = __Vdly__sha256_stream__DOT__msg_q[0xcU];
    vlSelfRef.sha256_stream__DOT__msg_q[0xdU] = __Vdly__sha256_stream__DOT__msg_q[0xdU];
    vlSelfRef.sha256_stream__DOT__msg_q[0xeU] = __Vdly__sha256_stream__DOT__msg_q[0xeU];
    vlSelfRef.sha256_stream__DOT__msg_q[0xfU] = __Vdly__sha256_stream__DOT__msg_q[0xfU];
    vlSelfRef.sha256_stream__DOT__beat_idx_q = __Vdly__sha256_stream__DOT__beat_idx_q;
    vlSelfRef.sha256_stream__DOT__rx_state_q = __Vdly__sha256_stream__DOT__rx_state_q;
    vlSelfRef.sha256_stream__DOT__core_block[0U] = 
        vlSelfRef.sha256_stream__DOT__start_block[0U];
    vlSelfRef.sha256_stream__DOT__core_block[1U] = 
        vlSelfRef.sha256_stream__DOT__start_block[1U];
    vlSelfRef.sha256_stream__DOT__core_block[2U] = 
        vlSelfRef.sha256_stream__DOT__start_block[2U];
    vlSelfRef.sha256_stream__DOT__core_block[3U] = 
        vlSelfRef.sha256_stream__DOT__start_block[3U];
    vlSelfRef.sha256_stream__DOT__core_block[4U] = 
        vlSelfRef.sha256_stream__DOT__start_block[4U];
    vlSelfRef.sha256_stream__DOT__core_block[5U] = 
        vlSelfRef.sha256_stream__DOT__start_block[5U];
    vlSelfRef.sha256_stream__DOT__core_block[6U] = 
        vlSelfRef.sha256_stream__DOT__start_block[6U];
    vlSelfRef.sha256_stream__DOT__core_block[7U] = 
        vlSelfRef.sha256_stream__DOT__start_block[7U];
    vlSelfRef.sha256_stream__DOT__core_block[8U] = 
        vlSelfRef.sha256_stream__DOT__start_block[8U];
    vlSelfRef.sha256_stream__DOT__core_block[9U] = 
        vlSelfRef.sha256_stream__DOT__start_block[9U];
    vlSelfRef.sha256_stream__DOT__core_block[0xaU] 
        = vlSelfRef.sha256_stream__DOT__start_block[0xaU];
    vlSelfRef.sha256_stream__DOT__core_block[0xbU] 
        = vlSelfRef.sha256_stream__DOT__start_block[0xbU];
    vlSelfRef.sha256_stream__DOT__core_block[0xcU] 
        = vlSelfRef.sha256_stream__DOT__start_block[0xcU];
    vlSelfRef.sha256_stream__DOT__core_block[0xdU] 
        = vlSelfRef.sha256_stream__DOT__start_block[0xdU];
    vlSelfRef.sha256_stream__DOT__core_block[0xeU] 
        = vlSelfRef.sha256_stream__DOT__start_block[0xeU];
    vlSelfRef.sha256_stream__DOT__core_block[0xfU] 
        = vlSelfRef.sha256_stream__DOT__start_block[0xfU];
    __Vtableidx1 = ((((IData)(vlSelfRef.sha256_stream__DOT__digest_valid_q) 
                      << 4U) | ((IData)(vlSelfRef.m_axis_tready) 
                                << 3U)) | (((IData)(vlSelfRef.sha256_stream__DOT__tx_state_q) 
                                            << 1U) 
                                           | (IData)(vlSelfRef.aresetn)));
    vlSelfRef.sha256_stream__DOT__tx_consume_digest 
        = Vtop__ConstPool__TABLE_h8f853809_0[__Vtableidx1];
    if ((2U & Vtop__ConstPool__TABLE_he27f979f_0[__Vtableidx1])) {
        vlSelfRef.sha256_stream__DOT__tx_state_q = 
            Vtop__ConstPool__TABLE_h78dc6dc1_0[__Vtableidx1];
    }
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[0U] 
        = vlSelfRef.sha256_stream__DOT__core_block[0U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[1U] 
        = vlSelfRef.sha256_stream__DOT__core_block[1U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[2U] 
        = vlSelfRef.sha256_stream__DOT__core_block[2U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[3U] 
        = vlSelfRef.sha256_stream__DOT__core_block[3U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[4U] 
        = vlSelfRef.sha256_stream__DOT__core_block[4U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[5U] 
        = vlSelfRef.sha256_stream__DOT__core_block[5U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[6U] 
        = vlSelfRef.sha256_stream__DOT__core_block[6U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[7U] 
        = vlSelfRef.sha256_stream__DOT__core_block[7U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[8U] 
        = vlSelfRef.sha256_stream__DOT__core_block[8U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[9U] 
        = vlSelfRef.sha256_stream__DOT__core_block[9U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[0xaU] 
        = vlSelfRef.sha256_stream__DOT__core_block[0xaU];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[0xbU] 
        = vlSelfRef.sha256_stream__DOT__core_block[0xbU];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[0xcU] 
        = vlSelfRef.sha256_stream__DOT__core_block[0xcU];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[0xdU] 
        = vlSelfRef.sha256_stream__DOT__core_block[0xdU];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[0xeU] 
        = vlSelfRef.sha256_stream__DOT__core_block[0xeU];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__block[0xfU] 
        = vlSelfRef.sha256_stream__DOT__core_block[0xfU];
    vlSelfRef.sha256_stream__DOT__digest_valid_q = __Vdly__sha256_stream__DOT__digest_valid_q;
    vlSelfRef.sha256_stream__DOT__s_axis_tready = (
                                                   (~ (IData)(vlSelfRef.sha256_stream__DOT__digest_valid_q)) 
                                                   & (0U 
                                                      == (IData)(vlSelfRef.sha256_stream__DOT__rx_state_q)));
    vlSelfRef.sha256_stream__DOT__m_axis_tvalid = 0U;
    vlSelfRef.sha256_stream__DOT__m_axis_tlast = 0U;
    vlSelfRef.sha256_stream__DOT__m_axis_tdata[0U] = 0U;
    vlSelfRef.sha256_stream__DOT__m_axis_tdata[1U] = 0U;
    vlSelfRef.sha256_stream__DOT__m_axis_tdata[2U] = 0U;
    vlSelfRef.sha256_stream__DOT__m_axis_tdata[3U] = 0U;
    if ((1U == (IData)(vlSelfRef.sha256_stream__DOT__tx_state_q))) {
        vlSelfRef.sha256_stream__DOT__m_axis_tvalid = 1U;
        vlSelfRef.sha256_stream__DOT__m_axis_tlast = 0U;
        vlSelfRef.sha256_stream__DOT__m_axis_tdata[0U] 
            = vlSelfRef.sha256_stream__DOT__digest_q[4U];
        vlSelfRef.sha256_stream__DOT__m_axis_tdata[1U] 
            = vlSelfRef.sha256_stream__DOT__digest_q[5U];
        vlSelfRef.sha256_stream__DOT__m_axis_tdata[2U] 
            = vlSelfRef.sha256_stream__DOT__digest_q[6U];
        vlSelfRef.sha256_stream__DOT__m_axis_tdata[3U] 
            = vlSelfRef.sha256_stream__DOT__digest_q[7U];
    } else if ((2U == (IData)(vlSelfRef.sha256_stream__DOT__tx_state_q))) {
        vlSelfRef.sha256_stream__DOT__m_axis_tvalid = 1U;
        vlSelfRef.sha256_stream__DOT__m_axis_tlast = 1U;
        vlSelfRef.sha256_stream__DOT__m_axis_tdata[0U] 
            = vlSelfRef.sha256_stream__DOT__digest_q[0U];
        vlSelfRef.sha256_stream__DOT__m_axis_tdata[1U] 
            = vlSelfRef.sha256_stream__DOT__digest_q[1U];
        vlSelfRef.sha256_stream__DOT__m_axis_tdata[2U] 
            = vlSelfRef.sha256_stream__DOT__digest_q[2U];
        vlSelfRef.sha256_stream__DOT__m_axis_tdata[3U] 
            = vlSelfRef.sha256_stream__DOT__digest_q[3U];
    }
    vlSelfRef.s_axis_tready = vlSelfRef.sha256_stream__DOT__s_axis_tready;
    vlSelfRef.m_axis_tvalid = vlSelfRef.sha256_stream__DOT__m_axis_tvalid;
    vlSelfRef.m_axis_tlast = vlSelfRef.sha256_stream__DOT__m_axis_tlast;
    vlSelfRef.m_axis_tdata[0U] = vlSelfRef.sha256_stream__DOT__m_axis_tdata[0U];
    vlSelfRef.m_axis_tdata[1U] = vlSelfRef.sha256_stream__DOT__m_axis_tdata[1U];
    vlSelfRef.m_axis_tdata[2U] = vlSelfRef.sha256_stream__DOT__m_axis_tdata[2U];
    vlSelfRef.m_axis_tdata[3U] = vlSelfRef.sha256_stream__DOT__m_axis_tdata[3U];
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__1(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__1\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __Vdly__sha256_stream__DOT__u_core__DOT__a_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__a_q = 0;
    IData/*31:0*/ __Vdly__sha256_stream__DOT__u_core__DOT__av_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__av_q = 0;
    IData/*31:0*/ __Vdly__sha256_stream__DOT__u_core__DOT__b_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__b_q = 0;
    IData/*31:0*/ __Vdly__sha256_stream__DOT__u_core__DOT__bv_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__bv_q = 0;
    IData/*31:0*/ __Vdly__sha256_stream__DOT__u_core__DOT__c_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__c_q = 0;
    IData/*31:0*/ __Vdly__sha256_stream__DOT__u_core__DOT__cv_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__cv_q = 0;
    IData/*31:0*/ __Vdly__sha256_stream__DOT__u_core__DOT__d_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__d_q = 0;
    IData/*31:0*/ __Vdly__sha256_stream__DOT__u_core__DOT__dv_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__dv_q = 0;
    IData/*31:0*/ __Vdly__sha256_stream__DOT__u_core__DOT__e_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__e_q = 0;
    IData/*31:0*/ __Vdly__sha256_stream__DOT__u_core__DOT__ev_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__ev_q = 0;
    IData/*31:0*/ __Vdly__sha256_stream__DOT__u_core__DOT__f_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__f_q = 0;
    IData/*31:0*/ __Vdly__sha256_stream__DOT__u_core__DOT__fv_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__fv_q = 0;
    IData/*31:0*/ __Vdly__sha256_stream__DOT__u_core__DOT__g_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__g_q = 0;
    IData/*31:0*/ __Vdly__sha256_stream__DOT__u_core__DOT__gv_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__gv_q = 0;
    IData/*31:0*/ __Vdly__sha256_stream__DOT__u_core__DOT__hv_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__hv_q = 0;
    CData/*5:0*/ __Vdly__sha256_stream__DOT__u_core__DOT__t_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__t_q = 0;
    CData/*0:0*/ __Vdly__sha256_stream__DOT__u_core__DOT__busy_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__busy_q = 0;
    IData/*31:0*/ __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v0;
    __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v0 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v0;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v0 = 0;
    IData/*31:0*/ __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v1;
    __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v1 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v1;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v1 = 0;
    IData/*31:0*/ __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v2;
    __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v2 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v2;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v2 = 0;
    IData/*31:0*/ __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v3;
    __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v3 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v3;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v3 = 0;
    IData/*31:0*/ __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v4;
    __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v4 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v4;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v4 = 0;
    IData/*31:0*/ __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v5;
    __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v5 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v5;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v5 = 0;
    IData/*31:0*/ __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v6;
    __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v6 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v6;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v6 = 0;
    IData/*31:0*/ __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v7;
    __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v7 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v7;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v7 = 0;
    IData/*31:0*/ __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v8;
    __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v8 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v8;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v8 = 0;
    IData/*31:0*/ __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v9;
    __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v9 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v9;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v9 = 0;
    IData/*31:0*/ __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v10;
    __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v10 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v10;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v10 = 0;
    IData/*31:0*/ __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v11;
    __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v11 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v11;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v11 = 0;
    IData/*31:0*/ __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v12;
    __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v12 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v12;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v12 = 0;
    IData/*31:0*/ __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v13;
    __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v13 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v13;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v13 = 0;
    IData/*31:0*/ __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v14;
    __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v14 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v14;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v14 = 0;
    IData/*31:0*/ __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v15;
    __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v15 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v16;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v16 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v17;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v17 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v18;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v18 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v19;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v19 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v20;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v20 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v21;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v21 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v22;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v22 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v23;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v23 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v24;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v24 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v25;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v25 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v26;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v26 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v27;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v27 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v28;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v28 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v29;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v29 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v30;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v30 = 0;
    CData/*0:0*/ __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v31;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v31 = 0;
    // Body
    __Vdly__sha256_stream__DOT__u_core__DOT__av_q = vlSelfRef.sha256_stream__DOT__u_core__DOT__av_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__bv_q = vlSelfRef.sha256_stream__DOT__u_core__DOT__bv_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__cv_q = vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__dv_q = vlSelfRef.sha256_stream__DOT__u_core__DOT__dv_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__ev_q = vlSelfRef.sha256_stream__DOT__u_core__DOT__ev_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__fv_q = vlSelfRef.sha256_stream__DOT__u_core__DOT__fv_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__gv_q = vlSelfRef.sha256_stream__DOT__u_core__DOT__gv_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__hv_q = vlSelfRef.sha256_stream__DOT__u_core__DOT__hv_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__busy_q 
        = vlSelfRef.sha256_stream__DOT__u_core__DOT__busy_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__d_q = vlSelfRef.sha256_stream__DOT__u_core__DOT__d_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__a_q = vlSelfRef.sha256_stream__DOT__u_core__DOT__a_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__b_q = vlSelfRef.sha256_stream__DOT__u_core__DOT__b_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__c_q = vlSelfRef.sha256_stream__DOT__u_core__DOT__c_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__e_q = vlSelfRef.sha256_stream__DOT__u_core__DOT__e_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__f_q = vlSelfRef.sha256_stream__DOT__u_core__DOT__f_q;
    __Vdly__sha256_stream__DOT__u_core__DOT__g_q = vlSelfRef.sha256_stream__DOT__u_core__DOT__g_q;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v0 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v1 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v2 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v3 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v4 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v5 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v6 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v7 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v8 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v9 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v10 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v11 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v12 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v13 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v14 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v16 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v17 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v18 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v19 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v20 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v21 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v22 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v23 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v24 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v25 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v26 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v27 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v28 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v29 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v30 = 0U;
    __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v31 = 0U;
    __Vdly__sha256_stream__DOT__u_core__DOT__t_q = vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q;
    if (vlSelfRef.aresetn) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__done_q = 0U;
        if (((~ (IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__busy_q)) 
             & (IData)(vlSelfRef.sha256_stream__DOT__core_start))) {
            __Vdly__sha256_stream__DOT__u_core__DOT__a_q 
                = vlSelfRef.sha256_stream__DOT__core_cv_in[7U];
            __Vdly__sha256_stream__DOT__u_core__DOT__av_q 
                = vlSelfRef.sha256_stream__DOT__core_cv_in[7U];
            __Vdly__sha256_stream__DOT__u_core__DOT__b_q 
                = vlSelfRef.sha256_stream__DOT__core_cv_in[6U];
            __Vdly__sha256_stream__DOT__u_core__DOT__bv_q 
                = vlSelfRef.sha256_stream__DOT__core_cv_in[6U];
            __Vdly__sha256_stream__DOT__u_core__DOT__c_q 
                = vlSelfRef.sha256_stream__DOT__core_cv_in[5U];
            __Vdly__sha256_stream__DOT__u_core__DOT__cv_q 
                = vlSelfRef.sha256_stream__DOT__core_cv_in[5U];
            __Vdly__sha256_stream__DOT__u_core__DOT__d_q 
                = vlSelfRef.sha256_stream__DOT__core_cv_in[4U];
            __Vdly__sha256_stream__DOT__u_core__DOT__dv_q 
                = vlSelfRef.sha256_stream__DOT__core_cv_in[4U];
            __Vdly__sha256_stream__DOT__u_core__DOT__e_q 
                = vlSelfRef.sha256_stream__DOT__core_cv_in[3U];
            __Vdly__sha256_stream__DOT__u_core__DOT__ev_q 
                = vlSelfRef.sha256_stream__DOT__core_cv_in[3U];
            __Vdly__sha256_stream__DOT__u_core__DOT__f_q 
                = vlSelfRef.sha256_stream__DOT__core_cv_in[2U];
            __Vdly__sha256_stream__DOT__u_core__DOT__fv_q 
                = vlSelfRef.sha256_stream__DOT__core_cv_in[2U];
            __Vdly__sha256_stream__DOT__u_core__DOT__g_q 
                = vlSelfRef.sha256_stream__DOT__core_cv_in[1U];
            __Vdly__sha256_stream__DOT__u_core__DOT__gv_q 
                = vlSelfRef.sha256_stream__DOT__core_cv_in[1U];
            vlSelfRef.sha256_stream__DOT__u_core__DOT__h_q 
                = vlSelfRef.sha256_stream__DOT__core_cv_in[0U];
            __Vdly__sha256_stream__DOT__u_core__DOT__hv_q 
                = vlSelfRef.sha256_stream__DOT__core_cv_in[0U];
            __Vdly__sha256_stream__DOT__u_core__DOT__t_q = 0U;
            __Vdly__sha256_stream__DOT__u_core__DOT__busy_q = 1U;
        } else if (vlSelfRef.sha256_stream__DOT__u_core__DOT__busy_q) {
            __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v0 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                [1U];
            __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v0 = 1U;
            vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 1U;
            vlSelfRef.sha256_stream__DOT__u_core__DOT__h_q 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__g_q;
            vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 2U;
            __Vdly__sha256_stream__DOT__u_core__DOT__g_q 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__f_q;
            __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v1 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                [2U];
            __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v1 = 1U;
            vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 3U;
            __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v2 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                [3U];
            __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v2 = 1U;
            vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 4U;
            __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v3 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                [4U];
            __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v3 = 1U;
            vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 5U;
            __Vdly__sha256_stream__DOT__u_core__DOT__f_q 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__e_q;
            __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v4 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                [5U];
            __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v4 = 1U;
            vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 6U;
            __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v5 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                [6U];
            __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v5 = 1U;
            vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 7U;
            __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v6 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                [7U];
            __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v6 = 1U;
            vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 8U;
            __Vdly__sha256_stream__DOT__u_core__DOT__e_q 
                = (vlSelfRef.sha256_stream__DOT__u_core__DOT__d_q 
                   + vlSelfRef.sha256_stream__DOT__u_core__DOT__T1);
            __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v7 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                [8U];
            __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v7 = 1U;
            vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 9U;
            __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v8 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                [9U];
            __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v8 = 1U;
            vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 0xaU;
            __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v9 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                [0xaU];
            __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v9 = 1U;
            vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 0xbU;
            __Vdly__sha256_stream__DOT__u_core__DOT__d_q 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__c_q;
            __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v10 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                [0xbU];
            __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v10 = 1U;
            vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 0xcU;
            __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v11 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                [0xcU];
            __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v11 = 1U;
            vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 0xdU;
            __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v12 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                [0xdU];
            __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v12 = 1U;
            vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 0xeU;
            __Vdly__sha256_stream__DOT__u_core__DOT__c_q 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__b_q;
            __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v13 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                [0xeU];
            __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v13 = 1U;
            vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 0xfU;
            __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v14 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                [0xfU];
            __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v14 = 1U;
            __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v15 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__Wt;
            __Vdly__sha256_stream__DOT__u_core__DOT__b_q 
                = vlSelfRef.sha256_stream__DOT__u_core__DOT__a_q;
            __Vdly__sha256_stream__DOT__u_core__DOT__a_q 
                = (vlSelfRef.sha256_stream__DOT__u_core__DOT__T1 
                   + vlSelfRef.sha256_stream__DOT__u_core__DOT__T2);
            if ((0x3fU == (IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q))) {
                vlSelfRef.sha256_stream__DOT__u_core__DOT__h_q 
                    = (vlSelfRef.sha256_stream__DOT__u_core__DOT__g_q 
                       + vlSelfRef.sha256_stream__DOT__u_core__DOT__hv_q);
                __Vdly__sha256_stream__DOT__u_core__DOT__busy_q = 0U;
                vlSelfRef.sha256_stream__DOT__u_core__DOT__done_q = 1U;
                __Vdly__sha256_stream__DOT__u_core__DOT__g_q 
                    = (vlSelfRef.sha256_stream__DOT__u_core__DOT__f_q 
                       + vlSelfRef.sha256_stream__DOT__u_core__DOT__gv_q);
                __Vdly__sha256_stream__DOT__u_core__DOT__f_q 
                    = (vlSelfRef.sha256_stream__DOT__u_core__DOT__e_q 
                       + vlSelfRef.sha256_stream__DOT__u_core__DOT__fv_q);
                __Vdly__sha256_stream__DOT__u_core__DOT__e_q 
                    = ((vlSelfRef.sha256_stream__DOT__u_core__DOT__d_q 
                        + vlSelfRef.sha256_stream__DOT__u_core__DOT__T1) 
                       + vlSelfRef.sha256_stream__DOT__u_core__DOT__ev_q);
                __Vdly__sha256_stream__DOT__u_core__DOT__d_q 
                    = (vlSelfRef.sha256_stream__DOT__u_core__DOT__c_q 
                       + vlSelfRef.sha256_stream__DOT__u_core__DOT__dv_q);
                __Vdly__sha256_stream__DOT__u_core__DOT__c_q 
                    = (vlSelfRef.sha256_stream__DOT__u_core__DOT__b_q 
                       + vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_q);
                __Vdly__sha256_stream__DOT__u_core__DOT__b_q 
                    = (vlSelfRef.sha256_stream__DOT__u_core__DOT__a_q 
                       + vlSelfRef.sha256_stream__DOT__u_core__DOT__bv_q);
                __Vdly__sha256_stream__DOT__u_core__DOT__a_q 
                    = ((vlSelfRef.sha256_stream__DOT__u_core__DOT__T1 
                        + vlSelfRef.sha256_stream__DOT__u_core__DOT__T2) 
                       + vlSelfRef.sha256_stream__DOT__u_core__DOT__av_q);
            } else {
                __Vdly__sha256_stream__DOT__u_core__DOT__t_q 
                    = (0x3fU & ((IData)(1U) + (IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q)));
            }
        }
    } else {
        __Vdly__sha256_stream__DOT__u_core__DOT__g_q = 0U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 1U;
        __Vdly__sha256_stream__DOT__u_core__DOT__busy_q = 0U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__done_q = 0U;
        __Vdly__sha256_stream__DOT__u_core__DOT__t_q = 0U;
        __Vdly__sha256_stream__DOT__u_core__DOT__a_q = 0U;
        __Vdly__sha256_stream__DOT__u_core__DOT__b_q = 0U;
        __Vdly__sha256_stream__DOT__u_core__DOT__c_q = 0U;
        __Vdly__sha256_stream__DOT__u_core__DOT__d_q = 0U;
        __Vdly__sha256_stream__DOT__u_core__DOT__e_q = 0U;
        __Vdly__sha256_stream__DOT__u_core__DOT__f_q = 0U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__h_q = 0U;
        __Vdly__sha256_stream__DOT__u_core__DOT__av_q = 0U;
        __Vdly__sha256_stream__DOT__u_core__DOT__bv_q = 0U;
        __Vdly__sha256_stream__DOT__u_core__DOT__cv_q = 0U;
        __Vdly__sha256_stream__DOT__u_core__DOT__dv_q = 0U;
        __Vdly__sha256_stream__DOT__u_core__DOT__ev_q = 0U;
        __Vdly__sha256_stream__DOT__u_core__DOT__fv_q = 0U;
        __Vdly__sha256_stream__DOT__u_core__DOT__gv_q = 0U;
        __Vdly__sha256_stream__DOT__u_core__DOT__hv_q = 0U;
        __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v16 = 1U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 2U;
        __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v17 = 1U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 3U;
        __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v18 = 1U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 4U;
        __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v19 = 1U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 5U;
        __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v20 = 1U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 6U;
        __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v21 = 1U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 7U;
        __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v22 = 1U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 8U;
        __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v23 = 1U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 9U;
        __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v24 = 1U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 0xaU;
        __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v25 = 1U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 0xbU;
        __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v26 = 1U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 0xcU;
        __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v27 = 1U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 0xdU;
        __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v28 = 1U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 0xeU;
        __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v29 = 1U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 0xfU;
        __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v30 = 1U;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__i = 0x10U;
        __VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v31 = 1U;
    }
    vlSelfRef.sha256_stream__DOT__u_core__DOT__av_q 
        = __Vdly__sha256_stream__DOT__u_core__DOT__av_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__bv_q 
        = __Vdly__sha256_stream__DOT__u_core__DOT__bv_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_q 
        = __Vdly__sha256_stream__DOT__u_core__DOT__cv_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__dv_q 
        = __Vdly__sha256_stream__DOT__u_core__DOT__dv_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__ev_q 
        = __Vdly__sha256_stream__DOT__u_core__DOT__ev_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__fv_q 
        = __Vdly__sha256_stream__DOT__u_core__DOT__fv_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__gv_q 
        = __Vdly__sha256_stream__DOT__u_core__DOT__gv_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__hv_q 
        = __Vdly__sha256_stream__DOT__u_core__DOT__hv_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__busy_q 
        = __Vdly__sha256_stream__DOT__u_core__DOT__busy_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__d_q 
        = __Vdly__sha256_stream__DOT__u_core__DOT__d_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__a_q 
        = __Vdly__sha256_stream__DOT__u_core__DOT__a_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__b_q 
        = __Vdly__sha256_stream__DOT__u_core__DOT__b_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__c_q 
        = __Vdly__sha256_stream__DOT__u_core__DOT__c_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__e_q 
        = __Vdly__sha256_stream__DOT__u_core__DOT__e_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__f_q 
        = __Vdly__sha256_stream__DOT__u_core__DOT__f_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__g_q 
        = __Vdly__sha256_stream__DOT__u_core__DOT__g_q;
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v0) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[0U] 
            = __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v0;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v1) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[1U] 
            = __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v1;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v2) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[2U] 
            = __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v2;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v3) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[3U] 
            = __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v3;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v4) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[4U] 
            = __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v4;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v5) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[5U] 
            = __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v5;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v6) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[6U] 
            = __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v6;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v7) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[7U] 
            = __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v7;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v8) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[8U] 
            = __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v8;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v9) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[9U] 
            = __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v9;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v10) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[0xaU] 
            = __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v10;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v11) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[0xbU] 
            = __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v11;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v12) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[0xcU] 
            = __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v12;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v13) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[0xdU] 
            = __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v13;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v14) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[0xeU] 
            = __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v14;
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[0xfU] 
            = __VdlyVal__sha256_stream__DOT__u_core__DOT__W_q__v15;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v16) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[0U] = 0U;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v17) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[1U] = 0U;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v18) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[2U] = 0U;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v19) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[3U] = 0U;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v20) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[4U] = 0U;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v21) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[5U] = 0U;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v22) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[6U] = 0U;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v23) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[7U] = 0U;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v24) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[8U] = 0U;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v25) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[9U] = 0U;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v26) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[0xaU] = 0U;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v27) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[0xbU] = 0U;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v28) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[0xcU] = 0U;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v29) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[0xdU] = 0U;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v30) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[0xeU] = 0U;
    }
    if (__VdlySet__sha256_stream__DOT__u_core__DOT__W_q__v31) {
        vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[0xfU] = 0U;
    }
    vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q 
        = __Vdly__sha256_stream__DOT__u_core__DOT__t_q;
    vlSelfRef.sha256_stream__DOT__core_done = vlSelfRef.sha256_stream__DOT__u_core__DOT__done_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__done 
        = vlSelfRef.sha256_stream__DOT__u_core__DOT__done_q;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__ready 
        = (1U & (~ (IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__busy_q)));
    vlSelfRef.sha256_stream__DOT__u_core__DOT__T2 = 
        (([&]() {
                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS0__14__x 
                    = vlSelfRef.sha256_stream__DOT__u_core__DOT__a_q;
                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS0__14__Vfuncout 
                    = ((([&]() {
                                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__15__x 
                                    = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS0__14__x;
                                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__15__Vfuncout 
                                    = (VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__15__x, 2U) 
                                       | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__15__x, 0x1eU));
                            }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__15__Vfuncout) 
                        ^ ([&]() {
                                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__16__x 
                                    = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS0__14__x;
                                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__16__Vfuncout 
                                    = (VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__16__x, 0xdU) 
                                       | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__16__x, 0x13U));
                            }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__16__Vfuncout)) 
                       ^ ([&]() {
                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__17__x 
                                = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS0__14__x;
                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__17__Vfuncout 
                                = (VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__17__x, 0x16U) 
                                   | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__17__x, 0xaU));
                        }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__17__Vfuncout));
            }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS0__14__Vfuncout) 
         + ([&]() {
                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__z 
                    = vlSelfRef.sha256_stream__DOT__u_core__DOT__c_q;
                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__y 
                    = vlSelfRef.sha256_stream__DOT__u_core__DOT__b_q;
                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__x 
                    = vlSelfRef.sha256_stream__DOT__u_core__DOT__a_q;
                vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__Vfuncout 
                    = (((vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__x 
                         & vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__y) 
                        ^ (vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__x 
                           & vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__z)) 
                       ^ (vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__y 
                          & vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__z));
            }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Maj__18__Vfuncout));
    vlSelfRef.sha256_stream__DOT__core_cv_out[0U] = vlSelfRef.sha256_stream__DOT__u_core__DOT__h_q;
    vlSelfRef.sha256_stream__DOT__core_cv_out[1U] = vlSelfRef.sha256_stream__DOT__u_core__DOT__g_q;
    vlSelfRef.sha256_stream__DOT__core_cv_out[2U] = (IData)(
                                                            (((QData)((IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__e_q)) 
                                                              << 0x20U) 
                                                             | (QData)((IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__f_q))));
    vlSelfRef.sha256_stream__DOT__core_cv_out[3U] = (IData)(
                                                            ((((QData)((IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__e_q)) 
                                                               << 0x20U) 
                                                              | (QData)((IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__f_q))) 
                                                             >> 0x20U));
    vlSelfRef.sha256_stream__DOT__core_cv_out[4U] = vlSelfRef.sha256_stream__DOT__u_core__DOT__d_q;
    vlSelfRef.sha256_stream__DOT__core_cv_out[5U] = vlSelfRef.sha256_stream__DOT__u_core__DOT__c_q;
    vlSelfRef.sha256_stream__DOT__core_cv_out[6U] = (IData)(
                                                            (((QData)((IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__a_q)) 
                                                              << 0x20U) 
                                                             | (QData)((IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__b_q))));
    vlSelfRef.sha256_stream__DOT__core_cv_out[7U] = (IData)(
                                                            ((((QData)((IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__a_q)) 
                                                               << 0x20U) 
                                                              | (QData)((IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__b_q))) 
                                                             >> 0x20U));
    vlSelfRef.sha256_stream__DOT__core_ready = vlSelfRef.sha256_stream__DOT__u_core__DOT__ready;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out[0U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_out[0U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out[1U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_out[1U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out[2U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_out[2U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out[3U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_out[3U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out[4U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_out[4U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out[5U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_out[5U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out[6U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_out[6U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out[7U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_out[7U];
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__2(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__2\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.sha256_stream__DOT__core_start = vlSelfRef.sha256_stream__DOT__start_pulse;
    vlSelfRef.sha256_stream__DOT__core_cv_in[0U] = 
        vlSelfRef.sha256_stream__DOT__start_cv[0U];
    vlSelfRef.sha256_stream__DOT__core_cv_in[1U] = 
        vlSelfRef.sha256_stream__DOT__start_cv[1U];
    vlSelfRef.sha256_stream__DOT__core_cv_in[2U] = 
        vlSelfRef.sha256_stream__DOT__start_cv[2U];
    vlSelfRef.sha256_stream__DOT__core_cv_in[3U] = 
        vlSelfRef.sha256_stream__DOT__start_cv[3U];
    vlSelfRef.sha256_stream__DOT__core_cv_in[4U] = 
        vlSelfRef.sha256_stream__DOT__start_cv[4U];
    vlSelfRef.sha256_stream__DOT__core_cv_in[5U] = 
        vlSelfRef.sha256_stream__DOT__start_cv[5U];
    vlSelfRef.sha256_stream__DOT__core_cv_in[6U] = 
        vlSelfRef.sha256_stream__DOT__start_cv[6U];
    vlSelfRef.sha256_stream__DOT__core_cv_in[7U] = 
        vlSelfRef.sha256_stream__DOT__start_cv[7U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__start 
        = vlSelfRef.sha256_stream__DOT__core_start;
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in[0U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_in[0U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in[1U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_in[1U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in[2U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_in[2U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in[3U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_in[3U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in[4U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_in[4U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in[5U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_in[5U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in[6U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_in[6U];
    vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in[7U] 
        = vlSelfRef.sha256_stream__DOT__core_cv_in[7U];
}

VL_INLINE_OPT void Vtop___024root___nba_comb__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.sha256_stream__DOT__u_core__DOT__Wt_from_block 
        = (((0U == (0x1fU & (((IData)(0x1ffU) - VL_SHIFTL_III(9,9,32, (IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q), 5U)) 
                             - (IData)(0x1fU)))) ? 0U
             : (vlSelfRef.sha256_stream__DOT__start_block[
                (((IData)(0x1fU) + (0x1ffU & (((IData)(0x1ffU) 
                                               - VL_SHIFTL_III(9,9,32, (IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q), 5U)) 
                                              - (IData)(0x1fU)))) 
                 >> 5U)] << ((IData)(0x20U) - (0x1fU 
                                               & (((IData)(0x1ffU) 
                                                   - 
                                                   VL_SHIFTL_III(9,9,32, (IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q), 5U)) 
                                                  - (IData)(0x1fU)))))) 
           | (vlSelfRef.sha256_stream__DOT__start_block[
              (0xfU & ((((IData)(0x1ffU) - VL_SHIFTL_III(9,9,32, (IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q), 5U)) 
                        - (IData)(0x1fU)) >> 5U))] 
              >> (0x1fU & (((IData)(0x1ffU) - VL_SHIFTL_III(9,9,32, (IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q), 5U)) 
                           - (IData)(0x1fU)))));
    vlSelfRef.sha256_stream__DOT__u_core__DOT__Wt = 
        ((0x10U > (IData)(vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q))
          ? vlSelfRef.sha256_stream__DOT__u_core__DOT__Wt_from_block
          : (((([&]() {
                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS1__0__x 
                                = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                                [0xeU];
                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS1__0__Vfuncout 
                                = ((([&]() {
                                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__1__x 
                                                = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS1__0__x;
                                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__1__Vfuncout 
                                                = (
                                                   VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__1__x, 0x11U) 
                                                   | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__1__x, 0xfU));
                                        }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__1__Vfuncout) 
                                    ^ ([&]() {
                                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__2__x 
                                                = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS1__0__x;
                                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__2__Vfuncout 
                                                = (
                                                   VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__2__x, 0x13U) 
                                                   | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__2__x, 0xdU));
                                        }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__2__Vfuncout)) 
                                   ^ ([&]() {
                                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__shr__3__x 
                                            = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS1__0__x;
                                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__shr__3__Vfuncout 
                                            = VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__shr__3__x, 0xaU);
                                    }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__shr__3__Vfuncout));
                        }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS1__0__Vfuncout) 
               + vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
               [9U]) + ([&]() {
                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS0__4__x 
                            = vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
                            [1U];
                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS0__4__Vfuncout 
                            = ((([&]() {
                                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__5__x 
                                            = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS0__4__x;
                                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__5__Vfuncout 
                                            = (VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__5__x, 7U) 
                                               | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__5__x, 0x19U));
                                    }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__5__Vfuncout) 
                                ^ ([&]() {
                                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__6__x 
                                            = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS0__4__x;
                                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__6__Vfuncout 
                                            = (VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__6__x, 0x12U) 
                                               | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__6__x, 0xeU));
                                    }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__6__Vfuncout)) 
                               ^ ([&]() {
                                    vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__shr__7__x 
                                        = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS0__4__x;
                                    vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__shr__7__Vfuncout 
                                        = VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__shr__7__x, 3U);
                                }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__shr__7__Vfuncout));
                    }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__SmS0__4__Vfuncout)) 
             + vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q
             [0U]));
    vlSelfRef.sha256_stream__DOT__u_core__DOT__T1 = 
        ((((vlSelfRef.sha256_stream__DOT__u_core__DOT__h_q 
            + ([&]() {
                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS1__8__x 
                                = vlSelfRef.sha256_stream__DOT__u_core__DOT__e_q;
                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS1__8__Vfuncout 
                                = ((([&]() {
                                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__9__x 
                                                = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS1__8__x;
                                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__9__Vfuncout 
                                                = (
                                                   VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__9__x, 6U) 
                                                   | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__9__x, 0x1aU));
                                        }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__9__Vfuncout) 
                                    ^ ([&]() {
                                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__10__x 
                                                = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS1__8__x;
                                            vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__10__Vfuncout 
                                                = (
                                                   VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__10__x, 0xbU) 
                                                   | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__10__x, 0x15U));
                                        }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__10__Vfuncout)) 
                                   ^ ([&]() {
                                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__11__x 
                                            = vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS1__8__x;
                                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__11__Vfuncout 
                                            = (VL_SHIFTR_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__11__x, 0x19U) 
                                               | VL_SHIFTL_III(32,32,32, vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__11__x, 7U));
                                    }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__rotr__11__Vfuncout));
                        }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__BigS1__8__Vfuncout)) 
           + ([&]() {
                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__z 
                            = vlSelfRef.sha256_stream__DOT__u_core__DOT__g_q;
                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__y 
                            = vlSelfRef.sha256_stream__DOT__u_core__DOT__f_q;
                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__x 
                            = vlSelfRef.sha256_stream__DOT__u_core__DOT__e_q;
                        vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__Vfuncout 
                            = ((vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__x 
                                & vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__y) 
                               ^ ((~ vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__x) 
                                  & vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__z));
                    }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__Ch__12__Vfuncout)) 
          + ([&]() {
                    vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t 
                        = vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q;
                    vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__Vfuncout 
                        = ((0x20U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                            ? ((0x10U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                ? ((8U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                    ? ((4U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                        ? ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xc67178f2U
                                                : 0xbef9a3f7U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xa4506cebU
                                                : 0x90befffaU))
                                        : ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x8cc70208U
                                                : 0x84c87814U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x78a5636fU
                                                : 0x748f82eeU)))
                                    : ((4U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                        ? ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x682e6ff3U
                                                : 0x5b9cca4fU)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x4ed8aa4aU
                                                : 0x391c0cb3U))
                                        : ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x34b0bcb5U
                                                : 0x2748774cU)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x1e376c08U
                                                : 0x19a4c116U))))
                                : ((8U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                    ? ((4U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                        ? ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x106aa070U
                                                : 0xf40e3585U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xd6990624U
                                                : 0xd192e819U))
                                        : ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xc76c51a3U
                                                : 0xc24b8b70U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xa81a664bU
                                                : 0xa2bfe8a1U)))
                                    : ((4U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                        ? ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x92722c85U
                                                : 0x81c2c92eU)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x766a0abbU
                                                : 0x650a7354U))
                                        : ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x53380d13U
                                                : 0x4d2c6dfcU)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x2e1b2138U
                                                : 0x27b70a85U)))))
                            : ((0x10U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                ? ((8U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                    ? ((4U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                        ? ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x14292967U
                                                : 0x6ca6351U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xd5a79147U
                                                : 0xc6e00bf3U))
                                        : ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xbf597fc7U
                                                : 0xb00327c8U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xa831c66dU
                                                : 0x983e5152U)))
                                    : ((4U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                        ? ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x76f988daU
                                                : 0x5cb0a9dcU)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x4a7484aaU
                                                : 0x2de92c6fU))
                                        : ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x240ca1ccU
                                                : 0xfc19dc6U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xefbe4786U
                                                : 0xe49b69c1U))))
                                : ((8U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                    ? ((4U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                        ? ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xc19bf174U
                                                : 0x9bdc06a7U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x80deb1feU
                                                : 0x72be5d74U))
                                        : ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x550c7dc3U
                                                : 0x243185beU)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x12835b01U
                                                : 0xd807aa98U)))
                                    : ((4U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                        ? ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xab1c5ed5U
                                                : 0x923f82a4U)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x59f111f1U
                                                : 0x3956c25bU))
                                        : ((2U & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0xe9b5dba5U
                                                : 0xb5c0fbcfU)
                                            : ((1U 
                                                & (IData)(vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__t))
                                                ? 0x71374491U
                                                : 0x428a2f98U))))));
                }(), vlSelfRef.__Vfunc_sha256_stream__DOT__u_core__DOT__K_const__13__Vfuncout)) 
         + vlSelfRef.sha256_stream__DOT__u_core__DOT__Wt);
}

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<2> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtop___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vtop___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtop___024root___eval_phase__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtop___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY(((0x64U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("/home/pavand96/litefury-pcie-sha256/sim/../rtl/sha256_stream.sv", 35, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vtop___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("/home/pavand96/litefury-pcie-sha256/sim/../rtl/sha256_stream.sv", 35, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("/home/pavand96/litefury-pcie-sha256/sim/../rtl/sha256_stream.sv", 35, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vtop___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vtop___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.aclk & 0xfeU)))) {
        Verilated::overWidthError("aclk");}
    if (VL_UNLIKELY(((vlSelfRef.aresetn & 0xfeU)))) {
        Verilated::overWidthError("aresetn");}
    if (VL_UNLIKELY(((vlSelfRef.s_axis_tvalid & 0xfeU)))) {
        Verilated::overWidthError("s_axis_tvalid");}
    if (VL_UNLIKELY(((vlSelfRef.s_axis_tlast & 0xfeU)))) {
        Verilated::overWidthError("s_axis_tlast");}
    if (VL_UNLIKELY(((vlSelfRef.m_axis_tready & 0xfeU)))) {
        Verilated::overWidthError("m_axis_tready");}
}
#endif  // VL_DEBUG
