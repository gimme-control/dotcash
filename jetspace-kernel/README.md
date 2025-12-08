# Jetspace Kernel

Post-quantum, privacy-preserving ledger kernel. Three orthogonal layers: linkage (BLAKE3 + Dilithium), conservation (Cairo/STARK), canonicalization (threshold sigs).

## Architecture

**Linkage**: BLAKE3 hashing + Dilithium-3 signatures for immutable history.  
**Conservation**: Cairo circuits + Stone Prover (STARK) for zero-knowledge value conservation.  
**Canonicalization**: 5-of-7 Dilithium threshold signatures for consensus.

## Stack

- **BLAKE3**: Merkle trees, commitments
- **Dilithium-3**: Post-quantum signatures (NIST standard)
- **Cairo**: ZK circuit language
- **Stone Prover**: STARK proving engine (~80KB proofs, constant-time verify)
- **CMake**: Static C++ binary

## Build

```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
```

Binary: `build/zk_kernel` (302 KB)

## Usage

Run the kernel:
```bash
./build/zk_kernel
```

Run performance benchmarks:
```bash
./build/perf_test
```

## Results

### Performance Metrics

**BLAKE3 Hashing**: 2.28 µs/hash, 448.7 MB/s throughput  
**Block Hash**: 0.60 µs/hash  
**Dilithium-3 Sign**: 1,808 µs/sign  
**Dilithium-3 Verify**: 500 µs/verify  
**End-to-End**: 100 blocks generated (10 transactions per block, proof verification fails due to missing Stone Prover)

### What This Demonstrates

The kernel implements the three-layer architecture with working cryptographic primitives. BLAKE3 provides fast hashing for Merkle trees and commitments. Dilithium-3 enables post-quantum signatures for consensus. The Cairo circuit enforces value conservation, and the block structure links everything cryptographically.

### Current Limitations

- **Stone Prover**: Not integrated (requires Docker build). Proof generation uses placeholder.
- **Proof Verification**: Fails because Stone Prover binaries are missing.
- **Consensus**: Simplified stub (not full DAG-BFT implementation).
- **End-to-End**: Blocked on Stone Prover integration for full functionality.

The core cryptographic operations work. Full end-to-end testing requires Stone Prover binaries.

## Status

Active development. Sequential build order. Contact joel-saucedo or repo owner for status.

## References

- [BLAKE3](https://github.com/BLAKE3-team/BLAKE3)
- [Dilithium](https://github.com/pq-crystals/dilithium)
- [Stone Prover](https://github.com/starkware-libs/stone-prover)
- [Cairo](https://github.com/starkware-libs/cairo)
