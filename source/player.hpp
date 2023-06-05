#ifndef WORLD_OF_CUBE_PLAYER_HPP
#define WORLD_OF_CUBE_PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>

#include <omp.h>

// Raylib
#include "raylib.h"
#include "raymath.h"

// World of blocks
#include "chunk.hpp"
#include "game_class.hpp"

class player : public game_class
{
    public:
        player();

        ~player();

        void update() override;
        void draw2d() override;
        void draw3d() override;

        Vector3 get_position() const;

        Camera camera;
};

#endif  // WORLD_OF_CUBE_WORLD_HPP