#ifndef WORLD_OF_CUBE_BLOCK_HPP
#define WORLD_OF_CUBE_BLOCK_HPP

#include <cstdint>
#include <optional>

#include "block_type.hpp"

class block
{
    public:
        explicit block(uint16_t block_type)
            : block_type(block_type)
        {
        }

        block() {}

        ~block() {}

        [[nodiscard]] inline uint16_t get_block_type() const { return block_type; }

        uint16_t block_type = 0;

        // All aditional data
        // std::vector<data> data;
};

#endif  // WORLD_OF_CUBE_BLOCK_HPP