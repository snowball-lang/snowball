
#include "../include/snowball/api.h"
#include "../include/snowball/types.h"
#include "../include/snowball/snowball.h"
#include "../include/snowball/constants.h"

#include "../include/snowball/utils/api.h"

#include <string>
#include <vector>
#include <utility>
#include <iostream>

extern "C" void sn_System__println(String* __msg) {
    printf("%s\n", __msg->__buffer);
}

extern "C" void sn_System__print(String* __msg) {
    printf("%s", __msg->__buffer);
}

extern "C" String* sn_System__input(String* __msg) {
    std::string line;
    std::cin >> line;

    return sn_String____init((char*)line.c_str());
}

using namespace snowball;
extern "C" ScopeValue* sn_export(SNAPI* API) {
    llvm::Type* string_class = (*API->get_compiler()->get_enviroment()->get(STRING_TYPE->mangle(), nullptr)->llvm_struct)->getPointerTo();

    return API->create_module("System", {}, [&](ScopeValue* CLASS) {
        METHOD("input",   string_class, {})
        METHOD("print",   string_class, { METHOD_ARGUMENT(STRING_TYPE, string_class) })
        METHOD("println", string_class, { METHOD_ARGUMENT(STRING_TYPE, string_class) })
    });
}
