cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

set(CMAKE_CXX_CLANG_TIDY_TMP "${CMAKE_CXX_CLANG_TIDY}")
set(CMAKE_CXX_CLANG_TIDY "")

FetchContent_Declare(
    googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG 604f6fd3f4b34a84ec4eb4db81d842fa4db829cd
    #GIT_SHALLOW TRUE
    ) # 16-06-2023

# Disable tests on google benchmark
set(BENCHMARK_ENABLE_TESTING
    OFF
    CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_WERROR
    OFF
    CACHE BOOL "" FORCE)
set(BENCHMARK_FORCE_WERROR
    OFF
    CACHE BOOL "" FORCE)

set(BENCHMARK_ENABLE_INSTALL
    OFF
    CACHE BOOL "" FORCE)

set(BENCHMARK_DOWNLOAD_DEPENDENCIES
    ON
    CACHE BOOL "" FORCE)

set(BENCHMARK_CXX_LINKER_FLAGS
    ""
    CACHE STRING "" FORCE)

set(BENCHMARK_CXX_LIBRARIES
    ""
    CACHE STRING "" FORCE)

set(BENCHMARK_CXX_FLAGS
    ""
    CACHE STRING "" FORCE)

set(CMAKE_CXX_FLAGS_COVERAGE
    ""
    CACHE STRING "" FORCE)

set(CMAKE_REQUIRED_FLAGS
    ""
    CACHE STRING "" FORCE)

FetchContent_MakeAvailable(googlebenchmark)
# Lib: benchmark::benchmark benchmark::benchmark_main

set(CMAKE_CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY_TMP}")
