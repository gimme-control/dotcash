# Jetspace Kernel Metrics

## Build Metrics

- **Binary Size**: 302 KB (dynamically linked)
- **Target Size**: <20 MB (fully static)
- **Compilation Time**: <5 seconds (incremental)
- **Source Files**: 15 (headers + implementations)
- **Lines of Code**: ~600 LOC

## Library Sizes

- **libblake3.a**: 232 KB
- **libdilithium.a**: 91 KB
- **libstone.a**: Pending (Docker build required)

## Performance Targets

- **TPS**: >5,000 transactions/second
- **Verification Time**: <20 ms (light client)
- **Proof Size**: ~80 KB per block
- **Hash Time**: ~1-2 µs (BLAKE3)
- **Signature Verify**: <80 µs (Dilithium-3)

## Code Quality

- **C++ Standard**: C++20 strict
- **Memory Safety**: RAII throughout
- **Type Safety**: std::span for arrays
- **Layer Isolation**: Clean interfaces

## Optimization Checklist

- [ ] Static linking (reduce binary size)
- [ ] Stone library linking (replace binary invocation)
- [ ] Batch transaction proving
- [ ] Memory pool allocation
- [ ] SIMD optimization verification
- [ ] Cache locality improvements
- [ ] Zero-copy optimizations
