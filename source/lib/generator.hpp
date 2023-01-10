#ifndef WORLD_OF_CUBE_GENERATOR_HPP
#define WORLD_OF_CUBE_GENERATOR_HPP

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

// Cube lib
#include "block.hpp"
#include "chunk.hpp"
#include "math.hpp"

class generator
{
    public:
        generator(uint32_t _seed);

        generator();

        ~generator();

        void reseed(uint32_t seed);

        uint32_t randomize_seed();

        uint32_t get_seed();

        void generate_2d_heightmap(std::vector<uint32_t>& heightmap,
                                   const int begin_x,
                                   const int begin_y,
                                   const int begin_z,
                                   const uint32_t size_x,
                                   const uint32_t size_y,
                                   const uint32_t size_z);

        void generate_3d_heightmap(std::vector<uint32_t>& heightmap,
                                   const int begin_x,
                                   const int begin_y,
                                   const int begin_z,
                                   const uint32_t size_x,
                                   const uint32_t size_y,
                                   const uint32_t size_z);

        std::vector<chunk> generate_word(const int begin_chunk_x,
                                         const int begin_chunk_y,
                                         const int begin_chunk_z,
                                         const uint32_t chunk_x,
                                         const uint32_t chunk_y,
                                         const uint32_t chunk_z);

        void generate_word(std::vector<chunk>& chunks,
                           const int begin_chunk_x,
                           const int begin_chunk_y,
                           const int begin_chunk_z,
                           const uint32_t chunk_x,
                           const uint32_t chunk_y,
                           const uint32_t chunk_z,
                           const bool generate_3d_terrian = true);

        void generate_2d(std::vector<block>& blocks,
                         const int begin_x,
                         const int begin_y,
                         const int begin_z,
                         const uint32_t size_x,
                         const uint32_t size_y,
                         const uint32_t size_z);

        void generate_3d(std::vector<block>& blocks,
                         const int begin_x,
                         const int begin_y,
                         const int begin_z,
                         const uint32_t size_x,
                         const uint32_t size_y,
                         const uint32_t size_z);

    private:
        // default seed
        siv::PerlinNoise::seed_type seed = 2647393077u;
        siv::PerlinNoise perlin {seed};
        int32_t octaves = 4;
        double persistence = 0.8f;
        double lacunarity = 255.0f;
};

#endif  // WORLD_OF_CUBE_GENERATOR_HPP