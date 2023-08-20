#ifndef BRAWL_MASTERS_GAME_BASE_HPP
#define BRAWL_MASTERS_GAME_BASE_HPP

class GameBase {
public:
  virtual ~GameBase();
  explicit GameBase();

  bool is_active = true;
  bool is_visible = true;
};

#endif // BRAWL_MASTERS_GAME_BASE_HPP