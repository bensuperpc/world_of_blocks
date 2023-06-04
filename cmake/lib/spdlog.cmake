cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG 0ca574ae168820da0268b3ec7607ca7b33024d05) # 2023-04-08

FetchContent_MakeAvailable(spdlog)