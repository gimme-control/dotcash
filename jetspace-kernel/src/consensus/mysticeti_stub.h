#pragma once

#include "../crypto/dilithium_wrapper.h"
#include <vector>
#include <cstddef>

struct ConsensusNode {
    DilithiumPk public_key;
};

std::vector<ConsensusNode> initialize_consensus_nodes(size_t num_nodes = 7);

std::vector<std::vector<uint8_t>> simulate_mysticeti_consensus(
    const std::array<uint8_t, 32>& header_hash,
    const std::vector<ConsensusNode>& nodes
);

