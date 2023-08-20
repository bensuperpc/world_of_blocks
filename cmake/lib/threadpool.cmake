cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(bs-thread-pool
    GIT_REPOSITORY https://github.com/bshoshany/thread-pool.git
    GIT_TAG cabb3df5876c9a6824b07fcb0ff73d4a0e506ca0 # 2023-07-14
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)
FetchContent_MakeAvailable(bs-thread-pool)
include_directories("${bs-thread-pool_SOURCE_DIR}")
