
#pragma once

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <optional>

namespace snowball {
  
template <typename T>
using Vector = std::vector<T>;

template <typename T>
using List = std::list<T>;

template <typename K, typename V>
using Map = std::map<K, V>;

template <typename T>
using Opt = std::optional<T>;

template <typename T>
std::optional<T> Some(T value) {
  return std::make_optional(value);
}

template <typename T>
std::optional<T> None() {
  return std::nullopt;
}

template <typename T>
using Set = std::set<T>;

template <typename T>
using Queue = std::queue<T>;

template <typename T>
using Stack = std::stack<T>;

} // namespace snowball
