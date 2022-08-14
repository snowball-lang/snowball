#include "snowball/snowball.h"
#include "snowball/utils/utils.h"
#include "snowball/utils/mangle.h"

#include "snowball/types.h"

#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

namespace snowball {

    /*=======================================
    * Mangling in snowball.
    * ---------------------------
    * rules:
    *  1. if the name is being mangled, the
    *     function's name must be prefixed with
    *     `_M`.
    *  2. After the rule number 1, the function
    *     name must contain the following:
    *       "N{LENGTH OF VARIABLE NAME}{NAME}"
    *     we must declare the length for the
    *     variable to avoid any confusion.
    *  3. After the variable name, we need to
    *     set the arguments. By following this
    *     template:
    *       "A{LENGTH OF ARGUMENT}{TYPE OF ARGUMENt}"
    *     the template can be repeated as much
    *     times as the function has arguments.
    *     This is used so that the generator can
    *     identify witch parameters this function
    *     is uses.
    *=======================================*/
    std::string mangle(std::string name, std::vector<Type*> arguments, bool is_public, bool is_class) {

        if (is_class) {
            return TypeChecker::to_mangle(new Type(name, arguments));
        }

        std::stringstream mangled_name;
        mangled_name << "_M"; // step #1

        // Step #2
        for (std::string n : snowball_utils::split(name, ".")) {
            mangled_name << "$";
            mangled_name << n.size();
            mangled_name << n;
        }

        // Step #3
        for(Type* argument : arguments) {
            std::string mangled = TypeChecker::to_mangle(argument);
            mangled_name << mangled;
        }

        if (is_public) {
            mangled_name << "P";
        } else {
            mangled_name << "I";
        }

        return mangled_name.str();
    }

    unmangledResult unmangle(std::string name) {
        unmangledResult result;
        // result.name = name;

        if (!(name.size() > 4)) return result;

        for (int index = 0; index < name.length();) {
            if (index == 0) {
                if (name.substr(0, 2) != "_M") {
                    return result;
                }

                result.isMangled = true;
                index += 2;
            }

            const char* c_str = name.c_str();

            if (c_str[index] == 'C') {
                index++;
                result.isFunction = false;
            }

            if (c_str[index] == '$') {
                std::stringstream _length;
                _length << c_str[index + 1];
                index += 2;

                while (c_str[index] >= '0' && c_str[index] <= '9') {
                    _length << c_str[index];
                    index++;
                }

                int length = std::stoi(_length.str());

                std::string extracted = name.substr(index, length);
                index += length;

                if (result.name == "") {
                    result.name = extracted;
                    continue;
                }

                result.name += "." + extracted;
            }

            if (c_str[index] == 'P' || c_str[index] == 'I') {
                result.isPublic = c_str[index] == 'P';
                index++;
            }

            while (c_str[index] == '@') {
                std::string tname = name.substr(index);
                tname.pop_back();

                auto [type, len] = TypeChecker::to_type(tname);
                index += (len);

                result.arguments.push_back(type);
            }
        }

        return result;
    }
}