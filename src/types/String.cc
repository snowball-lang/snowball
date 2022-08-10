
#include "snowball/export.hpp"
#include "snowball/types/String.h"
#include "snowball/api.h"

#include <vector>
#include <utility>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "snowball/constants.h"

String* String::__init(const char* __str) {
    String* instance;
    instance = (struct String*)(malloc(sizeof(String*) + (sizeof(__str) + 1)));

    instance->__buffer = __str;
    instance->__length = strlen(__str);

    return instance;
}

String* String::__sum(String* self, String* sum) {

    char *result = (char*)malloc(self->__length + sum->__length + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, self->__buffer);
    strcat(result, sum->__buffer);

    return __init(result);
}

Bool* String::__eqeq(String* self, String* second) {
    return Bool::__init(strcmp(self->__buffer, second->__buffer) == 0);
}

Bool* String::__bool(String* self) {
    return Bool::__init(self->__length != 0);
}

void register_string(snowball::SNAPI* API) {
    API->create_class("String", std::map<std::string, llvm::Type*> {
        {
            "__buffer",
            snowball::get_llvm_type_from_sn_type(
                snowball::BuildinTypes::STRING,
                API->get_compiler()->builder
            ),
        },
        {
            "__length",
            snowball::get_llvm_type_from_sn_type(
                snowball::BuildinTypes::NUMBER,
                API->get_compiler()->builder
            ),
        }
    }, [&](snowball::ScopeValue* cls) {
        llvm::Type* class_type = (*cls->llvm_struct)->getPointerTo();
        llvm::Type* bool_class = (*API->get_compiler()->get_enviroment()->get("Bool", nullptr)->llvm_struct)->getPointerTo();

        API->create_class_method(
            cls,
            "__init",
            class_type,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair(
                    "s",
                    snowball::get_llvm_type_from_sn_type(
                        snowball::BuildinTypes::STRING,
                        API->get_compiler()->builder
                    )
                )
            },
            true,
            (void*)static_cast<String*(*)(const char*)>(String::__init)
        );

        API->create_class_method(
            cls,
            "__bool",
            bool_class,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair("String", class_type)
            },
            true,
            (void*)static_cast<Bool*(*)(String*)>(String::__bool)
        );

        API->create_class_method(
            cls,
            "__sum",
            class_type,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair("String", class_type),
                std::make_pair("String", class_type)
            },
            true,
            (void*)static_cast<String*(*)(String*, String*)>(String::__sum)
        );

        API->create_class_method(
            cls,
            "__eqeq",
            bool_class,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair("String", class_type),
                std::make_pair("String", class_type)
            },
            true,
            (void*)static_cast<Bool*(*)(String*, String*)>(String::__eqeq)
        );
    });
}
