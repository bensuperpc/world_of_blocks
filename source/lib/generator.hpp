#ifndef CUBE_GENERATOR_HPP
#define CUBE_GENERATOR_HPP

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
// Raylib
#include "raylib-cpp.hpp"
#include "raylib.h"
#include "raymath.h"

// Cube lib
#include "block.hpp"
#include "chunk.hpp"
#include "optimizer.hpp"

class generator
{
    public:
        explicit generator(uint32_t _seed)
            : seed(_seed)
        {
            perlin.reseed(seed);
        }

        generator() = default;

        ~generator() {}

        void reseed(uint32_t seed)
        {
            this->seed = seed;
            perlin.reseed(seed);
        }

        uint32_t randomize_seed()
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<uint32_t> dis(0, std::numeric_limits<uint32_t>::max());
            seed = dis(gen);
            perlin.reseed(seed);
            return seed;
        }

        [[nodiscard]] uint32_t get_seed() const { return seed; }

        template<typename T = int>
        void generate_2d_heightmap(std::vector<uint32_t>& heightmap,
                                   const T begin_x,
                                   const T begin_y,
                                   const T begin_z,
                                   const uint32_t size_x,
                                   const uint32_t size_y,
                                   const uint32_t size_z)
        {
            constexpr bool debug = false;

            if (heightmap.size() < size_x * size_z) {
                std::cout << "Heightmap size is not equal or bigger than size_x * size_z" << std::endl;
                exit(1);
            }

            const T end_x = static_cast<T>(begin_x + size_x);
            const T end_y = static_cast<T>(begin_y + size_y);
            const T end_z = static_cast<T>(begin_z + size_z);

            if constexpr (debug) {
                std::cout << "Generating:" << std::endl;
                std::cout << "From (xyz): " << begin_x << ", " << begin_y << ", " << begin_z << std::endl;
                std::cout << "To (xyz): " << end_x << ", " << end_y << ", " << end_z << std::endl;
                std::cout << "Size (xyz): " << size_x << ", " << size_y << ", " << size_z << std::endl;

                std::cout << "Generating 2D noise..." << std::endl;
            }

#pragma omp parallel for collapse(2) schedule(auto)
            for (uint32_t x = 0; x < size_x; x++) {
                for (uint32_t z = 0; z < size_z; z++) {
                    // Calculate real x and z from begin_x and begin_z
                    const int real_x = x + begin_x;
                    const int real_z = z + begin_z;

                    const uint32_t value_int = static_cast<uint32_t>(
                        perlin.octave2D_01(real_x / 256.0, real_z / 256.0, octaves, persistence) * lacunarity);

                    if (debug) {
                        std::cout << "x: " << x << ", z: " << z << " index: " << z * size_z + x
                                  << ", value: " << static_cast<int>(value_int) << std::endl;
                    }
                    heightmap[z * size_x + x] = value_int;
                }
            }

            if constexpr (debug) {
                // cout max and min
                auto minmax = std::minmax_element(heightmap.begin(), heightmap.end());
                std::cout << "min: " << static_cast<int>(*minmax.first) << std::endl;
                std::cout << "max: " << static_cast<int>(*minmax.second) << std::endl;
            }
        }

        template<typename T = int>
        void generate_3d_heightmap(std::vector<uint32_t>& heightmap,
                                   const T begin_x,
                                   const T begin_y,
                                   const T begin_z,
                                   const uint32_t size_x,
                                   const uint32_t size_y,
                                   const uint32_t size_z)
        {
            constexpr bool debug = false;

            if (heightmap.size() < size_x * size_y * size_z) {
                std::cout << "Heightmap size is not equal or bigger than size_x * size_y * size_z!" << std::endl;
                exit(1);
            }

            const T end_x = static_cast<T>(begin_x + size_x);
            const T end_y = static_cast<T>(begin_y + size_y);
            const T end_z = static_cast<T>(begin_z + size_z);

            if constexpr (debug) {
                std::cout << "Generating:" << std::endl;
                std::cout << "From (xyz): " << begin_x << ", " << begin_y << ", " << begin_z << std::endl;
                std::cout << "To (xyz): " << end_x << ", " << end_y << ", " << end_z << std::endl;
                std::cout << "Size (xyz): " << size_x << ", " << size_y << ", " << size_z << std::endl;

                std::cout << "Generating 3D noise..." << std::endl;
            }

#pragma omp parallel for collapse(3) schedule(auto)
            for (uint32_t x = 0; x < size_x; x++) {
                for (uint32_t z = 0; z < size_z; z++) {
                    for (uint32_t y = 0; y < size_z; y++) {
                        // Calculate real x and z from begin_x and begin_z
                        const int real_x = x + begin_x;
                        const int real_z = z + begin_z;
                        const int real_y = y + begin_y;

                        const uint32_t value_int = static_cast<uint32_t>(
                            perlin.octave3D_01(real_x / 256.0, real_z / 256.0, real_y / 256.0, octaves, persistence)
                            * lacunarity);

                        if (debug) {
                            std::cout << "x: " << x << ", y: " << y << ", z: " << z
                                      << " index: " << z * size_x + y * size_x * size_z + x
                                      << ", value: " << static_cast<int>(value_int) << std::endl;
                        }
                        heightmap[z * size_x + y * size_x * size_z + x] = value_int;
                    }
                }
            }
        }
        void generate_word(std::vector<chunk>& chunks,
                           const uint32_t chunk_x,
                           const uint32_t chunk_y,
                           const uint32_t chunk_z)
        {
            if (chunks.size() < chunk_x * chunk_y * chunk_z) {
                std::cout << "Chunks size is not equal or bigger than chunk_x * chunk_y * chunk_z!" << std::endl;
                exit(1);
            }

            // Generate each 16x64x16 chunk
            for (uint32_t x = 0; x < chunk_x; x++) {
                for (uint32_t z = 0; z < chunk_z; z++) {
                    for (uint32_t y = 0; y < chunk_y; y++) {
                        std::vector<uint32_t> heightmap(chunk::chunk_size_x * chunk::chunk_size_z);
                        generate_2d_heightmap(heightmap,
                                              x * chunk::chunk_size_x,
                                              y * chunk::chunk_size_y,
                                              z * chunk::chunk_size_z,
                                              chunk::chunk_size_x,
                                              chunk::chunk_size_y,
                                              chunk::chunk_size_z);
                        std::vector<block> blocks = std::vector<block>(
                            chunk::chunk_size_x * chunk::chunk_size_y * chunk::chunk_size_z, block());
                        // TODO: Add for negative values
                        generate(blocks,
                                 x * chunk::chunk_size_x,
                                 y * chunk::chunk_size_y,
                                 z * chunk::chunk_size_z,
                                 chunk::chunk_size_x,
                                 chunk::chunk_size_y,
                                 chunk::chunk_size_z);
                        chunk& current_chunk = chunks[z * chunk_x + y * chunk_x * chunk_z + x];
                        current_chunk.set_blocks(blocks);
                        // TODO: Add for negative values
                        current_chunk.set_chuck_pos(x, y, z);
                    }
                }
            }
        }

        template<typename T = int>
        void generate(std::vector<block>& blocks,
                      const T begin_x,
                      const T begin_y,
                      const T begin_z,
                      const uint32_t size_x,
                      const uint32_t size_y,
                      const uint32_t size_z)
        {
            constexpr bool debug = false;

            const T end_x = static_cast<T>(begin_x + size_x);
            const T end_y = static_cast<T>(begin_y + size_y);
            const T end_z = static_cast<T>(begin_z + size_z);

            std::vector<uint32_t> heightmap(size_x * size_z);

            generate_2d_heightmap(heightmap, begin_x, begin_y, begin_z, size_x, size_y, size_z);

            // Insert blocks if needed to make sure the vector is the correct size
            if (blocks.size() < size_x * size_y * size_z) {
                blocks.insert(blocks.end(), size_x * size_y * size_z - blocks.size(), block());
            }

            if constexpr (debug) {
                std::cout << "Generating blocks..." << std::endl;
            }
// Generate blocks
#pragma omp parallel for collapse(2) schedule(auto)
            for (uint32_t x = 0; x < size_x; x++) {
                for (uint32_t z = 0; z < size_z; z++) {
                    // Calculate real x and z from begin_x and begin_z
                    const int real_x = x + begin_x;
                    const int real_z = z + begin_z;

                    // Noise value is divided by 4 to make it smaller and it is used as the height of the block (z)
                    std::vector<block>::size_type vec_index = z * size_x + x;

                    /*
                    if constexpr (debug) {
                        std::cout << "x: " << x << ", z: " << z << " index: " << vec_index << std::endl;
                    }
                    */

                    uint32_t noise_value = heightmap[vec_index] / 8;

                    for (uint32_t y = 0; y < size_y; y++) {
                        // Calculate real y from begin_y
                        const int real_y = y + begin_y;

                        // vec_index = z * size_x * size_z + z * size_z + x;
                        // vec_index = y * size_x * size_z + z * size_x + x;
                        // vec_index = x * size_z * size_z + z * size_z + y;
                        vec_index = z * size_x + y * size_x * size_z + x;

                        if constexpr (debug) {
                            std::cout << "x: " << x << ", z: " << z << ", y: " << y << " index: " << vec_index
                                      << ", noise: " << static_cast<int>(noise_value) << std::endl;
                        }

                        block& current_block = blocks[vec_index];

                        current_block.x = real_x;
                        current_block.y = real_y;
                        current_block.z = real_z;

                        current_block.color = raylib::Color::Gray();

                        // If the noise value is greater than the current block, make it air
                        if (y > noise_value) {
                            current_block.is_visible = false;
                            current_block.block_type = block_type::air;
                            continue;
                        }

                        current_block.is_visible = true;
                        current_block.block_type = block_type::stone;
                    }
                }
            }
            // Optimize blocks
            opt.optimize(blocks, begin_x, begin_y, begin_z, size_x, size_y, size_z);
        }

    private:
        // default seed
        siv::PerlinNoise::seed_type seed = 2647393077u;
        siv::PerlinNoise perlin {seed};
        int32_t octaves = 16;
        double persistence = 0.2f;
        double lacunarity = 255.0f;

        optimizer opt;
};

#endif  // CUBE_GENERATOR_HPP