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

# ---- Declare library ----

add_library(
    world_of_blocks_lib OBJECT
    source/lib.cpp
)

target_include_directories(
    world_of_blocks_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(world_of_blocks_lib PUBLIC cxx_std_20)

# ---- Declare executable ----

add_executable(world_of_blocks_exe source/main.cpp)
add_executable(world_of_blocks::exe ALIAS world_of_blocks_exe)

set_property(TARGET world_of_blocks_exe PROPERTY OUTPUT_NAME world_of_blocks)

target_compile_features(world_of_blocks_exe PRIVATE cxx_std_20)

target_link_libraries(world_of_blocks_exe PRIVATE world_of_blocks_lib)

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
