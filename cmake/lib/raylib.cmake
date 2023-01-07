cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
set(INCLUDE_EVERYTHING ON CACHE BOOL "" FORCE)
#set(OPENGL_VERSION OFF CACHE STRING "4.3" FORCE)

#find_package(raylib QUIET)
if (NOT raylib_FOUND)
    FetchContent_Declare(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 4.2.0
    )
    FetchContent_MakeAvailable(raylib)
endif()