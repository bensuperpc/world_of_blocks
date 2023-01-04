cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
  vector
  GIT_REPOSITORY https://github.com/bensuperpc/vector.git
  GIT_TAG 9febb9c84e7b73e6c621afd920dd3c8bb47a130c) # 2022-10-23

FetchContent_MakeAvailable(vector)
