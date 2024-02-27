
#include "compiler/reports/dbg.h"

namespace snowball {
namespace reports {

DebugSourceLocation DebugSourceLocation::from_file(const std::string& file, unsigned int line) {
  DebugSourceLocation dsl;
  unsigned int line_number = 1;
  unsigned int char_index = 0;
  while (char_index < file.size()) {
    if (file[char_index] == '\n') {
      line_number++;
      char_index++;
      continue;
    }
    if (line_number+2 == line) {
      dsl.line_before_before += file[char_index];
    } else if (line_number+1 == line) {
      dsl.line_before += file[char_index];
    } else if (line_number == line) {
      dsl.line += file[char_index];
    } else if (line_number == line+1) {
      dsl.line_after += file[char_index];
    } else if (line_number == line+2) {
      dsl.line_after_after += file[char_index];
    }
    char_index++;
  }
  return dsl;
}

}
}
