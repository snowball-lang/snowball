
#pragma once

#include "common/stl.h"
#include "common/utility/logger.h"
#include "common/utility/format.h"

#include <fmt/format.h>

namespace snowball {
namespace utils {
namespace cargo {

/// @brief Display a message to the console.
/// @param label The label to display.
/// @param message The message to display.
auto DisplayStatus(const String& label, const String& message) -> void;

}
} // namespace utils
} // namespace snowball
