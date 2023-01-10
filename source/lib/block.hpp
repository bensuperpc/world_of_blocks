#ifndef WORLD_OF_CUBE_BLOCK_HPP
#define WORLD_OF_CUBE_BLOCK_HPP

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <string_view>
#include <vector>

#include <omp.h>

#include "math.hpp"
#include "raylib-cpp.hpp"
#include "raylib.h"
#include "raymath.h"

// Block type enum

namespace block_type
{
uint16_t constexpr air = 0;
uint16_t constexpr grass = 1;
uint16_t constexpr dirt = 2;
uint16_t constexpr stone = 3;
uint16_t constexpr sand = 4;
uint16_t constexpr water = 5;
uint16_t constexpr wood = 6;
uint16_t constexpr leaves = 7;
uint16_t constexpr unknown = std::numeric_limits<uint16_t>::max();

[[nodiscard]] inline std::string get_name(uint16_t block_type)
{
    switch (block_type) {
        case air:
            return "air";
        case grass:
            return "grass";
        case dirt:
            return "dirt";
        case stone:
            return "stone";
        case sand:
            return "sand";
        case water:
            return "water";
        case wood:
            return "wood";
        case leaves:
            return "leaves";
        default:
            return "unknown";
    }
}

}  // namespace block_type

class block
{
    public:
        explicit block(uint16_t block_type)
            : block_type(block_type)
        {
        }

        block() {}

        ~block() {}

        [[nodiscard]] uint16_t get_block_type() const { return block_type; }

        uint16_t block_type = 0;

        // All aditional data
        // std::vector<data> data;
};

#endif  // WORLD_OF_CUBE_BLOCK_HPP