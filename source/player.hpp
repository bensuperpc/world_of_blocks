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

class player
{
    public:
        player();

        ~player();

        void update();

        Vector3 get_position() const;

        Camera camera;
};

#endif  // WORLD_OF_CUBE_WORLD_HPP