cmake_minimum_required(VERSION 3.22)
project(dotcash LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)

add_executable(dotcash
    src/main.cpp
)

target_include_directories(dotcash PRIVATE include)
target_link_libraries(dotcash PRIVATE OpenSSL::Crypto)
