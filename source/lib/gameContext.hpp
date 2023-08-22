#ifndef WORLD_OF_CUBE_GAME_CONTEXT_HPP
#define WORLD_OF_CUBE_GAME_CONTEXT_HPP

#include <iostream>
#include <string>
#include <vector>

#include <omp.h>

// Raylib
#include "raylib.h"

// World of blocks
#include "gameElementHandler.hpp"
#include "vector.hpp"

#include "gameElementHandler.hpp"
#include "gameContext.hpp"

#include "nlohmann/json.hpp"

class gameContext : public gameElementHandler {
public:
  gameContext(std::vector<std::shared_ptr<gameElementHandler>> &game_classes, nlohmann::json &_config_json);

  ~gameContext();

  void updateGameInput() override;
  void updateGameLogic() override;

  void updateOpenglLogic() override;
  void updateDraw2d() override;
  void updateDraw3d() override;
  void updateDrawInterface() override;

  void load_texture();
  void unload_texture();

  // Game settings and window
  int screen_width = 1920;
  int screen_height = 1080;
  int target_fps = 240;

  uint64_t frame_count = 0;

  // Game variables
  Vector2 mouse_position = {0, 0};
  Vector2 screen_middle = {0, 0};

  Vector3 player_pos = {0, 0, 0};
  benlib::Vector3i player_chunk_pos = {0, 0, 0};

  benlib::Vector3i block_info_pos = {0, 0, 0};
  size_t block_info_index = 0;
  Texture2D _texture;

  // Stats
  size_t vectices_on_world_count = 0;
  size_t triangles_on_world_count = 0;
  size_t display_block_count = 0;
  size_t display_chunk_count = 0;

  size_t chunks_on_screen_count = 0;
  size_t vectices_on_screen_count = 0;
  size_t triangles_on_screen_count = 0;

  nlohmann::json &config_json;

  std::vector<std::shared_ptr<gameElementHandler>> &game_classes;

  // Debug menu
  bool *display_debug_menu = nullptr;
};

#endif // WORLD_OF_CUBE_WORLD_HPP