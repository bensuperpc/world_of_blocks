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

        void display_debug_menu();

    private:
        // Game settings and window
        raylib::Window window;
        int screen_width = 1920;
        int screen_height = 1080;
        int target_fps = 240;

        // Generator
        world world_new = world();

        // Menu
        bool debug_menu = true;

        // Debug menu
        size_t display_vectices_count = 0;
        size_t display_triangles_count = 0;
        size_t display_block_count = 0;
        size_t display_chunk_count = 0;

        Vector3i block_info_pos = {0, 0, 0};
        size_t block_info_index = 0;

        // Debug
        bool block_grid = true;

        // Game variables
        raylib::Vector2 mouse_position = {0, 0};
        raylib::Vector2 screen_middle = {0, 0};

        // Camera and player
        // player player1;

        // Ray collision
        raylib::Ray ray;
        std::vector<std::pair<block*, RayCollision>> collisions;
        raylib::RayCollision closest_collision = raylib::RayCollision(false, 0, {0, 0, 0}, {0, 0, 0});
        block* closest_block = nullptr;
};

#endif  // GAME_HPP
