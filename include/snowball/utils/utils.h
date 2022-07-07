#include <vector>
#include <string>

#ifndef __SNOWBALL_UTILS__MAIN_H_
#define __SNOWBALL_UTILS__MAIN_H_

#define GET_FUNCTION_FROM_CLASS(class, function, ...) \
    Logger::format("%s.%s", class, mangle(function, __VA_ARGS__).c_str())

namespace snowball_utils {
    std::vector<std::string> split(std::string str, std::string token);
}

#endif // __SNOWBALL_UTILS__MAIN_H_
