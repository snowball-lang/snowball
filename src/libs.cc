
#include "snowball/libs.h"
#include <llvm/Support/DynamicLibrary.h>
#include <string>
#include <dlfcn.h>
#include <unistd.h>

#include <filesystem>
namespace fs = std::filesystem;

namespace snowball {

    bool Library::is_snowball_lib(std::string name) {
        return ((name == "System") || (name == "Math") || (name == "Os") || (name == "Path"));
    }

    bool Library::snlib_is_object(std::string name) {
        return ((name == "Os"));
    }

    std::string Library::get_sn_lib_src(std::string name) {
        fs::path path = snowball_utils::get_lib_folder();
        return ((std::string)(path / name)) + ".sn";
    }

    std::pair<sn_module_export_ty, std::string> Library::get_sn_export_lib(std::string name) {
        fs::path path = snowball_utils::get_lib_folder();
        std::string full_path = path / Logger::format("lib%s.so", name.c_str());

        void* lib = dlopen(full_path.c_str(), RTLD_LAZY);
        if (!lib) {
            throw SNError(Error::IO_ERROR, Logger::format("The standard library '%s' has not been found! Have you installed snowball correctly?\n%s path%s: %s", name.c_str(), BRED, RESET, full_path.c_str()));
        }

        sn_module_export_ty export_function = reinterpret_cast<sn_module_export_ty>(dlsym(lib, "sn_export"));
        if (!export_function) {
            throw SNError(Error::COMPILER_ERROR, Logger::format("The standard library '%s' had an error: %s", name.c_str(), dlerror()));
        }

        llvm::sys::DynamicLibrary::LoadLibraryPermanently(full_path.c_str());
        // dlclose(lib);

        return {export_function, full_path};
    }

    std::string Library::find_lib_by_path(std::string initial_path) {
        #define RETURN_IF_EXISTS(path) \
            if ( access( (path).c_str(), F_OK ) != -1 ) { \
                return path; \
            }

        RETURN_IF_EXISTS(initial_path)
        RETURN_IF_EXISTS(initial_path + ".sn")

        return "";

        #undef RETURN_IF_EXISTS
    }

    std::string Library::get_module_name(std::string path){
        std::vector<std::string> split_path;
        std::string character;
        std::string temp;
        uint64_t index = 0;
        while (index < path.length()) {
            character = path.at(index);
            if (character == "/" || character == "\\") {
                split_path.push_back(temp);
                temp = "";
            } else {
                temp += character;
            }
            index++;
        }
        if (temp != "") {
            split_path.push_back(temp);
        }
        return split_path.back();
    }
}
