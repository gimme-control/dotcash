#pragma once

#include <array>
#include <vector>
#include <cstdint>

std::array<uint8_t, 32> blake3_hash(const std::vector<uint8_t>& data);

std::array<uint8_t, 32> blake3_hash_tree(const std::vector<std::array<uint8_t, 32>>& leaves);

std::array<uint8_t, 32> pedersen_commit(uint64_t value, const std::array<uint8_t, 32>& salt);

