cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

find_package(json QUIET)

if (NOT json_FOUND)
    FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG a3e6e26dc83a726b292f5be0492fcc408663ce55 # 2022-11-05
    )
    FetchContent_MakeAvailable(json)
    # nlohmann_json::nlohmann_json
endif()