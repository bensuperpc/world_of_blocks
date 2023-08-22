

#include "world_model.hpp"

world_model::world_model() { world_model_logger = std::make_unique<LoggerDecorator>("world_model_logger", "world_model_logger.log"); }

world_model::~world_model() {}

inline void world_model::add_vertex(Mesh &mesh, size_t &triangle_index, size_t &vert_index, const Vector3 &vertex, const Vector3 &offset, const Vector3 &normal,
                                    const Vector2 &texcoords) noexcept {
  size_t index = triangle_index * 12 + vert_index * 3;

  index = triangle_index * 6 + vert_index * 2;
  mesh.texcoords[index] = texcoords.x;
  mesh.texcoords[index + 1] = texcoords.y;

  index = triangle_index * 9 + vert_index * 3;
  mesh.normals[index] = normal.x;
  mesh.normals[index + 1] = normal.y;
  mesh.normals[index + 2] = normal.z;

  index = triangle_index * 9 + vert_index * 3;
  mesh.vertices[index] = vertex.x + offset.x;
  mesh.vertices[index + 1] = vertex.y + offset.y;
  mesh.vertices[index + 2] = vertex.z + offset.z;

  vert_index++;
  if (vert_index > 2) {
    triangle_index++;
    vert_index = 0;
  }
}

inline void world_model::add_cube(Mesh &mesh, size_t &triangle_index, size_t &vert_index, const Vector3 &position, bool faces[6],
                                  [[maybe_unused]] Block &current_block) noexcept {
  Rectangle texcoords_rect = Rectangle{0.25f, 0, 0.5f, 1};
  // z-
  if (faces[north_face]) {
    const Vector3 normal = Vector3{0, 0, -1};

    add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 0}, normal, {texcoords_rect.x, texcoords_rect.y});

    add_vertex(mesh, triangle_index, vert_index, position, {1, 1, 0}, normal, {texcoords_rect.width, texcoords_rect.height});

    add_vertex(mesh, triangle_index, vert_index, position, {1, 0, 0}, normal, {texcoords_rect.width, texcoords_rect.y});

    // Issue with this triangle
    add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 0}, normal, {texcoords_rect.x, texcoords_rect.width});

    add_vertex(mesh, triangle_index, vert_index, position, {0, 1, 0}, normal, {texcoords_rect.x, texcoords_rect.height});

    // Seems to be fixed here
    add_vertex(mesh, triangle_index, vert_index, position, {1, 1, 0}, normal, {texcoords_rect.y, texcoords_rect.width});
  }

  // z+
  if (faces[south_face]) {
    const Vector3 normal = Vector3{0, 0, 1};

    add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 1}, normal, {texcoords_rect.x, texcoords_rect.y});

    add_vertex(mesh, triangle_index, vert_index, position, {1, 0, 1}, normal, {texcoords_rect.width, texcoords_rect.y});

    add_vertex(mesh, triangle_index, vert_index, position, {1, 1, 1}, normal, {texcoords_rect.width, texcoords_rect.height});

    add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 1}, normal, {texcoords_rect.x, texcoords_rect.y});

    add_vertex(mesh, triangle_index, vert_index, position, {1, 1, 1}, normal, {texcoords_rect.width, texcoords_rect.height});

    add_vertex(mesh, triangle_index, vert_index, position, {0, 1, 1}, normal, {texcoords_rect.x, texcoords_rect.height});
  }

  // x+
  if (faces[west_face]) {
    const Vector3 normal = Vector3{1, 0, 0};

    add_vertex(mesh, triangle_index, vert_index, position, {1, 0, 1}, normal, {texcoords_rect.x, texcoords_rect.height});

    add_vertex(mesh, triangle_index, vert_index, position, {1, 0, 0}, normal, {texcoords_rect.x, texcoords_rect.y});

    add_vertex(mesh, triangle_index, vert_index, position, {1, 1, 0}, normal, {texcoords_rect.width, texcoords_rect.y});

    add_vertex(mesh, triangle_index, vert_index, position, {1, 0, 1}, normal, {texcoords_rect.x, texcoords_rect.height});

    add_vertex(mesh, triangle_index, vert_index, position, {1, 1, 0}, normal, {texcoords_rect.width, texcoords_rect.y});

    add_vertex(mesh, triangle_index, vert_index, position, {1, 1, 1}, normal, {texcoords_rect.width, texcoords_rect.height});
  }

  // x-
  if (faces[east_face]) {
    const Vector3 normal = Vector3{-1, 0, 0};

    add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 1}, normal, {texcoords_rect.x, texcoords_rect.height});

    add_vertex(mesh, triangle_index, vert_index, position, {0, 1, 0}, normal, {texcoords_rect.width, texcoords_rect.y});

    add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 0}, normal, {texcoords_rect.x, texcoords_rect.y});

    add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 1}, normal, {texcoords_rect.x, texcoords_rect.height});

    add_vertex(mesh, triangle_index, vert_index, position, {0, 1, 1}, normal, {texcoords_rect.width, texcoords_rect.height});

    add_vertex(mesh, triangle_index, vert_index, position, {0, 1, 0}, normal, {texcoords_rect.width, texcoords_rect.y});
  }

  // y+
  if (faces[up_face]) {
    const Vector3 normal = Vector3{0, 1, 0};

    add_vertex(mesh, triangle_index, vert_index, position, {0, 1, 0}, normal, {texcoords_rect.x, texcoords_rect.y});

    add_vertex(mesh, triangle_index, vert_index, position, {1, 1, 1}, normal, {texcoords_rect.width, texcoords_rect.height});

    add_vertex(mesh, triangle_index, vert_index, position, {1, 1, 0}, normal, {texcoords_rect.width, texcoords_rect.y});

    add_vertex(mesh, triangle_index, vert_index, position, {0, 1, 0}, normal, {texcoords_rect.x, texcoords_rect.y});

    add_vertex(mesh, triangle_index, vert_index, position, {0, 1, 1}, normal, {texcoords_rect.x, texcoords_rect.height});

    add_vertex(mesh, triangle_index, vert_index, position, {1, 1, 1}, normal, {texcoords_rect.width, texcoords_rect.height});
  }

  // y-
  if (faces[down_face]) {
    const Vector3 normal = Vector3{0, -1, 0};

    add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 0}, normal, {texcoords_rect.x, texcoords_rect.y});

    add_vertex(mesh, triangle_index, vert_index, position, {1, 0, 0}, normal, {texcoords_rect.width, texcoords_rect.y});

    add_vertex(mesh, triangle_index, vert_index, position, {1, 0, 1}, normal, {texcoords_rect.width, texcoords_rect.height});

    add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 0}, normal, {texcoords_rect.x, texcoords_rect.y});

    add_vertex(mesh, triangle_index, vert_index, position, {1, 0, 1}, normal, {texcoords_rect.width, texcoords_rect.height});

    add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 1}, normal, {texcoords_rect.x, texcoords_rect.height});
  }
}

