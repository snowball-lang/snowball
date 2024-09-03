
#include "common/utility/assert.h"

namespace snowball::utils {

auto ReleaseAssert(bool condition, const std::string& message) -> void {
  if (!condition) {
    throw AssertError(message);
  }
}

}; // namespace snowball::utils
