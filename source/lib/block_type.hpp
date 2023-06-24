#ifndef WORLD_OF_CUBE_BLOCK_TYPE_HPP
#define WORLD_OF_CUBE_BLOCK_TYPE_HPP

#include <cstdint>
#include <limits>
#include <string>

// Block type enum

namespace block_type
{

// Block variable type
typedef uint8_t block_t;

inline constexpr block_t air = 0;
inline constexpr block_t grass = 1;
inline constexpr block_t dirt = 2;
inline constexpr block_t stone = 3;
inline constexpr block_t sand = 4;
inline constexpr block_t water = 5;
inline constexpr block_t wood = 6;
inline constexpr block_t leaves = 7;
inline constexpr block_t cobblestone = 8;
inline constexpr block_t unknown = std::numeric_limits<block_t>::max();

inline constexpr std::string get_name(block_t block_type)
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

#endif  // WORLD_OF_CUBE_BLOCK_TYPE_HPP