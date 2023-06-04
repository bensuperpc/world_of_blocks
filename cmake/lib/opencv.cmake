cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)
set(OpenCV_DIR ${CMAKE_CURRENT_BINARY_DIR})

find_package(OpenCV QUIET)

if (NOT OpenCV_FOUND)
    #set(OpenCV_STATIC ON)
    set(BUILD_EXAMPLES CACHE BOOL OFF)
    set(BUILD_DOCS CACHE BOOL OFF)
    set(BUILD_TESTS CACHE BOOL OFF)
    set(BUILD_PERF_TESTS CACHE BOOL OFF)
    #set(BUILD_PACKAGE CACHE BOOL OFF)


    set(BUILD_opencv_apps CACHE BOOL OFF)

    FetchContent_Declare(
        OpenCV
        GIT_REPOSITORY https://github.com/opencv/opencv.git
        GIT_TAG        4.7.0
        #GIT_SHALLOW    TRUE
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(OpenCV)
    #set(OpenCV_DIR ${CMAKE_CURRENT_BINARY_DIR})
    #include_directories(${OpenCV_INCLUDE_DIRS})
    #message(FATAL_ERROR "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
    #find_package(OpenCV REQUIRED)

    #include_directories(${OpenCV_INCLUDE_DIRS})
    #target_include_directories("${NAME}" PRIVATE
    #${OPENCV_CONFIG_FILE_INCLUDE_DIR}
    #${OPENCV_MODULE_opencv_core_LOCATION}/include
    #${OPENCV_MODULE_opencv_highgui_LOCATION}/include
    #)
    #target_link_libraries("${NAME}" PRIVATE opencv_core opencv_highgui)
    #target_link_libraries("${NAME}" PRIVATE ${OpenCV_LIBS})
    #opencv_add_module()
    
endif()
