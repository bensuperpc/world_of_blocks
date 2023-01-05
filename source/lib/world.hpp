#ifndef WORLD_OF_CUBE_WORLD_HPP
#define WORLD_OF_CUBE_WORLD_HPP

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

#endif  // WORLD_OF_CUBE_WORLD_HPP