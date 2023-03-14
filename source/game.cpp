#include "game.hpp"

game::game() {}

game::~game() {}

void game::init()
{
    std::ios_base::sync_with_stdio(false);
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
}

void game::run()
{
    InitWindow(screen_width, screen_height, "World of blocks");

    auto generate_world_async = std::async(std::launch::async, [&]() { world_new.generate_world(); });

    // Play intro animation
    SetTargetFPS(60);
    // AudioDevice audiodevice;

    // async intro animation
    play_intro_raylib(screen_width, screen_height);
    play_intro_raylib_cpp(screen_width, screen_height);
    play_intro_benlib(screen_width, screen_height);

    generate_world_async.wait();
    world_new.generate_world_models();

    SetTargetFPS(target_fps);

    player player1 = player();

    // Image img = GenImageChecked(256, 256, 32, 32, GREEN, RED);
    // Image img = GenImageColor(16, 16, WHITE);
    // Texture2D textureGrid = LoadTextureFromImage(img);
    // SetTextureFilter(textureGrid, TEXTURE_FILTER_ANISOTROPIC_16X);
    // SetTextureWrap(textureGrid, TEXTURE_WRAP_CLAMP);

    Texture2D texture = LoadTexture("grass.png");

    for (size_t ci = 0; ci < world_new.chunks_model.size(); ci++) {
        world_new.chunks_model[ci].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    }

    while (!WindowShouldClose()) {
        // If window is not focused or minimized, don't update to save resources
        // !IsWindowFocused()
        if (IsWindowMinimized()) {
            continue;
        }

        player1.update();

        closest_collision = {0};
        closest_collision.hit = false;
        closest_collision.distance = std::numeric_limits<float>::max();
        if (closest_block != nullptr) {
        }
        collisions.clear();

        mouse_position = GetMousePosition();

        player_chunk_pos = std::move(chunk::get_chunk_position(player1.camera.position));
        player_pos = std::move(player1.camera.position);

        screen_middle = Vector2({static_cast<float>(screen_width / 2), static_cast<float>(triangles_on_world_count / 2)});

        ray = GetMouseRay(screen_middle, player1.camera);

        if (IsKeyPressed(KEY_R)) {
            siv::PerlinNoise::seed_type seed = std::random_device()();
            world_new.seed = seed;
            std::cout << "seed: " << seed << std::endl;
            world_new.generate_world();
            world_new.generate_world_models();
            for (size_t ci = 0; ci < world_new.chunks_model.size(); ci++) {
                world_new.chunks_model[ci].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
            }
        }

        if (IsKeyPressed(KEY_C)) {
            world_new.clear();
        }

        if (IsKeyPressed(KEY_G)) {
            block_grid = !block_grid;
        }

        if (IsKeyPressed(KEY_F3)) {
            debug_menu = !debug_menu;
        }

        if (IsKeyPressed(KEY_F5)) {
            // Take screenshot
            TakeScreenshot("screenshot.png");
        }

        /*
        // TODO: optimize to check only the blocks around the player
        for (size_t ci = 0; ci < world_new.chunks.size(); ci++) {
            auto& current_chunk = world_new.chunks[ci];
            auto& blocks = current_chunk.get_blocks();
#pragma omp parallel for schedule(auto)
            for (size_t bi = 0; bi < current_chunk.size(); bi++) {
                block& current_block = blocks[bi];
                if (current_block.block_type != block_type::air) {
                    raylib::BoundingBox box = block_utils::get_bounding_box(current_block, 1.0f);

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

        // Check if the player is in a new chunk by finding if chunk position exists in the world chunks
        auto it = std::find_if(world_new.chunks.begin(),
                               world_new.chunks.end(),
                               [&](const auto& chunk)
                               {
                                   const auto&& chunk_pos = chunk.get_position();
                                   return chunk_pos.x == player_chunk_pos.x && chunk_pos.y == player_chunk_pos.y && chunk_pos.z == player_chunk_pos.z;
                               });

        if (it == world_new.chunks.end()) {
            // Player is in a new chunk
            std::cout << "Player is in a new chunk:" << std::endl;
            std::cout << "x: " << player_chunk_pos.x << " y: " << player_chunk_pos.y << " z: " << player_chunk_pos.z << std::endl;
            world_new.generate_chunk(player_chunk_pos.x, player_chunk_pos.y, player_chunk_pos.z);
            world_new.chunks_model.back().materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
        }

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            player1.camera.BeginMode();

            for (size_t ci = 0; ci < world_new.chunks.size(); ci++) {
                chunk& current_chunk = world_new.chunks[ci];
                auto&& chunk_coor = current_chunk.get_position();
                auto& blocks = current_chunk.get_blocks();

                if (world_new.chunks_model.size() < ci) {
                    continue;
                }
                Model& current_model = world_new.chunks_model[ci];

                auto&& chunk_pos = chunk::get_real_position(current_chunk);

                Vector3 chunk_pos_center = {static_cast<float>(chunk_coor.x * chunk::chunk_size_x + chunk::chunk_size_x / 2.0f),
                                            static_cast<float>(chunk_coor.y * chunk::chunk_size_y + chunk::chunk_size_y / 2.0f),
                                            static_cast<float>(chunk_coor.z * chunk::chunk_size_z + chunk::chunk_size_z / 2.0f)};

                if (debug_menu) {
                    vectices_on_world_count += current_model.meshes->vertexCount;
                    triangles_on_world_count += current_model.meshes->triangleCount;
                    display_block_count += chunk::chunk_size_x * chunk::chunk_size_y * chunk::chunk_size_z;
                    display_chunk_count++;
                }
                /*
                const Vector2&& chunk_screen_pos = player1.camera.GetWorldToScreen(chunk_pos_center);

                if (chunk_screen_pos.x < -1000.0 || chunk_screen_pos.x > static_cast<float>(GetScreenWidth()) + 1000.0 || chunk_screen_pos.y < -1000.0
                    || chunk_screen_pos.y > static_cast<float>(GetScreenHeight()) + 1000.0)
                {
                    continue;
                }
                */

                DrawModelEx(current_model, chunk_pos, {0, 0, 0}, 1.0f, {1, 1, 1}, WHITE);
                if (debug_menu) {
                    chunks_on_screen_count++;
                    vectices_on_screen_count += current_model.meshes->vertexCount;
                    triangles_on_screen_count += current_model.meshes->triangleCount;

                    chunk_pos.x += static_cast<float>(chunk::chunk_size_x / 2.0f);
                    chunk_pos.y += static_cast<float>(chunk::chunk_size_y / 2.0f);
                    chunk_pos.z += static_cast<float>(chunk::chunk_size_z / 2.0f);

                    DrawCubeWires(chunk_pos,
                                  static_cast<float>(chunk::chunk_size_x),
                                  static_cast<float>(chunk::chunk_size_y),
                                  static_cast<float>(chunk::chunk_size_z),
                                RED);
                }
            }

            if (block_grid) {
                DrawGrid(256, 1.0f);
            }

            if (closest_collision.hit) {
                DrawCube(closest_collision.point, 0.3f, 0.3f, 0.3f, YELLOW);
                DrawCubeWires(closest_collision.point, 0.3f, 0.3f, 0.3f, BLACK);

                Vector3 normalEnd;
                normalEnd.x = closest_collision.point.x + closest_collision.normal.x;
                normalEnd.y = closest_collision.point.y + closest_collision.normal.y;
                normalEnd.z = closest_collision.point.z + closest_collision.normal.z;

                DrawLine3D(closest_collision.point, normalEnd, BLUE);
            }

            player1.camera.EndMode();

            draw_debug_menu();

            // Draw crosshair in the middle of the screen
            DrawLine(screen_middle.x - 10, screen_middle.y, screen_middle.x + 10, screen_middle.y, SKYBLUE);
            DrawLine(screen_middle.x, screen_middle.y - 10, screen_middle.x, screen_middle.y + 10, SKYBLUE);
        }
        EndDrawing();
    }
}

