#include "game.hpp"

game::game() {}

game::~game() {}

void game::init() {}

void game::run()
{
    std::ios_base::sync_with_stdio(false);
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    raylib::Window _window(screen_width, screen_height, "Minecube");
    this->window = std::move(_window);

    player player1 = player();

    SetTargetFPS(target_fps);

    // raylib::Image img = GenImageChecked(256, 256, 32, 32, GREEN, RED);
    raylib::Image img = GenImageColor(16, 16, raylib::Color::White());
    raylib::Texture2D textureGrid = LoadTextureFromImage(img);
    // SetTextureFilter(textureGrid, TEXTURE_FILTER_ANISOTROPIC_16X);
    // SetTextureWrap(textureGrid, TEXTURE_WRAP_CLAMP);

    raylib::Texture2D texture = LoadTexture("grass.png");
    world_new.generate_world();

    for (size_t ci = 0; ci < world_new.chunks_model.size(); ci++) {
        world_new.chunks_model[ci].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    }

    while (!window.ShouldClose()) {
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
        screen_middle = Vector2({static_cast<float>(screen_width / 2), static_cast<float>(screen_height / 2)});

        ray = ray.GetMouse(screen_middle, player1.camera);

        if (IsKeyPressed(KEY_R)) {
            siv::PerlinNoise::seed_type seed = std::random_device()();
            world_new.seed = seed;
            std::cout << "seed: " << seed << std::endl;
            world_new.generate_world();
            for (size_t ci = 0; ci < world_new.chunks_model.size(); ci++) {
                world_new.chunks_model[ci].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
            }
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

        BeginDrawing();
        {
            window.ClearBackground(RAYWHITE);

            player1.camera.BeginMode();

            for (size_t ci = 0; ci < world_new.chunks.size(); ci++) {
                chunk& current_chunk = world_new.chunks[ci];
                auto&& chunk_coor = current_chunk.get_position();
                auto& blocks = current_chunk.get_blocks();

                if (world_new.chunks_model.size() <= ci) {
                    continue;
                }

                Model& current_model = world_new.chunks_model[ci];

                Vector3 chunk_pos = {static_cast<float>(chunk_coor.x * chunk::chunk_size_x * 1.0f),
                                     static_cast<float>(chunk_coor.y * chunk::chunk_size_y * 1.0f),
                                     static_cast<float>(chunk_coor.z * chunk::chunk_size_z * 1.0f)};

                DrawModelEx(current_model, chunk_pos, {0, 0, 0}, 1.0f, {1, 1, 1}, WHITE);

                if (!debug_menu) {
                    continue;
                }
                display_vectices_count += current_model.meshes->vertexCount;
                display_triangles_count += current_model.meshes->triangleCount;
                display_block_count += chunk::chunk_size_x * chunk::chunk_size_y * chunk::chunk_size_z;
                display_chunk_count++;
            }

            if (block_grid) {
                DrawGrid(256, 1.0f);
            }

            if (closest_collision.hit) {
                DrawCube(closest_collision.point, 0.3f, 0.3f, 0.3f, raylib::Color::Yellow());
                DrawCubeWires(closest_collision.point, 0.3f, 0.3f, 0.3f, raylib::Color::Black());

                Vector3 normalEnd;
                normalEnd.x = closest_collision.point.x + closest_collision.normal.x;
                normalEnd.y = closest_collision.point.y + closest_collision.normal.y;
                normalEnd.z = closest_collision.point.z + closest_collision.normal.z;

                DrawLine3D(closest_collision.point, normalEnd, raylib::Color::Blue());
            }

            player1.camera.EndMode();

            display_debug_menu();

            // Draw crosshair in the middle of the screen
            DrawLine(screen_middle.x - 10, screen_middle.y, screen_middle.x + 10, screen_middle.y, raylib::Color::SkyBlue());
            DrawLine(screen_middle.x, screen_middle.y - 10, screen_middle.x, screen_middle.y + 10, raylib::Color::SkyBlue());
        }
        EndDrawing();
    }
}

void game::display_debug_menu()
{
    if (!this->debug_menu) {
        return;
    }

    DrawRectangle(4, 4, 300, 200, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(4, 4, 300, 200, BLUE);

    // Draw FPS
    DrawFPS(8, 8);

    // Draw block info
    /*
    std::string block_info ="XYZ: " + std::to_string(block_info_pos.x) + ", " + std::to_string(block_info_pos.y) + ", " +
    std::to_string(block_info_pos.z); DrawText(block_info.c_str(), 10, 30, 20, raylib::Color::Black()); DrawText(("Index: " +
    std::to_string(block_info_index)).c_str(), 10, 50, 20, raylib::Color::Black());
    */

    // Draw statistics
    DrawText(("Blocks on world: " + std::to_string(display_block_count)).c_str(), 10, 70, 20, raylib::Color::Black());

    DrawText(("Chunks on world: " + std::to_string(display_chunk_count)).c_str(), 10, 90, 20, raylib::Color::Black());
    DrawText(("Vertices on world: " + std::to_string(display_vectices_count)).c_str(), 10, 110, 20, raylib::Color::Black());

    DrawText(("Triangles on world: " + std::to_string(display_triangles_count)).c_str(), 10, 130, 20, raylib::Color::Black());

    // Draw player position
    /*
    DrawText(
        ("Position: " + std::to_string(player1.position.x) + ", " + std::to_string(player1.position.y) + ", " + std::to_string(player1.position.z))
            .c_str(),
        10,
        150,
        20,
        raylib::Color::Black());
    */

    // Reset statistics
    display_vectices_count = 0;
    display_triangles_count = 0;
    display_block_count = 0;
    display_chunk_count = 0;
}