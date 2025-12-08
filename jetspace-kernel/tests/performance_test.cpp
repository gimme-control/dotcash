#include "crypto/blake3_wrapper.h"
#include "crypto/dilithium_wrapper.h"
#include "consensus/block.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <cstring>
#include <array>

using namespace std::chrono;

void benchmark_blake3() {
    std::cout << "\n=== BLAKE3 Performance ===\n";

    const int iterations = 10000;
    std::vector<uint8_t> data(1024, 0x42);

    auto start = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        auto hash = blake3_hash(data);
        (void)hash;
    }
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    double avg_us = duration.count() / double(iterations);
    double throughput = (data.size() * iterations) / (duration.count() / 1e6) / 1e6; // MB/s

    std::cout << "Iterations: " << iterations << "\n";
    std::cout << "Data size: " << data.size() << " bytes\n";
    std::cout << "Total time: " << duration.count() << " µs\n";
    std::cout << "Average: " << avg_us << " µs/hash\n";
    std::cout << "Throughput: " << throughput << " MB/s\n";
}

void benchmark_dilithium() {
    std::cout << "\n=== Dilithium-3 Performance ===\n";

    const int iterations = 100;
    std::array<uint8_t, 32> message;
    std::fill(message.begin(), message.end(), 0x42);

    auto keypair = dilithium_keygen();
    DilithiumPk pk = keypair.first;
    DilithiumSk sk = keypair.second;

    auto start = high_resolution_clock::now();
    DilithiumSig sig;
    for (int i = 0; i < iterations; ++i) {
        sig = dilithium_sign(sk, message);
    }
    auto end = high_resolution_clock::now();

    auto sign_duration = duration_cast<microseconds>(end - start);
    double sign_avg_us = sign_duration.count() / double(iterations);

    start = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        bool valid = dilithium_verify(message, sig, pk);
        (void)valid;
    }
    end = high_resolution_clock::now();

    auto verify_duration = duration_cast<microseconds>(end - start);
    double verify_avg_us = verify_duration.count() / double(iterations);

    std::cout << "Iterations: " << iterations << "\n";
    std::cout << "Message size: " << message.size() << " bytes\n";
    std::cout << "Sign time: " << sign_avg_us << " µs/sign\n";
    std::cout << "Verify time: " << verify_avg_us << " µs/verify\n";
}

void benchmark_block_hash() {
    std::cout << "\n=== Block Hash Performance ===\n";

    const int iterations = 1000;

    BlockHeader block;
    block.height = 0;
    std::memset(block.prev_hash.data(), 0, 32);
    block.stark_proof.clear();
    std::memset(block.state_root.data(), 0, 32);

    auto start = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        block.height = i;
        auto hash = block.compute_hash();
        (void)hash;
    }
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    double avg_us = duration.count() / double(iterations);

    std::cout << "Iterations: " << iterations << "\n";
    std::cout << "Average: " << avg_us << " µs/hash\n";
}

int main() {
    std::cout << "=== Jetspace Kernel Performance Benchmarks ===\n";

    benchmark_blake3();
    benchmark_dilithium();
    benchmark_block_hash();

    std::cout << "\n=== Benchmark Complete ===\n";
    return 0;
}
