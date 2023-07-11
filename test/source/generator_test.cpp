#include <string>

#include "generator.hpp"

#include "block.hpp"
#include "chunk.hpp"
#include "world_model.hpp"

#include "gtest/gtest.h"

TEST(world_of_blocks, basic_generation_2) {
  generator new_generator(2510586073u);

  uint32_t chunk_x = 2;
  uint32_t chunk_y = 2;
  uint32_t chunk_z = 2;

  uint32_t chunk_size = chunk_x * chunk_y * chunk_z;
  std::vector<std::unique_ptr<chunk>> chunks = new_generator.generate_chunks(-4, 0, -4, chunk_x, chunk_y, chunk_z, true);

  for (size_t i = 0; i < chunks.size(); i++) {
    std::vector<block> &blocks = chunks[i]->get_blocks();
    EXPECT_EQ(blocks.size(), chunk::chunk_size_x * chunk::chunk_size_y * chunk::chunk_size_z);
    for (size_t j = 0; j < blocks.size(); j++) {
      block &b = blocks[j];
      EXPECT_NE(b.get_block_type(), block_type::unknown);
    }
  }

  world_model world_md = world_model();

  std::vector<Mesh> meshes;

  for (auto &chunk : chunks) {
    meshes.push_back(world_md.generate_chunk_mesh(*chunk.get()));
  }

  for (auto &mesh : meshes) {
    UnloadMesh(mesh);
  }
}
