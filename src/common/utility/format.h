
#pragma once

#include "common/stl.h"
#include <fmt/format.h>

namespace snowball {
namespace utils {

template <typename ...Args>
inline auto Format(const String& fmt, Args&&... args) -> String {
  return fmt::format(fmt, std::forward<Args>(args)...);
};

#ifndef SnowballFormat
#define SnowballFormat format_as
#endif 

} // namespace utils
} // namespace snowball
