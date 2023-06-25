#include "world.hpp"

world::world(game_context &game_context_ref, nlohmann::json &_config_json) : _game_context_ref(game_context_ref), config_json(_config_json) {
  render_distance = config_json["world"].value("render_distance", 4);
  view_distance = config_json["world"].value("view_distance", 8);
  world_logger = std::make_unique<logger_decorator>("world", "world.log");
  generate_world_thread = std::thread(&world::generate_world_thread_func, this);
  generate_world_thread_running = true;
}

world::~world() {
  generate_world_thread_running = false;
  generate_world_thread.join();
}

void world::generate_chunk(const int32_t x, const int32_t y, const int32_t z, bool generate_model) {
  // Generate the chunk
  // auto start = std::chrono::high_resolution_clock::now();
  std::unique_ptr<chunk> chunk_new = genv2.generate_chunk(x, y, z, true);
  // auto end = std::chrono::high_resolution_clock::now();

  // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  // world_logger->debug("Chunk generation took {}ms", duration.count());

  // Add the chunk to the world
  if (generate_model) {
    generate_chunk_models(*chunk_new.get());
  }
  chunks.push_back(std::move(chunk_new));
}

void world::generate_chunk_models(chunk &chunk_new) {
  auto start = std::chrono::high_resolution_clock::now();
  std::unique_ptr<Model> chunk_model = world_md.generate_chunk_model(chunk_new);
  chunk_model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _game_context_ref._texture;
  chunk_new.model = std::move(chunk_model);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  world_logger->debug("Chunk model generation took {}ms", duration.count());
}

bool world::is_chunk_exist(const int32_t x, const int32_t y, const int32_t z) {
  auto it = std::find_if(chunks.begin(), chunks.end(), [&](const auto &chunk) {
    const auto chunk_pos = chunk->get_position();
    return chunk_pos.x == x && chunk_pos.y == y && chunk_pos.z == z;
  });

  return it != chunks.end();
}

void world::clear() {
  // Clear the chunks
  chunks.clear();
}

void world::update() {
  if (IsKeyPressed(KEY_R)) {
    std::lock_guard<std::mutex> lock(world_generator_mutex);
    seed = std::random_device()();
    genv1.reseed(this->seed);
    genv2.reseed(this->seed);
    clear();
    spdlog::info("seed: {}", seed);
  }

  if (IsKeyPressed(KEY_C)) {
    std::lock_guard<std::mutex> lock(world_generator_mutex);
    clear();
  }
}

void world::draw3d() {
  for (auto const &_chunk : chunks) {
    chunk &current_chunk = *_chunk.get();
    auto chunk_coor = current_chunk.get_position();
    auto &blocks = current_chunk.get_blocks();

    auto &player1_pose = _game_context_ref.player_chunk_pos;

    // If chunk is too far away, don't render it
    if (std::abs(chunk_coor.x - player1_pose.x) > view_distance || std::abs(chunk_coor.y - player1_pose.y) > view_distance ||
        std::abs(chunk_coor.z - player1_pose.z) > view_distance) {
      continue;
    }

    if (current_chunk.model.get() == nullptr) {
      generate_chunk_models(current_chunk);
    }

    Model &current_model = *current_chunk.model.get();

    auto chunk_pos = chunk::get_real_position(current_chunk);

    Vector3 chunk_pos_center = {static_cast<float>(chunk_coor.x * chunk::chunk_size_x + chunk::chunk_size_x / 2.0f),
                                static_cast<float>(chunk_coor.y * chunk::chunk_size_y + chunk::chunk_size_y / 2.0f),
                                static_cast<float>(chunk_coor.z * chunk::chunk_size_z + chunk::chunk_size_z / 2.0f)};

    // For debug menu
    if (*_game_context_ref.display_debug_menu) {
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

    if (*_game_context_ref.display_debug_menu) {
      _game_context_ref.chunks_on_screen_count++;
      _game_context_ref.vectices_on_screen_count += current_model.meshes->vertexCount;
      _game_context_ref.triangles_on_screen_count += current_model.meshes->triangleCount;

      chunk_pos.x += static_cast<float>(chunk::chunk_size_x / 2.0f);
      chunk_pos.y += static_cast<float>(chunk::chunk_size_y / 2.0f);
      chunk_pos.z += static_cast<float>(chunk::chunk_size_z / 2.0f);

      DrawCubeWires(chunk_pos, static_cast<float>(chunk::chunk_size_x), static_cast<float>(chunk::chunk_size_y), static_cast<float>(chunk::chunk_size_z), RED);
    }
  }
}

void world::draw2d() {}

void world::generate_world_thread_func() {
  while (generate_world_thread_running) {
    std::lock_guard<std::mutex> lock(world_generator_mutex);
    for (int32_t x = -render_distance; x <= render_distance; x++) {
      for (int32_t y = -render_distance; y <= render_distance; y++) {
        for (int32_t z = -render_distance; z <= render_distance; z++) {
          if (!is_chunk_exist(_game_context_ref.player_chunk_pos.x + x, _game_context_ref.player_chunk_pos.y + y, _game_context_ref.player_chunk_pos.z + z)) {
            generate_chunk(_game_context_ref.player_chunk_pos.x + x, _game_context_ref.player_chunk_pos.y + y, _game_context_ref.player_chunk_pos.z + z, false);
          }
        }
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}