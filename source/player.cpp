#include "player.hpp"

player::player()
{
    raylib::Camera _camera(
        // raylib::Vector3(48.0f, 48.0f, -48.0f),
        raylib::Vector3(48.0f, 48.0f, -48.0f),
        raylib::Vector3(16.0f, 16.0f, 16.0f),
        raylib::Vector3(0.0f, 1.0f, 0.0f),
        80.0f,
        CAMERA_PERSPECTIVE);

    _camera.SetMode(CAMERA_FIRST_PERSON);
    // To disable free camera movement, just set movement controls to KEY_NULL
    // _camera.SetMoveControls(KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL);
    this->camera = _camera;
}

player::~player() {}

void player::update()
{
    this->camera.Update();
}