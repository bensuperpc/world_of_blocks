# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(world_of_blocksTests LANGUAGES CXX)

# ---- Tests ----

add_executable(world_of_blocks_test source/world_of_blocks_test.cpp)
target_link_libraries(world_of_blocks_test PRIVATE world_of_blocks_lib)
target_compile_features(world_of_blocks_test PRIVATE cxx_std_17)

add_test(NAME world_of_blocks_test COMMAND world_of_blocks_test)

# ---- End-of-file commands ----

add_folders(Test)
