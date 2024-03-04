
#ifndef __SNOWBALL_COMPILER_UTILS_UTILS_H__
#define __SNOWBALL_COMPILER_UTILS_UTILS_H__

#include <string>
#include <vector>

#include <fmt/format.h>
#include "compiler/utils/logger.h"

#define F(...) fmt::format(__VA_ARGS__)

#ifndef NDEBUG
#define sn_assert(expr, ...) if (!(expr)) { \
  snowball::utils::Logger::fatal(F(__VA_ARGS__)); \
  abort(); \
}

#define DBG(x) fmt::print("DBG: "#x" = {}\n", x);
#else
#define sn_assert(expr, ...)
#define DBG(x)
#endif

namespace snowball {
namespace utils {

std::vector<std::string> split(std::string str, const std::string& delimiter);
bool sw(const std::string& str, const std::string& prefix);

}
}

#endif // __SNOWBALL_COMPILER_UTILS_UTILS_H__
