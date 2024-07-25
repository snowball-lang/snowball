
#include "common/stl.h"
#include "common/error.h"

#include "common/utility/format.h"
#include "common/utility/logger.h"
#include "common/utility/string.h"

#include "common/globals.h"

#include <fmt/color.h>

namespace snowball::utils {

auto Logger::LogImpl(const String& message) -> void {
  // TODO: Log to file.
  fmt::print("{}\n", message);
}

auto Logger::Log(Level level, const String& message) -> void {
  for (const auto& line : Split(message, '\n')) {
    LogImpl(Format("{}: {}", 
      fmt::styled(GetLevelPrefix(level), 
        fmt::fg(GetLevelColor(level)) | fmt::emphasis::bold),
      line));
  }
}

#define SNOWBALL_LOGGER_LEVEL(level) \
  auto Logger::level(const String& message) -> void { \
    Log(Level::level, message); \
  }

SNOWBALL_LOGGER_LEVEL(Info);
SNOWBALL_LOGGER_LEVEL(Warning);
SNOWBALL_LOGGER_LEVEL(Error);
SNOWBALL_LOGGER_LEVEL(Fatal);

auto Logger::Debug(const String& message) -> void {
  if (opts::IsDebugVerbose() || opts::IsVerbose()) {
    Log(Level::Debug, message);
  }
}

auto Logger::GetLevelPrefix(Level level) const -> String {
  String prefix;
#define SNOWBALL_LOGGER_LEVEL_PREFIX(level, name) \
  case Level::level: \
    prefix = name; \
    break;

  switch (level) {
    SNOWBALL_LOGGER_LEVEL_PREFIX(Debug  , "debug");
    SNOWBALL_LOGGER_LEVEL_PREFIX(Info   , "info");
    SNOWBALL_LOGGER_LEVEL_PREFIX(Warning, "warn");
    SNOWBALL_LOGGER_LEVEL_PREFIX(Error  , "error");
    SNOWBALL_LOGGER_LEVEL_PREFIX(Fatal  , "fatal");
  }
#undef SNOWBALL_LOGGER_LEVEL_PREFIX
  return prefix;
}

auto Logger::GetLevelColor(Level level) const -> fmt::terminal_color {
  switch (level) {
    case Level::Debug  : return fmt::terminal_color::magenta;
    case Level::Info   : return fmt::terminal_color::green;
    case Level::Warning: return fmt::terminal_color::yellow;
    case Level::Error  : return fmt::terminal_color::red;
    case Level::Fatal  : return fmt::terminal_color::magenta;
  }
  UnreachableError("Invalid log level!");
}

auto GetLogger() -> Logger& {
  static Logger logger;
  return logger;
}

}; // namespace snowball::utils
