cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

if(NOT DEFINED BOOST_INCLUDE_LIBRARIES)
  set(BOOST_INCLUDE_LIBRARIES system)
endif()


if(NOT DEFINED BOOST_ENABLE_CMAKE)
  set(BOOST_ENABLE_CMAKE ON)
endif()


FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.81.0
  #GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Boost)

