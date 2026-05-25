"""Direct unit test for sha256_compress — isolates core from stream wrapper."""
import hashlib
import struct
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge


def rotr(x, n): return ((x >> n) | (x << (32 - n))) & 0xFFFFFFFF


K = [
    0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,
    0x923f82a4,0xab1c5ed5,0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,
    0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,0xe49b69c1,0xefbe4786,
    0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
    0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,
    0x06ca6351,0x14292967,0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,
    0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,0xa2bfe8a1,0xa81a664b,
    0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
    0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,
    0x5b9cca4f,0x682e6ff3,0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,
    0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2,
]
H0 = [0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,
      0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19]


def compress_ref(block: bytes, h_in):
    w = list(struct.unpack(">16I", block))
    for t in range(16, 64):
        s0 = rotr(w[t-15], 7) ^ rotr(w[t-15], 18) ^ (w[t-15] >> 3)
        s1 = rotr(w[t-2], 17) ^ rotr(w[t-2], 19) ^ (w[t-2] >> 10)
        w.append((w[t-16] + s0 + w[t-7] + s1) & 0xFFFFFFFF)
    a, b, c, d, e, f, g, h = h_in
    for t in range(64):
        S1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25)
        ch = (e & f) ^ (((~e) & 0xFFFFFFFF) & g)
        T1 = (h + S1 + ch + K[t] + w[t]) & 0xFFFFFFFF
        S0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22)
        mj = (a & b) ^ (a & c) ^ (b & c)
        T2 = (S0 + mj) & 0xFFFFFFFF
        h = g; g = f; f = e; e = (d + T1) & 0xFFFFFFFF
        d = c; c = b; b = a; a = (T1 + T2) & 0xFFFFFFFF
    return [(x + y) & 0xFFFFFFFF for x, y in zip(h_in, [a, b, c, d, e, f, g, h])]


def cv_to_int(cv):
    n = 0
    for w in cv:
        n = (n << 32) | w
    return n


async def reset(dut):
    dut.rstn.value = 0
    dut.start.value = 0
    dut.block.value = 0
    dut.cv_in.value = 0
    for _ in range(4):
        await RisingEdge(dut.clk)
    dut.rstn.value = 1
    await RisingEdge(dut.clk)


@cocotb.test()
async def test_one_block_zeros(dut):
    cocotb.start_soon(Clock(dut.clk, 8, units="ns").start())
    await reset(dut)

    block = b"\x00" * 64
    iv_int = cv_to_int(H0)

    dut.block.value = int.from_bytes(block, "big")
    dut.cv_in.value = iv_int
    dut.start.value = 1
    await RisingEdge(dut.clk)
    dut.start.value = 0

    # Wait for done
    for _ in range(200):
        await RisingEdge(dut.clk)
        if dut.done.value == 1:
            break
    else:
        raise AssertionError("done never asserted")

    got = int(dut.cv_out.value)
    exp = cv_to_int(compress_ref(block, H0))
    dut._log.info(f"got = {got:064x}")
    dut._log.info(f"exp = {exp:064x}")
    assert got == exp, f"mismatch: got {got:064x} exp {exp:064x}"