void game::draw_debug_menu()
{
    if (!this->debug_menu) {
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
    DrawText(("Blocks on world: " + std::to_string(display_block_count)).c_str(), 10, 70, 20, BLACK);
    DrawText(("Chunks on world: " + std::to_string(display_chunk_count)).c_str(), 10, 90, 20, BLACK);
    DrawText(("Vertices on world: " + std::to_string(vectices_on_world_count)).c_str(), 10, 110, 20, BLACK);
    DrawText(("Triangles on world: " + std::to_string(triangles_on_world_count)).c_str(), 10, 130, 20, BLACK);
    DrawText(("Chunks on screen: " + std::to_string(chunks_on_screen_count)).c_str(), 10, 170, 20, BLACK);
    DrawText(("Vertices on screen: " + std::to_string(vectices_on_screen_count)).c_str(), 10, 190, 20, BLACK);
    DrawText(("Triangles on screen: " + std::to_string(triangles_on_screen_count)).c_str(), 10, 210, 20, BLACK);

    // Draw player position

    DrawText(("Player position: " + std::to_string(player_pos.x) + ", " + std::to_string(player_pos.y) + ", " + std::to_string(player_pos.z)).c_str(),
             10,
             250,
             20,
             BLACK);

    DrawText(("Player chunk position: " + std::to_string(player_chunk_pos.x) + ", " + std::to_string(player_chunk_pos.y) + ", "
              + std::to_string(player_chunk_pos.z))
                 .c_str(),
             10,
             270,
             20,
             BLACK);

    // Reset statistics
    vectices_on_world_count = 0;
    triangles_on_world_count = 0;
    display_block_count = 0;
    display_chunk_count = 0;

    chunks_on_screen_count = 0;
    triangles_on_screen_count = 0;
    vectices_on_screen_count = 0;
}