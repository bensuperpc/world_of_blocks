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
uint8_t constexpr air = 0;
uint8_t constexpr grass = 1;
uint8_t constexpr dirt = 2;
uint8_t constexpr stone = 3;
uint8_t constexpr sand = 4;
uint8_t constexpr water = 5;
uint8_t constexpr wood = 6;
uint8_t constexpr leaves = 7;
uint8_t constexpr unknown = std::numeric_limits<uint8_t>::max();

[[nodiscard]] inline std::string get_name(uint8_t block_type)
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
        explicit block(int x, int y, int z, uint8_t block_type, bool is_visible)
            : x(x)
            , y(y)
            , z(z)
            , block_type(block_type)
            , is_visible(is_visible)
        {
        }

        block() {}

        ~block() {}

        [[nodiscard]] Vector3i get_position() const { return {x, y, z}; }
        [[nodiscard]] uint8_t get_block_type() const { return block_type; }

        // Block coordinates
        int x = 0;
        int y = 0;
        int z = 0;

        uint8_t block_type = 0;

        // For rendering
        bool is_visible = true;
};

#endif  // WORLD_OF_CUBE_BLOCK_HPP