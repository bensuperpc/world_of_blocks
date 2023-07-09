#ifndef WORLD_OF_CUBE_PLAYER_HPP
#define WORLD_OF_CUBE_PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>

#include <omp.h>

// Raylib
#include "raylib.h"

// World of blocks
#include "chunk.hpp"
#include "game_class.hpp"
#include "game_context.hpp"

// spdlog
#include "logger/logger_facade.hpp"

class player : public game_class {
public:
  player(game_context &game_context_ref);

  ~player();

  void update_game_input() override;
  void update_game_logic() override;

  void update_opengl_logic() override;
  void update_draw2d() override;
  void update_draw3d() override;

  Vector3 get_position() const;

  Camera camera;

  // Ray collision
  Ray ray;
  std::vector<std::pair<block *, RayCollision>> collisions;
  RayCollision closest_collision = {false, 0, {0, 0, 0}, {0, 0, 0}};
  block *closest_block = nullptr;

private:
  game_context &_game_context_ref;

  // logger
  std::unique_ptr<logger_decorator> player_logger;
};

#endif // WORLD_OF_CUBE_WORLD_HPP