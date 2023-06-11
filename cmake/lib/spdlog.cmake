cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG 5a6b6cafa8d4aee3e6d0dd16a2cae9169141c831) # 2023-06-11

FetchContent_MakeAvailable(spdlog)
include_directories("${spdlog_SOURCE_DIR}")