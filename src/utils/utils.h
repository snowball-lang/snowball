#include "../common.h"

#include <assert.h>
#include <functional>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#ifndef __SNOWBALL_UTILS__MAIN_H_
#define __SNOWBALL_UTILS__MAIN_H_

#define ASSERT(x) assert(x);

namespace snowball {
namespace utils {

#if 0
std::string get_exe_folder();
#endif

std::string itos(int i);
std::string get_lib_folder();
std::string utf8_substr(const std::string str, unsigned int start,
                        unsigned int leng);
std::vector<std::string> split(std::string str, std::string token);
bool endsWith(const std::string& mainStr, const std::string& toMatch);
bool startsWith(const std::string& str, const std::string& comp);
void replaceAll(std::string& str, const std::string& from,
                const std::string& to);

template <typename Iter>
// https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
std::string join(Iter begin, Iter end, std::string const& separator) {
    std::ostringstream result;
    if (begin != end) result << *begin++;
    while (begin != end) result << separator << *begin++;
    return result.str();
}

template <typename StTy, typename Vec1>
std::vector<Vec1> vector_iterate(std::vector<StTy> p_vec,
                                 std::function<Vec1(StTy)> p_function) {
    std::vector<Vec1> vec;

    for (auto item : p_vec) {
        auto v1 = p_function(item);
        vec.push_back(v1);
    }

    return vec;
}

template <typename StTy, typename Vec1, typename Vec2>
std::pair<std::vector<Vec1>, std::vector<Vec2>>
vectors_iterate(std::vector<StTy> p_vec,
                std::function<std::pair<Vec1, Vec2>(StTy)> p_function) {
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
std::vector<Return> map(std::map<Key, Val> p_map,
                        std::function<Return(std::pair<Key, Val>)> cb) {
    std::vector<Return> vec;

    for (auto item : p_map) {
        vec.push_back(cb(item));
    }

    return vec;
}

template <typename Desired, typename Current>
snowball::ptr<Desired> cast(Current curr) {
    return dynamic_cast<ptr<Desired>>(curr);
}

template <typename Desired, typename Current>
std::shared_ptr<Desired> dyn_cast(std::shared_ptr<Current> curr) {
    return std::dynamic_pointer_cast<Desired>(curr);
}

template <typename Key, typename Value>
std::vector<Value> map_to_vector(std::map<Key, Value> m) {
    std::vector<Value> vec;
    for (auto i : m) {
        vec.push_back(i.second);
    }
    return vec;
}

} // namespace utils
} // namespace snowball

#endif // __SNOWBALL_UTILS__MAIN_H_
