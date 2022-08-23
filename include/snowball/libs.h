
#include "api.h"
#include <string>

#ifndef __SNOWBALL_LIBS_H_
#define __SNOWBALL_LIBS_H_

namespace snowball {
    typedef ScopeValue* (*sn_module_export_ty)(SNAPI*);

    bool is_snowball_lib(std::string name);
    std::pair<sn_module_export_ty, std::string> get_sn_export_lib(std::string name);
}

#endif // __SNOWBALL_LIBS_H_
