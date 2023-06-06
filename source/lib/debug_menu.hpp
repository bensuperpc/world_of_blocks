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
#include "game_context.hpp"

class debug_menu: public game_class
{
    public:
        debug_menu(game_context& game_context_ref);

        ~debug_menu();

        void update() override;
        void draw2d() override;
        void draw3d() override;

        // Menu
        bool display_debug_menu = true;

        game_context& _game_context_ref;
};

#endif  // WORLD_OF_CUBE_WORLD_HPP