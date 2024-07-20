export module stl;

import <vector>;
import <map>;
import <unordered_map>;
import <set>;
import <optional>;
import <string>;
import <functional>;

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

  using i8 = int8_t;
  using i16 = int16_t;
  using i32 = int32_t;
  using i64 = int64_t;
  
  using u8 = uint8_t;
  using u16 = uint16_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  using f32 = float;
  using f64 = double;
}; // namespace snowball
