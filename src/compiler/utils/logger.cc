
#include <fmt/color.h>
#include <fmt/ostream.h>

#include <sstream>

#include "compiler/utils/utils.h"
#include "compiler/utils/logger.h"

namespace snowball {
namespace utils {

#define BOLD "\033[1m"
#define OFF "\033[0m"

std::string highlight_quotes(const std::string& message) {
  std::stringstream ss;
  bool in_highlight = false;
  for (char c : message) {
    bool append = false;
    if (c == '\'') {
      if (in_highlight) append = true;
      else {
        in_highlight = true;
        ss << BOLD;
      }
    }
    ss << c;
    if (append) {
      ss << OFF;
      in_highlight = false;
    }
  }
  return ss.str();
}

}
}
