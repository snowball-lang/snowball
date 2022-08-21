
#include "../include/snowball/api.h"
#include "../include/snowball/types.h"
#include "../include/snowball/snowball.h"
#include "../include/snowball/constants.h"
#include "../include/snowball/types/String.h"

#include <string>
#include <vector>
#include <utility>
#include <iostream>

extern "C" void sn_System__println(String* __msg) {
    printf("%s\n", __msg->__buffer);
}

extern "C" void sn_System__print(String* __msg) {
    printf("%s\n", __msg->__buffer);
}

extern "C" String* sn_System__input(String* __msg) {
    std::string line;
    std::getline(std::cin, line);

    return sn_String____init((char*)line.c_str());
}

using namespace snowball;
extern "C" ScopeValue* sn_export(SNAPI* API) {
    llvm::Type* string_class = (*API->get_compiler()->get_enviroment()->get(STRING_TYPE->mangle(), nullptr)->llvm_struct)->getPointerTo();

    return API->create_module("System", {}, [&](ScopeValue* system_module) {

        API->create_class_method(
            system_module,
            "print",
            API->get_compiler()->builder.getVoidTy(),
            std::vector<std::pair<Type*, llvm::Type*>> {
                std::make_pair(STRING_TYPE, string_class)
            }
        );

        API->create_class_method(
            system_module,
            "println",
            API->get_compiler()->builder.getVoidTy(),
            std::vector<std::pair<Type*, llvm::Type*>> {
                std::make_pair(STRING_TYPE, string_class)
            }
        );

        API->create_class_method(
            system_module,
            "input",
            string_class,
            {}
        );
    });
}
