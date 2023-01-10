#ifndef WORLD_OF_CUBE_PLAYER_HPP
#define WORLD_OF_CUBE_PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>

#include <omp.h>

// Raylib
#include "raylib-cpp.hpp"
#include "raylib.h"
#include "raymath.h"

class player
{
    public:
        player();

        ~player();

        void update();

        raylib::Camera camera;

        Vector3& position = this->camera.position;
};

#endif  // WORLD_OF_CUBE_WORLD_HPP