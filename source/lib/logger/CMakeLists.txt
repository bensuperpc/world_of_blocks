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
    logger
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES NONE
)


# ---- Declare library ----

add_library(logger_logger INTERFACE)
add_library(logger::logger ALIAS logger_logger)

set_property(
    TARGET logger_logger PROPERTY
    EXPORT_NAME logger
)

target_include_directories(
    logger_logger ${warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>"
)

target_compile_features(logger_logger INTERFACE cxx_std_20)
