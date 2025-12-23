cmake_minimum_required(VERSION 3.22)
project(dotcash LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(dotcash ${SOURCES})

target_include_directories(dotcash PRIVATE 
    include 
    ${OPENSSL_INCLUDE_DIR}
)

target_link_libraries(dotcash PRIVATE OpenSSL::Crypto)
