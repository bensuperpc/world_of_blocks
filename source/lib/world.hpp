#ifndef WORLD_OF_CUBE_WORLD_HPP
#define WORLD_OF_CUBE_WORLD_HPP

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <string_view>
#include <vector>

#include <omp.h>

#include "PerlinNoise.hpp"
#include "raylib-cpp.hpp"
#include "raylib.h"

// Cube lib
#include "block.hpp"
#include "chunk.hpp"
#include "generator.hpp"
#include "world_model.hpp"

class world
{
    public:
        world();

        ~world();

        void generate_world();
        void generate_chunk(const int32_t x, const int32_t y, const int32_t z);

        void generate_world_models();
        void clear();

        int world_chunk_size_x = 4;
        int world_chunk_size_y = 1;
        int world_chunk_size_z = 4;

        int world_chunk_start_x = 0;
        int world_chunk_start_y = 0;
        int world_chunk_start_z = 0;

        siv::PerlinNoise::seed_type seed = 2510586073u;

        generator gen = generator(this->seed);
        world_model world_md = world_model();

        std::vector<chunk> chunks;
        std::vector<raylib::Model> chunks_model;
};

#endif  // WORLD_OF_CUBE_WORLD_HPP