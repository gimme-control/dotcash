#include <cstdio>
#include <cstring>
extern "C" {
#include "../third_party/blake3/c/blake3.h"
}

int main() {
    uint8_t hash[BLAKE3_OUT_LEN];
    uint8_t input[] = "test";
    
    blake3_hasher hasher;
    blake3_hasher_init(&hasher);
    blake3_hasher_update(&hasher, input, strlen((char*)input));
    blake3_hasher_finalize(&hasher, hash, BLAKE3_OUT_LEN);
    
    printf("BLAKE3 test: ");
    for (size_t i = 0; i < 8; i++) {
        printf("%02x", hash[i]);
    }
    printf("...\n");
    return 0;
}
