

# https://github.com/drogonframework/drogon/issues/1288#issuecomment-1163902139
FetchContent_Declare(drogon
    GIT_REPOSITORY https://github.com/drogonframework/drogon.git
    GIT_TAG v1.8.4  # 08-04-2023
)

# Reset CXX_FLAGS to avoid warnings from drogon
set(CMAKE_CXX_FLAGS_OLD "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "-std=c++17 -O3")

FetchContent_MakeAvailable(drogon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_OLD}")