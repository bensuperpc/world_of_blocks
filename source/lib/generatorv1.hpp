#ifndef WORLD_OF_CUBE_GENERATORV1_HPP
#define WORLD_OF_CUBE_GENERATORV1_HPP

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

#ifndef PERLINNOISE_HPP_INCLUDED
#define PERLINNOISE_HPP_INCLUDED
#ifdef __GNUC__
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#include "PerlinNoise.hpp"
#endif

// Cube lib
#include "block.hpp"
#include "chunk.hpp"
#include "math.hpp"

#include "generator.hpp"

class generatorv1 final : public generator {
public:
  explicit generatorv1(uint32_t _seed) : seed(_seed) { perlin.reseed(seed); }

  generatorv1() {}

  ~generatorv1() {}

  void reseed(uint32_t seed) {
    this->seed = seed;
    perlin.reseed(seed);
  }

  uint32_t randomize_seed() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dis(0, std::numeric_limits<uint32_t>::max());
    seed = dis(gen);
    perlin.reseed(seed);
    return seed;
  }

  [[nodiscard]] uint32_t get_seed() const { return seed; }

  void set_octaves(uint32_t octaves) { this->octaves = octaves; }

  [[nodiscard]] uint32_t get_octaves() const { return octaves; }

  void set_persistence(double persistence) { this->persistence = persistence; }

  [[nodiscard]] double get_persistence() const { return persistence; }

  void set_lacunarity(double lacunarity) { this->lacunarity = lacunarity; }

  [[nodiscard]] double get_lacunarity() const { return lacunarity; }

  std::vector<uint32_t> generate_2d_heightmap(const int32_t begin_x, [[maybe_unused]] const int32_t begin_y, const int32_t begin_z, const uint32_t size_x,
                                              [[maybe_unused]] const uint32_t size_y, const uint32_t size_z) override {
    constexpr bool debug = false;

    std::vector<uint32_t> heightmap(size_x * size_z);

    const int32_t end_x = static_cast<int32_t>(begin_x + size_x);
    const int32_t end_y = static_cast<int32_t>(begin_y + size_y);
    const int32_t end_z = static_cast<int32_t>(begin_z + size_z);

    if constexpr (debug) {
      std::cout << "Generating:" << std::endl;
      std::cout << "From (xyz): " << begin_x << ", " << begin_y << ", " << begin_z << std::endl;
      std::cout << "To (xyz): " << end_x << ", " << end_y << ", " << end_z << std::endl;
      std::cout << "Size (xyz): " << size_x << ", " << size_y << ", " << size_z << std::endl;

      std::cout << "Generating 2D noise..." << std::endl;
    }

    for (uint32_t x = 0; x < size_x; x++) {
      for (uint32_t z = 0; z < size_z; z++) {
        // Calculate real x and z from begin_x and begin_z
        const int32_t real_x = x + begin_x;
        const int32_t real_z = z + begin_z;

        const uint32_t value_int = static_cast<uint32_t>(
            perlin.octave2D_01(static_cast<double>(real_x) / 256.0, static_cast<double>(real_z) / 256.0, octaves, persistence) * lacunarity);

        if (debug) {
          std::cout << "x: " << x << ", z: " << z << " index: " << z * size_z + x << ", value: " << static_cast<int32_t>(value_int) << std::endl;
        }
        heightmap[math::convert_to_1d(x, z, size_x, size_z)] = value_int;
      }
    }

    if constexpr (debug) {
      // cout max and min
      auto minmax = std::minmax_element(heightmap.begin(), heightmap.end());
      std::cout << "min: " << static_cast<int32_t>(*minmax.first) << std::endl;
      std::cout << "max: " << static_cast<int32_t>(*minmax.second) << std::endl;
    }
    return heightmap;
  }

  std::vector<uint32_t> generate_3d_heightmap(const int32_t begin_x, const int32_t begin_y, const int32_t begin_z, const uint32_t size_x, const uint32_t size_y,
                                              const uint32_t size_z) override {
    constexpr bool debug = false;

    std::vector<uint32_t> heightmap(size_x * size_y * size_z);

    const int32_t end_x = static_cast<int32_t>(begin_x + size_x);
    const int32_t end_y = static_cast<int32_t>(begin_y + size_y);
    const int32_t end_z = static_cast<int32_t>(begin_z + size_z);

    if constexpr (debug) {
      std::cout << "Generating:" << std::endl;
      std::cout << "From (xyz): " << begin_x << ", " << begin_y << ", " << begin_z << std::endl;
      std::cout << "To (xyz): " << end_x << ", " << end_y << ", " << end_z << std::endl;
      std::cout << "Size (xyz): " << size_x << ", " << size_y << ", " << size_z << std::endl;
    }
    // #pragma omp parallel for collapse(3) schedule(dynamic)
    for (uint32_t x = 0; x < size_x; x++) {
      for (uint32_t z = 0; z < size_z; z++) {
        for (uint32_t y = 0; y < size_y; y++) {
          // Calculate real x and z from begin_x and begin_z
          const int32_t real_x = x + begin_x;
          const int32_t real_z = z + begin_z;
          const int32_t real_y = y + begin_y;

          const uint32_t value_int = static_cast<uint32_t>(perlin.octave3D_01(static_cast<double>(real_x) / 256.0, static_cast<double>(real_z) / 256.0,
                                                                              static_cast<double>(real_y) / 256.0, octaves, persistence) *
                                                           lacunarity);

          if constexpr (debug) {
#pragma omp critical
            std::cout << "x: " << x << ", y: " << y << ", z: " << z << " index: " << math::convert_to_1d(x, y, z, size_x, size_y, size_z)
                      << ", value: " << static_cast<int32_t>(value_int) << std::endl;
          }
          heightmap[math::convert_to_1d(x, y, z, size_x, size_y, size_z)] = value_int;
        }
      }
    }
    if constexpr (debug) {
      // cout max and min
      auto minmax = std::minmax_element(heightmap.begin(), heightmap.end());
      std::cout << "min: " << static_cast<int32_t>(*minmax.first) << std::endl;
      std::cout << "max: " << static_cast<int32_t>(*minmax.second) << std::endl;
    }

    return heightmap;
  }

  [[nodiscard]] std::unique_ptr<chunk> generate_chunk(const int32_t chunk_x, const int32_t chunk_y, const int32_t chunk_z,
                                                      const bool generate_3d_terrain) override {
    const int32_t real_x = chunk_x * chunk::chunk_size_x;
    const int32_t real_y = chunk_y * chunk::chunk_size_y;
    const int32_t real_z = chunk_z * chunk::chunk_size_z;

    std::vector<block> blocks;

    std::unique_ptr<chunk> _chunk = std::make_unique<chunk>();

    if (generate_3d_terrain) {
      blocks = std::move(generate_3d(real_x, real_y, real_z, chunk::chunk_size_x, chunk::chunk_size_y, chunk::chunk_size_z));
    } else {
      blocks = std::move(generate_2d(real_x, real_y, real_z, chunk::chunk_size_x, chunk::chunk_size_y, chunk::chunk_size_z));
    }

    _chunk->set_blocks(blocks);
    _chunk->set_chuck_pos(chunk_x, chunk_y, chunk_z);

    return _chunk;
  }

  [[nodiscard]] std::vector<std::unique_ptr<chunk>> generate_chunks(const int32_t begin_chunk_x, const int32_t begin_chunk_y, const int32_t begin_chunk_z,
                                                                    const uint32_t size_x, const uint32_t size_y, const uint32_t size_z,
                                                                    const bool generate_3d_terrain) override {
    constexpr bool debug = false;

    std::vector<std::unique_ptr<chunk>> chunks;
    chunks.reserve(size_x * size_y * size_z);
    /*
    if (chunks.size() < size_x * size_y * size_z) {
        spdlog::error("Chunks size is not equal or bigger than size_x * size_y * size_z!");
        exit(1);
    }
    */

#pragma omp parallel for collapse(3) schedule(auto)
    for (int32_t x = begin_chunk_x; x < begin_chunk_x + size_x; x++) {
      for (int32_t z = begin_chunk_y; z < begin_chunk_y + size_z; z++) {
        for (int32_t y = begin_chunk_z; y < begin_chunk_z + size_y; y++) {
          auto gen_chunk = generate_chunk(x, y, z, generate_3d_terrain);
#pragma omp critical
          chunks.emplace_back(std::move(gen_chunk));
        }
      }
    }

    return chunks;
  }

  std::vector<block> generate_2d(const int32_t begin_x, const int32_t begin_y, const int32_t begin_z, const uint32_t size_x, const uint32_t size_y,
                                 const uint32_t size_z) override {
    constexpr bool debug = false;

    std::vector<uint32_t> heightmap;
    std::vector<block> blocks = std::vector<block>(size_x * size_y * size_z, block());

    heightmap = std::move(generate_2d_heightmap(begin_x, begin_y, begin_z, size_x, size_y, size_z));

    if constexpr (debug) {
      std::cout << "Generating blocks..." << std::endl;
    }
    // Generate blocks
    for (uint32_t x = 0; x < size_x; x++) {
      for (uint32_t z = 0; z < size_z; z++) {
        // Noise value is divided by 4 to make it smaller and it is used as the height of the block (z)
        // std::vector<block>::size_type vec_index = z * size_x + x;
        std::vector<block>::size_type vec_index = math::convert_to_1d(x, z, size_x, size_z);

        uint32_t noise_value = heightmap[vec_index] / 4;

        for (uint32_t y = 0; y < size_y; y++) {
          // Calculate real y from begin_y
          vec_index = math::convert_to_1d(x, y, z, size_x, size_y, size_z);

          if constexpr (debug) {
            std::cout << "x: " << x << ", z: " << z << ", y: " << y << " index: " << vec_index << ", noise: " << static_cast<int32_t>(noise_value) << std::endl;
          }

          block &current_block = blocks[vec_index];

          // If the noise value is greater than the current block, make it air
          if (noise_value > 120) {
            current_block.block_type = block_type::stone;
            continue;
          }
        }
      }
    }
    return blocks;
  }

  std::vector<block> generate_3d(const int32_t begin_x, const int32_t begin_y, const int32_t begin_z, const uint32_t size_x, const uint32_t size_y,
                                 const uint32_t size_z) override {
    constexpr bool debug = false;

    // const int32_t end_x = static_cast<int32_t>(begin_x + size_x);
    // const int32_t end_y = static_cast<int32_t>(begin_y + size_y);
    // const int32_t end_z = static_cast<int32_t>(begin_z + size_z);

    std::vector<block> blocks = std::vector<block>(size_x * size_y * size_z, block());

    std::vector<uint32_t> heightmap = generate_3d_heightmap(begin_x, begin_y, begin_z, size_x, size_y, size_z);

    if constexpr (debug) {
      std::cout << "Generating blocks..." << std::endl;
    }
    // Generate blocks
    for (uint32_t x = 0; x < size_x; x++) {
      for (uint32_t z = 0; z < size_z; z++) {
        for (uint32_t y = 0; y < size_y; y++) {
          size_t vec_index = math::convert_to_1d(x, y, z, size_x, size_y, size_z);
          const auto noise_value = heightmap[vec_index];
          auto &current_block = blocks[vec_index];

          if constexpr (debug) {
            std::cout << "x: " << x << ", z: " << z << ", y: " << y << " index: " << vec_index << ", noise: " << static_cast<int32_t>(noise_value) << std::endl;
          }

          if (noise_value > 120) {
            current_block.block_type = block_type::stone;
            continue;
          }
        }
      }
    }
    return blocks;
  }

private:
  // default seed
  siv::PerlinNoise::seed_type seed = 404;
  siv::PerlinNoise perlin{seed};

  int32_t octaves = 4;
  double persistence = 0.8f;
  double lacunarity = 255.0f;
};

#endif // WORLD_OF_CUBE_GENERATOR_HPP