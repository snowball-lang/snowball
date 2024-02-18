
#include <vector>
#include "compiler/reports/reporter.h"
#include "compiler/utils/logger.h"

namespace snowball {
using namespace utils;

void Reporter::add_error(const Error& error) {
  errors.push_back(error);
}

bool Reporter::handle_errors() {
  unsigned int error_count = 0;
  unsigned int warning_count = 0;
  for (auto error : errors) {
    error.print();
    switch (error.get_type()) {
      case Error::Type::Err:
        error_count++;
        break;
      case Error::Type::Warn:
        warning_count++;
        break;
      default:
        break;
    }
  }
  Logger::error("Snowball encountered {} error(s) and {} warning(s).", error_count, warning_count);
  return has_errors();
}

bool Reporter::has_errors() const {
  return errors.size() > 0;
}

}
