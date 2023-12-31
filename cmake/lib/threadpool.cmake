cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(bs-thread-pool
    GIT_REPOSITORY https://github.com/bshoshany/thread-pool.git
    GIT_TAG 6790920f61ab3e928ddaea835ab6a803d467f41d # 2023-12-28
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)
FetchContent_MakeAvailable(bs-thread-pool)
include_directories("${bs-thread-pool_SOURCE_DIR}/include")
