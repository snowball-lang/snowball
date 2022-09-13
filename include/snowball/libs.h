
#include "api.h"
#include <string>

#ifndef __SNOWBALL_LIBS_H_
#define __SNOWBALL_LIBS_H_

namespace snowball {
    typedef ScopeValue* (*sn_module_export_ty)(SNAPI*);


    class Library {
        public:
        static bool is_snowball_lib(std::string name);
        static bool snlib_is_object(std::string name);
        static std::string get_sn_lib_src(std::string name);
        static std::pair<sn_module_export_ty, std::string> get_sn_export_lib(std::string name);

        static std::string find_lib_by_path(std::string initial_path);
        static std::string get_module_name(std::string path);
    };
}

#endif // __SNOWBALL_LIBS_H_
