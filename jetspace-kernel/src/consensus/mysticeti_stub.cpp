#include "mysticeti_stub.h"
#include "../crypto/dilithium_wrapper.h"
#include <algorithm>

std::vector<ConsensusNode> initialize_consensus_nodes(size_t num_nodes) {
    std::vector<ConsensusNode> nodes;
    nodes.reserve(num_nodes);
    
    for (size_t i = 0; i < num_nodes; ++i) {
        auto [pk, sk] = dilithium_keygen();
        nodes.push_back({pk, sk});
    }
    
    return nodes;
}

std::vector<std::vector<uint8_t>> simulate_mysticeti_consensus(
    const std::array<uint8_t, 32>& header_hash,
    const std::vector<ConsensusNode>& nodes) {
    
    std::vector<std::vector<uint8_t>> signatures;
    size_t quorum = (nodes.size() * 5 + 6) / 7;
    
    for (size_t i = 0; i < quorum && i < nodes.size(); ++i) {
        auto sig = dilithium_sign(nodes[i].secret_key, header_hash);
        signatures.push_back(sig);
    }
    
    return signatures;
}

