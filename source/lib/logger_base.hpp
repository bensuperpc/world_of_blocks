#ifndef WORLD_OF_CUBE_LOGGER_BASE_HPP
#define WORLD_OF_CUBE_LOGGER_BASE_HPP

#include <filesystem>
#include <string>

#include "logger_base.hpp"

class logger_base {
public:
  explicit logger_base(const std::string &name, std::filesystem::path path) {
  }

  virtual ~logger_base() {
  }

private:
};

#endif // WORLD_OF_CUBE_LOGGER_BASE_HPP