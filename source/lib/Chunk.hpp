#ifndef WORLD_OF_CUBE_CHUNK_HPP
#define WORLD_OF_CUBE_CHUNK_HPP

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Cube lib
#include "Block.hpp"
#include "math.hpp"

// Raylib
#include "raylib.h"

class Chunk {
public:
  Chunk() {}
  Chunk(std::vector<Block> _blocks, int _chunk_x, int _chunk_y, int _chunk_z)
      : blocks(std::move(_blocks)), chunk_coor_x(_chunk_x), chunk_coor_y(_chunk_y), chunk_coor_z(_chunk_z) {}

  ~Chunk() { unload_model(); }

  void unload_model() noexcept {
    if (model == nullptr) {
      return;
    }
    UnloadModel(*model);
    model = nullptr;
  }

  inline std::vector<Block> &get_blocks() { return blocks; }

  inline Block &get_block(const int x, const int y, const int z) { return blocks[math::convert_to_1d(x, y, z, chunk_size_x, chunk_size_y, chunk_size_z)]; }

  inline void set_blocks(std::vector<Block> &_blocks) { this->blocks = std::move(_blocks); }

  inline std::vector<Block>::size_type size() const noexcept { return blocks.size(); }

  inline benlib::Vector3i chunk_size() const noexcept { return {chunk_size_x, chunk_size_y, chunk_size_z}; }

  inline benlib::Vector3i get_position() const noexcept { return {chunk_coor_x, chunk_coor_y, chunk_coor_z}; }

  inline void set_chuck_pos(const int x, const int y, const int z) noexcept {
    chunk_coor_x = x;
    chunk_coor_y = y;
    chunk_coor_z = z;
  }

  // From Chunk position to real position
  [[nodiscard]] static inline Vector3 get_real_position(const Chunk &Chunk) {
    auto chunk_pos = Chunk.get_position();
    return {static_cast<float>(chunk_pos.x * Chunk::chunk_size_x), static_cast<float>(chunk_pos.y * Chunk::chunk_size_y),
            static_cast<float>(chunk_pos.z * Chunk::chunk_size_z)};
  }

  // From real position to Chunk position
  [[nodiscard]] static inline benlib::Vector3i get_chunk_position(const float x, const float y, const float z) {
    return {static_cast<int>((x < 0 ? std::floor(x / chunk_size_x) : x / chunk_size_x)),
            static_cast<int>((y < 0 ? std::floor(y / chunk_size_y) : y / chunk_size_y)),
            static_cast<int>((z < 0 ? std::floor(z / chunk_size_z) : z / chunk_size_z))};
  }

  [[nodiscard]] static inline benlib::Vector3i get_chunk_position(const Vector3 &pos) { return get_chunk_position(pos.x, pos.y, pos.z); }

  void set_model(std::unique_ptr<Model> _model) { model = std::move(_model); }

  inline Model *get_model() const { return model.get(); }

  inline bool has_model() const { return model != nullptr; }

  inline bool is_empty() const { return blocks.empty(); }

  inline bool is_full() const { return blocks.size() == chunk_size_x * chunk_size_y * chunk_size_z; }

  inline bool is_in_chunk(const int x, const int y, const int z) const {
    return x >= 0 && x < chunk_size_x && y >= 0 && y < chunk_size_y && z >= 0 && z < chunk_size_z;
  }

  inline bool is_in_chunk(const benlib::Vector3i &pos) const { return is_in_chunk(pos.x, pos.y, pos.z); }

  inline bool is_in_chunk(const Vector3 &pos) const { return is_in_chunk(pos.x, pos.y, pos.z); }

  inline bool is_in_chunk(const Vector3 &pos, const benlib::Vector3i &chunk_pos) const {
    return is_in_chunk(pos.x - chunk_pos.x * chunk_size_x, pos.y - chunk_pos.y * chunk_size_y, pos.z - chunk_pos.z * chunk_size_z);
  }

  inline bool is_in_chunk(const benlib::Vector3i &pos, const benlib::Vector3i &chunk_pos) const {
    return is_in_chunk(pos.x - chunk_pos.x * chunk_size_x, pos.y - chunk_pos.y * chunk_size_y, pos.z - chunk_pos.z * chunk_size_z);
  }

  inline bool is_in_chunk(const int x, const int y, const int z, const benlib::Vector3i &chunk_pos) const {
    return is_in_chunk(x - chunk_pos.x * chunk_size_x, y - chunk_pos.y * chunk_size_y, z - chunk_pos.z * chunk_size_z);
  }

  inline bool is_in_chunk(const int x, const int y, const int z, const int chunk_x, const int chunk_y, const int chunk_z) const {
    return is_in_chunk(x - chunk_x * chunk_size_x, y - chunk_y * chunk_size_y, z - chunk_z * chunk_size_z);
  }

  inline bool is_active_chunk() const noexcept { return isActive; }
  inline void set_active_chunk(const bool active) noexcept { isActive = active; }

  inline bool is_visible_chunk() const noexcept { return isVisible; }
  inline void set_visible_chunk(const bool visible) noexcept { isVisible = visible; }

  static constexpr int chunk_size_x = 32;
  static constexpr int chunk_size_y = 32;
  static constexpr int chunk_size_z = 32;

protected:
  std::vector<Block> blocks;
  std::unique_ptr<Model> model = nullptr;

  // Chunk coordinates
  int chunk_coor_x = 0;
  int chunk_coor_y = 0;
  int chunk_coor_z = 0;

  bool isActive = true;
  bool isVisible = true;
};

#endif // WORLD_OF_CUBE_CHUNK_HPP