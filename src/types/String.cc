
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

void register_string(snowball::SNAPI* API) {
    snowball::ScopeValue* string_class = API->create_class("String", std::map<std::string, llvm::Type*> {
        {
            "buffer",
            snowball::get_llvm_type_from_sn_type(
                snowball::BuildinTypes::STRING,
                API->get_compiler()->get_builder()
            ),
        },
        {
            "length",
            snowball::get_llvm_type_from_sn_type(
                snowball::BuildinTypes::NUMBER,
                API->get_compiler()->get_builder()
            ),
        }
    });

    llvm::Type* class_type = (*string_class->llvm_struct)->getPointerTo();

    API->create_class_method(
        string_class,
        "__init",
        class_type,
        std::vector<std::pair<std::string, llvm::Type*>> {
            std::make_pair(
                "s",
                snowball::get_llvm_type_from_sn_type(
                    snowball::BuildinTypes::STRING,
                    API->get_compiler()->get_builder()
                )
            )
        }
    );

    API->create_class_method(
        string_class,
        "__sum",
        class_type,
        std::vector<std::pair<std::string, llvm::Type*>> {
            std::make_pair("String", class_type),
            std::make_pair("String", class_type)
        }
    );

    API->add_to_enviroment("String", std::make_unique<snowball::ScopeValue*>(string_class));
}

extern "C" DLLEXPORT String* String__init_s(const char* string_ptr) {
    String* instance;
    instance = (struct String*)(malloc(sizeof(String*) + (sizeof(string_ptr) + 1)));

    instance->buffer = string_ptr;
    instance->length = strlen(string_ptr);

    return instance;
}

extern "C" DLLEXPORT String* String__sum_String(String* self, String* sum) {

    char *result = (char*)malloc(self->length + sum->length + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, self->buffer);
    strcat(result, sum->buffer);

    return String__init_s(result);
}
