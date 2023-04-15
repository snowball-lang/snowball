
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

std::string getSubstringByRange(const std::string& str,
                                const std::pair<int, int>& start,
                                const std::pair<int, int>& end) {
    int startPos      = 0;
    int endPos        = 0;
    int currentLine   = 1;
    int currentColumn = 1;

    // Iterate over the string to find the starting and ending positions of the
    // substring
    for (int i = 0; i < str.length(); i++) {
        if (currentLine == start.first && currentColumn == start.second) {
            startPos = i;
        }
        if (currentLine == end.first && currentColumn == end.second) {
            endPos = i;
            break;
        }
        if (str[i] == '\n') {
            currentLine++;
            currentColumn = 1;
        } else {
            currentColumn++;
        }
    }

    // Return the substring
    return str.substr(startPos, endPos - startPos);
}

std::string getUTF8FromIndex(const std::string& s, const int index) {
    std::string result;
    unsigned char c = s[index];

    if (c & 0x80) {                      // check if it's a multi-byte sequence
        if ((c & 0xE0) == 0xC0) {        // 2-byte sequence
            result = s.substr(index, 2);
        } else if ((c & 0xF0) == 0xE0) { // 3-byte sequence
            result = s.substr(index, 3);
        } else if ((c & 0xF8) == 0xF0) { // 4-byte sequence
            result = s.substr(index, 4);
        }
    } else { // single byte character
        result = c;
    }

    return result;
}

std::string get_lib_folder() {
    fs::path home       = getenv("HOME");
    fs::path exe_folder = home / (std::string)STATICLIB_DIR;
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

std::string itos(int i) // convert int to string
{
    std::stringstream s;
    s << i;

    return s.str();
}

} // namespace utils
} // namespace snowball
