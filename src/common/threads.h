#pragma once

#include "common/stl.h"
#include "common/globals.h"

namespace snowball {

/// @brief Get the number of threads to use.
/// @note It takes into account the `--threads` flag. If
///     the flag is not set (or set to 0), it will return
///     the number of threads available on the system.
auto GetNumThreads() -> u8;

/// @brief It will create a thread pool with the number of threads
///     and execute the given function for the given number of times.
/// @param numThreads The number of threads to use.
/// @param numTimes The number of times to execute the function.
/// @param func The function to execute.
auto ThreadPoolExecutor(usize numTimes, Function<void(usize)> func, 
    u8 numThreads = ::snowball::GetNumThreads()) -> void;

} // namespace snowball