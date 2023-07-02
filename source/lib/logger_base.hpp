#ifndef WORLD_OF_CUBE_LOGGER_BASE_HPP
#define WORLD_OF_CUBE_LOGGER_BASE_HPP

#include <filesystem>
#include <string>

#include "logger_decorator.hpp"

class logger_base {
protected:
  explicit logger_base(const std::string &name, std::filesystem::path path) {
    logger = std::make_unique<logger_decorator>("world", "world.log");
  }
  logger_base() = delete;

  virtual ~logger_base() {
    logger->flush();
    logger.reset();
  }
  std::unique_ptr<logger_decorator> logger;
};

#endif // WORLD_OF_CUBE_LOGGER_BASE_HPP