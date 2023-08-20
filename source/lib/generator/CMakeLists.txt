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
    generator
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES NONE
)

include(../../../cmake/lib/spdlog.cmake)

#add_library(${PROJECT_NAME} INTERFACE ${HEADERS} ${SOURCES})
#target_precompile_headers(${PROJECT_NAME} INTERFACE ${HEADERS})

set(HEADERS
)

# ---- Declare library ----

add_library(generator_generator INTERFACE ${HEADERS})
add_library(generator::generator ALIAS generator_generator)

set_property(
    TARGET generator_generator PROPERTY
    EXPORT_NAME generator
)

target_include_directories(
    generator_generator ${warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>"
)

target_compile_features(generator_generator INTERFACE cxx_std_20)

target_link_libraries(
    generator_generator ${warning_guard}
    INTERFACE
    FastNoise2
)


