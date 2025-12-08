#include "dilithium_wrapper.h"
#include <span>
#include <cstring>
extern "C" {
#include "../../third_party/dilithium/ref/api.h"
#include "../../third_party/dilithium/ref/randombytes.h"
}

std::pair<DilithiumPk, DilithiumSk> dilithium_keygen() {
    DilithiumPk pk;
    DilithiumSk sk;
    pqcrystals_dilithium3_ref_keypair(pk.data(), sk.data());
    return {pk, sk};
}

DilithiumSig dilithium_sign(const DilithiumSk& sk, const std::array<uint8_t, 32>& msg) {
    DilithiumSig sig(pqcrystals_dilithium3_ref_BYTES);
    size_t siglen = sig.size();
    const uint8_t ctx[] = "";
    pqcrystals_dilithium3_ref_signature(sig.data(), &siglen, msg.data(), msg.size(), ctx, 0, sk.data());
    sig.resize(siglen);
    return sig;
}

bool dilithium_verify(const std::array<uint8_t, 32>& msg, const DilithiumSig& sig, const DilithiumPk& pk) {
    const uint8_t ctx[] = "";
    return pqcrystals_dilithium3_ref_verify(sig.data(), sig.size(), msg.data(), msg.size(), ctx, 0, pk.data()) == 0;
}

std::vector<DilithiumSig> aggregate_sigs(const std::vector<DilithiumSig>& sigs, uint8_t threshold_bitmap) {
    std::vector<DilithiumSig> result;
    for (size_t i = 0; i < sigs.size() && i < 7; ++i) {
        if (threshold_bitmap & (1 << i)) {
            result.push_back(sigs[i]);
        }
    }
    return result;
}
