#ifndef WORLD_OF_CUBE_BLOCK_UTILS_HPP
#define WORLD_OF_CUBE_BLOCK_UTILS_HPP

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <string_view>
#include <vector>

#include <omp.h>

namespace block_utils
{

[[nodiscard]] inline raylib::Vector3 get_real_position(const block& block,
                                                       const float block_size_x,
                                                       const float block_size_y,
                                                       const float block_size_z)
{
    auto&& block_pos = block.get_position();
    return {block_pos.x * block_size_x + block_size_x / 2.0,
            block_pos.y * block_size_y + block_size_y / 2.0,
            block_pos.z * block_size_y + block_size_y / 2.0};
}
[[nodiscard]] inline raylib::Vector3 get_real_position(const block& block, const float block_size)
{
    return get_real_position(block, block_size, block_size, block_size);
}

[[nodiscard]] inline BoundingBox get_bounding_box(const block& block,
                                                  const float block_size_x,
                                                  const float block_size_y,
                                                  const float block_size_z)
{
    raylib::Vector3&& cube_begin = get_real_position(block, block_size_x, block_size_y, block_size_z);
    cube_begin.x -= block_size_x / 2.0;
    cube_begin.y -= block_size_y / 2.0;
    cube_begin.z -= block_size_z / 2.0;

    raylib::Vector3&& cube_end = get_real_position(block, block_size_x, block_size_y, block_size_z);
    cube_end.x += block_size_x / 2.0;
    cube_end.y += block_size_y / 2.0;
    cube_end.z += block_size_z / 2.0;

    BoundingBox&& box = {cube_begin, cube_end};

    return box;
}

[[nodiscard]] inline BoundingBox get_bounding_box(const block& block, const float block_size)
{
    return get_bounding_box(block, block_size, block_size, block_size);
}

[[nodiscard]] inline raylib::Vector3 get_center(const block& block,
                                                const float block_size_x,
                                                const float block_size_y,
                                                const float block_size_z)
{
    Vector3&& center = get_real_position(block, block_size_x, block_size_y, block_size_z);
    center.x += block_size_x / 2.0;
    center.y += block_size_y / 2.0;
    center.z += block_size_z / 2.0;
    return center;
}

[[nodiscard]] inline raylib::Vector3 get_center(const block& block, const float block_size)
{
    return get_center(block, block_size, block_size, block_size);
}

}  // namespace block_utils

#endif  // WORLD_OF_CUBE_BLOCK_HPP