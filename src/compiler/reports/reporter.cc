
#include <vector>
#include "compiler/utils/utils.h"
#include "compiler/utils/logger.h"
#include "compiler/reports/reporter.h"

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
  if (has_errors())
    Logger::info(F("Snowball encountered {} error(s) and {} warning(s).", error_count, warning_count));
  return error_count > 0;
}

size_t Reporter::get_error_count() const {
  unsigned int error_count = 0;
  for (auto error : errors) {
    if (error.get_type() == Error::Type::Err)
      error_count++;
  }
  return error_count;
}

bool Reporter::has_errors() const {
  return errors.size() > 0;
}

}
