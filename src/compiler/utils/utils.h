
#if !defined(SNOWBALL_COMPILER_UTILS_UTILS_H) || defined(SNOWBALL_UTILS_REDEFINE_F__)
#include <fmt/format.h>
#define F(...) fmt::format(__VA_ARGS__)
#undef SNOWBALL_UTILS_REDEFINE_F__
#endif

#ifndef __SNOWBALL_COMPILER_UTILS_UTILS_H__
#define __SNOWBALL_COMPILER_UTILS_UTILS_H__

#include <string>
#include <vector>
#include <functional>

#include "compiler/utils/logger.h"

#ifndef sn_abort
#define sn_abort() abort()
#endif

#ifndef NDEBUG
#define sn_assert(expr, ...) if (!(expr)) { \
  snowball::utils::Logger::fatal(F(__VA_ARGS__)); \
  sn_abort(); \
}

#define DBG(x) fmt::print("DBG: "#x" = {}\n", x);
#else
#define sn_assert(expr, ...)
#define DBG(x)
#endif

namespace snowball {

template <typename...Ts>
class Self;

template <typename X, typename...Ts>
class Self<X,Ts...> : public Ts...
{
protected:
    typedef X self;
};

namespace utils {

std::vector<std::string> split(std::string str, const std::string& delimiter);
std::string join(const std::vector<std::string>& vec, const std::string& delimiter);
bool sw(const std::string& str, const std::string& prefix);

template <typename T, typename U>
std::vector<T> map(const std::vector<U>& vec, std::function<T(U)> fn) {
  std::vector<T> result;
  for (auto& item : vec) {
    result.push_back(fn(item));
  }
  return result;
}

}
}

#endif // __SNOWBALL_COMPILER_UTILS_UTILS_H__
