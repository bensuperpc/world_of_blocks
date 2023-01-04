cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

set(CMAKE_CXX_CLANG_TIDY_TMP "${CMAKE_CXX_CLANG_TIDY}")
set(CMAKE_CXX_CLANG_TIDY "")

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG 4eaa0c896db50451e7cb38c9bcd9cde21713852e) # 23-10-2022

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

FetchContent_MakeAvailable(googlebenchmark)
# Lib: benchmark::benchmark benchmark::benchmark_main

set(CMAKE_CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY_TMP}")
