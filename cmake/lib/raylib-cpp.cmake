cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

#find_package(raylib_cpp QUIET)

if (NOT raylib_cpp_FOUND)
    FetchContent_Declare(raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG df0cbb4204fd34fa644f1eb43914abce987a79c7 # 24-02-2023
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()