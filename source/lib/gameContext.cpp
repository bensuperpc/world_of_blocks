#include "gameContext.hpp"

gameContext::gameContext(std::vector<std::shared_ptr<gameElementHandler>> &_game_classes, nlohmann::json &_config_json)
    : game_classes(_game_classes), _configJson(_config_json) {
  screen_width = _config_json["display"].value("screen_width", 1920);
  screen_height = _config_json["display"].value("screen_height", 1080);
  target_fps = _config_json["display"].value("target_fps", 240);

  // Set address of display_debug_menu to avoid segfault if accessed before init
  bool useless = true;
  display_debug_menu = &useless;
}

gameContext::~gameContext() {}

void gameContext::updateGameInput() {

  mouse_position = GetMousePosition();
  screen_middle = Vector2({static_cast<float>(screen_height / 2), static_cast<float>(screen_width / 2)});
}

void gameContext::updateGameLogic() {}

void gameContext::updateOpenglLogic() {}

void gameContext::updateDraw2d() { }

void gameContext::updateDraw3d() {}

void gameContext::updateDrawInterface() {}

void gameContext::unload_texture() { UnloadTexture(_texture); }

void gameContext::load_texture() {
  _texture = LoadTexture("grass.png");
  // Image img = GenImageChecked(256, 256, 32, 32, GREEN, RED);
  // Image img = GenImageColor(16, 16, WHITE);
  // Texture2D textureGrid = LoadTextureFromImage(img);
  // SetTextureFilter(textureGrid, TEXTURE_FILTER_ANISOTROPIC_16X);
  // SetTextureWrap(textureGrid, TEXTURE_WRAP_CLAMP);
}
