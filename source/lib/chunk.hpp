#ifndef WORLD_OF_CUBE_CHUNK_HPP
#define WORLD_OF_CUBE_CHUNK_HPP

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Cube lib
#include "block.hpp"
#include "math.hpp"

// Raylib
#include "raylib.h"

class chunk {
public:
  chunk() {}
  chunk(std::vector<block> _blocks, int _chunk_x, int _chunk_y, int _chunk_z)
      : blocks(std::move(_blocks)), chunk_x(_chunk_x), chunk_y(_chunk_y), chunk_z(_chunk_z) {}

  ~chunk() { unload_model(); }

  [[nodiscard]] inline std::vector<block> &get_blocks() { return blocks; }

  [[nodiscard]] inline block &get_block(const int x, const int y, const int z) {
    return blocks[math::convert_to_1d(x, y, z, chunk_size_x, chunk_size_y, chunk_size_z)];
  }

  inline void set_blocks(std::vector<block> &blocks) { this->blocks = std::move(blocks); }

  [[nodiscard]] inline std::vector<block>::size_type size() const noexcept { return blocks.size(); }

  [[nodiscard]] inline Vector3i chunk_size() const noexcept { return {chunk_size_x, chunk_size_y, chunk_size_z}; }

  [[nodiscard]] inline Vector3i get_position() const noexcept { return {chunk_x, chunk_y, chunk_z}; }

  inline void set_chuck_pos(const int x, const int y, const int z) noexcept {
    chunk_x = x;
    chunk_y = y;
    chunk_z = z;
  }

  // From chunk position to real position
  [[nodiscard]] static inline Vector3 get_real_position(const chunk &chunk) {
    auto chunk_pos = chunk.get_position();
    return {static_cast<float>(chunk_pos.x * chunk::chunk_size_x), static_cast<float>(chunk_pos.y * chunk::chunk_size_y),
            static_cast<float>(chunk_pos.z * chunk::chunk_size_z)};
  }

  // From real position to chunk position
  [[nodiscard]] static inline Vector3i get_chunk_position(const float x, const float y, const float z) {
    return {static_cast<int>((x < 0 ? std::floor(x / chunk_size_x) : x / chunk_size_x)),
            static_cast<int>((y < 0 ? std::floor(y / chunk_size_y) : y / chunk_size_y)),
            static_cast<int>((z < 0 ? std::floor(z / chunk_size_z) : z / chunk_size_z))};
  }

  [[nodiscard]] static inline Vector3i get_chunk_position(const Vector3 &pos) { return get_chunk_position(pos.x, pos.y, pos.z); }

  void unload_model() {
    if (model == nullptr) {
      return;
    }
    UnloadModel(*model);
  }

  std::unique_ptr<Model> model;

  static constexpr int chunk_size_x = 32;
  static constexpr int chunk_size_y = 32;
  static constexpr int chunk_size_z = 32;

protected:
  std::vector<block> blocks;

  // Chunk coordinates
  int chunk_x = 0;
  int chunk_y = 0;
  int chunk_z = 0;
};

#endif // WORLD_OF_CUBE_CHUNK_HPP