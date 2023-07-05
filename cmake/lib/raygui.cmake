cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

if(NOT DEFINED BUILD_EXAMPLES)
    set(BUILD_RAYGUI_EXAMPLES OFF CACHE BOOL "" FORCE)
endif()

# CMakefile are under projects/CMake
find_package(raygui QUIET)

#set(RAYGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/projects/CMake")

FetchContent_Declare(raygui
    GIT_REPOSITORY https://github.com/raysan5/raygui.git
    GIT_TAG 3.6 # 11-06-2023
    CONFIGURE_COMMAND ""
    #SOURCE_DIR     ${RAYGUI_DIR}
)
FetchContent_MakeAvailable(raygui)
include_directories(${raygui_SOURCE_DIR})