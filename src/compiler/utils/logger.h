
#ifndef __SNOWBALL_COMPILER_UTILS_LOGGER_H__
#define __SNOWBALL_COMPILER_UTILS_LOGGER_H__

#include <fmt/color.h>
#include <sstream>

namespace snowball {
namespace utils {

class Logger {
public:
  static void error(const std::string& message) {
    fmt::print("{}: {}\n", fmt::styled("error", fmt::fg(fmt::terminal_color::bright_red) | fmt::emphasis::bold), message);
  }
  static void warn(const std::string& message) {
    fmt::print("{}: {}\n", fmt::styled("warning", fmt::fg(fmt::terminal_color::bright_yellow) | fmt::emphasis::bold), message);
  }
  
  static void info(const std::string& message) {
    fmt::print(" {}: {}\n", fmt::styled("info", fmt::fg(fmt::terminal_color::bright_blue) | fmt::emphasis::bold), message);
  }
  
  static void fatal(const std::string& message) {
    fmt::print("{}: {}\n", fmt::styled("fatal", fmt::fg(fmt::terminal_color::bright_red) | fmt::emphasis::bold), message);
    std::exit(1);
  }
  
  static void success(const std::string& message) {
    fmt::print("{}: {}\n", fmt::styled("success", fmt::fg(fmt::terminal_color::bright_green) | fmt::emphasis::bold), message);
  }

  static void raw(const std::string& message) {
    fmt::print("{}\n", message);
  }

  static void status(const std::string& label, const std::string& message) {
    fmt::print("{:>11} {}\n", fmt::styled(label, fmt::fg(fmt::terminal_color::bright_green) | fmt::emphasis::bold), message);
  }

  static void progress(const std::string& label, float progress = 0.0f) {
    Logger::reset_status();
    std::stringstream output;
    output << "[";
    int pos = 20 * progress;
    for (int i = 0; i < 20; ++i) {
      if (i < pos)
        output << "=";
      else if (i == pos)
        output << ">";
      else
        output << " ";
    }
    output << "] ";
    fmt::print("{:>10} {} {}%", fmt::styled(label, fmt::fg(fmt::terminal_color::green) | fmt::emphasis::bold), output.str(), int(progress * 100.0f));
    fflush(stdout);
  }

  static void reset_status() {
    fmt::print("\33[2K\r");
    fflush(stdout);
  };
};

std::string highlight_quotes(const std::string& message);

}
}

#endif // __SNOWBALL_COMPILER_UTILS_LOGGER_H__
