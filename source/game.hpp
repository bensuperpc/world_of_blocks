#ifndef GAME_HPP
#define GAME_HPP

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <future>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <string_view>
#include <vector>

#include <omp.h>

// #include "PerlinNoise.hpp"
//  Raylib
#include "raylib.h"
#include "raymath.h"

// Cube lib

extern "C"
{
#include "benlib_intro.h"
#include "raylib_cpp_intro.h"
#include "raylib_intro.h"
}

#include "block.hpp"
#include "block_utils.hpp"
#include "chunk.hpp"
#include "generator.hpp"
#include "player.hpp"
#include "world.hpp"
#include "world_model.hpp"

#include "debug_menu.hpp"
#include "game_class.hpp"
#include "game_context.hpp"

class game
{
    public:
        game();
        ~game();
        void run();
        void init();
        Mesh cube_mesh(chunk& _chunk);

        void draw_debug_menu();

    private:
        std::shared_ptr<debug_menu> debug_menu1;
        std::shared_ptr<player> player1;
        std::shared_ptr<world> world_new;
        std::shared_ptr<game_context> game_context1;

        // Debug
        bool block_grid = true;

        std::vector<std::shared_ptr<game_class>> game_classes;
};

#endif  // GAME_HPP
