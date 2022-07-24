
#include "snowball/api.h"
#include "snowball/types.h"
#include "snowball/scopes.h"
#include "snowball/snowball.h"
#include "snowball/types/Number.h"

#include "snowball/export.hpp"

#include <vector>
#include <utility>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "snowball/constants.h"

extern "C" struct Number {
  snowball_int_t number;

    // to reference it: static_cast<Number*(*)(snowball_int_t)>(Number::__init);
    static Number* __init(snowball_int_t num) {
        Number* instance;
        instance = (struct Number*)(malloc(sizeof(Number)));

        instance->number = num;

        return instance;
    }
};

extern "C" DLLEXPORT Number* _MN6NumberN6__initA1iP(snowball_int_t n) {
    Number* instance;
    instance = (struct Number*)(malloc(sizeof(Number)));

    instance->number = n;

    return instance;
}

extern "C" DLLEXPORT Number* _MN6NumberN5__sumA6NumberA6NumberP(Number* number, Number* sum) {
    return _MN6NumberN6__initA1iP(number->number + sum->number);
}


void register_number(snowball::SNAPI* API) {
    API->create_class("Number", std::map<std::string, llvm::Type*> {
        {
            "number",
            snowball::get_llvm_type_from_sn_type(
                snowball::BuildinTypes::NUMBER,
                API->get_compiler()->builder
            ),
        },
    }, [&](snowball::ScopeValue* cls) {
        llvm::Type* class_type = (*cls->llvm_struct)->getPointerTo();

        API->create_class_method(
            cls,
            "__init",
            class_type,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair(
                    "i",
                    snowball::get_llvm_type_from_sn_type(
                        snowball::BuildinTypes::NUMBER,
                        API->get_compiler()->builder
                    )
                )
            },
            true,
            nullptr
        );

        API->create_class_method(
            cls,
            "__sum",
            class_type,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair("Number", class_type),
                std::make_pair("Number", class_type)
            },
            true,
            nullptr
        );
    });
}