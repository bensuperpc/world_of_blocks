cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

set(BUILD_RAYLIB_CPP_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(raygui QUIET)

if (NOT raylib_FOUND)
    FetchContent_Declare(raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG 3.2
    )
    FetchContent_MakeAvailable(raygui)
    include_directories(${raygui_SOURCE_DIR}/src)
endif()