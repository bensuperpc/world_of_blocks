#ifndef WORLD_OF_CUBE_DEBUG_MENU_HPP
#define WORLD_OF_CUBE_DEBUG_MENU_HPP

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include <omp.h>

// Raylib
#include "raylib.h"

#include "gameElementHandler.hpp"
#include "gameContext.hpp"
#include "vector.hpp"

class debugMenu : public gameElementHandler {
public:
  debugMenu(gameContext &game_context_ref);

  ~debugMenu();

  void updateGameInput() override;
  void updateGameLogic() override;

  void updateOpenglLogic() override;
  void updateDraw2d() override;
  void updateDraw3d() override;
  void updateDrawInterface() override;

  gameContext &_game_context_ref;

  // Debug
  bool block_grid = true;
};

#endif // WORLD_OF_CUBE_WORLD_HPP