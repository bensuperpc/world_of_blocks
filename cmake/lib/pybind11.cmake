cmake_minimum_required(VERSION 3.15)

find_package(Python 3.8 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11)
# add_subdirectory(pybind11)

if (NOT pybind11_FOUND)
	include(FetchContent)
	FetchContent_Declare(
		pybind11
		GIT_REPOSITORY https://github.com/pybind/pybind11.git
		GIT_TAG v2.10.3
		GIT_SHALLOW TRUE
	)
	FetchContent_MakeAvailable(pybind11)
endif()

#pybind11_add_module(${PROJECT_NAME} main.cpp)
