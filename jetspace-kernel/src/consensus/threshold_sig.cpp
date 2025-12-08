#include "threshold_sig.h"
#include "../crypto/dilithium_wrapper.h"

bool verify_threshold_signature(
    const std::array<uint8_t, 32>& msg,
    const std::vector<std::vector<uint8_t>>& signatures,
    const std::vector<DilithiumPk>& public_keys,
    size_t threshold) {

    if (signatures.size() < threshold || public_keys.size() < threshold) {
        return false;
    }

    size_t valid_count = 0;
    for (size_t i = 0; i < signatures.size() && i < public_keys.size(); ++i) {
        if (dilithium_verify(msg, signatures[i], public_keys[i])) {
            valid_count++;
        }
    }

    return valid_count >= threshold;
}
