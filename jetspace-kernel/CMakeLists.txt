cmake_minimum_required(VERSION 3.20)
project(jetspace_kernel CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -flto -fPIC")

find_library(BLAKE3_LIB blake3 HINTS ${CMAKE_SOURCE_DIR}/libs)
if(NOT BLAKE3_LIB)
    message(FATAL_ERROR "libblake3.a not found in libs/")
endif()

find_library(DILITHIUM_LIB dilithium HINTS ${CMAKE_SOURCE_DIR}/libs)
if(NOT DILITHIUM_LIB)
    message(FATAL_ERROR "libdilithium.a not found in libs/")
endif()

find_library(STONE_LIB stone HINTS ${CMAKE_SOURCE_DIR}/libs)
if(NOT STONE_LIB)
    message(WARNING "libstone.a not found - Stone integration will use binaries")
endif()

include_directories(third_party/blake3/c)
include_directories(third_party/dilithium/ref)
include_directories(third_party/stone-prover/src)

find_program(CAIRO_COMPILE cairo-compile)
if(CAIRO_COMPILE)
    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/transfer.json
        COMMAND ${CAIRO_COMPILE} ${CMAKE_SOURCE_DIR}/circuits/transfer.cairo
                --output ${CMAKE_BINARY_DIR}/transfer.json
        DEPENDS ${CMAKE_SOURCE_DIR}/circuits/transfer.cairo
        COMMENT "Compiling Cairo circuit"
    )
    add_custom_target(compile_circuits DEPENDS ${CMAKE_BINARY_DIR}/transfer.json)
else()
    message(WARNING "cairo-compile not found - Cairo circuit compilation skipped")
    add_custom_target(compile_circuits)
endif()

add_executable(zk_kernel
    src/main.cpp
    src/crypto/blake3_wrapper.cpp
    src/crypto/dilithium_wrapper.cpp
    src/zk/stone_prover.cpp
    src/zk/verifier.cpp
    src/consensus/block.cpp
    src/consensus/mysticeti_stub.cpp
    src/consensus/threshold_sig.cpp
)

target_compile_definitions(zk_kernel PRIVATE DILITHIUM_MODE=3)

target_link_libraries(zk_kernel
    PRIVATE
    ${BLAKE3_LIB}
    ${DILITHIUM_LIB}
    pthread
    dl
)

add_dependencies(zk_kernel compile_circuits)

# Performance test
add_executable(perf_test tests/performance_test.cpp
    src/crypto/blake3_wrapper.cpp
    src/crypto/dilithium_wrapper.cpp
    src/consensus/block.cpp
)
target_link_libraries(perf_test ${BLAKE3_LIB} ${DILITHIUM_LIB})
target_include_directories(perf_test PRIVATE src)
target_compile_definitions(perf_test PRIVATE DILITHIUM_MODE=3)
