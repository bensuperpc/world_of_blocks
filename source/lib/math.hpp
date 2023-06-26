#ifndef WORLD_OF_CUBE_MATH_HPP
#define WORLD_OF_CUBE_MATH_HPP

#include "vector.hpp"

namespace math {

template <typename T = size_t>
[[nodiscard]] inline constexpr T convert_to_1d(const T x, const T y, [[maybe_unused]] const T z, const T max_x, const T max_y,
                                               [[maybe_unused]] const T max_z) noexcept {
  return (z * max_x * max_y) + (y * max_x) + x;
}

/*
template<typename T = size_t>
benlib::Vector3i convert_to_3d(const T index, const T max_x, const T max_y, const T max_z) noexcept
{
    int z = i / (max_x * max_y);
    const int tmp = i - (z * max_x * max_y);
    int y = tmp / max_x;
    int x = tmp % max_x;

    return {x, y, z};
}
*/

template <typename T = size_t> [[nodiscard]] inline constexpr T convert_to_1d(const T x, const T y, const T max_x, [[maybe_unused]] const T max_y) noexcept {
  return y * max_x + x;
}

} // namespace math

#endif // WORLD_OF_CUBE_BLOCK_HPP