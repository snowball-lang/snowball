#include <vector>
#include <string>

#ifndef __SNOWBALL_UTILS__MANGLE_H_
#define __SNOWBALL_UTILS__MANGLE_H_

namespace snowball {

    struct unmangledResult {
        bool isMangled = false;

        std::string name;
        std::vector<std::string> arguments;
        std::string return_type;
    };

    unmangledResult unmangle(std::string name);
    std::string mangle(std::string name, std::vector<std::string> arguments = {}, std::string return_type = "void");
}

#endif // __SNOWBALL_UTILS__MANGLE_H_
