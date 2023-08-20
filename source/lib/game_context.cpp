#include "game_context.hpp"

game_context::game_context(std::vector<std::shared_ptr<gameElementHandler>> &_game_classes, nlohmann::json &_config_json)
    : game_classes(_game_classes), config_json(_config_json) {
  screen_width = _config_json["display"].value("screen_width", 1920);
  screen_height = _config_json["display"].value("screen_height", 1080);
  target_fps = _config_json["display"].value("target_fps", 240);

  // Set address of display_debug_menu to avoid segfault if accessed before init
  bool useless = true;
  display_debug_menu = &useless;
}

game_context::~game_context() {}

void game_context::updateGameInput() {

  mouse_position = GetMousePosition();
  screen_middle = Vector2({static_cast<float>(screen_height / 2), static_cast<float>(screen_width / 2)});
}

void game_context::updateGameLogic() {}

void game_context::updateOpenglLogic() {}

void game_context::updateDraw2d() { return; }

void game_context::updateDraw3d() { return; }

void game_context::updateDrawInterface() { return; }

void game_context::unload_texture() { UnloadTexture(_texture); }

void game_context::load_texture() {
  _texture = LoadTexture("grass.png");
  // Image img = GenImageChecked(256, 256, 32, 32, GREEN, RED);
  // Image img = GenImageColor(16, 16, WHITE);
  // Texture2D textureGrid = LoadTextureFromImage(img);
  // SetTextureFilter(textureGrid, TEXTURE_FILTER_ANISOTROPIC_16X);
  // SetTextureWrap(textureGrid, TEXTURE_WRAP_CLAMP);
}
