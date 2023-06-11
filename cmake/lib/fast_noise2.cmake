cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

set(FASTNOISE2_NOISETOOL OFF CACHE BOOL "Build Noise Tool" FORCE)

FetchContent_Declare(FastNoise2
    GIT_REPOSITORY https://github.com/Auburn/FastNoise2.git
    GIT_TAG 0928ca22cd4cfd50e9b17cec4fe9d867b59c3943 # 2023-06-07
)
FetchContent_MakeAvailable(FastNoise2)