std::vector<std::unique_ptr<Model>> world_model::generate_world_models(std::vector<Chunk> &chunks) {
  std::vector<std::unique_ptr<Model>> models;
  std::vector<Mesh> meshes;
  meshes.reserve(chunks.size());
  models.reserve(chunks.size());
// Generate meshes on multiple threads
#pragma omp for ordered schedule(static, 1)
  for (size_t i = 0; i < chunks.size(); i++) {
    Mesh mesh = generate_chunk_mesh(chunks[i]);
#pragma omp ordered
    meshes.push_back(std::move(mesh));
  }
  // Generate models on mono thread (OpenGL)
  for (size_t i = 0; i < meshes.size(); i++) {
    UploadMesh(&meshes[i], false);
    models.push_back(std::make_unique<Model>(LoadModelFromMesh(meshes[i])));
  }
  return models;
}

std::unique_ptr<Model> world_model::generate_chunk_model(Chunk &chunks) {
  Mesh mesh = generate_chunk_mesh(chunks);
  UploadMesh(&mesh, false);
  std::unique_ptr<Model> model = std::make_unique<Model>(std::move(LoadModelFromMesh(mesh)));
  return model;
}

inline bool world_model::block_is_solid(int x, int y, int z, Chunk &_chunk) noexcept {
  // Check out of bounds
  if (x < 0 || x >= Chunk::chunk_size_x) {
    return false;
  }
  if (y < 0 || y >= Chunk::chunk_size_y) {
    return false;
  }
  if (z < 0 || z >= Chunk::chunk_size_z) {
    return false;
  }

  // Check if Block type is not air
  return _chunk.get_block(x, y, z).block_type != block_type::air;
}

