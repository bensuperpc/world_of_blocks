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
        player()
        {
            raylib::Camera _camera(
                raylib::Vector3(
                    static_cast<float>(64 * 2.0f / 4), (64 / 2) * 2.0f + 24.0f, static_cast<float>(64 * 2.0f / 4)),
                raylib::Vector3(static_cast<float>(64 * 2.0f / 2), 0.0f, static_cast<float>(64 * 2.0f / 2)),
                raylib::Vector3(1.0f, 1.0f, 1.0f),
                80.0f,
                CAMERA_PERSPECTIVE);

            _camera.SetMode(CAMERA_FIRST_PERSON);
            _camera.SetMoveControls(KEY_W, KEY_S, KEY_A, KEY_D, KEY_LEFT_SHIFT, KEY_SPACE);
            this->camera = _camera;
        }

        ~player() {}

        void update()
        {
            this->camera.Update();
        }

        raylib::Camera camera;

        Vector3 &position = this->camera.position;

};

#endif  // WORLD_OF_CUBE_WORLD_HPP