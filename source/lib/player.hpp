#ifndef WORLD_OF_CUBE_PLAYER_HPP
#define WORLD_OF_CUBE_PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>

#include <omp.h>

// Raylib
#include "raylib.h"

// World of blocks
#include "Chunk.hpp"
#include "gameElementHandler.hpp"
#include "game_context.hpp"

// spdlog
#include "logger/logger_facade.hpp"

class player : public gameElementHandler {
public:
  player(game_context &game_context_ref);

  ~player();

  void updateGameInput() override;
  void updateGameLogic() override;

  void updateOpenglLogic() override;
  void updateDraw2d() override;
  void updateDraw3d() override;
  void updateDrawInterface() override;

  Vector3 get_position() const;

  Camera camera;

  // Ray collision
  Ray ray;
  std::vector<std::pair<Block *, RayCollision>> collisions;
  RayCollision closest_collision = {false, 0, {0, 0, 0}, {0, 0, 0}};
  Block *closest_block = nullptr;

private:
  game_context &_game_context_ref;

  // logger
  std::unique_ptr<logger_decorator> player_logger;
};

#endif // WORLD_OF_CUBE_WORLD_HPP