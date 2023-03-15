#include "player.hpp"

player::player()
{
    /*
    raylib::Camera _camera(
        // raylib::Vector3(48.0f, 48.0f, -48.0f),
        raylib::Vector3(-28.0f, 48.0f, -28.0f),
        raylib::Vector3(16.0f, 16.0f, 16.0f),
        raylib::Vector3(0.0f, 1.0f, 0.0f),
        80.0f,
        CAMERA_PERSPECTIVE);

    _camera.SetMode(CAMERA_FIRST_PERSON);
    // To disable free camera movement, just set movement controls to KEY_NULL
    // _camera.SetMoveControls(KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL);
    this->camera = _camera;
    */
    Camera _camera = { 0 };
    _camera.position = (Vector3){ 48.0f, 48.0f, -48.0f };
    _camera.target = (Vector3){ -28.0f, 48.0f, -28.0f };
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    _camera.fovy = 80.0f;
    _camera.projection = CAMERA_PERSPECTIVE;

    this->camera = _camera;
    DisableCursor();
}

Vector3 player::get_position() const
{
    return this->camera.position;
}

player::~player() {}

void player::update()
{
    UpdateCamera(&camera, CAMERA_FIRST_PERSON);
}