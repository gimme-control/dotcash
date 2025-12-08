#include <cstdio>
#include <cstring>
#include <cstdlib>
extern "C" {
#include "../third_party/dilithium/ref/api.h"
void randombytes(uint8_t *x, size_t xlen) {
    FILE *f = fopen("/dev/urandom", "r");
    fread(x, 1, xlen, f);
    fclose(f);
}
}

int main() {
    uint8_t pk[pqcrystals_dilithium3_ref_PUBLICKEYBYTES];
    uint8_t sk[pqcrystals_dilithium3_ref_SECRETKEYBYTES];
    uint8_t sig[pqcrystals_dilithium3_ref_BYTES];
    uint8_t msg[] = "test";
    uint8_t ctx[] = "";
    size_t siglen = pqcrystals_dilithium3_ref_BYTES;
    
    pqcrystals_dilithium3_ref_keypair(pk, sk);
    pqcrystals_dilithium3_ref_signature(sig, &siglen, msg, sizeof(msg), ctx, 0, sk);
    
    int result = pqcrystals_dilithium3_ref_verify(sig, siglen, msg, sizeof(msg), ctx, 0, pk);
    printf("Dilithium test: %s\n", result == 0 ? "PASS" : "FAIL");
    return result;
}
