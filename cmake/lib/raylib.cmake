cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

if(NOT DEFINED BUILD_EXAMPLES)
  set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
endif()

if(NOT DEFINED BUILD_GAMES)
  set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
endif()

if(NOT DEFINED INCLUDE_EVERYTHING)
  set(INCLUDE_EVERYTHING ON CACHE BOOL "" FORCE)
endif()

if(NOT DEFINED OPENGL_VERSION)
  #set(OPENGL_VERSION OFF CACHE STRING "4.3" FORCE)
endif()

#find_package(raylib QUIET)
if (NOT raylib_FOUND)
    FetchContent_Declare(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 4.5.0  # 08-04-2023
    )
    FetchContent_MakeAvailable(raylib)
endif()
