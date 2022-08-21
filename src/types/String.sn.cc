
#include "snowball/export.hpp"
#include "snowball/types/String.h"
#include "snowball/api.h"
#include "snowball/types.h"

#include <vector>
#include <utility>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "snowball/constants.h"

extern "C" int sn_String____eqeq(String* self, String* second) {
    return strcmp(self->__buffer, second->__buffer) == 0;
}

extern "C" int sn_String____bool(String* self) {
    return self->__length != 0;
}

extern "C" String* sn_String____init(char* __str) {
    String* instance = (struct String*)(malloc(sizeof(String*) + (sizeof(__str) + 1)));

    instance->__buffer = (char*)malloc(sizeof(__str) + 1);
    strcpy(instance->__buffer, __str);
    instance->__length = strlen(__str);

    return instance;
}

extern "C" String* sn_String____sum(String* self, String* sum) {

    char *result = (char*)malloc(self->__length + sum->__length + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, self->__buffer);
    strcat(result, sum->__buffer);

    return sn_String____init(result);
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
    }, [API](snowball::ScopeValue* cls) {
        llvm::Type* class_type = (*cls->llvm_struct)->getPointerTo();
        llvm::Type* bool_class = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::BOOL, API->get_compiler()->builder);

        API->create_class_method(
            cls,
            "__init",
            class_type,
            std::vector<std::pair<snowball::Type*, llvm::Type*>> {
                std::make_pair(
                    new snowball::Type("&s"),
                    snowball::get_llvm_type_from_sn_type(
                        snowball::BuildinTypes::STRING,
                        API->get_compiler()->builder
                    )
                )
            }
        );

        API->create_class_method(
            cls,
            "__sum",
            class_type,
            std::vector<std::pair<snowball::Type*, llvm::Type*>> {
                std::make_pair(snowball::STRING_TYPE, class_type),
                std::make_pair(snowball::STRING_TYPE, class_type)
            }
        );

        API->create_class_method(
            cls,
            "__bool",
            bool_class,
            std::vector<std::pair<snowball::Type*, llvm::Type*>> {
                std::make_pair(snowball::STRING_TYPE, class_type),
            }
        );

        API->create_class_method(
            cls,
            "__eqeq",
            bool_class,
            std::vector<std::pair<snowball::Type*, llvm::Type*>> {
                std::make_pair(snowball::STRING_TYPE, class_type),
                std::make_pair(snowball::STRING_TYPE, class_type)
            }
        );
    });
}
