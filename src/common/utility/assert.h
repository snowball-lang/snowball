
#pragma once
#include "common/stl.h"

#if !defined(SNOWBALL_RELEASE) && !defined(SNOWBALL_DEBUG)
#error "SNOWBALL_RELEASE or SNOWBALL_DEBUG must be defined."
#elif defined(SNOWBALL_RELEASE) && defined(SNOWBALL_DEBUG)
#error "SNOWBALL_RELEASE and SNOWBALL_DEBUG cannot be defined at the same time."
#endif

namespace snowball {
namespace utils {

class AssertError : public std::runtime_error {
public:
  explicit AssertError(const std::string& message) 
    : std::runtime_error(message) {}
};

#ifdef SNOWBALL_DEBUG

/// @brief Create a basic assert function.
/// @param condition The condition to check.
/// @param message The message to print if the condition is false.
auto Assert(bool condition, const std::string& message) -> void;

#define SNOWBALL_ASSERT(...) \
  SNOWBALL_RELEASE_ASSERT(__VA_ARGS__)
#else
#define SNOWBALL_ASSERT(condition, message)
#endif

/// @brief Create an assert function that will always be called.
/// @param condition The condition to check.
/// @param message The message to print if the condition is false.
auto ReleaseAssert(bool condition, const std::string& message) -> void;

#define SNOWBALL_RELEASE_ASSERT(condition, message) \
  snowball::utils::ReleaseAssert(condition, message)

#define SNOWBALL_ASSERT_SUCCESS(expr, ...) \
  SNOWBALL_RELEASE_ASSERT((expr) == ::snowball::Success, __VA_ARGS__)

#define RET_FAIL(expr) \
  if ((expr) == Failure) return Failure;

}; // namespace utils
}; // namespace snowball
