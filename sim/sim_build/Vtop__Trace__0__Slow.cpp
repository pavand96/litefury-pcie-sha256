// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+1,0,"aclk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"aresetn",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+3,0,"s_axis_tdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBus(c+7,0,"s_axis_tkeep",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+8,0,"s_axis_tvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+9,0,"s_axis_tready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+10,0,"s_axis_tlast",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+11,0,"m_axis_tdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBus(c+15,0,"m_axis_tkeep",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+16,0,"m_axis_tvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+17,0,"m_axis_tready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+18,0,"m_axis_tlast",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("sha256_stream", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+203,0,"DATA_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+204,0,"KEEP_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBit(c+19,0,"aclk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+20,0,"aresetn",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+21,0,"s_axis_tdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBus(c+25,0,"s_axis_tkeep",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+26,0,"s_axis_tvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+27,0,"s_axis_tready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+28,0,"s_axis_tlast",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+29,0,"m_axis_tdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBus(c+33,0,"m_axis_tkeep",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+34,0,"m_axis_tvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+35,0,"m_axis_tready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+36,0,"m_axis_tlast",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+205,0,"SHA256_IV",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 255,0);
    tracep->declArray(c+213,0,"PAD_BLOCK",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 511,0);
    tracep->declBit(c+37,0,"core_start",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+38,0,"core_ready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+39,0,"core_done",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+40,0,"core_block",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 511,0);
    tracep->declArray(c+56,0,"core_cv_in",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 255,0);
    tracep->declArray(c+64,0,"core_cv_out",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 255,0);
    tracep->declBus(c+72,0,"rx_state_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declArray(c+73,0,"msg_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 511,0);
    tracep->declBus(c+89,0,"beat_idx_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declArray(c+90,0,"digest_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 255,0);
    tracep->declBit(c+98,0,"digest_valid_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+99,0,"start_pulse",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+100,0,"start_block",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 511,0);
    tracep->declArray(c+116,0,"start_cv",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 255,0);
    tracep->declBit(c+124,0,"tx_consume_digest",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+125,0,"tx_state_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->pushPrefix("u_core", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+126,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+127,0,"rstn",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+128,0,"start",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+129,0,"block",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 511,0);
    tracep->declArray(c+145,0,"cv_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 255,0);
    tracep->declBit(c+153,0,"ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+154,0,"done",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+155,0,"cv_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 255,0);
    tracep->declBus(c+163,0,"a_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+164,0,"b_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+165,0,"c_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+166,0,"d_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+167,0,"e_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+168,0,"f_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+169,0,"g_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+170,0,"h_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+171,0,"av_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+172,0,"bv_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+173,0,"cv_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+174,0,"dv_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+175,0,"ev_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+176,0,"fv_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+177,0,"gv_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+178,0,"hv_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("W_q", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 16; ++i) {
        tracep->declBus(c+179+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+195,0,"t_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBit(c+196,0,"busy_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+197,0,"done_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+198,0,"Wt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+199,0,"Wt_from_block",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+200,0,"T1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+201,0,"T2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+202,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vtop___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vtop___024root__trace_const_0, 0U, vlSelf);
    tracep->addFullCb(&Vtop___024root__trace_full_0, 0U, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_0, 0U, vlSelf);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_const_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

extern const VlWide<8>/*255:0*/ Vtop__ConstPool__CONST_ha51a22ca_0;
extern const VlWide<16>/*511:0*/ Vtop__ConstPool__CONST_h9a6efa96_0;

VL_ATTR_COLD void Vtop___024root__trace_const_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_const_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+203,(0x80U),32);
    bufp->fullIData(oldp+204,(0x10U),32);
    bufp->fullWData(oldp+205,(Vtop__ConstPool__CONST_ha51a22ca_0),256);
    bufp->fullWData(oldp+213,(Vtop__ConstPool__CONST_h9a6efa96_0),512);
}

VL_ATTR_COLD void Vtop___024root__trace_full_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullBit(oldp+1,(vlSelfRef.aclk));
    bufp->fullBit(oldp+2,(vlSelfRef.aresetn));
    bufp->fullWData(oldp+3,(vlSelfRef.s_axis_tdata),128);
    bufp->fullSData(oldp+7,(vlSelfRef.s_axis_tkeep),16);
    bufp->fullBit(oldp+8,(vlSelfRef.s_axis_tvalid));
    bufp->fullBit(oldp+9,(vlSelfRef.s_axis_tready));
    bufp->fullBit(oldp+10,(vlSelfRef.s_axis_tlast));
    bufp->fullWData(oldp+11,(vlSelfRef.m_axis_tdata),128);
    bufp->fullSData(oldp+15,(vlSelfRef.m_axis_tkeep),16);
    bufp->fullBit(oldp+16,(vlSelfRef.m_axis_tvalid));
    bufp->fullBit(oldp+17,(vlSelfRef.m_axis_tready));
    bufp->fullBit(oldp+18,(vlSelfRef.m_axis_tlast));
    bufp->fullBit(oldp+19,(vlSelfRef.sha256_stream__DOT__aclk));
    bufp->fullBit(oldp+20,(vlSelfRef.sha256_stream__DOT__aresetn));
    bufp->fullWData(oldp+21,(vlSelfRef.sha256_stream__DOT__s_axis_tdata),128);
    bufp->fullSData(oldp+25,(vlSelfRef.sha256_stream__DOT__s_axis_tkeep),16);
    bufp->fullBit(oldp+26,(vlSelfRef.sha256_stream__DOT__s_axis_tvalid));
    bufp->fullBit(oldp+27,(vlSelfRef.sha256_stream__DOT__s_axis_tready));
    bufp->fullBit(oldp+28,(vlSelfRef.sha256_stream__DOT__s_axis_tlast));
    bufp->fullWData(oldp+29,(vlSelfRef.sha256_stream__DOT__m_axis_tdata),128);
    bufp->fullSData(oldp+33,(vlSelfRef.sha256_stream__DOT__m_axis_tkeep),16);
    bufp->fullBit(oldp+34,(vlSelfRef.sha256_stream__DOT__m_axis_tvalid));
    bufp->fullBit(oldp+35,(vlSelfRef.sha256_stream__DOT__m_axis_tready));
    bufp->fullBit(oldp+36,(vlSelfRef.sha256_stream__DOT__m_axis_tlast));
    bufp->fullBit(oldp+37,(vlSelfRef.sha256_stream__DOT__core_start));
    bufp->fullBit(oldp+38,(vlSelfRef.sha256_stream__DOT__core_ready));
    bufp->fullBit(oldp+39,(vlSelfRef.sha256_stream__DOT__core_done));
    bufp->fullWData(oldp+40,(vlSelfRef.sha256_stream__DOT__core_block),512);
    bufp->fullWData(oldp+56,(vlSelfRef.sha256_stream__DOT__core_cv_in),256);
    bufp->fullWData(oldp+64,(vlSelfRef.sha256_stream__DOT__core_cv_out),256);
    bufp->fullCData(oldp+72,(vlSelfRef.sha256_stream__DOT__rx_state_q),3);
    bufp->fullWData(oldp+73,(vlSelfRef.sha256_stream__DOT__msg_q),512);
    bufp->fullCData(oldp+89,(vlSelfRef.sha256_stream__DOT__beat_idx_q),2);
    bufp->fullWData(oldp+90,(vlSelfRef.sha256_stream__DOT__digest_q),256);
    bufp->fullBit(oldp+98,(vlSelfRef.sha256_stream__DOT__digest_valid_q));
    bufp->fullBit(oldp+99,(vlSelfRef.sha256_stream__DOT__start_pulse));
    bufp->fullWData(oldp+100,(vlSelfRef.sha256_stream__DOT__start_block),512);
    bufp->fullWData(oldp+116,(vlSelfRef.sha256_stream__DOT__start_cv),256);
    bufp->fullBit(oldp+124,(vlSelfRef.sha256_stream__DOT__tx_consume_digest));
    bufp->fullCData(oldp+125,(vlSelfRef.sha256_stream__DOT__tx_state_q),2);
    bufp->fullBit(oldp+126,(vlSelfRef.sha256_stream__DOT__u_core__DOT__clk));
    bufp->fullBit(oldp+127,(vlSelfRef.sha256_stream__DOT__u_core__DOT__rstn));
    bufp->fullBit(oldp+128,(vlSelfRef.sha256_stream__DOT__u_core__DOT__start));
    bufp->fullWData(oldp+129,(vlSelfRef.sha256_stream__DOT__u_core__DOT__block),512);
    bufp->fullWData(oldp+145,(vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_in),256);
    bufp->fullBit(oldp+153,(vlSelfRef.sha256_stream__DOT__u_core__DOT__ready));
    bufp->fullBit(oldp+154,(vlSelfRef.sha256_stream__DOT__u_core__DOT__done));
    bufp->fullWData(oldp+155,(vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_out),256);
    bufp->fullIData(oldp+163,(vlSelfRef.sha256_stream__DOT__u_core__DOT__a_q),32);
    bufp->fullIData(oldp+164,(vlSelfRef.sha256_stream__DOT__u_core__DOT__b_q),32);
    bufp->fullIData(oldp+165,(vlSelfRef.sha256_stream__DOT__u_core__DOT__c_q),32);
    bufp->fullIData(oldp+166,(vlSelfRef.sha256_stream__DOT__u_core__DOT__d_q),32);
    bufp->fullIData(oldp+167,(vlSelfRef.sha256_stream__DOT__u_core__DOT__e_q),32);
    bufp->fullIData(oldp+168,(vlSelfRef.sha256_stream__DOT__u_core__DOT__f_q),32);
    bufp->fullIData(oldp+169,(vlSelfRef.sha256_stream__DOT__u_core__DOT__g_q),32);
    bufp->fullIData(oldp+170,(vlSelfRef.sha256_stream__DOT__u_core__DOT__h_q),32);
    bufp->fullIData(oldp+171,(vlSelfRef.sha256_stream__DOT__u_core__DOT__av_q),32);
    bufp->fullIData(oldp+172,(vlSelfRef.sha256_stream__DOT__u_core__DOT__bv_q),32);
    bufp->fullIData(oldp+173,(vlSelfRef.sha256_stream__DOT__u_core__DOT__cv_q),32);
    bufp->fullIData(oldp+174,(vlSelfRef.sha256_stream__DOT__u_core__DOT__dv_q),32);
    bufp->fullIData(oldp+175,(vlSelfRef.sha256_stream__DOT__u_core__DOT__ev_q),32);
    bufp->fullIData(oldp+176,(vlSelfRef.sha256_stream__DOT__u_core__DOT__fv_q),32);
    bufp->fullIData(oldp+177,(vlSelfRef.sha256_stream__DOT__u_core__DOT__gv_q),32);
    bufp->fullIData(oldp+178,(vlSelfRef.sha256_stream__DOT__u_core__DOT__hv_q),32);
    bufp->fullIData(oldp+179,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[0]),32);
    bufp->fullIData(oldp+180,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[1]),32);
    bufp->fullIData(oldp+181,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[2]),32);
    bufp->fullIData(oldp+182,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[3]),32);
    bufp->fullIData(oldp+183,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[4]),32);
    bufp->fullIData(oldp+184,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[5]),32);
    bufp->fullIData(oldp+185,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[6]),32);
    bufp->fullIData(oldp+186,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[7]),32);
    bufp->fullIData(oldp+187,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[8]),32);
    bufp->fullIData(oldp+188,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[9]),32);
    bufp->fullIData(oldp+189,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[10]),32);
    bufp->fullIData(oldp+190,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[11]),32);
    bufp->fullIData(oldp+191,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[12]),32);
    bufp->fullIData(oldp+192,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[13]),32);
    bufp->fullIData(oldp+193,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[14]),32);
    bufp->fullIData(oldp+194,(vlSelfRef.sha256_stream__DOT__u_core__DOT__W_q[15]),32);
    bufp->fullCData(oldp+195,(vlSelfRef.sha256_stream__DOT__u_core__DOT__t_q),6);
    bufp->fullBit(oldp+196,(vlSelfRef.sha256_stream__DOT__u_core__DOT__busy_q));
    bufp->fullBit(oldp+197,(vlSelfRef.sha256_stream__DOT__u_core__DOT__done_q));
    bufp->fullIData(oldp+198,(vlSelfRef.sha256_stream__DOT__u_core__DOT__Wt),32);
    bufp->fullIData(oldp+199,(vlSelfRef.sha256_stream__DOT__u_core__DOT__Wt_from_block),32);
    bufp->fullIData(oldp+200,(vlSelfRef.sha256_stream__DOT__u_core__DOT__T1),32);
    bufp->fullIData(oldp+201,(vlSelfRef.sha256_stream__DOT__u_core__DOT__T2),32);
    bufp->fullIData(oldp+202,(vlSelfRef.sha256_stream__DOT__u_core__DOT__i),32);
}
