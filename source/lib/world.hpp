#ifndef WORLD_OF_CUBE_WORLD_HPP
#define WORLD_OF_CUBE_WORLD_HPP

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <future>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <numeric>
#include <queue>
#include <random>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

#include <omp.h>

#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"

#include "raylib.h"

// Cube lib
#include "block.hpp"
#include "chunk.hpp"
#include "game_class.hpp"
#include "game_context.hpp"
#include "generatorv1.hpp"
#include "generatorv2.hpp"
#include "world_model.hpp"

class world : public game_class {
public:
  world(game_context &game_context_ref, nlohmann::json &_config_json);

  ~world();

  void generate_world();
  void generate_world_models();

  void generate_chunk(const int32_t, const int32_t, const int32_t, bool);
  void generate_chunk_models(chunk &);
  bool is_chunk_exist(const int32_t, const int32_t, const int32_t);

  void generate_world_thread_func();

  void clear();

  void update() override;
  void draw2d() override;
  void draw3d() override;

  siv::PerlinNoise::seed_type seed = 2510586073u;

  generatorv1 genv1 = generatorv1(this->seed);
  generatorv2 genv2 = generatorv2(this->seed);

  world_model world_md = world_model();

  std::list<std::unique_ptr<chunk>> chunks;

  int32_t render_distance = 4;
  int32_t view_distance = 8;

  std::mutex world_mutex;
  std::queue<std::tuple<int32_t, int32_t, int32_t>> world_queue;
  std::thread generate_world_thread;
  bool generate_world_thread_running = true;

  game_context &_game_context_ref;
  nlohmann::json &config_json;
};

#endif // WORLD_OF_CUBE_WORLD_HPP