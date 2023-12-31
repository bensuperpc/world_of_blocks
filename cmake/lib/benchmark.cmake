cmake_minimum_required(VERSION 3.14.0)

find_package(benchmark QUIET)

if (NOT benchmark_FOUND)
    message(STATUS "benchmark not found on system, downloading...")
    include(FetchContent)

    set(CMAKE_CXX_CLANG_TIDY_TMP "${CMAKE_CXX_CLANG_TIDY}")
    set(CMAKE_CXX_CLANG_TIDY "")

    FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG ca8d0f7b613ac915cd6b161ab01b7be449d1e1cd
        #GIT_SHALLOW TRUE
        ) # 12-10-2023

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

    set_target_properties(benchmark
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif()
