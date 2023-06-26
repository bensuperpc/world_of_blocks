#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"
#include "raylib.h"

#include "logger_decorator.hpp"

#include "game.hpp"

auto main(int argc, char *argv[]) -> int {
  // Set log level for Raylib
  SetTraceLogLevel(LOG_WARNING);

  auto loggerer = logger_decorator("main", "main.log");

  loggerer.info("Welcome to world of blocks!");
  if (std::filesystem::exists("config.json")) {
    std::filesystem::remove("config.json");
  }


  nlohmann::json config_json;
  // Create json if not exist
  if (!std::filesystem::exists("config.json")) {
    spdlog::info("Config file not found, creating one...");
    config_json["display"]["screen_width"] = 1920;
    config_json["display"]["screen_height"] = 1080;
    config_json["display"]["target_fps"] = 240;
    config_json["world"]["render_distance"] = 2;
    config_json["world"]["view_distance"] = 4;

    std::ofstream config_file("config.json");
    config_file << config_json;
    config_file.close();
  }

  // Load json
  std::ifstream config_file("config.json");
  if (!config_file.is_open()) {
    spdlog::error("Failed to open config file!");
    return 1;
  }

  config_file >> config_json;

  game current_game = game(config_json);
  current_game.init();
  spdlog::info("Game initialized!");
  spdlog::info("Starting game loop...");
  current_game.run();
  spdlog::info("Game loop ended!");
  spdlog::shutdown();
  return 0;
}