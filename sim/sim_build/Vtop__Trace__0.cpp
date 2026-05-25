// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtop___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    bufp->chgBit(oldp+0,(vlSelfRef.aclk));
    bufp->chgBit(oldp+1,(vlSelfRef.aresetn));
    bufp->chgWData(oldp+2,(vlSelfRef.s_axis_tdata),128);
    bufp->chgSData(oldp+6,(vlSelfRef.s_axis_tkeep),16);
    bufp->chgBit(oldp+7,(vlSelfRef.s_axis_tvalid));
    bufp->chgBit(oldp+8,(vlSelfRef.s_axis_tready));
    bufp->chgBit(oldp+9,(vlSelfRef.s_axis_tlast));
    bufp->chgWData(oldp+10,(vlSelfRef.m_axis_tdata),128);
    bufp->chgSData(oldp+14,(vlSelfRef.m_axis_tkeep),16);
    bufp->chgBit(oldp+15,(vlSelfRef.m_axis_tvalid));
    bufp->chgBit(oldp+16,(vlSelfRef.m_axis_tready));
    bufp->chgBit(oldp+17,(vlSelfRef.m_axis_tlast));
    bufp->chgBit(oldp+18,(vlSelfRef.sha256_stream__DOT__aclk));
    bufp->chgBit(oldp+19,(vlSelfRef.sha256_stream__DOT__aresetn));
    bufp->chgWData(oldp+20,(vlSelfRef.sha256_stream__DOT__s_axis_tdata),128);
    bufp->chgSData(oldp+24,(vlSelfRef.sha256_stream__DOT__s_axis_tkeep),16);
    bufp->chgBit(oldp+25,(vlSelfRef.sha256_stream__DOT__s_axis_tvalid));
    bufp->chgBit(oldp+26,(vlSelfRef.sha256_stream__DOT__s_axis_tready));
    bufp->chgBit(oldp+27,(vlSelfRef.sha256_stream__DOT__s_axis_tlast));
    bufp->chgWData(oldp+28,(vlSelfRef.sha256_stream__DOT__m_axis_tdata),128);
    bufp->chgSData(oldp+32,(vlSelfRef.sha256_stream__DOT__m_axis_tkeep),16);
    bufp->chgBit(oldp+33,(vlSelfRef.sha256_stream__DOT__m_axis_tvalid));
    bufp->chgBit(oldp+34,(vlSelfRef.sha256_stream__DOT__m_axis_tready));
    bufp->chgBit(oldp+35,(vlSelfRef.sha256_stream__DOT__m_axis_tlast));
    bufp->chgBit(oldp+36,(vlSelfRef.sha256_stream__DOT__core_start));
    bufp->chgBit(oldp+37,(vlSelfRef.sha256_stream__DOT__core_ready));
    bufp->chgBit(oldp+38,(vlSelfRef.sha256_stream__DOT__core_done));
    bufp->chgWData(oldp+39,(vlSelfRef.sha256_stream__DOT__core_block),512);
    bufp->chgWData(oldp+55,(vlSelfRef.sha256_stream__DOT__core_cv_in),256);
    bufp->chgWData(oldp+63,(vlSelfRef.sha256_stream__DOT__core_cv_out),256);
    bufp->chgCData(oldp+71,(vlSelfRef.sha256_stream__DOT__rx_state_q),3);
    bufp->chgWData(oldp+72,(vlSelfRef.sha256_stream__DOT__msg_q),512);
    bufp->chgCData(oldp+88,(vlSelfRef.sha256_stream__DOT__beat_idx_q),2);
    bufp->chgWData(oldp+89,(vlSelfRef.sha256_stream__DOT__digest_q),256);
    bufp->chgBit(oldp+97,(vlSelfRef.sha256_stream__DOT__digest_valid_q));
    bufp->chgBit(oldp+98,(vlSelfRef.sha256_stream__DOT__start_pulse));
    bufp->chgWData(oldp+99,(vlSelfRef.sha256_stream__DOT__start_block),512);
    bufp->chgWData(oldp+115,(vlSelfRef.sha256_stream__DOT__start_cv),256);
    bufp->chgBit(oldp+123,(vlSelfRef.sha256_stream__DOT__tx_consume_digest));
    bufp->chgCData(oldp+124,(vlSelfRef.sha256_stream__DOT__tx_state_q),2);
    bufp->chgBit(oldp+125,(vlSelfRef.sha256_stream__DOT__u_core__DOT__clk));
    bufp->chgBit(oldp+126,(vlSelfRef.sha256_stream__DOT__u_core__DOT__rstn));
    bufp->chgBit(oldp+127,(vlSelfRef.sha256_stream__DOT__u_core__DOT__start));
    bufp->chgWData(oldp+128,(vlSelfRef.sha256_stream__DOT__u_core__DOT__block),512);
    bufp->chgWData(oldp+144,(vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in),256);
    bufp->chgBit(oldp+152,(vlSelfRef.sha256_stream__DOT__u_core__DOT__ready));
    bufp->chgBit(oldp+153,(vlSelfRef.sha256_stream__DOT__u_core__DOT__done));
    bufp->chgWData(oldp+154,(vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out),256);
    bufp->chgIData(oldp+162,(vlSelfRef.sha256_stream__DOT__u_core__DOT__a_q),32);
    bufp->chgIData(oldp+163,(vlSelfRef.sha256_stream__DOT__u_core__DOT__b_q),32);
    bufp->chgIData(oldp+164,(vlSelfRef.sha256_stream__DOT__u_core__DOT__c_q),32);
    bufp->chgIData(oldp+165,(vlSelfRef.sha256_stream__DOT__u_core__DOT__d_q),32);
    bufp->chgIData(oldp+166,(vlSelfRef.sha256_stream__DOT__u_core__DOT__e_q),32);
    bufp->chgIData(oldp+167,(vlSelfRef.sha256_stream__DOT__u_core__DOT__f_q),32);
    bufp->chgIData(oldp+168,(vlSelfRef.sha256_stream__DOT__u_core__DOT__g_q),32);
    bufp->chgIData(oldp+169,(vlSelfRef.sha256_stream__DOT__u_core__DOT__h_q),32);
    bufp->chgIData(oldp+170,(vlSelfRef.sha256_stream__DOT__u_core__DOT__av_q),32);
    bufp->chgIData(oldp+171,(vlSelfRef.sha256_stream__DOT__u_core__DOT__bv_q),32);
    bufp->chgIData(oldp+172,(vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_q),32);
    bufp->chgIData(oldp+173,(vlSelfRef.sha256_stream__DOT__u_core__DOT__dv_q),32);
    bufp->chgIData(oldp+174,(vlSelfRef.sha256_stream__DOT__u_core__DOT__ev_q),32);
    bufp->chgIData(oldp+175,(vlSelfRef.sha256_stream__DOT__u_core__DOT__fv_q),32);
    bufp->chgIData(oldp+176,(vlSelfRef.sha256_stream__DOT__u_core__DOT__gv_q),32);
    bufp->chgIData(oldp+177,(vlSelfRef.sha256_stream__DOT__u_core__DOT__hv_q),32);
    bufp->chgIData(oldp+178,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[0]),32);
    bufp->chgIData(oldp+179,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[1]),32);
    bufp->chgIData(oldp+180,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[2]),32);
    bufp->chgIData(oldp+181,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[3]),32);
    bufp->chgIData(oldp+182,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[4]),32);
    bufp->chgIData(oldp+183,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[5]),32);
    bufp->chgIData(oldp+184,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[6]),32);
    bufp->chgIData(oldp+185,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[7]),32);
    bufp->chgIData(oldp+186,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[8]),32);
    bufp->chgIData(oldp+187,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[9]),32);
    bufp->chgIData(oldp+188,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[10]),32);
    bufp->chgIData(oldp+189,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[11]),32);
    bufp->chgIData(oldp+190,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[12]),32);
    bufp->chgIData(oldp+191,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[13]),32);
    bufp->chgIData(oldp+192,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[14]),32);
    bufp->chgIData(oldp+193,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[15]),32);
    bufp->chgCData(oldp+194,(vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q),6);
    bufp->chgBit(oldp+195,(vlSelfRef.sha256_stream__DOT__u_core__DOT__busy_q));
    bufp->chgBit(oldp+196,(vlSelfRef.sha256_stream__DOT__u_core__DOT__done_q));
    bufp->chgIData(oldp+197,(vlSelfRef.sha256_stream__DOT__u_core__DOT__Wt),32);
    bufp->chgIData(oldp+198,(vlSelfRef.sha256_stream__DOT__u_core__DOT__Wt_from_block),32);
    bufp->chgIData(oldp+199,(vlSelfRef.sha256_stream__DOT__u_core__DOT__T1),32);
    bufp->chgIData(oldp+200,(vlSelfRef.sha256_stream__DOT__u_core__DOT__T2),32);
    bufp->chgIData(oldp+201,(vlSelfRef.sha256_stream__DOT__u_core__DOT__i),32);
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
