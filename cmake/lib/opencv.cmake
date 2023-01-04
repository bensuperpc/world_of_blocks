cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)
#set(OpenCV_DIR "")

find_package(OpenCV QUIET)
if (NOT OpenCV_FOUND)
    FetchContent_Declare(
        opencv
        GIT_REPOSITORY https://github.com/opencv/opencv.git
        GIT_TAG        4.7.0
    )
    FetchContent_MakeAvailable(opencv)
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()