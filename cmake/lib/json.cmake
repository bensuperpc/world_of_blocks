cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

#find_package(json QUIET)

if (NOT json_FOUND)
    FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG c71ecde505ebf236048a731c81ae8ecaf2b260a8 # 2023-06-11
    )
    FetchContent_MakeAvailable(json)
    # nlohmann_json::nlohmann_json
endif()
