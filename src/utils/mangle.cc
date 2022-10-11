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



    std::string op2str(OperatorType op) {
        switch (op)
        {
            #define HANDLE(ty, str) case OperatorType::ty: { return str; };

            HANDLE(EQ, "Eq")
            HANDLE(EQEQ, "DbEq")
            HANDLE(PLUS, "Pl")
            HANDLE(PLUSEQ, "PlEq")
            HANDLE(MINUS, "Mn")
            HANDLE(MINUSEQ, "MnEq")
            HANDLE(MUL, "Ml")
            HANDLE(MULEQ, "MlEq")
            HANDLE(DIV, "Di")
            HANDLE(DIVEQ, "DiEq")
            HANDLE(MOD, "Md")
            HANDLE(MOD_EQ, "MdEq")
            HANDLE(LT, "Lt")
            HANDLE(LTEQ, "LtEq")
            HANDLE(GT, "Gt")
            HANDLE(GTEQ, "GtEq")
            HANDLE(AND, "An")
            HANDLE(OR, "O")
            HANDLE(NOT, "Nt")
            HANDLE(NOTEQ, "NtE")

            HANDLE(BIT_NOT, "BNt")
			HANDLE(BIT_LSHIFT, "BLsShft")
			HANDLE(BIT_LSHIFT_EQ, "BLsShftEq")
			HANDLE(BIT_RSHIFT, "BRshft")
			HANDLE(BIT_RSHIFT_EQ, "BRshftEq")
			HANDLE(BIT_OR, "BOr")
			HANDLE(BIT_OR_EQ, "BOrEq")
			HANDLE(BIT_AND, "BAnd")
			HANDLE(BIT_AND_EQ, "BAndEq")
			HANDLE(BIT_XOR, "BXor")
			HANDLE(BIT_XOR_EQ, "BXorEq")

			HANDLE(CONSTRUCTOR, "NwC")
			HANDLE(DESTRUCTOR, "Dle")
			HANDLE(CALL, "Cll")

			HANDLE(STRING, "StrC")
			HANDLE(BOOL, "BlC")

            #undef HANDLE

            default:
                throw SNError(BUG, Logger::format("Op type not handled: %i", op));
        }
    }

    std::string mangle(std::string name, std::vector<Type*> arguments, bool is_public, bool is_class) {

        if (is_class) {
            return TypeChecker::to_mangle(new Type(name, arguments));
        }

        std::stringstream mangled_name;
        mangled_name << "_S#"; // step #1

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

    unmangledResult unmangle(std::string name, std::string separator) {
        unmangledResult result;
        // result.name = name;

        if (!(name.size() > 4)) return result;

        for (int index = 0; index < name.length();) {
            if (index == 0) {
                if (name.substr(0, 3) != "_S#") {
                    return result;
                }

                result.isMangled = true;
                index += 3;
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

                result.name += separator + extracted;
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