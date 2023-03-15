cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(perlin_noise
    GIT_REPOSITORY https://github.com/Reputeless/PerlinNoise.git
    GIT_TAG bdf39fe92b2a585cdef485bcec2bca8ab5614095 # 2022-12-30
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)
FetchContent_MakeAvailable(perlin_noise)
include_directories("${perlin_noise_SOURCE_DIR}")
