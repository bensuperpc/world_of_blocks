#include "game_context.hpp"

game_context::game_context()
{
}

game_context::~game_context() {}

void game_context::update() {
    vectices_on_world_count = 0;
    triangles_on_world_count = 0;
    display_block_count = 0;
    display_chunk_count = 0;

    chunks_on_screen_count = 0;
    triangles_on_screen_count = 0;
    vectices_on_screen_count = 0;

    mouse_position = GetMousePosition();
    screen_middle = Vector2({static_cast<float>(screen_height / 2), static_cast<float>(screen_width / 2)});
}

void game_context::draw2d() {
    return;
}

void game_context::draw3d() {
    return;
}

void game_context::load_texture() {
    _texture = LoadTexture("grass.png");
}
