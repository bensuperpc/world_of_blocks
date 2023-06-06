#ifndef WORLD_OF_CUBE_GAME_CONTEXT_HPP
#define WORLD_OF_CUBE_GAME_CONTEXT_HPP

#include <iostream>
#include <string>
#include <vector>

#include <omp.h>

// Raylib
#include "raylib.h"
#include "raymath.h"

// World of blocks
#include "game_class.hpp"
#include "vector.hpp"

class game_context : public game_class
{
    public:
        game_context();

        ~game_context();

        void update() override;
        void draw2d() override;
        void draw3d() override;

        void load_texture();

        // Game settings and window
        int screen_width = 1920;
        int screen_height = 1080;
        int target_fps = 240;
        
        uint64_t frame_count = 0;
    
        // Game variables
        Vector2 mouse_position = {0, 0};
        Vector2 screen_middle = {0, 0};

        Vector3 player_pos = {0, 0, 0};
        Vector3i player_chunk_pos = {0, 0, 0};

        Vector3i block_info_pos = {0, 0, 0};
        size_t block_info_index = 0;
        Texture2D _texture;

        // Stats
        size_t vectices_on_world_count = 0;
        size_t triangles_on_world_count = 0;
        size_t display_block_count = 0;
        size_t display_chunk_count = 0;

        size_t chunks_on_screen_count = 0;
        size_t vectices_on_screen_count = 0;
        size_t triangles_on_screen_count = 0;
};

#endif  // WORLD_OF_CUBE_WORLD_HPP