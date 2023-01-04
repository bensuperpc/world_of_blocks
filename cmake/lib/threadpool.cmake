cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(bs-thread-pool
    GIT_REPOSITORY https://github.com/bshoshany/thread-pool.git
    GIT_TAG 67fad04348b91cf93bdfad7495d298f54825602c # 2022-10-23
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)
FetchContent_MakeAvailable(bs-thread-pool)
include_directories("${bs-thread-pool_SOURCE_DIR}")
