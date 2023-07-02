#ifndef WORLD_OF_CUBE_DEBUG_MENU_HPP
#define WORLD_OF_CUBE_DEBUG_MENU_HPP

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include <omp.h>

// Raylib
#include "raylib.h"

#include "game_class.hpp"
#include "game_context.hpp"
#include "vector.hpp"

class debug_menu : public game_class {
public:
  debug_menu(game_context &game_context_ref);

  ~debug_menu();

  void update_game_input() override;
  void update_game_logic() override;

  void update_opengl_logic() override;
  void update_draw2d() override;
  void update_draw3d() override;

  game_context &_game_context_ref;

  // Debug
  bool block_grid = true;
};

#endif // WORLD_OF_CUBE_WORLD_HPP