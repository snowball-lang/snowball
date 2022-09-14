
#include <string>
#include <vector>

#include "snowball/snowball.h"
#include "snowball/utils/utils.h"

#ifdef _WIN32
#include <windows.h>    //GetModuleFileNameW
#else
#include <limits.h>
#include <unistd.h>     //readlink
#endif

#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

namespace snowball_utils {

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

    std::string get_lib_folder(bool is_obj) {
        fs::path exe_folder = STATICLIB_DIR;
        fs::path full_path = is_obj ? exe_folder : (exe_folder / _SNOWBALL_LIBRARY_DIR);

        bool filepathExists = fs::is_directory(full_path);
        if (!filepathExists) {
            throw snowball::SNError(snowball::Error::IO_ERROR, "Could not find system libraries!");
        }

        return full_path;
    }

    std::vector<std::string> split(std::string str, std::string token){
        std::vector<std::string>result;
        while(str.size()){
            int index = str.find(token);
            if(index!=std::string::npos){
                result.push_back(str.substr(0,index));
                str = str.substr(index+token.size());
                if(str.size()==0)result.push_back(str);
            }else{
                result.push_back(str);
                str = "";
            }
        }
        return result;
    }

    bool endsWith(const std::string &mainStr, const std::string &toMatch) {
        if(mainStr.size() >= toMatch.size() &&
            mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
            return true;
        else
            return false;
    }

}
