
#ifndef __SNOWBALL_COMPILER_REPORTS_REPORTER_H__
#define __SNOWBALL_COMPILER_REPORTS_REPORTER_H__

#include <vector>
#include "compiler/reports/error.h"

namespace snowball {

class Reporter {
  std::vector<Error> errors;
public:
  bool handle_errors();
  bool has_errors() const;

  // not counting warnings
  size_t get_error_count() const;

  void add_error(const Error& error);
};

}

#endif // __SNOWBALL_COMPILER_REPORTS_REPORTER_H__
