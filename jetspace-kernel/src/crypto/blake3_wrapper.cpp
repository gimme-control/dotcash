#include "blake3_wrapper.h"
#include <span>
#include <cstring>
extern "C" {
#include "../../third_party/blake3/c/blake3.h"
}

std::array<uint8_t, 32> blake3_hash(const std::vector<uint8_t>& data) {
    blake3_hasher hasher;
    blake3_hasher_init(&hasher);
    blake3_hasher_update(&hasher, data.data(), data.size());
    
    std::array<uint8_t, 32> hash;
    blake3_hasher_finalize(&hasher, hash.data(), hash.size());
    return hash;
}

std::array<uint8_t, 32> blake3_hash_tree(const std::vector<std::array<uint8_t, 32>>& leaves) {
    if (leaves.empty()) {
        return std::array<uint8_t, 32>{};
    }
    if (leaves.size() == 1) {
        return leaves[0];
    }
    
    std::vector<std::array<uint8_t, 32>> current = leaves;
    while (current.size() > 1) {
        std::vector<std::array<uint8_t, 32>> next;
        for (size_t i = 0; i < current.size(); i += 2) {
            if (i + 1 < current.size()) {
                std::vector<uint8_t> pair;
                pair.insert(pair.end(), current[i].begin(), current[i].end());
                pair.insert(pair.end(), current[i+1].begin(), current[i+1].end());
                next.push_back(blake3_hash(pair));
            } else {
                next.push_back(current[i]);
            }
        }
        current = next;
    }
    return current[0];
}

std::array<uint8_t, 32> pedersen_commit(uint64_t value, const std::array<uint8_t, 32>& salt) {
    std::vector<uint8_t> input;
    input.resize(8 + 32);
    std::memcpy(input.data(), &value, 8);
    std::memcpy(input.data() + 8, salt.data(), 32);
    return blake3_hash(input);
}

