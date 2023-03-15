cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG 50e07d1c92875e66138d5d5ee3bb46ef237115bb) # 07-03-2023

# Disable tests on gtest
set(gtest_build_tests
    OFF
    CACHE BOOL "" FORCE)
set(gtest_build_samples
    OFF
    CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
# Lib: gtest gtest_main
