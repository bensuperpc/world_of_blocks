#include "game.hpp"

game::game(nlohmann::json &_config_json) : config_json(_config_json) {}

game::~game() {}

void game::init() {
  std::ios_base::sync_with_stdio(false);
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

  game_context1 = std::make_shared<game_context>(game_classes, config_json);
  game_classes.push_back(game_context1);

  world_new = std::make_shared<world>(*game_context1.get(), config_json);
  game_classes.push_back(world_new);

  debug_menu1 = std::make_shared<debug_menu>(*game_context1.get());
  game_classes.push_back(debug_menu1);
}

void game::run() {
  auxillary_thread = std::thread(&game::auxillary_thread_game_logic, this);

  InitWindow(game_context1->screen_width, game_context1->screen_height, "World of blocks");

  game_context1->load_texture();

  // Play intro animation
  SetTargetFPS(60);
  // AudioDevice audiodevice;

  // async intro animation
  play_intro_raylib(game_context1->screen_width, game_context1->screen_height);
  play_intro_raylib_cpp(game_context1->screen_width, game_context1->screen_height);
  play_intro_benlib(game_context1->screen_width, game_context1->screen_height);

  SetTargetFPS(game_context1->target_fps);

  // Player init after window is created
  player1 = std::make_shared<player>(*game_context1.get());
  game_classes.push_back(player1);


  while (game_running) {
    game_running = !WindowShouldClose();
    // !IsWindowFocused()
    if (IsWindowMinimized()) {
      continue;
    }

    for (auto &item : game_classes) {
      item->update_opengl_logic();
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);

    
    BeginMode3D(player1->camera);
    
    for (auto &item : game_classes) {
      item->update_draw3d();
    }
  
    EndMode3D();

    for (auto &item : game_classes) {
      item->update_draw2d();
    }
    
    EndDrawing();
    game_context1->frame_count++;
  }

  auxillary_thread.join();

  // Unload chunks and textures before ending openGL !

  game_classes.clear();

  world_new.reset();
  player1.reset();
  debug_menu1.reset();
  game_context1.reset();

  CloseWindow();
}

// Update game logic and input
void game::auxillary_thread_game_logic() {
  while (game_running) {
    auto start_time = std::chrono::high_resolution_clock::now();
    for (auto &item : game_classes) {
      // Skip inactive items
      if (!item->is_active) {
        continue;
      }

      // Avoid multiple keypresses with a delay
      if (std::chrono::steady_clock::now() - item->last_action_time < item->action_cooldown) {
        continue;
      }
      item->update_game_input();
      item->update_game_logic();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    auto sleep_time = std::chrono::milliseconds(1000 / game_context1->target_fps) - duration;
    std::this_thread::sleep_for(sleep_time);
  }

  std::cout << "auxillary_thread_game_logic() exiting" << std::endl;
}