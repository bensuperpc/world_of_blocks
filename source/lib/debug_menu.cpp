#include "debug_menu.hpp"

#include "raygui_cpp.hpp"

debug_menu::debug_menu(game_context &game_context_ref) : _game_context_ref(game_context_ref) {
  game_context_ref.display_debug_menu = &this->is_visible;
}

debug_menu::~debug_menu() {}

void debug_menu::update() {
  if (IsKeyPressed(KEY_F3)) {
    last_action_time = std::chrono::steady_clock::now();
    is_visible = !is_visible;
  }
  if (IsKeyPressed(KEY_G)) {
    last_action_time = std::chrono::steady_clock::now();
    block_grid = !block_grid;
  }
}

void debug_menu::draw3d() {
  if (block_grid) {
    DrawGrid(256, 1.0f);
  }
}

void debug_menu::draw2d() {
  if (!this->is_visible) {
    return;
  }

  DrawRectangle(4, 4, 370, 290, Fade(SKYBLUE, 0.5f));
  DrawRectangleLines(4, 4, 370, 290, BLUE);

  // Draw FPS
  DrawFPS(8, 8);

  // Draw block info
  /*
  std::string block_info ="XYZ: " + std::to_string(block_info_pos.x) + ", " + std::to_string(block_info_pos.y) + ", " +
  std::to_string(block_info_pos.z); DrawText(block_info.c_str(), 10, 30, 20, BLACK); DrawText(("Index: " +
  std::to_string(block_info_index)).c_str(), 10, 50, 20, BLACK);
  */

  // Draw statistics
  DrawText(("Blocks on world: " + std::to_string(_game_context_ref.display_block_count)).c_str(), 10, 70, 20, BLACK);
  DrawText(("Chunks on world: " + std::to_string(_game_context_ref.display_chunk_count)).c_str(), 10, 90, 20, BLACK);
  DrawText(("Vertices on world: " + std::to_string(_game_context_ref.vectices_on_world_count)).c_str(), 10, 110, 20, BLACK);
  DrawText(("Triangles on world: " + std::to_string(_game_context_ref.triangles_on_world_count)).c_str(), 10, 130, 20, BLACK);
  DrawText(("Chunks on screen: " + std::to_string(_game_context_ref.chunks_on_screen_count)).c_str(), 10, 170, 20, BLACK);
  DrawText(("Vertices on screen: " + std::to_string(_game_context_ref.vectices_on_screen_count)).c_str(), 10, 190, 20, BLACK);
  DrawText(("Triangles on screen: " + std::to_string(_game_context_ref.triangles_on_screen_count)).c_str(), 10, 210, 20, BLACK);

  // Draw player position

  DrawText(("Player position: " + std::to_string(static_cast<int32_t>(_game_context_ref.player_pos.x)) + ", " +
            std::to_string(static_cast<int32_t>(_game_context_ref.player_pos.y)) + ", " + std::to_string(static_cast<int32_t>(_game_context_ref.player_pos.z)))
               .c_str(),
           10, 250, 20, BLACK);

  DrawText(("Player chunk position: " + std::to_string(_game_context_ref.player_chunk_pos.x) + ", " + std::to_string(_game_context_ref.player_chunk_pos.y) +
            ", " + std::to_string(_game_context_ref.player_chunk_pos.z))
               .c_str(),
           10, 270, 20, BLACK);
  bool forceSquaredChecked = false;
  // GuiCheckBox((Rectangle){ 25, 108, 15, 15 }, "FORCE CHECK!", &forceSquaredChecked);

  _game_context_ref.vectices_on_world_count = 0;
  _game_context_ref.triangles_on_world_count = 0;
  _game_context_ref.display_block_count = 0;
  _game_context_ref.display_chunk_count = 0;

  _game_context_ref.chunks_on_screen_count = 0;
  _game_context_ref.triangles_on_screen_count = 0;
  _game_context_ref.vectices_on_screen_count = 0;
}
