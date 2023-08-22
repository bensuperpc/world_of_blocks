##############################################################
#   ____                                                     #
#  | __ )  ___ _ __  ___ _   _ _ __   ___ _ __ _ __   ___    #
#  |  _ \ / _ \ '_ \/ __| | | | '_ \ / _ \ '__| '_ \ / __|   #
#  | |_) |  __/ | | \__ \ |_| | |_) |  __/ |  | |_) | (__    #
#  |____/ \___|_| |_|___/\__,_| .__/ \___|_|  | .__/ \___|   #
#                             |_|             |_|            #
##############################################################
#                                                            #
#  BenLib, 2021                                              #
#  Created: 16, March, 2021                                  #
#  Modified: 17, March, 2021                                 #
#  file: CMakeLists.txt                                      #
#  CMake                                                     #
#  Source:                                                   #
#  OS: ALL                                                   #
#  CPU: ALL                                                  #
#                                                            #
##############################################################

cmake_minimum_required(VERSION 3.14)
project(
    world_of_blocks_lib
    VERSION 0.1.0
    DESCRIPTION "world of blocks lib"
    HOMEPAGE_URL "https://github.com/bensuperpc"
    LANGUAGES C CXX
)

include(../../cmake/lib/raygui.cmake)
include(../../cmake/lib/raylib.cmake)
include(../../cmake/lib/openmp.cmake)
include(../../cmake/lib/fast_noise2.cmake)
include(../../cmake/lib/json.cmake)
include(../../cmake/utile/ccache.cmake)

add_subdirectory(logger)

set(SOURCES
    world.cpp
    world_model.cpp
    player.cpp
    debugMenu.cpp
    gameContext.cpp
    GameBase.cpp
    Generator.cpp
)

set(HEADERS
    block_type.hpp
    block_utils.hpp
    world.hpp
    world_model.hpp
    player.hpp
    debugMenu.hpp
    gameContext.hpp
    Chunk.hpp
    Generator.hpp
    raygui_cpp.hpp
    GameBase.hpp
)

#add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME} ${SOURCES})
#target_precompile_headers(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/Generator.hpp>)

target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
target_link_libraries(${PROJECT_NAME} PUBLIC FastNoise2 nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_C OpenMP::OpenMP_CXX)
target_link_libraries(${PROJECT_NAME} PUBLIC logger::logger)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

set_target_properties(world_of_blocks_lib
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)


target_include_directories(
    world_of_blocks_lib INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
)


