
#pragma once

#include "common/stl.h"
#include "common/utility/assert.h"

namespace snowball {
namespace utils {

/// @brief Wrapper for a safe pointer.
/// A safe pointer is a pointer that is guaranteed to be non-null
/// or it at least throws an exception if it is null. This is useful
/// for ensuring that pointers are not null and that they are safe to
/// dereference.
template <typename T>
class SafePointer final {
public:
  /// @brief Construct a new safe pointer.
  /// @param ptr The pointer to wrap.
  explicit SafePointer(T* ptr) : mPtr(ptr) {
    SNOWBALL_RELEASE_ASSERT(ptr != nullptr, "Pointer cannot be null.");
  }

  SafePointer() = default;

  /// @brief Dereference the pointer.
  /// @return The dereferenced pointer.
  auto operator*() -> T& { return *mPtr; }
  /// @brief Dereference the pointer.
  /// @return The dereferenced pointer.
  auto operator*() const -> const T& { return *mPtr; }

  /// @brief Access the pointer.
  /// @return The pointer.
  auto operator->() -> T* { return mPtr; }
  /// @brief Access the pointer.
  /// @return The pointer.
  auto operator->() const -> const T* { return mPtr; }

  /// @brief Get the pointer.
  /// @return The pointer.
  auto Get() -> T* { return mPtr; }
  /// @brief Get the pointer.
  /// @return The pointer.
  auto Get() const -> const T* { return mPtr; }

  /// @brief Default destructor.
  ~SafePointer() = default;
private:
  T* mPtr; ///< The pointer.
};

}; // namespace utils

template <typename T>
using SafePointer = utils::SafePointer<T>; // We want to use SafePointer without the utils namespace.
}; // namespace snowball
