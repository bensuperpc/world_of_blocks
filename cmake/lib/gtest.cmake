cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG 9b12f749fa972d08703d8459e9bf3239617491ca) # 16-06-2023

# Disable tests on gtest
set(gtest_build_tests
    OFF
    CACHE BOOL "" FORCE)
set(gtest_build_samples
    OFF
    CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
# Lib: gtest gtest_main
