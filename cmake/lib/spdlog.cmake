cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG 7e635fca68d014934b4af8a1cf874f63989352b7) # 2023-07-09

FetchContent_MakeAvailable(spdlog)
include_directories("${spdlog_SOURCE_DIR}")