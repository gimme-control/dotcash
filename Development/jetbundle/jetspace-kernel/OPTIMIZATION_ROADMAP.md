# Optimization Roadmap

## Phase 1: Stone Prover Integration (Critical Path)

### Tasks
1. Build Stone Prover binaries via Docker
2. Test proof generation with Cairo circuit
3. Migrate from binary invocation to library linking
4. Validate proof sizes (~80KB target)

### Expected Impact
- Enable full end-to-end functionality
- Reduce proof generation overhead
- Improve integration stability

## Phase 2: Static Linking (High Priority)

### Tasks
1. Configure CMake for static linking
2. Link all dependencies statically
3. Verify binary size (<20 MB target)
4. Test on clean system (no shared libs)

### Expected Impact
- Single deployable binary
- Reduced dependency issues
- Better portability

## Phase 3: Performance Profiling

### Tasks
1. Instrument hot paths (hash, sign, verify)
2. Profile with perf/valgrind
3. Identify bottlenecks
4. Optimize critical sections

### Metrics to Track
- Hash computation time
- Signature generation/verification time
- Proof generation time
- Memory allocation patterns
- Cache miss rates

### Expected Impact
- >5,000 TPS target
- <20 ms verification time
- Reduced memory footprint

## Phase 4: Batch Processing

### Tasks
1. Parallelize transaction batch proving
2. Implement work-stealing queue
3. Optimize memory allocation
4. Test with varying batch sizes

### Expected Impact
- Linear scaling with cores
- Better resource utilization
- Higher throughput

## Phase 5: Memory Optimization

### Tasks
1. Implement memory pools for hot paths
2. Pre-allocate buffers
3. Reduce allocations in loops
4. Profile memory usage

### Expected Impact
- Reduced allocation overhead
- Better cache locality
- Lower memory footprint

## Phase 6: SIMD Verification

### Tasks
1. Verify BLAKE3 SIMD usage
2. Verify Dilithium AVX2 usage
3. Profile SIMD instruction usage
4. Optimize data alignment

### Expected Impact
- Faster hash computation
- Faster signature operations
- Better CPU utilization

## Phase 7: Zero-Copy Optimizations

### Tasks
1. Audit all data copies
2. Replace with const references
3. Use move semantics where appropriate
4. Profile copy overhead

### Expected Impact
- Reduced memory bandwidth
- Lower latency
- Better cache performance

## Phase 8: Cache Locality

### Tasks
1. Analyze data structure layout
2. Reorganize for better cache lines
3. Profile cache miss rates
4. Optimize hot path data access

### Expected Impact
- Lower cache miss rates
- Faster data access
- Better performance

## Success Criteria

- [ ] Binary size <20 MB (static)
- [ ] TPS >5,000
- [ ] Verification <20 ms
- [ ] Proof size ~80 KB
- [ ] Zero memory leaks
- [ ] All tests passing
- [ ] Production-ready error handling
