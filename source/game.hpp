#ifndef GAME_HPP
#define GAME_HPP

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <numeric>
#include <omp.h>
#include <queue>
#include <random>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

//  Raylib
#include "raylib.h"

// Cube lib

extern "C" {
#include "benlib_intro.h"
#include "raylib_cpp_intro.h"
#include "raylib_intro.h"
}

#include "Block.hpp"
#include "block_utils.hpp"
#include "Chunk.hpp"
#include "player.hpp"
#include "world.hpp"
#include "world_model.hpp"

#include "debugMenu.hpp"
#include "gameElementHandler.hpp"
#include "gameContext.hpp"
#include "nlohmann/json.hpp"

class game {
public:
  game(nlohmann::json &_config_json);
  ~game();
  void run();
  void init();

  void render_thread_func();
  void auxillary_thread_game_logic();

private:
  std::shared_ptr<debugMenu> debug_menu1;
  std::shared_ptr<player> player1;
  std::shared_ptr<world> world_new;
  std::shared_ptr<gameContext> game_context1;
  std::mutex _mutex;

  std::vector<std::shared_ptr<gameElementHandler>> game_classes;

  nlohmann::json &_configJson;
  std::future<void> auxillary_thread;

  bool game_running = true;
};

#endif // GAME_HPP
