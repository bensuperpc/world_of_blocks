#include "player.hpp"

player::player()
{
    Camera _camera = {0};
    _camera.position = (Vector3) {48.0f, 48.0f, -48.0f};
    _camera.target = (Vector3) {-28.0f, 48.0f, -28.0f};
    _camera.up = (Vector3) {0.0f, 1.0f, 0.0f};
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

void player::update() {
    float player_speed = 0.5f;
    float zoom = GetMouseWheelMove() * 0.5f;
    Vector3 movement = { 0.0f, 0.0f, 0.0f };
    Vector3 rotation = { 0.0f, 0.0f, 0.0f };


    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        movement.x = player_speed;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        movement.x = -player_speed;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        movement.y = player_speed;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        movement.y = -player_speed;
    }
    if (IsKeyDown(KEY_SPACE)) {
        movement.z = player_speed;
    }
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        movement.z = -player_speed;
    }

    rotation.x = GetMouseDelta().x * 0.05f;
    rotation.y = GetMouseDelta().y * 0.05f;


    UpdateCameraPro(&camera,movement,rotation,zoom);
}

void player::draw2d() {

}

void player::draw3d() {

}
