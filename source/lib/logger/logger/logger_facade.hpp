#ifndef WORLD_OF_CUBE_LOGGER_DECORATOR_HPP
#define WORLD_OF_CUBE_LOGGER_DECORATOR_HPP

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#ifdef __GNUC__
#pragma GCC diagnostic push 
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang system_header
#endif
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/stopwatch.h"
#include <spdlog/async.h>
#include <spdlog/spdlog.h>

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic pop
#endif

class logger_decorator final {
public:
  explicit logger_decorator(const std::string &name, std::filesystem::path path) {
    {
      std::lock_guard<std::mutex> lock(_mutex);
      if (_thread_pool == nullptr) {
        _thread_pool = std::make_shared<spdlog::details::thread_pool>(32768, 16);
      }
    }

    std::vector<spdlog::sink_ptr> _sinks;

    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto specific_file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(path, 1024 * 1024 * 20, 5);

    stdout_sink->set_level(spdlog::level::debug);
    specific_file_sink->set_level(spdlog::level::trace);

    _sinks.push_back(stdout_sink);
    _sinks.push_back(specific_file_sink);

    _logger = std::make_shared<spdlog::async_logger>(name, _sinks.begin(), _sinks.end(), _thread_pool, spdlog::async_overflow_policy::block);

    _logger->set_level(spdlog::level::trace);
    _logger->flush_on(spdlog::level::trace);

    debug("Logger {} started", name);
  }

  template <typename... Args> void trace(spdlog::format_string_t<Args...> fmt, Args &&...args) { _logger->trace(fmt, std::forward<Args>(args)...); }

  template <typename... Args> void debug(spdlog::format_string_t<Args...> fmt, Args &&...args) { _logger->debug(fmt, std::forward<Args>(args)...); }

  template <typename... Args> void info(spdlog::format_string_t<Args...> fmt, Args &&...args) { _logger->info(fmt, std::forward<Args>(args)...); }

  template <typename... Args> void warn(spdlog::format_string_t<Args...> fmt, Args &&...args) { _logger->warn(fmt, std::forward<Args>(args)...); }

  template <typename... Args> void error(spdlog::format_string_t<Args...> fmt, Args &&...args) { _logger->error(fmt, std::forward<Args>(args)...); }

  template <typename... Args> void critical(spdlog::format_string_t<Args...> fmt, Args &&...args) { _logger->critical(fmt, std::forward<Args>(args)...); }

  void flush() { _logger->flush(); }

  void set_pattern(std::string &pattern, spdlog::pattern_time_type time_type = spdlog::pattern_time_type::local) { _logger->set_pattern(pattern, time_type); }

  void set_level(spdlog::level::level_enum lvl) { _logger->set_level(lvl); }

  void set_flush_level(spdlog::level::level_enum lvl) { _logger->flush_on(lvl); }

  spdlog::level::level_enum get_level() { return _logger->level(); }

  spdlog::level::level_enum get_flush_level() { return _logger->flush_level(); }

  ~logger_decorator() {
    debug("Logger {} stopped", _logger->name());
    flush();
  }

  std::shared_ptr<spdlog::async_logger> get_logger() { return _logger; }

  std::shared_ptr<spdlog::details::thread_pool> get_thread_pool() { return _thread_pool; }

private:
  std::shared_ptr<spdlog::async_logger> _logger;
  // Ensure thread pool is deleted at end of program after all loggers
  static inline std::shared_ptr<spdlog::details::thread_pool> _thread_pool = nullptr;
  static inline std::mutex _mutex;
};

#endif // WORLD_OF_CUBE_SODLOG_LOGGER_HPP