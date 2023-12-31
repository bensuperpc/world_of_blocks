cmake_minimum_required(VERSION 3.14.0)

find_package(GTest QUIET)

if (NOT GTEST_FOUND)
    message(STATUS "GTest not found on system, downloading...")
    include(FetchContent)

    FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 2dd1c131950043a8ad5ab0d2dda0e0970596586a) # 12-10-2023

    # Disable tests on gtest
    set(gtest_build_tests
        OFF
        CACHE BOOL "" FORCE)
    set(gtest_build_samples
        OFF
        CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)
    # Lib: gtest gtest_main

    set_target_properties(gtest
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif()
