#ifndef CUBE_WORLD_HPP
#define CUBE_WORLD_HPP

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <string_view>
#include <vector>

#include <omp.h>

#include "PerlinNoise.hpp"
// Raylib
#include "raylib-cpp.hpp"
#include "raylib.h"
#include "raymath.h"

// Cube lib
#include "block.hpp"
#include "chunk.hpp"
#include "generator.hpp"

class world
{
    public:
        explicit world() {}

        ~world() {}

        void generate() {}

        generator gen = generator();

        std::vector<chunk> chunks;
};

#endif  // CUBE_WORLD_HPP