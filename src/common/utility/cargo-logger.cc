
#include "common/utility/cargo-logger.h"

namespace snowball::utils::cargo {

auto DisplayStatus(const String& label, const String& message) -> void {
  fmt::println("{:>13} {}", 
    fmt::styled(label,
      fmt::fg(fmt::terminal_color::green) | fmt::emphasis::bold),
    message);
}

}