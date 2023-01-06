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
                    48.0f, 48.0f, -48.0f),
                raylib::Vector3(16.0f, 16.0f, 16.0f),
                raylib::Vector3(0.0f, 1.0f, 0.0f),
                80.0f,
                CAMERA_PERSPECTIVE);

            _camera.SetMode(CAMERA_FIRST_PERSON);
            // To disable free camera movement, just set movement controls to KEY_NULL
            // _camera.SetMoveControls(KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL);
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