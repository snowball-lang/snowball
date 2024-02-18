
#ifndef __SNOWBALL_COMPILER_REPORTS_DBG_H__
#define __SNOWBALL_COMPILER_REPORTS_DBG_H__

#include <string>

namespace snowball {
namespace reports {

class DebugSourceLocation {
public:
  std::string line_after_after;
  std::string line_after;
  std::string line;
  std::string line_before;
  std::string line_before_before;

  static DebugSourceLocation from_file(const std::string& file, unsigned int line);
};
}
}

#endif // __SNOWBALL_COMPILER_REPORTS_DBG_H__
