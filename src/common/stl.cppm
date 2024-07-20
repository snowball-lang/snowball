export module stl;

import std;

export namespace snowball {
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
  Opt<T> Some(T&& value) {
    return std::make_optional(std::forward<T>(value));
  }

  template <typename T>
  Opt<T> None() {
    return std::nullopt;
  }

  using String = std::string;
  
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

  constexpr i32 Success = false;
  constexpr i32 Failure = true;
}; // namespace snowball
