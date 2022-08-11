
#include "snowball/libs.h"
#include "snowball/utils/utils.h"
#include <string>


namespace snowball {

    bool is_snowball_lib(std::string name) {
        return ((name == "System") || (name == "Math") || (name == "Os") || (name == "Path"));
    }

    sn_module_export_ty get_sn_export_lib(std::string name) {

        std::string folder = snowball_utils::get_lib_folder();

        // if (name == "System") {
        //     return sn_system_export;
        // }

        // TODO: rest of the modules

        return nullptr;
    }
}
