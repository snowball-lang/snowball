#include <vector>
#include <string>
#include <assert.h>

#ifndef __SNOWBALL_UTILS__MAIN_H_
#define __SNOWBALL_UTILS__MAIN_H_

#define ASSERT(x) assert(x);
#define GET_FUNCTION_FROM_CLASS(class, function, ...) \
    Logger::format("%s.%s", class, mangle(function, __VA_ARGS__).c_str())

namespace snowball_utils {
    std::string get_exe_folder();
    std::vector<std::string> split(std::string str, std::string token);
    bool endsWith(const std::string &mainStr, const std::string &toMatch);
}

#endif // __SNOWBALL_UTILS__MAIN_H_
