#include "game.hpp"

game::game() {}

game::~game() {}

void game::init()
{
    std::ios_base::sync_with_stdio(false);
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    game_context1 = std::make_shared<game_context>();
    game_classes.push_back(game_context1);

    world_new = std::make_shared<world>(*game_context1.get());
    game_classes.push_back(world_new);

    debug_menu1 = std::make_shared<debug_menu>(*game_context1.get());
    game_classes.push_back(debug_menu1);
}

void game::run()
{
    InitWindow(game_context1->screen_width, game_context1->screen_height, "World of blocks");

    game_context1->load_texture();

    auto generate_world_async = std::async(std::launch::async, [&]() { world_new->generate_world(); });

    // Play intro animation
    SetTargetFPS(60);
    // AudioDevice audiodevice;

    // async intro animation
    play_intro_raylib(game_context1->screen_width, game_context1->screen_height);
    play_intro_raylib_cpp(game_context1->screen_width, game_context1->screen_height);
    play_intro_benlib(game_context1->screen_width, game_context1->screen_height);

    generate_world_async.wait();
    world_new->generate_world_models();

    SetTargetFPS(game_context1->target_fps);

    // Image img = GenImageChecked(256, 256, 32, 32, GREEN, RED);
    // Image img = GenImageColor(16, 16, WHITE);
    // Texture2D textureGrid = LoadTextureFromImage(img);
    // SetTextureFilter(textureGrid, TEXTURE_FILTER_ANISOTROPIC_16X);
    // SetTextureWrap(textureGrid, TEXTURE_WRAP_CLAMP);

    // Player init after window is created
    player1 = std::make_shared<player>(*game_context1.get());
    game_classes.push_back(player1);

    while (!WindowShouldClose()) {
        // If window is not focused or minimized, don't update to save resources
        // !IsWindowFocused()
        if (IsWindowMinimized()) {
            continue;
        }

        if (IsKeyPressed(KEY_G)) {
            block_grid = !block_grid;
        }

        if (IsKeyPressed(KEY_F5)) {
            // Take screenshot
            TakeScreenshot("screenshot.png");
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

        for (auto& item : game_classes) {
            item->update();
        }

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            BeginMode3D(player1->camera);

            if (block_grid) {
                DrawGrid(256, 1.0f);
            }

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
            for (auto& item : game_classes) {
                item->draw3d();
            }
            EndMode3D();

            for (auto& item : game_classes) {
                item->draw2d();
            }
        }
        EndDrawing();
        game_context1->frame_count++;
    }
}