#include <vector>
#include <sstream>
#include <string>
#include <assert.h>

#ifndef __SNOWBALL_UTILS__MAIN_H_
#define __SNOWBALL_UTILS__MAIN_H_

#define ASSERT(x) assert(x);
#define GET_FUNCTION_FROM_CLASS(class, function, ...) \
    Logger::format("%s.%s", class, mangle(function, __VA_ARGS__).c_str())
#define GET_FUNCTION_FROM_CLASS_NO_MANGLE(class, function) \
    Logger::format("%s.%s", class.c_str(), function.c_str())


namespace snowball_utils {
    #if 0
    std::string get_exe_folder();
    #endif
    std::string get_lib_folder(bool is_obj = false);
    std::vector<std::string> split(std::string str, std::string token);
    bool endsWith(const std::string &mainStr, const std::string &toMatch);

    template <typename Iter>
    // https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
    std::string join(Iter begin, Iter end, std::string const& separator)
    {
        std::ostringstream result;
        if (begin != end)
            result << *begin++;
        while (begin != end)
            result << separator << *begin++;
        return result.str();
    }
}

#endif // __SNOWBALL_UTILS__MAIN_H_
