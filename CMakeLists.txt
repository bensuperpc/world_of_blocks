cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    world_of_blocks
    VERSION 1.0.0
    DESCRIPTION "The world of cubes!"
    HOMEPAGE_URL "https://github.com/bensuperpc"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare options ----
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# ---- Dependencies ----

add_subdirectory(source/lib) # world_of_blocks_lib
add_subdirectory(source/intro) # benlib_intro

#include(cmake/lib/json.cmake)
#include(cmake/lib/opencv.cmake)
include(cmake/lib/openmp.cmake)
include(cmake/lib/raylib.cmake)
include(cmake/lib/perlin_noise.cmake)

# ---- Declare executable ----

add_executable(world_of_blocks_exe source/main.cpp source/game.cpp)
add_executable(world_of_blocks::exe ALIAS world_of_blocks_exe)

set_property(TARGET world_of_blocks_exe PROPERTY OUTPUT_NAME world_of_blocks)

target_compile_features(world_of_blocks_exe PRIVATE cxx_std_20)

target_link_libraries(world_of_blocks_exe PRIVATE world_of_blocks_lib benlib_intro)
target_link_libraries(world_of_blocks_exe PRIVATE raylib OpenMP::OpenMP_CXX)

set_target_properties(world_of_blocks_exe
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT world_of_blocks_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of world_of_blocks"
  )
endif()

include(cmake/dev-mode.cmake)
