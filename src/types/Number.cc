
#include "snowball/export.hpp"
#include "snowball/api.h"
#include "snowball/types/Number.h"

#include <vector>
#include <utility>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "snowball/constants.h"

void register_number(snowball::SNAPI* API) {
    snowball::ScopeValue* number_class = API->create_class("Number", std::map<std::string, llvm::Type*> {
        {
            "number",
            snowball::get_llvm_type_from_sn_type(
                snowball::BuildinTypes::NUMBER,
                API->get_compiler()->get_builder()
            ),
        },
    });

    llvm::Type* class_type = (*number_class->llvm_struct)->getPointerTo();

    API->create_class_method(
        number_class,
        "__init",
        class_type,
        std::vector<std::pair<std::string, llvm::Type*>> {
            std::make_pair(
                "i",
                snowball::get_llvm_type_from_sn_type(
                    snowball::BuildinTypes::NUMBER,
                    API->get_compiler()->get_builder()
                )
            )
        },
        true
    );

    API->create_class_method(
        number_class,
        "__sum",
        class_type,
        std::vector<std::pair<std::string, llvm::Type*>> {
            std::make_pair("Number", class_type),
            std::make_pair("Number", class_type)
        },
        true
    );

    API->add_to_enviroment("Number", std::make_unique<snowball::ScopeValue*>(number_class));
}


extern "C" DLLEXPORT Number* _MN6NumberN6__initA1iP(snowball_int_t n){
    Number* instance;
    instance = (struct Number*)(malloc(sizeof(Number)));

    instance->number = n;

    return instance;
}

extern "C" DLLEXPORT Number* _MN6NumberN5__sumA6NumberA6NumberP(Number* number, Number* sum) {
    return _MN6NumberN6__initA1iP(number->number + sum->number);
}
