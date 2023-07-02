#ifndef WORLD_OF_CUBE_GAME_CLASS_HPP
#define WORLD_OF_CUBE_GAME_CLASS_HPP

#include "game_base.hpp"

#include <chrono>
#include <string>

class game_class : public game_base {
public:
  virtual ~game_class() = default;
  game_class() = default;

  virtual void update_game_input() = 0;
  virtual void update_game_logic() = 0;
  
  virtual void update_opengl_logic() = 0;
  virtual void update_draw3d() = 0;
  virtual void update_draw2d() = 0;

  std::string name = "game_class";

  bool is_active = true;
  bool is_visible = true;

  std::chrono::steady_clock::time_point last_action_time;
  std::chrono::milliseconds action_cooldown = std::chrono::milliseconds(15);
};

#endif // WORLD_OF_CUBE_GAME_CLASS_HPP