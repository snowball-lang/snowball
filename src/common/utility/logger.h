
#pragma once

#include "common/stl.h"
#include "common/utility/format.h"

#include <fmt/color.h>

namespace snowball {
namespace utils {

/// @brief An utility class used to display and format log messages.
/// @note It should be used from the global logger instance. @see GetLogger().
class Logger final {
  /// @brief Implementation of the log function.
  /// @note With use this function because we want to
  ///  log the message to various outputs (e.g. console, file).
  auto LogImpl(const String& message) -> void;
public:
  enum class Level : u8 {
    Debug,
    Info,
    Warning,
    Error,
    Fatal,
  };
  /// @brief Log a message with a specific log level.
  /// @param level The log level.
  /// @param message The log message.
  auto Log(Level level, const String& message) -> void;
  /// @brief Log a debug message.
  /// @param message The log message.
  auto Debug(const String& message) -> void;
  /// @brief Log an info message.
  /// @param message The log message.
  auto Info(const String& message) -> void;
  /// @brief Log a warning message.
  /// @param message The log message.
  auto Warning(const String& message) -> void;
  /// @brief Log an error message.
  /// @param message The log message.
  auto Error(const String& message) -> void;
  /// @brief Log a fatal error message.
  /// @param message The log message.
  auto Fatal(const String& message) -> void;

  /// @brief Get the prefix for the log level.
  /// @param level The log level.
  auto GetLevelPrefix(Level level) const -> String;

  /// @brief Get the color for the log level.
  /// @param level The log level.
  auto GetLevelColor(Level level) const -> fmt::terminal_color;

  Logger() = default;
  ~Logger() = default;
};

/// @brief Get the global logger instance.
auto GetLogger() -> Logger&;

} // namespace utils
} // namespace snowball
