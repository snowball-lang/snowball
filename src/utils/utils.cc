
#include "utils/utils.h"

#include "errors.h"

#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h> //GetModuleFileNameW
#else
#include <limits.h>
#include <unistd.h> //readlink
#endif

#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

namespace snowball {
namespace utils {

#if 0
std::string get_exe_folder() {
#ifdef _WIN32
        wchar_t path[MAX_PATH] = { 0 };
        GetModuleFileNameW(NULL, path, MAX_PATH);
        return path;
#else
        char result[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        return std::string(result, (count > 0) ? count : 0);
#endif
}

#endif

std::string get_lib_folder() {
    fs::path exe_folder = (std::string)STATICLIB_DIR;
    fs::path full_path  = exe_folder / _SNOWBALL_LIBRARY_DIR;

    bool filepathExists = fs::is_directory(full_path);
    if (!filepathExists) {
        throw snowball::SNError(snowball::Error::IO_ERROR,
                                "Could not find system libraries!");
    }

    return full_path;
}

void replaceAll(std::string& str, const std::string& from,
                const std::string& to) {
    if (from.empty()) return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like
                                  // replacing 'x' with 'yx'
    }
}

std::vector<std::string> split(std::string str, std::string token) {
    std::vector<std::string> result;
    while (str.size()) {
        int index = str.find(token);
        if (index != std::string::npos) {
            result.push_back(str.substr(0, index));
            str = str.substr(index + token.size());
            if (str.size() == 0) result.push_back(str);
        } else {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

bool endsWith(const std::string& mainStr, const std::string& toMatch) {
    return (mainStr.size() >= toMatch.size() &&
            mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(),
                            toMatch) == 0);
}

bool startsWith(const std::string& str, const std::string& comp) {
    return str.rfind(comp, 0) == 0;
}

std::string utf8_substr(const std::string str, unsigned int start,
                        unsigned int leng) {
    if (leng == 0) {
        return "";
    }
    long unsigned int c, i, ix, q, min = std::string::npos,
                                   max = std::string::npos;
    for (q = 0, i = 0, ix = str.length(); i < ix; i++, q++) {
        if (q == start) {
            min = i;
        }
        if (q <= start + leng || leng == std::string::npos) {
            max = i;
        }

        c = (unsigned char)str[i];
        if (
            // c>=0   &&
            c <= 127)
            i += 0;
        else if ((c & 0xE0) == 0xC0)
            i += 1;
        else if ((c & 0xF0) == 0xE0)
            i += 2;
        else if ((c & 0xF8) == 0xF0)
            i += 3;
        // else if (($c & 0xFC) == 0xF8) i+=4; // 111110bb //byte 5, unnecessary
        // in 4 byte UTF-8 else if (($c & 0xFE) == 0xFC) i+=5; // 1111110b
        // //byte 6, unnecessary in 4 byte UTF-8
        else
            return ""; // invalid utf8
    }
    if (q <= start + leng || leng == std::string::npos) {
        max = i;
    }
    if (min == std::string::npos || max == std::string::npos) {
        return "";
    }
    auto s = str.substr(min, leng + 1);
    return s;
}

std::string itos(int i) // convert int to string
{
    std::stringstream s;
    s << i;

    return s.str();
}

} // namespace utils
} // namespace snowball
