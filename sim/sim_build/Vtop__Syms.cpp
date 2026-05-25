// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtop__pch.h"
#include "Vtop.h"
#include "Vtop___024root.h"

// FUNCTIONS
Vtop__Syms::~Vtop__Syms()
{

    // Tear down scope hierarchy
    __Vhier.remove(0, &__Vscope_sha256_stream);
    __Vhier.remove(&__Vscope_sha256_stream, &__Vscope_sha256_stream__u_core);

}

Vtop__Syms::Vtop__Syms(VerilatedContext* contextp, const char* namep, Vtop* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
        // Check resources
        Verilated::stackCheck(475);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
    __Vscope_TOP.configure(this, name(), "TOP", "TOP", "<null>", 0, VerilatedScope::SCOPE_OTHER);
    __Vscope_sha256_stream.configure(this, name(), "sha256_stream", "sha256_stream", "sha256_stream", -9, VerilatedScope::SCOPE_MODULE);
    __Vscope_sha256_stream__u_core.configure(this, name(), "sha256_stream.u_core", "u_core", "sha256_compress", -9, VerilatedScope::SCOPE_MODULE);

    // Set up scope hierarchy
    __Vhier.add(0, &__Vscope_sha256_stream);
    __Vhier.add(&__Vscope_sha256_stream, &__Vscope_sha256_stream__u_core);

    // Setup export functions
    for (int __Vfinal = 0; __Vfinal < 2; ++__Vfinal) {
        __Vscope_TOP.varInsert(__Vfinal,"aclk", &(TOP.aclk), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"aresetn", &(TOP.aresetn), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"m_axis_tdata", &(TOP.m_axis_tdata), false, VLVT_WDATA,VLVD_OUT|VLVF_PUB_RW,0,1 ,127,0);
        __Vscope_TOP.varInsert(__Vfinal,"m_axis_tkeep", &(TOP.m_axis_tkeep), false, VLVT_UINT16,VLVD_OUT|VLVF_PUB_RW,0,1 ,15,0);
        __Vscope_TOP.varInsert(__Vfinal,"m_axis_tlast", &(TOP.m_axis_tlast), false, VLVT_UINT8,VLVD_OUT|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"m_axis_tready", &(TOP.m_axis_tready), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"m_axis_tvalid", &(TOP.m_axis_tvalid), false, VLVT_UINT8,VLVD_OUT|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"s_axis_tdata", &(TOP.s_axis_tdata), false, VLVT_WDATA,VLVD_IN|VLVF_PUB_RW,0,1 ,127,0);
        __Vscope_TOP.varInsert(__Vfinal,"s_axis_tkeep", &(TOP.s_axis_tkeep), false, VLVT_UINT16,VLVD_IN|VLVF_PUB_RW,0,1 ,15,0);
        __Vscope_TOP.varInsert(__Vfinal,"s_axis_tlast", &(TOP.s_axis_tlast), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"s_axis_tready", &(TOP.s_axis_tready), false, VLVT_UINT8,VLVD_OUT|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"s_axis_tvalid", &(TOP.s_axis_tvalid), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"DATA_WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.sha256_stream__DOT__DATA_WIDTH))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"KEEP_WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.sha256_stream__DOT__KEEP_WIDTH))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"PAD_BLOCK", const_cast<void*>(static_cast<const void*>(&(TOP.sha256_stream__DOT__PAD_BLOCK))), true, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,0,1 ,511,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"SHA256_IV", const_cast<void*>(static_cast<const void*>(&(TOP.sha256_stream__DOT__SHA256_IV))), true, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,0,1 ,255,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"aclk", &(TOP.sha256_stream__DOT__aclk), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"aresetn", &(TOP.sha256_stream__DOT__aresetn), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"beat_idx_q", &(TOP.sha256_stream__DOT__beat_idx_q), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,1,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"core_block", &(TOP.sha256_stream__DOT__core_block), false, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,0,1 ,511,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"core_cv_in", &(TOP.sha256_stream__DOT__core_cv_in), false, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,0,1 ,255,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"core_cv_out", &(TOP.sha256_stream__DOT__core_cv_out), false, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,0,1 ,255,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"core_done", &(TOP.sha256_stream__DOT__core_done), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"core_ready", &(TOP.sha256_stream__DOT__core_ready), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"core_start", &(TOP.sha256_stream__DOT__core_start), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"digest_q", &(TOP.sha256_stream__DOT__digest_q), false, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,0,1 ,255,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"digest_valid_q", &(TOP.sha256_stream__DOT__digest_valid_q), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"m_axis_tdata", &(TOP.sha256_stream__DOT__m_axis_tdata), false, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,0,1 ,127,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"m_axis_tkeep", &(TOP.sha256_stream__DOT__m_axis_tkeep), false, VLVT_UINT16,VLVD_NODIR|VLVF_PUB_RW,0,1 ,15,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"m_axis_tlast", &(TOP.sha256_stream__DOT__m_axis_tlast), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"m_axis_tready", &(TOP.sha256_stream__DOT__m_axis_tready), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"m_axis_tvalid", &(TOP.sha256_stream__DOT__m_axis_tvalid), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"msg_q", &(TOP.sha256_stream__DOT__msg_q), false, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,0,1 ,511,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"rx_state_q", &(TOP.sha256_stream__DOT__rx_state_q), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,2,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"s_axis_tdata", &(TOP.sha256_stream__DOT__s_axis_tdata), false, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,0,1 ,127,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"s_axis_tkeep", &(TOP.sha256_stream__DOT__s_axis_tkeep), false, VLVT_UINT16,VLVD_NODIR|VLVF_PUB_RW,0,1 ,15,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"s_axis_tlast", &(TOP.sha256_stream__DOT__s_axis_tlast), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"s_axis_tready", &(TOP.sha256_stream__DOT__s_axis_tready), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"s_axis_tvalid", &(TOP.sha256_stream__DOT__s_axis_tvalid), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"start_block", &(TOP.sha256_stream__DOT__start_block), false, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,0,1 ,511,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"start_cv", &(TOP.sha256_stream__DOT__start_cv), false, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,0,1 ,255,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"start_pulse", &(TOP.sha256_stream__DOT__start_pulse), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"tx_consume_digest", &(TOP.sha256_stream__DOT__tx_consume_digest), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream.varInsert(__Vfinal,"tx_state_q", &(TOP.sha256_stream__DOT__tx_state_q), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,1,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"T1", &(TOP.sha256_stream__DOT__u_core__DOT__T1), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"T2", &(TOP.sha256_stream__DOT__u_core__DOT__T2), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"W_q", &(TOP.sha256_stream__DOT__u_core__DOT__W_q), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,15 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"Wt", &(TOP.sha256_stream__DOT__u_core__DOT__Wt), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"Wt_from_block", &(TOP.sha256_stream__DOT__u_core__DOT__Wt_from_block), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"a_q", &(TOP.sha256_stream__DOT__u_core__DOT__a_q), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"av_q", &(TOP.sha256_stream__DOT__u_core__DOT__av_q), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"b_q", &(TOP.sha256_stream__DOT__u_core__DOT__b_q), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"block", &(TOP.sha256_stream__DOT__u_core__DOT__block), false, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,0,1 ,511,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"busy_q", &(TOP.sha256_stream__DOT__u_core__DOT__busy_q), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"bv_q", &(TOP.sha256_stream__DOT__u_core__DOT__bv_q), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"c_q", &(TOP.sha256_stream__DOT__u_core__DOT__c_q), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"clk", &(TOP.sha256_stream__DOT__u_core__DOT__clk), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"cv_in", &(TOP.sha256_stream__DOT__u_core__DOT__cv_in), false, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,0,1 ,255,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"cv_out", &(TOP.sha256_stream__DOT__u_core__DOT__cv_out), false, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,0,1 ,255,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"cv_q", &(TOP.sha256_stream__DOT__u_core__DOT__cv_q), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"d_q", &(TOP.sha256_stream__DOT__u_core__DOT__d_q), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"done", &(TOP.sha256_stream__DOT__u_core__DOT__done), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"done_q", &(TOP.sha256_stream__DOT__u_core__DOT__done_q), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"dv_q", &(TOP.sha256_stream__DOT__u_core__DOT__dv_q), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"e_q", &(TOP.sha256_stream__DOT__u_core__DOT__e_q), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"ev_q", &(TOP.sha256_stream__DOT__u_core__DOT__ev_q), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"f_q", &(TOP.sha256_stream__DOT__u_core__DOT__f_q), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"fv_q", &(TOP.sha256_stream__DOT__u_core__DOT__fv_q), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"g_q", &(TOP.sha256_stream__DOT__u_core__DOT__g_q), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"gv_q", &(TOP.sha256_stream__DOT__u_core__DOT__gv_q), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"h_q", &(TOP.sha256_stream__DOT__u_core__DOT__h_q), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"hv_q", &(TOP.sha256_stream__DOT__u_core__DOT__hv_q), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"i", &(TOP.sha256_stream__DOT__u_core__DOT__i), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"ready", &(TOP.sha256_stream__DOT__u_core__DOT__ready), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"rstn", &(TOP.sha256_stream__DOT__u_core__DOT__rstn), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"start", &(TOP.sha256_stream__DOT__u_core__DOT__start), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sha256_stream__u_core.varInsert(__Vfinal,"t_q", &(TOP.sha256_stream__DOT__u_core__DOT__t_q), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,5,0);
    }
}
