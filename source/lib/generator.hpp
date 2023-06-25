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

#include "spdlog/spdlog.h"

// Cube lib
#include "block.hpp"
#include "chunk.hpp"
#include "math.hpp"

class generator {
protected:
  explicit generator();

  virtual ~generator();

  virtual std::vector<uint32_t> generate_2d_heightmap(const int32_t begin_x, const int32_t begin_y, const int32_t begin_z, const uint32_t size_x,
                                                      const uint32_t size_y, const uint32_t size_z) = 0;

  virtual std::vector<uint32_t> generate_3d_heightmap(const int32_t begin_x, const int32_t begin_y, const int32_t begin_z, const uint32_t size_x,
                                                      const uint32_t size_y, const uint32_t size_z) = 0;

  virtual std::unique_ptr<chunk> generate_chunk(const int32_t chunk_x, const int32_t chunk_y, const int32_t chunk_z, const bool generate_3d_terrain) = 0;

  virtual std::vector<std::unique_ptr<chunk>> generate_chunks(const int32_t begin_chunk_x, const int32_t begin_chunk_y, const int32_t begin_chunk_z,
                                                              const uint32_t chunk_x, const uint32_t chunk_y, const uint32_t chunk_z,
                                                              const bool generate_3d_terrain) = 0;

  virtual std::vector<block> generate_2d(const int32_t begin_x, const int32_t begin_y, const int32_t begin_z, const uint32_t size_x, const uint32_t size_y,
                                         const uint32_t size_z) = 0;

  virtual std::vector<block> generate_3d(const int32_t begin_x, const int32_t begin_y, const int32_t begin_z, const uint32_t size_x, const uint32_t size_y,
                                         const uint32_t size_z) = 0;
};

#endif // WORLD_OF_CUBE_GENERATOR_HPP