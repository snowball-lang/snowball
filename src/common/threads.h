#pragma once

#include "common/stl.h"
#include "common/globals.h"

namespace snowball {

/// @brief Get the number of threads to use.
/// @note It takes into account the `--threads` flag. If
///     the flag is not set (or set to 0), it will return
///     the number of threads available on the system.
auto GetNumThreads() -> u8;

} // namespace snowball