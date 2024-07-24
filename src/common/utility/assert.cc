
#include "common/utility/assert.h"

namespace snowball::utils {

auto ReleaseAssert(bool condition, const std::string& message) -> void {
  if (!condition) {
    throw AssertError(message);
  }
}

#if defined(SNOWBALL_DEBUG)
inline auto Assert(bool condition, const std::string& message) -> void {
  ReleaseAssert(condition, message);
}
#endif

}; // namespace snowball::utils
