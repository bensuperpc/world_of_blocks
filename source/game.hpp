#ifndef GAME_HPP
#define GAME_HPP

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

// #include "PerlinNoise.hpp"
//  Raylib
#include "raylib-cpp.hpp"
#include "raylib.h"
#include "raymath.h"

// Cube lib

#include "block.hpp"
#include "block_utils.hpp"
#include "chunk.hpp"
#include "generator.hpp"
#include "optimizer.hpp"
#include "world.hpp"

#include "player.hpp"

#include "world_model.hpp"

class game {
public:
    game();
    ~game();
    void run();
    Mesh cube_mesh(chunk& _chunk);

    private:
    
    raylib::Window window;
};

#endif // GAME_HPP
