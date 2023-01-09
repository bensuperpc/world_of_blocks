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
#include "player.hpp"
#include "world.hpp"
#include "world_model.hpp"

class game
{
    public:
        game();
        ~game();
        void run();
        void init();
        Mesh cube_mesh(chunk& _chunk);

    private:
        // Game settings and window
        raylib::Window window;
        int screen_width = 1920;
        int screen_height = 1080;
        int target_fps = 480;

        world world_new = world();
        world_model world_md = world_model();
};

#endif  // GAME_HPP
