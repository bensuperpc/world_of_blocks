cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

find_package(mcmap_core QUIET)

if (NOT mcmap_core_FOUND)
    FetchContent_Declare(
        mcmap_core
        #GIT_REPOSITORY git@github.com:spoutn1k/mcmap.git
        #GIT_TAG        0f474f41a797ed9a32f14722e120bdfe83acd4bd

        GIT_REPOSITORY git@github.com:bensuperpc/mcmap.git
        GIT_TAG        9d181654e2c5b439a1185799e2e00e9faa9c88da
    )
    FetchContent_MakeAvailable(mcmap_core)
endif()