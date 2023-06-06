#include "world.hpp"

world::world(game_context& game_context_ref): _game_context_ref(game_context_ref)
{
}

world::~world() {}

void world::generate_world()
{
    std::cout << "Generating world" << std::endl;
    // Clear the chunks
    chunks.clear();
    chunks.shrink_to_fit();

    // Generate new perlin noise
    gen.reseed(this->seed);

    // Generate the world
    auto start = std::chrono::high_resolution_clock::now();

    for (int32_t x = world_chunk_start_x; x < world_chunk_start_x + world_chunk_size_x; x++) {
        for (int32_t y = world_chunk_start_y; y < world_chunk_start_y + world_chunk_size_y; y++) {
            for (int32_t z = world_chunk_start_z; z < world_chunk_start_z + world_chunk_size_z; z++) {
                std::cout << "Generating chunk " << x << " " << y << " " << z << std::endl;
                generate_chunk(x, y, z, false);
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "World generation took " << duration.count() << "ms" << std::endl;
}

void world::generate_world_models()
{
    // Free the models
    for (auto& chunk : chunks) {
        chunk->model = std::move(world_md.generate_chunk_model(*chunk.get()));
        chunk->model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _game_context_ref._texture;
    }

    std::cout << "Generating world models" << std::endl;
}

void world::generate_chunk(const int32_t x, const int32_t y, const int32_t z, bool generate_model)
{
    // Generate the chunk
    auto start = std::chrono::high_resolution_clock::now();
    std::unique_ptr<chunk> chunk_new = std::move(gen.generate_chunk(x, y, z, true));
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Chunk generation took " << duration.count() << "ms" << std::endl;

    // Add the chunk to the world
    if (generate_model) {
        start = std::chrono::high_resolution_clock::now();
        // Generate the model (TODO: Separate the model generation from the chunk generation)
        std::unique_ptr<Model> chunk_model = world_md.generate_chunk_model(*chunk_new.get());
        chunk_model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _game_context_ref._texture;
        chunk_new->model = std::move(chunk_model);

        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Chunk model generation took " << duration.count() << "ms" << std::endl;
    }
    chunks.push_back(std::move(chunk_new));
}

bool world::is_chunk_exist(const int32_t x, const int32_t y, const int32_t z)
{
    auto it = std::find_if(chunks.begin(),
                           chunks.end(),
                           [&](const auto& chunk)
                           {
                               const auto chunk_pos = chunk->get_position();
                               return chunk_pos.x == x && chunk_pos.y == y && chunk_pos.z == z;
                           });

    return it != chunks.end();
}

void world::clear()
{
    // Clear the chunks
    chunks.clear();
    chunks.shrink_to_fit();
}

void world::update()
{
    if (IsKeyPressed(KEY_R)) {
        seed = std::random_device()();
        std::cout << "seed: " << seed << std::endl;
        generate_world();
        generate_world_models();
    }

    if (IsKeyPressed(KEY_F3)) {
        display_debug_menu = !display_debug_menu;
    }

    if (IsKeyPressed(KEY_C)) {
        clear();
    }

    if (_game_context_ref.frame_count % 10 == 0) {
        // TODO: make render distance configurable on x, y and z axis, and -x, -y and -z axis
        for (int32_t x = -render_distance; x <= render_distance; x++) {
            for (int32_t y = -render_distance; y <= render_distance; y++) {
                for (int32_t z = -render_distance; z <= render_distance; z++) {
                    if (!is_chunk_exist(_game_context_ref.player_chunk_pos.x + x, _game_context_ref.player_chunk_pos.y + y, _game_context_ref.player_chunk_pos.z + z)) {
                        generate_chunk(_game_context_ref.player_chunk_pos.x + x, _game_context_ref.player_chunk_pos.y + y, _game_context_ref.player_chunk_pos.z + z, true);
                    }
                }
            }
        }
    }
}

void world::draw3d()
{
    for (size_t ci = 0; ci < chunks.size(); ci++) {
        chunk& current_chunk = *chunks[ci].get();
        auto&& chunk_coor = current_chunk.get_position();
        auto& blocks = current_chunk.get_blocks();

        Model& current_model = *current_chunk.model.get();

        auto&& chunk_pos = chunk::get_real_position(current_chunk);

        Vector3 chunk_pos_center = {static_cast<float>(chunk_coor.x * chunk::chunk_size_x + chunk::chunk_size_x / 2.0f),
                                    static_cast<float>(chunk_coor.y * chunk::chunk_size_y + chunk::chunk_size_y / 2.0f),
                                    static_cast<float>(chunk_coor.z * chunk::chunk_size_z + chunk::chunk_size_z / 2.0f)};
        
        if (true) {
            _game_context_ref.vectices_on_world_count += current_model.meshes->vertexCount;
            _game_context_ref.triangles_on_world_count += current_model.meshes->triangleCount;
            _game_context_ref.display_block_count += chunk::chunk_size_x * chunk::chunk_size_y * chunk::chunk_size_z;
            _game_context_ref.display_chunk_count++;
        }

        /*
        const Vector2&& chunk_screen_pos = player1->camera.GetWorldToScreen(chunk_pos_center, player1->camera);

        if (chunk_screen_pos.x < -1000.0 || chunk_screen_pos.x > static_cast<float>(GetScreenWidth()) + 1000.0 || chunk_screen_pos.y < -1000.0
            || chunk_screen_pos.y > static_cast<float>(GetScreenHeight()) + 1000.0)
        {
            continue;
        }
        */

        DrawModelEx(current_model, chunk_pos, {0, 0, 0}, 1.0f, {1, 1, 1}, WHITE);

        if (display_debug_menu) {
            _game_context_ref.chunks_on_screen_count++;
            _game_context_ref.vectices_on_screen_count += current_model.meshes->vertexCount;
            _game_context_ref.triangles_on_screen_count += current_model.meshes->triangleCount;

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
}

void world::draw2d()
{
}
