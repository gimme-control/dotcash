#include "crypto/blake3_wrapper.h"
#include "crypto/dilithium_wrapper.h"
#include <cstdio>
#include <cstring>
#include <vector>

int main() {
    std::vector<uint8_t> data = {0x74, 0x65, 0x73, 0x74};
    auto hash = blake3_hash(data);
    printf("BLAKE3 wrapper: ");
    for (size_t i = 0; i < 8; i++) {
        printf("%02x", hash[i]);
    }
    printf("...\n");
    
    auto [pk, sk] = dilithium_keygen();
    std::array<uint8_t, 32> msg = {};
    std::memcpy(msg.data(), "test", 4);
    auto sig = dilithium_sign(sk, msg);
    bool valid = dilithium_verify(msg, sig, pk);
    printf("Dilithium wrapper: %s\n", valid ? "PASS" : "FAIL");
    
    return valid ? 0 : 1;
}
