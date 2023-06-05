#ifndef WORLD_OF_CUBE_DEBUG_MENU_HPP
#define WORLD_OF_CUBE_DEBUG_MENU_HPP

#include <iostream>
#include <string>
#include <vector>

#include <omp.h>

// Raylib
#include "raylib.h"
#include "raymath.h"

#include "vector.hpp"
#include "game_class.hpp"

class debug_menu: public game_class
{
    public:
        debug_menu();

        ~debug_menu();

        void update() override;
        void draw2d() override;
        void draw3d() override;

        // Menu
        bool display_debug_menu = true;

        // Debug menu
        size_t vectices_on_world_count = 0;
        size_t triangles_on_world_count = 0;
        size_t display_block_count = 0;
        size_t display_chunk_count = 0;

        size_t chunks_on_screen_count = 0;
        size_t vectices_on_screen_count = 0;
        size_t triangles_on_screen_count = 0;

        Vector3 player_pos = {0, 0, 0};
        Vector3i player_chunk_pos = {0, 0, 0};

        Vector3i block_info_pos = {0, 0, 0};
        size_t block_info_index = 0;
};

#endif  // WORLD_OF_CUBE_WORLD_HPP