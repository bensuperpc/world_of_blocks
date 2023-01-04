#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "world_of_blocks" ? 0 : 1;
}
