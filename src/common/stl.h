
#pragma once 

#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <optional>
#include <functional>
#include <string>
#include <cstdint>
#include <memory>
#include <filesystem>
#include <deque>
#include <fstream>

#ifndef SNOWBALL_NO_DISCARD
#define SNOWBALL_NO_DISCARD [[nodiscard]]
#endif

#include "common/llvm.h"
#include "common/utility/safe-pointer.h"

namespace snowball {
template <typename T, typename A = std::allocator<T>>
using Vector = std::vector<T, A>;

template <typename K, typename V>
using Map = std::map<K, V>;

template <typename K, typename V>
using UnorderedMap = std::unordered_map<K, V>;

template <typename T>
using Set = std::set<T>;

template <typename T>
using Opt = std::optional<T>;

template <typename T>
using Deque = std::deque<T>;

template <typename T>
Opt<T> Some(T&& value) {
  return std::make_optional(std::forward<T>(value));
}

constexpr std::nullopt_t None = std::nullopt;

using String = std::basic_string<char>;

template <typename T>
using Function = std::function<T>;

using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using f32 = float;
using f64 = double;

#ifdef SNOWBALL_SIZE_32
using usize = u32;
using isize = i32;
#else
using usize = u64;
using isize = i64;
#endif

using ptr_t = char *;
using const_ptr_t = const char *;
using SizeT = u64;
using uintptr_t = std::uintptr_t;

template <typename T>
using UniquePtr = std::unique_ptr<T>;

template <typename T>
using SharedPtr = std::shared_ptr<T>;

constexpr i32 Success = false;
constexpr i32 Failure = true;

/// @brief A class that cannot be copied.
class NonCopyable {
protected:
  constexpr NonCopyable() = default;
  ~NonCopyable()          = default;

private:
  NonCopyable(const NonCopyable &)    = delete;
  void operator=(const NonCopyable &) = delete;
};

/// @brief A class that cannot be moved.
class NonMovable {
protected:
  constexpr NonMovable() = default;
  ~NonMovable()          = default;

private:
  NonMovable(NonMovable &&)             = delete;
  NonMovable &operator=(NonMovable &&)  = delete;
};

/// @brief A class that can be created by using a static method.
template <typename T>
class Createable {
public:
  /// @brief Create a new instance of the class.
  /// @return The new instance.
  template <typename... Args>
  static auto Create(Args&&... args) -> T {
    return T(std::forward<Args>(args)...);
  }

protected:
  constexpr Createable() = default;
  ~Createable()          = default;
};

/// @brief A class that can be created by using a static method.
/// the difference between this and Createable is that this class
/// creates a safe pointer to the object.
template <typename T>
class SafeCreateable {
public:
  /// @brief Create a new instance of the class.
  /// @return The new instance.
  template <typename... Args>
  static auto Create(Args&&... args) -> SafePointer<T> {
    return SafePointer<T>(new T(std::forward<Args>(args)...));
  }

protected:
  constexpr SafeCreateable() = default;
  ~SafeCreateable()          = default;
};

/// @brief Create a pre-allocated vector.
/// @param size The size of the vector.
/// @return The pre-allocated vector.
template <typename T>
SNOWBALL_NO_DISCARD auto 
 AllocatedVector(usize size) -> Vector<T> {
  return Vector<T>(size);
}

namespace chrono {
  
using HighResClock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<HighResClock>;
using Duration = std::chrono::duration<f64>;

} // namespace chrono

namespace fs {

using Path = std::filesystem::path;
using namespace std::filesystem;

using FileStream = std::ifstream;

} // namespace fs
}; // namespace snowball

