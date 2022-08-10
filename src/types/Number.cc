
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

Number* Number::__init(snowball_int_t num) {
    Number* instance;
    instance = (Number*)(malloc(sizeof(Number)));
    instance->__number = num;

    return instance;
}

Number* Number::__init(Number* num) {
    return Number::__init(num->__number);
}

Number* Number::__sum(Number* self, Number* num) {
    return __init(self->__number + num->__number);
}

String* Number::__str(Number* self) {
    std::ostringstream s;
    s << (int)self->__number;

    return String::__init(s.str().c_str());
}

Bool* Number::__eqeq(Number* self, Number* comp) {
    return Bool::__init(self->__number == comp->__number);
}

Bool* Number::__bool(Number* self) {
    return Bool::__init(self);
}

Bool* Number::__not(Number* self) {
    return Bool::__init(!(self->__number != 0));
}

void register_number(snowball::SNAPI* API) {

    API->create_class("Number", std::map<std::string, llvm::Type*> {
        {
            "__number",
            snowball::get_llvm_type_from_sn_type(
                snowball::BuildinTypes::NUMBER,
                API->get_compiler()->builder
            ),
        },
    }, [API](snowball::ScopeValue* cls) {
        llvm::Type* class_type = (*cls->llvm_struct)->getPointerTo();
        llvm::Type* bool_class = (*API->get_compiler()->get_enviroment()->get("Bool", nullptr)->llvm_struct)->getPointerTo();
        llvm::Type* string_class = (*API->get_compiler()->get_enviroment()->get("String", nullptr)->llvm_struct)->getPointerTo();

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
            (void*)static_cast<Number*(*)(snowball_int_t)>(Number::__init)
        );

        API->create_class_method( // new Number(2)
            cls,
            "__init",
            class_type,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair("Number", class_type)
            },
            true,
            (void*)static_cast<Number*(*)(Number*)>(Number::__init)
        );

        API->create_class_method(
            cls,
            "__not",
            bool_class,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair("Number", class_type)
            },
            true,
            (void*)static_cast<Bool*(*)(Number*)>(Number::__not)
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
            (void*)static_cast<Number*(*)(Number*, Number*)>(Number::__sum)
        );

        API->create_class_method(
            cls,
            "__str",
            string_class,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair("Number", class_type)
            },
            true,
            (void*)static_cast<String*(*)(Number*)>(Number::__str)
        );

        API->create_class_method(
            cls,
            "__bool",
            bool_class,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair("Number", class_type)
            },
            true,
            (void*)static_cast<Bool*(*)(Number*)>(Number::__bool)
        );

        API->create_class_method(
            cls,
            "__eqeq",
            bool_class,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair("Number", class_type),
                std::make_pair("Number", class_type)
            },
            true,
            (void*)static_cast<Bool*(*)(Number*, Number*)>(Number::__eqeq)
        );
    });
}