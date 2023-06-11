cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

if(NOT DEFINED BUILD_EXAMPLES)
    set(BUILD_RAYLIB_EXAMPLES OFF CACHE BOOL "" FORCE)
endif()


find_package(raygui QUIET)

if (NOT raylib_FOUND)
    FetchContent_Declare(raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG 3.6 # 11-06-2023
    )
    FetchContent_MakeAvailable(raygui)
    include_directories(${raygui_SOURCE_DIR}/src)
endif()