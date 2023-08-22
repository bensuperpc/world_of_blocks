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

// spdlog
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/async.h>
#include <spdlog/spdlog.h>

#include "raylib.h"

// Cube lib
#include "Block.hpp"
#include "Chunk.hpp"
#include "gameElementHandler.hpp"
#include "game_context.hpp"
#include "Generator.hpp"
#include "world_model.hpp"

#include "logger/logger_base.hpp"

class world : public gameElementHandler {
public:
  world(game_context &game_context_ref, nlohmann::json &_config_json);

  ~world();

  void generate_world();
  void generate_world_models();

  std::unique_ptr<Chunk> generate_chunk(const int32_t, const int32_t, const int32_t, bool);
  void generate_chunk_models(Chunk &);
  bool is_chunk_exist(std::list<std::unique_ptr<Chunk>>& _chunks, const int32_t, const int32_t, const int32_t) const noexcept;

  void generate_world_thread_func();

  void clear();

  void updateGameInput() override;
  void updateGameLogic() override;

  void updateOpenglLogic() override;
  void updateDraw2d() override;
  void updateDraw3d() override;
  void updateDrawInterface() override;

  int32_t seed = 251058607;

  Generator genv2 = Generator(seed);

  world_model world_md = world_model();

  std::list<std::unique_ptr<Chunk>> chunks;
  std::list<std::unique_ptr<Chunk>> tmpChunks;

  int32_t render_distance = 4;
  int32_t view_distance = 6;
  int32_t unload_distance = 8;

  std::thread generate_world_thread;
  bool generate_world_thread_running = true;

  bool free_world = false;

  game_context &_game_context_ref;
  nlohmann::json &config_json;

  // logger
  std::unique_ptr<LoggerDecorator> logger;
};

#endif // WORLD_OF_CUBE_WORLD_HPP