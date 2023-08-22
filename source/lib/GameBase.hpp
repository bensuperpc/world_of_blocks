#ifndef BRAWL_MASTERS_GAME_BASE_HPP
#define BRAWL_MASTERS_GAME_BASE_HPP

class GameBase {
public:
  virtual ~GameBase();
  explicit GameBase();

  bool isActive = true;
  bool isVisible = true;
};

#endif // BRAWL_MASTERS_GAME_BASE_HPP