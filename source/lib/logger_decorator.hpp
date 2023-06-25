#ifndef WORLD_OF_CUBE_LOGGER_HPP
#define WORLD_OF_CUBE_LOGGER_HPP

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/async.h>
#include <spdlog/spdlog.h>
#include "spdlog/stopwatch.h"

class logger_decorator {
public:
  explicit logger_decorator(const std::string name, std::filesystem::path path) {
    spdlog::init_thread_pool(16384, 8);
    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto stderr_sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
    auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(path, 1024 * 1024 * 20, 5);

    _sinks.push_back(stdout_sink);
    _sinks.push_back(stderr_sink);
    _sinks.push_back(rotating_sink);
    
    _logger = std::make_shared<spdlog::async_logger>(name, _sinks.begin(), _sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::overrun_oldest);

    _logger->set_level(spdlog::level::trace);
    _logger->flush_on(spdlog::level::trace);
    //_logger->set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    //spdlog::flush_every(std::chrono::seconds(3));
    spdlog::register_logger(_logger);

    debug("Logger {} started", name);
    // spdlog::set_default_logger(_logger);

    //spdlog::stopwatch sw;    
    //world_logger->debug("Elapsed {}", sw);
    //world_logger->debug("Elapsed {:.3}", sw);
  }

  template <typename... Args> void trace(spdlog::format_string_t<Args...> fmt, Args &&...args) { _logger->trace(fmt, std::forward<Args>(args)...); }

  template <typename... Args> void debug(spdlog::format_string_t<Args...> fmt, Args &&...args) { _logger->debug(fmt, std::forward<Args>(args)...); }

  template <typename... Args> void info(spdlog::format_string_t<Args...> fmt, Args &&...args) { _logger->info(fmt, std::forward<Args>(args)...); }

  template <typename... Args> void warn(spdlog::format_string_t<Args...> fmt, Args &&...args) { _logger->warn(fmt, std::forward<Args>(args)...); }

  template <typename... Args> void error(spdlog::format_string_t<Args...> fmt, Args &&...args) { _logger->error(fmt, std::forward<Args>(args)...); }

  template <typename... Args> void critical(spdlog::format_string_t<Args...> fmt, Args &&...args) { _logger->critical(fmt, std::forward<Args>(args)...); }

  void flush() { _logger->flush(); }

  void set_level(spdlog::level::level_enum lvl) { _logger->set_level(lvl); }

  void set_flush_level(spdlog::level::level_enum lvl) { _logger->flush_on(lvl); }

  spdlog::level::level_enum get_level() { return _logger->level(); }

  spdlog::level::level_enum get_flush_level() { return _logger->flush_level(); }

  ~logger_decorator() {}

  spdlog::async_logger &get_logger() { return *_logger; }

  std::shared_ptr<spdlog::async_logger> get_logger_ptr() { return _logger; }

  static void shutdown() { spdlog::shutdown(); }
  static void flush_every(std::chrono::seconds interval) { spdlog::flush_every(interval); }

private:
  std::vector<spdlog::sink_ptr> _sinks;
  std::shared_ptr<spdlog::async_logger> _logger;
};

#endif // WORLD_OF_CUBE_WORLD_HPP