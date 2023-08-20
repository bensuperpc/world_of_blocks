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

#set (CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install CACHE PATH "default install path" FORCE)
#set (CMAKE_INSTALL_LIBDIR ${CMAKE_BINARY_DIR}/lib CACHE PATH "default install path" FORCE)

#message(STATUS "CMAKE_INSTALL_LIBDIR: ${CMAKE_INSTALL_LIBDIR}")
if (NOT raylib_FOUND)
    FetchContent_Declare(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 4.5.0  # 08-04-2023
    )
    FetchContent_MakeAvailable(raylib)
endif()

set_target_properties(raylib
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

