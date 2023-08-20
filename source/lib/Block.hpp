#ifndef WORLD_OF_CUBE_BLOCK_HPP
#define WORLD_OF_CUBE_BLOCK_HPP

#include <cstdint>
#include <optional>

#include "block_type.hpp"

class Block {
public:
  explicit Block(block_type::block_t _block_type) : block_type(_block_type) {}

  Block() {}

  ~Block() {}

  [[nodiscard]] inline block_type::block_t get_block_type() const noexcept { return block_type; }

  block_type::block_t block_type = block_type::air;

  // All aditional data
  // std::vector<data> data;
};

#endif // WORLD_OF_CUBE_BLOCK_HPP