"""
test_sha256_stream.py — cocotb testbench for sha256_stream.

Strategy:
  - Drive the AXI-Stream slave (s_axis) with a sequence of 64-byte random
    messages, each as 4 beats of 128 bits.
  - Capture the AXI-Stream master (m_axis) output as 2 beats of 128 bits
    per message and compare against hashlib.sha256.

The dut consumes one message at a time (single engine), so the input side
has natural back-pressure: s_axis_tready will fall while the core is busy
or while the previous digest hasn't been read out.
"""

import hashlib
import os
import random

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge


CLK_PERIOD_NS = 8  # 125 MHz, matches XDMA axi_aclk on the LiteFury build
DW = 128
BPB = DW // 8  # bytes per beat = 16


def bytes_to_beats(msg: bytes):
    """Split a 64-byte message into 4 × 128-bit big-endian beats."""
    assert len(msg) == 64
    return [int.from_bytes(msg[i * BPB:(i + 1) * BPB], "big") for i in range(4)]


def beats_to_bytes(beats):
    """Concatenate 2 × 128-bit beats (digest) into 32 bytes."""
    out = b""
    for b in beats:
        out += int(b).to_bytes(BPB, "big")
    return out


async def reset(dut, cycles=8):
    dut.aresetn.value = 0
    dut.s_axis_tdata.value = 0
    dut.s_axis_tkeep.value = (1 << (DW // 8)) - 1
    dut.s_axis_tvalid.value = 0
    dut.s_axis_tlast.value = 0
    dut.m_axis_tready.value = 0
    for _ in range(cycles):
        await RisingEdge(dut.aclk)
    dut.aresetn.value = 1
    await RisingEdge(dut.aclk)


async def send_message(dut, msg: bytes):
    beats = bytes_to_beats(msg)
    keep_all = (1 << (DW // 8)) - 1
    for i, beat in enumerate(beats):
        dut.s_axis_tdata.value = beat
        dut.s_axis_tkeep.value = keep_all
        dut.s_axis_tvalid.value = 1
        dut.s_axis_tlast.value = 1 if (i == 3) else 0
        # Wait until tready is high to consummate the beat.
        await RisingEdge(dut.aclk)
        while dut.s_axis_tready.value != 1:
            await RisingEdge(dut.aclk)
    dut.s_axis_tvalid.value = 0
    dut.s_axis_tlast.value = 0


async def recv_digest(dut) -> bytes:
    dut.m_axis_tready.value = 1
    beats = []
    while len(beats) < 2:
        await RisingEdge(dut.aclk)
        if dut.m_axis_tvalid.value == 1 and dut.m_axis_tready.value == 1:
            beats.append(int(dut.m_axis_tdata.value))
    return beats_to_bytes(beats)


@cocotb.test()
async def test_known_vector(dut):
    """SHA-256 of 64 zero bytes — well-known test vector."""
    cocotb.start_soon(Clock(dut.aclk, CLK_PERIOD_NS, units="ns").start())
    await reset(dut)

    msg = b"\x00" * 64
    expected = hashlib.sha256(msg).digest()

    await send_message(dut, msg)
    got = await recv_digest(dut)

    dut._log.info(f"msg = {msg.hex()}")
    dut._log.info(f"got = {got.hex()}")
    dut._log.info(f"exp = {expected.hex()}")
    assert got == expected, f"Digest mismatch: got {got.hex()}, expected {expected.hex()}"


@cocotb.test()
async def test_random_messages(dut):
    """Push N random 64B messages and verify each digest."""
    cocotb.start_soon(Clock(dut.aclk, CLK_PERIOD_NS, units="ns").start())
    await reset(dut)

    n = int(os.environ.get("NUM_MSGS", "16"))
    random.seed(0xC0FFEE)
    msgs = [bytes(random.randint(0, 255) for _ in range(64)) for _ in range(n)]

    # Serial: send/recv per message (the single-engine dut requires this).
    for i, msg in enumerate(msgs):
        await send_message(dut, msg)
        got = await recv_digest(dut)
        exp = hashlib.sha256(msg).digest()
        assert got == exp, (
            f"msg #{i} mismatch:\n  msg={msg.hex()}\n  got={got.hex()}\n  exp={exp.hex()}"
        )

    dut._log.info(f"PASSED {n} random messages")


@cocotb.test()
async def test_pipelined_throughput(dut):
    """Stream N messages back-to-back with concurrent send/recv to exercise
    the 2-way pipeline.  Reports observed cycles/msg vs theoretical."""
    cocotb.start_soon(Clock(dut.aclk, CLK_PERIOD_NS, units="ns").start())
    await reset(dut)

    n = int(os.environ.get("NUM_PIPE_MSGS", "32"))
    random.seed(0xBADBEEF)
    msgs = [bytes(random.randint(0, 255) for _ in range(64)) for _ in range(n)]
    expected = [hashlib.sha256(m).digest() for m in msgs]

    sender_done = cocotb.start_soon(_sender(dut, msgs))
    receiver = cocotb.start_soon(_receiver(dut, n))

    await sender_done
    digests = await receiver
    for i, (g, e) in enumerate(zip(digests, expected)):
        assert g == e, f"msg #{i} mismatch g={g.hex()} e={e.hex()}"
    dut._log.info(f"PIPELINED PASS {n} messages")


async def _sender(dut, msgs):
    for m in msgs:
        await send_message(dut, m)


async def _receiver(dut, n):
    out = []
    for _ in range(n):
        out.append(await recv_digest(dut))
    return out
