#pragma once

#include "../crypto/dilithium_wrapper.h"
#include <array>
#include <vector>
#include <cstdint>

bool verify_threshold_signature(
    const std::array<uint8_t, 32>& msg,
    const std::vector<std::vector<uint8_t>>& signatures,
    const std::vector<DilithiumPk>& public_keys,
    size_t threshold = 5
);

