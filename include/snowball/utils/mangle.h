#include <vector>
#include <string>

#include "../types.h"
#include "../operators.h"
#include "../nodes.h"

#ifndef __SNOWBALL_UTILS__MANGLE_H_
#define __SNOWBALL_UTILS__MANGLE_H_

namespace snowball {

    struct unmangledResult {
        bool isMangled = false;
        bool isPublic = false;

        bool isFunction = true;

        std::string name;
        std::vector<Type*> arguments;
        std::string return_type;
    };


    unmangledResult unmangle(std::string name, std::string separator = ".", bool for_output = false);
    std::string op2str(OperatorType op);
    std::string mangle(std::string name, std::vector<Type*> arguments = {}, bool is_public = false, bool is_class = false);
}

#endif // __SNOWBALL_UTILS__MANGLE_H_