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

  void unload_model() noexcept {
    if (model == nullptr) {
      return;
    }
    UnloadModel(*model);
    model = nullptr;
  }

  [[nodiscard]] inline std::vector<block> &get_blocks() { return blocks; }

  [[nodiscard]] inline block &get_block(const int x, const int y, const int z) {
    return blocks[math::convert_to_1d(x, y, z, chunk_size_x, chunk_size_y, chunk_size_z)];
  }

  inline void set_blocks(std::vector<block> &_blocks) { this->blocks = std::move(_blocks); }

  [[nodiscard]] inline std::vector<block>::size_type size() const noexcept { return blocks.size(); }

  [[nodiscard]] inline benlib::Vector3i chunk_size() const noexcept { return {chunk_size_x, chunk_size_y, chunk_size_z}; }

  [[nodiscard]] inline benlib::Vector3i get_position() const noexcept { return {chunk_x, chunk_y, chunk_z}; }

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
  [[nodiscard]] static inline benlib::Vector3i get_chunk_position(const float x, const float y, const float z) {
    return {static_cast<int>((x < 0 ? std::floor(x / chunk_size_x) : x / chunk_size_x)),
            static_cast<int>((y < 0 ? std::floor(y / chunk_size_y) : y / chunk_size_y)),
            static_cast<int>((z < 0 ? std::floor(z / chunk_size_z) : z / chunk_size_z))};
  }

  [[nodiscard]] static inline benlib::Vector3i get_chunk_position(const Vector3 &pos) { return get_chunk_position(pos.x, pos.y, pos.z); }

  void set_model(std::unique_ptr<Model> _model) { model = std::move(_model); }

  [[nodiscard]] inline Model *get_model() const { return model.get(); }

  [[nodiscard]] inline bool has_model() const { return model != nullptr; }

  [[nodiscard]] inline bool is_empty() const { return blocks.empty(); }

  [[nodiscard]] inline bool is_full() const { return blocks.size() == chunk_size_x * chunk_size_y * chunk_size_z; }

  [[nodiscard]] inline bool is_in_chunk(const int x, const int y, const int z) const {
    return x >= 0 && x < chunk_size_x && y >= 0 && y < chunk_size_y && z >= 0 && z < chunk_size_z;
  }

  [[nodiscard]] inline bool is_in_chunk(const benlib::Vector3i &pos) const { return is_in_chunk(pos.x, pos.y, pos.z); }

  [[nodiscard]] inline bool is_in_chunk(const Vector3 &pos) const { return is_in_chunk(pos.x, pos.y, pos.z); }

  [[nodiscard]] inline bool is_in_chunk(const Vector3 &pos, const benlib::Vector3i &chunk_pos) const {
    return is_in_chunk(pos.x - chunk_pos.x * chunk_size_x, pos.y - chunk_pos.y * chunk_size_y, pos.z - chunk_pos.z * chunk_size_z);
  }

  [[nodiscard]] inline bool is_in_chunk(const benlib::Vector3i &pos, const benlib::Vector3i &chunk_pos) const {
    return is_in_chunk(pos.x - chunk_pos.x * chunk_size_x, pos.y - chunk_pos.y * chunk_size_y, pos.z - chunk_pos.z * chunk_size_z);
  }

  [[nodiscard]] inline bool is_in_chunk(const int x, const int y, const int z, const benlib::Vector3i &chunk_pos) const {
    return is_in_chunk(x - chunk_pos.x * chunk_size_x, y - chunk_pos.y * chunk_size_y, z - chunk_pos.z * chunk_size_z);
  }

  [[nodiscard]] inline bool is_in_chunk(const int x, const int y, const int z, const int chunk_x, const int chunk_y, const int chunk_z) const {
    return is_in_chunk(x - chunk_x * chunk_size_x, y - chunk_y * chunk_size_y, z - chunk_z * chunk_size_z);
  }

  static constexpr int chunk_size_x = 32;
  static constexpr int chunk_size_y = 32;
  static constexpr int chunk_size_z = 32;

protected:
  std::vector<block> blocks;
  std::unique_ptr<Model> model = nullptr;

  // Chunk coordinates
  int chunk_x = 0;
  int chunk_y = 0;
  int chunk_z = 0;
};

#endif // WORLD_OF_CUBE_CHUNK_HPP