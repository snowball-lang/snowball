
#include "api.h"
#include <string>

#ifndef __SNOWBALL_LIBS_H_
#define __SNOWBALL_LIBS_H_

namespace snowball {
    typedef void (*sn_module_export_ty)(SNAPI*);

    bool is_snowball_lib(std::string name);
    sn_module_export_ty get_sn_export_lib(std::string name);
}

#endif // __SNOWBALL_LIBS_H_
