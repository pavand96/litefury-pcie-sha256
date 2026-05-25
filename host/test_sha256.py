#!/usr/bin/env python3
"""
test_sha256.py — correctness smoke test for the FPGA SHA-256 engine.

Spec implemented by the FPGA:
    output[i] = SHA-256( input[i*64 : (i+1)*64] )

For each of N 64-byte messages we write 64 bytes to /dev/xdma0_h2c_0 and
read 32 bytes back from /dev/xdma0_c2h_0. Then compare against hashlib.
"""
import argparse
import hashlib
import os
import sys
import threading


H2C = "/dev/xdma0_h2c_0"
C2H = "/dev/xdma0_c2h_0"


def write_all(fd, buf):
    mv = memoryview(buf)
    n = 0
    while n < len(mv):
        n += os.write(fd, mv[n:])


def read_all(fd, mv):
    # NOTE: must use os.read (NOT os.readv). The OOT xdma driver
    # (v2020.2.2) has a NULL fn-ptr crash in async_io_handler on the
    # readv path under kernel >=6.x; it BUGs at fs/read_write.c and
    # the engine_service workqueue dies, wedging the channel.
    n = 0
    total = len(mv)
    while n < total:
        chunk = os.read(fd, total - n)
        if not chunk:
            raise IOError(f"short read at {n}")
        mv[n:n + len(chunk)] = chunk
        n += len(chunk)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("n", type=int, nargs="?", default=8,
                    help="number of 64-byte messages")
    args = ap.parse_args()
    n = args.n

    # Deterministic input so the test is reproducible.
    inp = bytes((i * 31 + 7) & 0xFF for i in range(n * 64))
    out = bytearray(n * 32)

    # Reader must be ready before writer (otherwise H2C back-pressures &
    # the engine wedges — same lesson as litefury-pcie-addone).
    ready = threading.Event()

    def reader():
        fd = os.open(C2H, os.O_RDONLY)
        ready.set()
        try:
            read_all(fd, memoryview(out))
        finally:
            os.close(fd)

    t = threading.Thread(target=reader)
    t.start()
    ready.wait()

    fd = os.open(H2C, os.O_WRONLY)
    try:
        write_all(fd, inp)
    finally:
        os.close(fd)
    t.join()

    failed = 0
    for i in range(n):
        msg = inp[i * 64:(i + 1) * 64]
        got = bytes(out[i * 32:(i + 1) * 32])
        exp = hashlib.sha256(msg).digest()
        if got != exp:
            failed += 1
            if failed <= 5:
                print(f"FAIL #{i:3d}  msg={msg[:8].hex()}.. got={got.hex()}  exp={exp.hex()}")
    if failed:
        print(f"FAILED  {failed}/{n}")
        sys.exit(1)
    print(f"PASS  {n} hashes verified")


if __name__ == "__main__":
    main()