// Count the number of solid blocks around a Block (excluding diagonals and corners)
inline int world_model::count_neighbours(int x, int y, int z, Chunk &_chunk) noexcept {
  int count = 0;
  if (block_is_solid(x - 1, y, z, _chunk))
    count++;
  if (block_is_solid(x + 1, y, z, _chunk))
    count++;
  if (block_is_solid(x, y - 1, z, _chunk))
    count++;
  if (block_is_solid(x, y + 1, z, _chunk))
    count++;
  if (block_is_solid(x, y, z - 1, _chunk))
    count++;
  if (block_is_solid(x, y, z + 1, _chunk))
    count++;
  return count;
}

int world_model::block_count_border(int x, int y, int z, [[maybe_unused]] Chunk &_chunk) noexcept {
  int count = 0;
  if (x == 0)
    count++;
  if (x == Chunk::chunk_size_x - 1)
    count++;
  if (y == 0)
    count++;
  if (y == Chunk::chunk_size_y - 1)
    count++;
  if (z == 0)
    count++;
  if (z == Chunk::chunk_size_z - 1)
    count++;
  return count;
}

int world_model::chunk_face_count(Chunk &_chunk) noexcept {
  int count = 0;
  // std::vector<Block> &blocks = _chunk.get_blocks();

  for (int x = 0; x < Chunk::chunk_size_x; x++) {
    for (int y = 0; y < Chunk::chunk_size_y; y++) {
      for (int z = 0; z < Chunk::chunk_size_z; z++) {
        Block &current_block = _chunk.get_block(x, y, z);
        if (current_block.block_type == block_type::air)
          continue;

        int border_count = block_count_border(x, y, z, _chunk);
        int neighbour_count = count_neighbours(x, y, z, _chunk);

        if (neighbour_count + border_count == 6) {
          continue;
        }

        if (!block_is_solid(x - 1, y, z, _chunk))
          count++;

        if (!block_is_solid(x + 1, y, z, _chunk))
          count++;

        if (!block_is_solid(x, y - 1, z, _chunk))
          count++;

        if (!block_is_solid(x, y + 1, z, _chunk))
          count++;

        if (!block_is_solid(x, y, z + 1, _chunk))
          count++;

        if (!block_is_solid(x, y, z - 1, _chunk))
          count++;
      }
    }
  }
  return count;
}

Mesh world_model::generate_chunk_mesh(Chunk &Chunk) noexcept {
  Mesh mesh = {0};
  int faces_count = chunk_face_count(Chunk);
  mesh.vertexCount = faces_count * 6;
  mesh.triangleCount = faces_count * 2;

  mesh.vertices = static_cast<float *>(MemAlloc(sizeof(float) * 3 * mesh.vertexCount));
  mesh.normals = static_cast<float *>(MemAlloc(sizeof(float) * 3 * mesh.vertexCount));
  mesh.texcoords = static_cast<float *>(MemAlloc(sizeof(float) * 2 * mesh.vertexCount));

  size_t triangle_index = 0;
  size_t vert_index = 0;

  //[[maybe_unused]] auto &blocks = Chunk.get_blocks();
  for (int x = 0; x < Chunk::chunk_size_x; x++) {
    for (int y = 0; y < Chunk::chunk_size_y; y++) {
      for (int z = 0; z < Chunk::chunk_size_z; z++) {
        Block &current_block = Chunk.get_block(x, y, z);
        if (current_block.block_type == block_type::air) {
          continue;
        }

        int border_count = block_count_border(x, y, z, Chunk);
        int neighbour_count = count_neighbours(x, y, z, Chunk);

        if (neighbour_count + border_count == 6) {
          continue;
        }

        bool faces[6] = {false, false, false, false, false, false};

        faces[world_model::east_face] = !block_is_solid(x - 1, y, z, Chunk);

        faces[world_model::west_face] = !block_is_solid(x + 1, y, z, Chunk);

        faces[world_model::down_face] = !block_is_solid(x, y - 1, z, Chunk);

        faces[world_model::up_face] = !block_is_solid(x, y + 1, z, Chunk);

        faces[world_model::south_face] = !block_is_solid(x, y, z + 1, Chunk);

        faces[world_model::north_face] = !block_is_solid(x, y, z - 1, Chunk);

        add_cube(mesh, triangle_index, vert_index, {static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)}, faces, current_block);
      }
    }
  }
  return mesh;
}