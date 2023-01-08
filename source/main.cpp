#include <iostream>
#include <string>
#include <vector>

#include "game.hpp"

auto main(int argc, char* argv[]) -> int
{
    game current_game;
    current_game.init();
    current_game.run();
    return 0;
}