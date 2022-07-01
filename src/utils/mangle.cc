
#include "include/snowball/snowball.h"
#include "include/snowball/utils/mangle.h"

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
    *  4. The return type will start with the
    *     prefix `R` and then the length of the
    *     return type followed by the type name.
    *       "R{LENGTH OF RETURN T}{TYPE OF RETURN T}"
    *=======================================*/
    std::string mangle(std::string name, std::vector<std::string> arguments, std::string return_type) {
        std::stringstream mangled_name;
        mangled_name << "_M"; // step #1

        // Step #2
        mangled_name << "N";
        mangled_name << name.size();
        mangled_name << name;

        // Step #3
        for(std::string argument : arguments) {
            mangled_name << "A";
            mangled_name << argument.size();
            mangled_name << argument;
        }

        // Step #4
        mangled_name << "R";
        mangled_name << return_type.size();
        mangled_name << return_type;

        return mangled_name.str();
    }

    unmangledResult unmangle(std::string name) {
        unmangledResult result;
        result.name = name;

        if (!(name.size() > 4)) return result;

        for (int index = 0; index < name.length(); index++) {
            if (index == 0) {
                if (name.substr(0, 2) != "_M") {
                    return result;
                }

                result.isMangled = true;
                index += 2;
            }

            const char* c_str = name.c_str();
            if (c_str[index] == 'N') {
                std::stringstream _length;
                _length << ((c_str[index + 1]) - '0');
                index += 2;

                while (c_str[index] >= '0' && c_str[index] <= '9') {
                    _length << ((c_str[index]) - '0');
                    index++;
                }

                int length = std::stoi(_length.str().c_str());
                result.name = name.substr(index, length);
            }

            while (c_str[index] == 'A') {
                std::stringstream _length;
                _length << ((c_str[index + 1]) - '0');
                index += 2;

                while (c_str[index] >= '0' && c_str[index] <= '9') {
                    _length << ((c_str[index]) - '0');
                    index++;
                }

                int length = std::stoi(_length.str().c_str());
                result.arguments.push_back(name.substr(index, length));
            }

            if (c_str[index] == 'R') {
                std::stringstream _length;
                _length << ((c_str[index + 1]) - '0');
                index += 2;

                while (c_str[index] >= '0' && c_str[index] <= '9') {
                    _length << ((c_str[index]) - '0');
                    index++;
                }

                int length = std::stoi(_length.str().c_str());
                result.return_type = name.substr(index, length);
            }
        }

        return result;
    }
}
