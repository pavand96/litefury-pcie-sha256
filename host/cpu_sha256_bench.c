/*
 * cpu_sha256_bench.c — fair single-threaded CPU SHA-256 baseline.
 *
 * Hashes N independent 64-byte messages and reports throughput.
 * Uses OpenSSL's EVP API which on modern CPUs will dispatch to SHA-NI
 * (Intel SHA extensions) when available — matching what a normal app
 * would see.
 *
 * Build:   make -C host cpu_sha256_bench
 * Run  :   ./host/cpu_sha256_bench <num_msgs> <iterations>
 *
 *   num_msgs   : number of 64-byte messages per iteration
 *   iterations : how many times to repeat the inner hash loop (for timing)
 *
 * Reports best-of-iterations throughput in MB/s of *input* bytes.
 */

#define _POSIX_C_SOURCE 200809L
#include <openssl/evp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static double now_s(void) {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec + t.tv_nsec * 1e-9;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "usage: %s <num_msgs> <iterations>\n", argv[0]);
        return 1;
    }
    size_t n_msgs = strtoull(argv[1], NULL, 0);
    int    iters  = atoi(argv[2]);
    if (n_msgs == 0 || iters <= 0) {
        fprintf(stderr, "num_msgs and iterations must be positive\n");
        return 1;
    }

    /* Pre-allocate input buffer; fill with a pattern so the compiler can't
     * elide the hashing (the digests are written into different per-msg
     * outputs and accumulated). */
    uint8_t *msgs = malloc(n_msgs * 64);
    if (!msgs) { perror("malloc"); return 1; }
    for (size_t i = 0; i < n_msgs * 64; i++) msgs[i] = (uint8_t)(i * 31 + 7);
    uint8_t digest[32];

    /* Reuse one EVP_MD_CTX across all hashes — avoids per-hash alloc. */
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_sha256();
    if (!ctx) { fprintf(stderr, "EVP_MD_CTX_new failed\n"); return 1; }

    double best_s = 1e30;
    uint64_t accum = 0;
    for (int it = 0; it < iters; it++) {
        double t0 = now_s();
        for (size_t i = 0; i < n_msgs; i++) {
            unsigned int dlen = 32;
            EVP_DigestInit_ex(ctx, md, NULL);
            EVP_DigestUpdate(ctx, msgs + i * 64, 64);
            EVP_DigestFinal_ex(ctx, digest, &dlen);
            accum ^= ((uint64_t *)digest)[0];   /* prevent dead-code elim */
        }
        double t1 = now_s();
        if (t1 - t0 < best_s) best_s = t1 - t0;
    }
    EVP_MD_CTX_free(ctx);

    double in_bytes = (double)n_msgs * 64.0;
    double mbps = (in_bytes / best_s) / (1024.0 * 1024.0);
    double us_per_hash = (best_s * 1e6) / (double)n_msgs;
    fprintf(stderr, "[cpu] msgs=%zu  best=%.6fs  %.2f MB/s in  %.3f us/hash  accum=%016lx\n",
            n_msgs, best_s, mbps, us_per_hash, (unsigned long)accum);
    /* Stdout one-line machine-parseable summary. */
    printf("CPU_MBPS=%.2f CPU_US_PER_HASH=%.3f\n", mbps, us_per_hash);

    free(msgs);
    return 0;
}
