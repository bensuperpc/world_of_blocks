cmake_minimum_required(VERSION 3.14)

project(experimentationTests LANGUAGES C CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)
include(../cmake/windows-set-path.cmake)

function(add_test_fn TEST_NAME)
  add_executable("${TEST_NAME}" "source/${TEST_NAME}.cpp")

  target_link_libraries("${TEST_NAME}" PRIVATE world_of_blocks_lib benlib_intro gtest_main)
  target_link_libraries("${TEST_NAME}" PRIVATE raylib raylib_cpp)
  target_link_libraries("${TEST_NAME}" PRIVATE FastNoise2 OpenMP::OpenMP_CXX)
  target_link_libraries("${TEST_NAME}" PRIVATE spdlog::spdlog nlohmann_json::nlohmann_json)

  if (OpenMP_FOUND OR OpenMP_CXX_FOUND)
    target_link_libraries("${TEST_NAME}" PRIVATE OpenMP::OpenMP_CXX)
  endif()

  if (CUDAToolkit_FOUND)
    target_include_directories("${TEST_NAME}" PRIVATE ${CUDAToolkit_INCLUDE_DIRS})
    target_link_libraries("${TEST_NAME}" PRIVATE CUDA::cudart)
  endif()
  set_target_properties("${TEST_NAME}"
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  )

  add_test(NAME "${TEST_NAME}" COMMAND $<TARGET_FILE:${TEST_NAME}>)
  #target_compile_features("${TEST_NAME}" PRIVATE cxx_std_20)
endfunction()

function(add_bench_fn BENCH_NAME)
  add_executable("${BENCH_NAME}" "source/${BENCH_NAME}.cpp")

  target_link_libraries("${BENCH_NAME}" PRIVATE world_of_blocks_lib benlib_intro benchmark::benchmark_main)
  target_link_libraries("${BENCH_NAME}" PRIVATE raylib raylib_cpp)
  target_link_libraries("${BENCH_NAME}" PRIVATE FastNoise2 OpenMP::OpenMP_CXX)
  target_link_libraries("${BENCH_NAME}" PRIVATE spdlog::spdlog nlohmann_json::nlohmann_json)

  if (OpenMP_FOUND OR OpenMP_CXX_FOUND)
    target_link_libraries("${BENCH_NAME}" PRIVATE OpenMP::OpenMP_CXX)
  endif()

  if (CUDAToolkit_FOUND)
    target_include_directories("${BENCH_NAME}" PRIVATE ${CUDAToolkit_INCLUDE_DIRS})
    target_link_libraries("${BENCH_NAME}" PRIVATE CUDA::cudart)
  endif()

  set_target_properties("${BENCH_NAME}"
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  )

  if(NOT CMAKE_BUILD_TYPE MATCHES Debug AND NOT CMAKE_BUILD_TYPE MATCHES Coverage)
    add_test(NAME "${BENCH_NAME}" COMMAND $<TARGET_FILE:${BENCH_NAME}>)
  elseif()
    message(STATUS "Disable ${BENCH_NAME}, Performance benchmark test only run on Release/RelWithDebInfo/MinSizeRel")
  endif()
  #target_compile_features("${TEST_NAME}" PRIVATE cxx_std_20)
endfunction()

function(add_exp_fn EXP_NAME)
  add_executable("${EXP_NAME}" "source/${EXP_NAME}.cpp")

  target_link_libraries("${EXP_NAME}" PRIVATE world_of_blocks_lib benlib_intro)
  target_link_libraries("${EXP_NAME}" PRIVATE raylib raylib_cpp)
  target_link_libraries("${EXP_NAME}" PRIVATE FastNoise2 OpenMP::OpenMP_CXX)
  target_link_libraries("${EXP_NAME}" PRIVATE spdlog::spdlog nlohmann_json::nlohmann_json)

  if (OpenMP_FOUND OR OpenMP_CXX_FOUND)
    target_link_libraries("${EXP_NAME}" PRIVATE OpenMP::OpenMP_CXX)
  endif()

  if (CUDAToolkit_FOUND)
    target_include_directories("${EXP_NAME}" PRIVATE ${CUDAToolkit_INCLUDE_DIRS})
    target_link_libraries("${EXP_NAME}" PRIVATE CUDA::cudart)
  endif()
  set_target_properties("${EXP_NAME}"
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  )
endfunction()

if(NOT WIN32)
  include(../cmake/lib/gtest.cmake)
  include(../cmake/lib/benchmark.cmake)
  include(../cmake/lib/openmp.cmake)
  include(../cmake/lib/raygui.cmake)
  include(../cmake/lib/raylib.cmake)
  include(../cmake/lib/raylib-cpp.cmake)
  include(../cmake/lib/perlin_noise.cmake)
  include(../cmake/lib/fast_noise2.cmake)
  include(../cmake/lib/spdlog.cmake)
  include(../cmake/lib/json.cmake)

  # Add tests
  add_test_fn(generator_test)
  # Add bench
  #  add_bench_fn(generator_bench)
  #add_bench_fn(noise_bench)
  # Add exp
  add_exp_fn(2d_perlin_noise_exp)
  
endif()

# ---- End-of-file commands ----

add_folders(Test)
