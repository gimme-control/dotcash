#pragma once

#include <array>
#include <vector>
#include <cstdint>

struct BlockHeader {
    uint64_t height;
    uint64_t timestamp;

    std::array<uint8_t, 32> prev_hash;
    std::array<uint8_t, 32> state_root;
    std::array<uint8_t, 32> nullifier_root;

    std::vector<uint8_t> stark_proof;

    std::vector<std::vector<uint8_t>> signatures;

    std::array<uint8_t, 32> compute_hash() const;
};
