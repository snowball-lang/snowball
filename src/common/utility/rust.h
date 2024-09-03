
#pragma once

#include "common/stl.h"
#include "clowder/src/lib.rs.h"

namespace snowball {
namespace utils {

template <typename T>
static inline auto RustToCpp(const ::rust::Vec<T>& vec) -> Vector<T> {
  Vector<T> result;
  result.reserve(vec.size());
  for (const auto& item : vec) {
    result.push_back(item);
  }
  return result;
}

}
}
