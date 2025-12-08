#include "block.h"
#include "../crypto/blake3_wrapper.h"
#include <span>
#include <cstring>

std::array<uint8_t, 32> BlockHeader::compute_hash() const {
    std::vector<uint8_t> data;
    data.resize(8 + 8 + 32 + 32 + 32);
    
    size_t offset = 0;
    std::memcpy(data.data() + offset, &height, 8);
    offset += 8;
    std::memcpy(data.data() + offset, &timestamp, 8);
    offset += 8;
    std::memcpy(data.data() + offset, prev_hash.data(), 32);
    offset += 32;
    std::memcpy(data.data() + offset, state_root.data(), 32);
    offset += 32;
    std::memcpy(data.data() + offset, nullifier_root.data(), 32);
    
    return blake3_hash(data);
}

