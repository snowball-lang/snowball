#include "../common.h"

#include <assert.h>
#include <filesystem>
#include <functional>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#ifndef __SNOWBALL_UTILS__MAIN_H_
#define __SNOWBALL_UTILS__MAIN_H_

#define ASSERT(x) assert(x);

namespace snowball {
namespace utils {

std::string get_exe_folder();
std::string itos(int i);
std::filesystem::path get_lib_folder();
bool isNumber(const std::string& s);
std::string getUTF8FromIndex(const std::string& s, const int index);
std::list<std::string> split(std::string str, std::string token);
bool endsWith(const std::string& mainStr, const std::string& toMatch);
bool startsWith(const std::string& str, const std::string& comp);
void replaceAll(std::string& str, const std::string& from, const std::string& to);
std::string getSubstringByRange(
        const std::string& str, const std::pair<int, int>& start, const std::pair<int, int>& end);
template <typename Iter>
// https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
std::string join(Iter begin, Iter end, std::string const& separator) {
  std::ostringstream result;
  if (begin != end) result << *begin++;
  while (begin != end) result << separator << *begin++;
  return result.str();
}

template <typename StTy, typename Vec1>
std::vector<Vec1> vector_iterate(std::vector<StTy> p_vec, std::function<Vec1(StTy)> p_function) {
  // Why did the programmer quit his job? He didn't get arrays.
  std::vector<Vec1> vec;

  for (auto item : p_vec) {
    auto v1 = p_function(item);
    vec.push_back(v1);
  }

  return vec;
}

template <typename StTy, typename Vec1, typename Vec2>
std::pair<std::vector<Vec1>, std::vector<Vec2>> vectors_iterate(
        std::vector<StTy> p_vec, std::function<std::pair<Vec1, Vec2>(StTy)> p_function) {
  std::vector<Vec1> vec1;
  std::vector<Vec2> vec2;

  for (auto item : p_vec) {
    auto [v1, v2] = p_function(item);

    vec1.push_back(v1);
    vec2.push_back(v2);
  }

  return {vec1, vec2};
}

template <typename Key, typename Val, typename Return = Val>
std::vector<Return> map(std::map<Key, Val> p_map, std::function<Return(std::pair<Key, Val>)> cb) {
  std::vector<Return> vec;

  for (auto item : p_map) { vec.push_back(cb(item)); }

  return vec;
}

template <typename IteratorType>
IteratorType at(std::list<IteratorType> _list, int _i) {
  typename std::list<IteratorType>::iterator it = _list.begin();
  for (int i = 0; i < _i; i++) { ++it; }
  return *it;
}

template <typename Key, typename Val, typename Return = Val>
std::vector<Return> map(std::list<std::pair<Key, Val>> p_map, std::function<Return(std::pair<Key, Val>)> cb) {
  std::vector<Return> vec;

  for (auto item : p_map) { vec.push_back(cb(item)); }

  return vec;
}

template <typename Desired, typename Current>
Desired* cast(Current curr) {
  return dynamic_cast<Desired*>(curr);
}

template <typename T>
std::shared_ptr<T> copy_shared(std::shared_ptr<T> x) {
  return std::make_shared<T>(*x);
}

template <typename Desired, typename Current>
std::shared_ptr<Desired> dyn_cast(std::shared_ptr<Current> curr) {
  return std::dynamic_pointer_cast<Desired>(curr);
}

template <typename T, typename R>
std::vector<R> _x_to_vec(T x) {
  std::vector<R> vec;
  for (auto i : x) { vec.push_back(i.second); }
  return vec;
}

template <typename Key, typename Value>
std::vector<Value> map_to_vector(std::map<Key, Value> m) {
  return _x_to_vec<std::map<Key, Value>, Value>(m);
}
template <typename Key, typename Value>
std::vector<Value> list_to_vector(std::list<std::pair<Key, Value>> l) {
  return _x_to_vec<std::list<std::pair<Key, Value>>, Value>(l);
}

template <typename T, class X>
void assert_value_type() {
  static_assert(std::is_same<T, X>::value, "value types must be the same!");
}

template <typename T>
T* copy(T* x) {
  return new T(*x);
}

#if _SNOWBALL_TIMERS_DEBUG
template <typename F, typename... Ts>
double _timer(F&& f, Ts&&... args) {
  clock_t start = clock();
  std::forward<F>(f)(std::forward<Ts>(args)...);
  return static_cast<double>(clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
}
#endif

} // namespace utils
} // namespace snowball

#endif // __SNOWBALL_UTILS__MAIN_H_
