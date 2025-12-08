# Jetspace Kernel

A post-quantum, privacy-preserving ledger kernel implementing the Jetspace architecture. This project demonstrates the engineering feasibility of building a blockchain kernel with strict layer separation, quantum-resistant cryptography, and constant-time verification.

## Conceptual Foundation

The Jetspace Kernel embodies three orthogonal architectural layers:

1. **Linkage Layer (The Jet)**: Irreversible cryptographic history using BLAKE3 hashing and Dilithium signatures. This layer ensures that once data enters the system, it creates an immutable record that cannot be altered without detection.

2. **Conservation Layer (The Flow)**: Zero-knowledge proofs enforcing value conservation via Cairo circuits and STARK proofs. This layer guarantees that all transactions satisfy conservation laws (e.g., input value equals output value plus fees) without revealing the transaction details.

3. **Canonicalization Layer (The Ruler)**: Anonymous consensus mechanism selecting the canonical timeline via threshold signatures. This layer breaks symmetry when multiple valid extensions exist, ensuring all participants agree on a single version of history.

## Infrastructure Components

### Cryptographic Primitives

**BLAKE3**: Fast, secure hash function used for Merkle tree construction and commitment schemes. BLAKE3 provides tree hashing capabilities essential for efficient state root computation.

**Dilithium**: Post-quantum digital signature scheme standardized by NIST. This project uses Dilithium-3, which provides 128-bit security against both classical and quantum attacks. The signature operations include:
- Key generation: Creating public/private key pairs
- Signing: Generating signatures over message hashes
- Verification: Validating signatures against public keys
- Threshold aggregation: Combining multiple signatures for consensus quorums

### Zero-Knowledge Proof System

**Cairo**: A Turing-complete language for writing zero-knowledge circuits. Cairo programs compile to STARK-friendly bytecode that can be proven and verified efficiently.

**Stone Prover**: StarkWare's production STARK proving engine. Stone generates approximately 80KB proofs that can be verified in constant time, regardless of the number of transactions being proven. The proofs are recursive, meaning each proof can verify the previous proof plus new transactions, enabling constant-time verification for light clients.

### Build System

The project uses CMake for building a statically linked C++ binary. All dependencies are compiled as static libraries to ensure portability and eliminate runtime dependencies.

## Engineering Approach

This kernel is designed as a proof of concept demonstrating that:
- Post-quantum cryptography can replace all elliptic curve primitives
- Layer separation enables independent upgrades without system-wide refactoring
- STARK proofs provide quantum security without trusted setups
- Constant-time verification is achievable through recursive proof composition

The implementation prioritizes clarity and maintainability over premature optimization. Each layer is isolated behind minimal interfaces, allowing future enhancements without breaking existing functionality.

## Learning Objectives

This project serves as a practical exploration of:
- Post-quantum cryptographic primitives and their integration
- Zero-knowledge proof systems and their application to blockchain privacy
- Recursive proof composition for scalable verification
- Architectural patterns for long-lived software systems

## Development Status

This is an active development project. The implementation follows a sequential build order where each phase depends on the previous phase's completion. You may request the status by contactinng joel-saucedo and the repository owner.

## References

- [BLAKE3](https://github.com/BLAKE3-team/BLAKE3)
- [Dilithium](https://github.com/pq-crystals/dilithium)
- [Stone Prover](https://github.com/starkware-libs/stone-prover)
- [Cairo Language](https://github.com/starkware-libs/cairo)
