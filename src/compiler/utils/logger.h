
#ifndef __SNOWBALL_COMPILER_UTILS_LOGGER_H__
#define __SNOWBALL_COMPILER_UTILS_LOGGER_H__

#include <fmt/color.h>

namespace snowball {
namespace utils {

class Logger {
public:
  template<typename... Args>
  static void error(const std::string& message, Args&&... args) {
    fmt::print("{}: {}\n", fmt::styled("error", fmt::fg(fmt::terminal_color::bright_red) | fmt::emphasis::bold), fmt::format(message, std::forward<Args>(args)...));
  }
  template<typename... Args>
  static void warn(const std::string& message, Args&&... args) {
    fmt::print("{}: {}\n", fmt::styled("warning", fmt::fg(fmt::terminal_color::bright_yellow) | fmt::emphasis::bold), fmt::format(message, std::forward<Args>(args)...));
  }
  template<typename... Args>
  static void info(const std::string& message, Args&&... args) {
    fmt::print(" {}: {}\n", fmt::styled("info", fmt::fg(fmt::terminal_color::bright_blue) | fmt::emphasis::bold), fmt::format(message, std::forward<Args>(args)...));
  }
  template<typename... Args>
  static void fatal(const std::string& message, Args&&... args) {
    fmt::print("{}: {}\n", fmt::styled("fatal", fmt::fg(fmt::terminal_color::bright_red) | fmt::emphasis::bold), fmt::format(message, std::forward<Args>(args)...));
    std::exit(1);
  }
};

std::string highlight_quotes(const std::string& message);

}
}

#endif // __SNOWBALL_COMPILER_UTILS_LOGGER_H__
