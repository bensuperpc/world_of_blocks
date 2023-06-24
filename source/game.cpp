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
  auxillary_thread = std::thread(&game::auxillary_thread_func, this);

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

    /*
    // TODO: optimize to check only the blocks around the player
    for (size_t ci = 0; ci < world_new->chunks.size(); ci++) {
        auto& current_chunk = world_new->chunks[ci];
        auto& blocks = current_chdebug_menu1Box box = block_utils::get_bounding_box(current_block, 1.0f);

                RayCollision box_hit_info = GetRayCollisionBox(ray, box);
                if (box_hit_info.hit) {
#pragma omp critical
                    collisions.push_back({&current_block, box_hit_info});
                }
            }
        }
    }

    if (!collisions.empty()) {
        // sort by distance and get the closest collision
        std::sort(collisions.begin(), collisions.end(), [](const auto& a, const auto& b) { return a.second.distance < b.second.distance; });
        closest_collision = collisions[0].second;
        closest_block = collisions[0].first;

        block_info_pos = closest_block->get_position();
        // block_info_index = closest_block->x + closest_block->z * 16 + closest_block->y * 16 * 16;
        block_info_index = 0;
    } else {
        block_info_pos = {0, 0, 0};
        block_info_index = 0;
    }
    */
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(player1->camera);

    /*
    if (closest_collision.hit) {
        DrawCube(closest_collision.point, 0.3f, 0.3f, 0.3f, YELLOW);
        DrawCubeWires(closest_collision.point, 0.3f, 0.3f, 0.3f, BLACK);

        Vector3 normalEnd;
        normalEnd.x = closest_collision.point.x + closest_collision.normal.x;
        normalEnd.y = closest_collision.point.y + closest_collision.normal.y;
        normalEnd.z = closest_collision.point.z + closest_collision.normal.z;

        DrawLine3D(closest_collision.point, normalEnd, BLUE);
    }
    */
    for (auto &item : game_classes) {
      item->draw3d();
    }
    EndMode3D();

    for (auto &item : game_classes) {
      item->draw2d();
    }

    EndDrawing();
    game_context1->frame_count++;
  }

  auxillary_thread.join();
}

void game::auxillary_thread_func() {
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
      item->update();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    auto sleep_time = std::chrono::milliseconds(1000 / game_context1->target_fps) - duration;
    std::this_thread::sleep_for(sleep_time);
  }
}