

#pragma once
#include "common/stl.h"

#include <future>

namespace snowball {
namespace utils {

/// @brief It runs a function asynchronously.
/// @param func The function to run.
/// @note The function should actually be an object that has an
///     `operator()` method.
template <typename Function, typename... Args>
auto RunAsync(Function&& func, Args&&... args) -> std::future<decltype(func(args...))> {
  return std::async(std::launch::async, 
    std::forward<Function>(func), std::forward<Args>(args)...);
}

}; // namespace utils
}; // namespace snowball

