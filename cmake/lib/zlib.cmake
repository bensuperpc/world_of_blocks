cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

find_package(zlib QUIET)

set(ZLIB_LIBRARY zlib)

if (NOT zlib_FOUND)
    FetchContent_Declare(
        zlib
        GIT_REPOSITORY https://github.com/madler/zlib.git
        GIT_TAG        v1.2.13
    )
    FetchContent_MakeAvailable(zlib)
endif()