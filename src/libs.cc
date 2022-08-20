
#include "snowball/libs.h"
#include <string>
#include <dlfcn.h>

#include <filesystem>
namespace fs = std::filesystem;

namespace snowball {

    bool is_snowball_lib(std::string name) {
        return ((name == "System") || (name == "Math") || (name == "Os") || (name == "Path"));
    }

    sn_module_export_ty get_sn_export_lib(std::string name) {
        fs::path path = snowball_utils::get_lib_folder();
        std::string full_path = path / name;

        void* lib = dlopen(full_path.c_str(), RTLD_LAZY | RTLD_DEEPBIND);
        if (!lib) {
            throw SNError(Error::IO_ERROR, Logger::format("The standard library '%s' has not been found! Have you installed snowball correctly?", name.c_str()));
        }

        sn_module_export_ty export_function = reinterpret_cast<sn_module_export_ty>(dlsym(lib, "sn_export"));
        dlclose(lib);

        return export_function;
    }
}
