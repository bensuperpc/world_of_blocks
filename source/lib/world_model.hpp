#ifndef WORLD_OF_CUBE_WORLD_MODEL_HPP
#define WORLD_OF_CUBE_WORLD_MODEL_HPP
#include <vector>

#include <omp.h>

#include "raylib.h"

// Cube lib
#include "Block.hpp"
#include "Chunk.hpp"
#include "math.hpp"

// spdlog
#include "logger/logger_facade.hpp"

class world_model {
public:
  world_model();

  ~world_model();

  static constexpr size_t south_face = 0;
  static constexpr size_t north_face = 1;
  static constexpr size_t west_face = 2;
  static constexpr size_t east_face = 3;
  static constexpr size_t up_face = 4;
  static constexpr size_t down_face = 5;

  inline void add_vertex(Mesh &mesh, size_t &triangle_index, size_t &vert_index, const Vector3 &vertex, const Vector3 &offset, const Vector3 &normal,
                         const Vector2 &texcoords) noexcept;

  inline void add_cube(Mesh &mesh, size_t &triangle_index, size_t &vert_index, const Vector3 &position, bool faces[6], Block &current_block) noexcept;

  std::vector<std::unique_ptr<Model>> generate_world_models(std::vector<Chunk> &Chunk);
  std::unique_ptr<Model> generate_chunk_model(Chunk &chunks);

  inline bool block_is_solid(int x, int y, int z, Chunk &_chunk) noexcept;

  inline int count_neighbours(int x, int y, int z, Chunk &_chunk) noexcept;

  inline int block_count_border(int x, int y, int z, Chunk &_chunk) noexcept;

  int chunk_face_count(Chunk &_chunk) noexcept;

  Mesh generate_chunk_mesh(Chunk &Chunk) noexcept;

  // logger
  std::unique_ptr<logger_decorator> world_model_logger;
};

#endif // WORLD_OF_CUBE_WORLD_HPP