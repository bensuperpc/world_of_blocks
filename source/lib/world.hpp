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
        explicit world() {}

        ~world() { unload_models(); }

        void generate_world()
        {
            std::cout << "Generating world" << std::endl;
            // Free the models
            unload_models();

            // Clear the chunks
            chunks.clear();
            chunks.shrink_to_fit();

            // Generate new perlin noise
            gen.reseed(this->seed);

            uint32_t chunk_size = world_chunk_size_x * world_chunk_size_y * world_chunk_size_z;
            chunks = std::vector<chunk>(chunk_size, chunk());

            gen.generate_word(chunks,
                              world_chunk_start_x,
                              world_chunk_start_y,
                              world_chunk_start_z,
                              world_chunk_size_x,
                              world_chunk_size_y,
                              world_chunk_size_z);

            chunks_model = std::move(world_md.generate_world_models(chunks));
        }

        void unload_models()
        {
            for (size_t ci = 0; ci < chunks.size(); ci++) {
                UnloadModel(chunks_model[ci]);
            }
            chunks_model.clear();
            chunks_model.shrink_to_fit();
        }

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
        std::vector<Model> chunks_model;
};

#endif  // WORLD_OF_CUBE_WORLD_HPP