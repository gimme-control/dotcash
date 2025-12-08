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

## Build Plan

1. Build static libs: BLAKE3, Dilithium, Stone
2. Crypto wrappers: BLAKE3/Dilithium C++ interfaces
3. Cairo circuit: Shielded transfer with conservation enforcement
4. Stone integration: Prover/verifier wrappers
5. Consensus stub: 5-of-7 threshold signature aggregation
6. Main loop: Genesis → 10k blocks → verification

Target: Single statically linked binary. Zero elliptic curves. Quantum-resistant end-to-end.

## Status

Active development. Sequential build order. Contact joel-saucedo or repo owner for status.

## References

- [BLAKE3](https://github.com/BLAKE3-team/BLAKE3)
- [Dilithium](https://github.com/pq-crystals/dilithium)
- [Stone Prover](https://github.com/starkware-libs/stone-prover)
- [Cairo](https://github.com/starkware-libs/cairo)
