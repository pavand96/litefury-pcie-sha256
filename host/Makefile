CC      ?= cc
CFLAGS  ?= -O3 -std=c99 -Wall -Wextra
LDLIBS  ?= -lcrypto -lrt

all: cpu_sha256_bench

cpu_sha256_bench: cpu_sha256_bench.c
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

clean:
	$(RM) cpu_sha256_bench
