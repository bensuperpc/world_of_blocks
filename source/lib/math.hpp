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

#include <omp.h>

namespace math
{

template<typename T = size_t>
[[nodiscard]] inline constexpr T convert_to_1d(
    const T x, const T y, const T z, const T max_x, const T max_y, const T max_z)
{
    // return x + y * max_x + z * max_x * max_y; // Another way to do it
    return z * max_x + y * max_x * max_z + x;
}

template<typename T = size_t>
[[nodiscard]] inline constexpr T convert_to_1d(const T x, const T y, const T max_x, const T max_y)
{
    return y * max_x + x;
}

}  // namespace math

#endif  // WORLD_OF_CUBE_BLOCK_HPP