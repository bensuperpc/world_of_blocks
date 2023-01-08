#ifndef WORLD_OF_CUBE_MATH_HPP
#define WORLD_OF_CUBE_MATH_HPP

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <string_view>
#include <vector>

struct Vector3i
{
        int x;
        int y;
        int z;
};

struct Vector2i
{
        int x;
        int y;
};

namespace math
{

template<typename T = size_t>
[[nodiscard]] inline constexpr T convert_to_1d(const T x, const T y, const T z, const T max_x, const T max_y, const T max_z)
{
    return (z * max_x * max_y) + (y * max_x) + x;
}

/*
template<typename T = size_t>
[[nodiscard]] inline constexpr Vector3i convert_to_3d(const T index, const T max_x, const T max_y, const T max_z)
{

                int z = i / (chunk::chunk_size_x * chunk::chunk_size_y);
            int tmp = i - (z * chunk::chunk_size_x * chunk::chunk_size_y);
            int y = tmp / chunk::chunk_size_x;
            int x = tmp % chunk::chunk_size_x;


    const int z = index / (max_x * max_y);
    const int y = (index - (z * max_x * max_y)) / max_x;
    const int x = index - (z * max_x * max_y) - (y * max_x);
    return {x, y, z};
}
*/

template<typename T = size_t>
[[nodiscard]] inline constexpr T convert_to_1d(const T x, const T y, const T max_x, const T max_y)
{
    return y * max_x + x;
}

}  // namespace math

#endif  // WORLD_OF_CUBE_BLOCK_HPP