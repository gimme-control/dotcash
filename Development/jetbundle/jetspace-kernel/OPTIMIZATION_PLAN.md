# Optimization Plan

## Phase 1: Stone Prover Integration (CRITICAL)

**Status**: Blocked on Docker daemon

**Steps**:
1. Start Docker: `sudo systemctl start docker` (or equivalent)
2. Build Stone Prover: `docker build -t stone-prover third_party/stone-prover`
3. Extract binaries: `docker run --rm -v $(pwd)/libs:/output stone-prover cp /usr/local/bin/cpu_air_prover /output/`
4. Update CMakeLists.txt to link libstone.a
5. Test proof generation

**Expected Impact**: Enable full end-to-end functionality

## Phase 2: Static Linking

**Status**: Ready to implement

**Steps**:
1. Add `-static` flag to CMake
2. Link all dependencies statically
3. Verify binary size (<20 MB target)
4. Test on clean system

**Expected Impact**: Single deployable binary, better portability

## Phase 3: Performance Profiling

**Status**: Benchmarks ready

**Steps**:
1. Run `perf_test` to establish baseline
2. Profile with `perf record ./build/zk_kernel`
3. Identify hot paths
4. Optimize critical sections

**Expected Impact**: >5,000 TPS, <20 ms verification

## Phase 4: Memory Optimization

**Status**: Pending profiling

**Steps**:
1. Implement memory pools for hot paths
2. Pre-allocate buffers
3. Reduce allocations in loops
4. Profile memory usage

**Expected Impact**: Lower latency, better cache performance

## Methodology

1. **Measure First**: Always benchmark before optimizing
2. **One Change at a Time**: Isolate optimizations
3. **Verify Correctness**: Tests must pass after each change
4. **Document Results**: Track performance improvements
5. **Iterate**: Continuous improvement cycle

