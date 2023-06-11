#include "game_context.hpp"

game_context::game_context(std::vector<std::shared_ptr<game_class>>& _game_classes, nlohmann::json& _config_json) 
    : game_classes(_game_classes), config_json(_config_json) {
    screen_width = _config_json["screen_width"];
    screen_height = _config_json["screen_height"];
    target_fps = _config_json["target_fps"];
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
    // Image img = GenImageChecked(256, 256, 32, 32, GREEN, RED);
    // Image img = GenImageColor(16, 16, WHITE);
    // Texture2D textureGrid = LoadTextureFromImage(img);
    // SetTextureFilter(textureGrid, TEXTURE_FILTER_ANISOTROPIC_16X);
    // SetTextureWrap(textureGrid, TEXTURE_WRAP_CLAMP);
}
