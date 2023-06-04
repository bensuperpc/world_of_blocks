cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

#find_package(json QUIET)

if (NOT json_FOUND)
    FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG bbe337c3a30d5f6eea418b4aee399525536de37a # 2023-03-08
    )
    FetchContent_MakeAvailable(json)
    # nlohmann_json::nlohmann_json
endif()
