cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

#find_package(json QUIET)

if (NOT json_FOUND)
    FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG b2306145e1789368e6f261680e8dc007e91cc986 # 2023-02-24
    )
    FetchContent_MakeAvailable(json)
    # nlohmann_json::nlohmann_json
endif()
