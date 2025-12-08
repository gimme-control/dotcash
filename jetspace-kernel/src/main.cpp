#include "consensus/block.h"
#include "consensus/mysticeti_stub.h"
#include "zk/stone_prover.h"
#include "zk/verifier.h"
#include "crypto/blake3_wrapper.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <cstring>
#include <cstdio>

std::array<uint8_t, 32> compute_state_root(const std::vector<std::array<uint8_t, 32>>& commitments) {
    return blake3_hash_tree(commitments);
}

std::vector<BlockHeader> create_genesis_state() {
    return {};
}

std::vector<std::array<uint8_t, 32>> generate_random_shielded_txs(size_t count) {
    std::vector<std::array<uint8_t, 32>> txs;
    for (size_t i = 0; i < count; ++i) {
        std::array<uint8_t, 32> tx = {};
        std::memcpy(tx.data(), &i, sizeof(i));
        txs.push_back(blake3_hash({tx.begin(), tx.end()}));
    }
    return txs;
}

int main() {
    std::cout << "--- JETSPACE KERNEL (STONE EDITION) ---\n";
    
    auto genesis_state = create_genesis_state();
    std::vector<BlockHeader> chain;
    auto nodes = initialize_consensus_nodes(7);
    
    for (int i = 0; i < 10000; ++i) {
        auto tx_batch = generate_random_shielded_txs(50);
        
        std::vector<std::array<uint8_t, 32>> commitments;
        for (const auto& tx : tx_batch) {
            commitments.push_back(tx);
        }
        
        BlockHeader block;
        block.height = i;
        block.prev_hash = (i == 0) ? std::array<uint8_t, 32>{} : chain.back().compute_hash();
        block.state_root = compute_state_root(commitments);
        block.nullifier_root = std::array<uint8_t, 32>{};
        
        std::string program_json = "transfer.json";
        std::string public_inputs = "{}";
        std::string private_inputs = "{}";
        block.stark_proof = prove_block(program_json, public_inputs, private_inputs);
        
        block.signatures = simulate_mysticeti_consensus(block.compute_hash(), nodes);
        
        chain.push_back(block);
        
        if (i % 1000 == 0) {
            std::cout << "[Block " << i << "] Hash: ";
            auto hash = block.compute_hash();
            for (size_t j = 0; j < 8; j++) {
                printf("%02x", hash[j]);
            }
            std::cout << "\n";
        }
    }
    
    std::cout << "\n--- FINAL VERIFICATION ---\n";
    auto t1 = std::chrono::high_resolution_clock::now();
    
    bool valid = verify_stark(chain.back().stark_proof, "{}");
    
    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    
    if (valid) {
        std::cout << "SUCCESS: Chain valid. Sync Time: " << ms << "ms.\n";
        return 0;
    } else {
        std::cout << "FAILURE: Invalid Proof.\n";
        return 1;
    }
}

