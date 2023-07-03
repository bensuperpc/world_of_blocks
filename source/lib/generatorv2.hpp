#ifndef WORLD_OF_CUBE_GENERATORV2_HPP
#define WORLD_OF_CUBE_GENERATORV2_HPP

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

#ifndef FASTNOISE_HPP_INCLUDED
#define FASTNOISE_HPP_INCLUDED
#ifdef __GNUC__
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#include "FastNoise/FastNoise.h"
#endif

// Cube lib
#include "block.hpp"
#include "chunk.hpp"
#include "generator.hpp"
#include "math.hpp"
class generatorv2 final : public generator {
public:
  explicit generatorv2(int32_t _seed) : seed(_seed) {
    fnSimplex = FastNoise::New<FastNoise::Perlin>();
    fnFractal = FastNoise::New<FastNoise::FractalFBm>();

    fnFractal->SetSource(fnSimplex);
    fnFractal->SetOctaveCount(octaves);
    fnFractal->SetGain(gain);
    fnFractal->SetLacunarity(lacunarity);
  }

  generatorv2() {
    fnSimplex = FastNoise::New<FastNoise::Perlin>();
    fnFractal = FastNoise::New<FastNoise::FractalFBm>();

    fnFractal->SetSource(fnSimplex);
    fnFractal->SetOctaveCount(octaves);
    fnFractal->SetGain(gain);
    fnFractal->SetLacunarity(lacunarity);
  }

  ~generatorv2() {}

  void reseed(uint32_t _seed) { this->seed = _seed; }

  uint32_t randomize_seed() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dis(0, std::numeric_limits<uint32_t>::max());
    this->seed = dis(gen);

    return seed;
  }

  uint32_t get_seed() const { return seed; }

  void set_octaves(uint32_t _octaves) { this->octaves = _octaves; }

  uint32_t get_octaves() const { return octaves; }

  void set_persistence(float _persistence) { this->persistence = _persistence; }

  double get_persistence() const { return persistence; }

  void set_lacunarity(double _lacunarity) { this->lacunarity = _lacunarity; }

  double get_lacunarity() const { return lacunarity; }

  std::vector<uint32_t> generate_2d_heightmap(const int32_t begin_x, [[maybe_unused]] const int32_t begin_y, const int32_t begin_z, const uint32_t size_x,
                                              [[maybe_unused]] const uint32_t size_y, const uint32_t size_z) override {
    constexpr bool debug = false;

    std::vector<uint32_t> heightmap(size_x * size_z);

    std::vector<float> noise_output(size_x * size_z);

    if (fnFractal == nullptr) {
      std::cout << "fnFractal is nullptr" << std::endl;
      return heightmap;
    }

    fnFractal->GenUniformGrid2D(noise_output.data(), begin_x, begin_z, size_x, size_z, frequency, seed);

    // Convert noise_output to heightmap
    for (uint32_t i = 0; i < size_x * size_z; i++) {
      heightmap[i] = static_cast<uint32_t>((noise_output[i] + 1.0) * 128.0);
      if constexpr (debug) {
        std::cout << "i: " << i << ", value: " << noise_output[i] << ", heightmap: " << heightmap[i] << std::endl;
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

    std::vector<float> noise_output(size_x * size_y * size_z);

    if (fnFractal == nullptr) {
      std::cout << "fnFractal is nullptr" << std::endl;
      return heightmap;
    }

    fnFractal->GenUniformGrid3D(noise_output.data(), begin_x, begin_y, begin_z, size_x, size_y, size_z, frequency, seed);

    // Convert noise_output to heightmap
    for (uint32_t i = 0; i < size_x * size_y * size_z; i++) {
      heightmap[i] = static_cast<uint32_t>((noise_output[i] + 1.0) * 128.0);
      if constexpr (debug) {
        std::cout << "i: " << i << ", noise_output: " << noise_output[i] << ", heightmap: " << heightmap[i] << std::endl;
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

  std::unique_ptr<chunk> generate_chunk(const int32_t chunk_x, const int32_t chunk_y, const int32_t chunk_z, const bool generate_3d_terrain) override {
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

    // Generate blocks
    for (uint32_t x = 0; x < size_x; x++) {
      for (uint32_t z = 0; z < size_z; z++) {
        // Noise value is divided by 4 to make it smaller and it is used as the height of the block (z)
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

    std::vector<block> blocks = std::vector<block>(size_x * size_y * size_z, block());

    std::vector<uint32_t> heightmap = generate_3d_heightmap(begin_x, begin_y, begin_z, size_x, size_y, size_z);

    // Generate blocks
    for (uint32_t x = 0; x < size_x; x++) {
      for (uint32_t z = 0; z < size_z; z++) {
        for (uint32_t y = 0; y < size_y; y++) {
          size_t vec_index = math::convert_to_1d(x, y, z, size_x, size_y, size_z);
          const uint32_t &noise_value = heightmap[vec_index];
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
  int32_t seed = 404;
  FastNoise::SmartNode<FastNoise::Perlin> fnSimplex;
  FastNoise::SmartNode<FastNoise::FractalFBm> fnFractal;
  float persistence = 0.05f;
  int32_t octaves = 6;
  float lacunarity = 0.5f;
  float gain = 3.5f;
  float frequency = 0.4f;
};

#endif // WORLD_OF_CUBE_GENERATOR_HPP