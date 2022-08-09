#include "snowball/api.h"
#include "snowball/types.h"
#include "snowball/scopes.h"
#include "snowball/snowball.h"
#include "snowball/types/Bool.h"

#include "snowball/export.hpp"

#include <vector>
#include <utility>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "snowball/constants.h"

Bool* Bool::__init(Number* value) {
    return Bool::__init(value->__number != 0);
}

Bool* Bool::__init(bool value) {
    Bool* instance = (Bool*)(malloc(sizeof(Bool)));

    instance->__bool = value;

    return instance;
}

snowball_int_t Bool::__real_bool(Bool* self) {
    return self->__bool;
}

String* Bool::__str(Bool* self) {
    return String::__init(self->__bool ? "true" : "false");
}

Bool* Bool::__eqeq(Bool* self, Bool* second) {
    return Bool::__init(self->__bool == second->__bool);
}

Bool* Bool::__not(Bool* self) {
    return Bool::__init(!self->__bool);
}

void register_bool(snowball::SNAPI* API) {

    API->create_class("Bool", std::map<std::string, llvm::Type*> {
        {
            "__bool",
            snowball::get_llvm_type_from_sn_type(
                snowball::BuildinTypes::NUMBER,
                API->get_compiler()->builder
            ),
        },
    }, [&](snowball::ScopeValue* cls) {

        llvm::Type* string_class = (*API->get_compiler()->get_enviroment()->get("String", nullptr)->llvm_struct)->getPointerTo();
        llvm::Type* number_class = (*API->get_compiler()->get_enviroment()->get("Number", nullptr)->llvm_struct)->getPointerTo();

        llvm::Type* class_type = (*cls->llvm_struct)->getPointerTo();

        API->create_class_method(
            cls,
            "__init",
            class_type,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair("Number", number_class)
            },
            true,
            (void*)static_cast<Bool*(*)(Number*)>(Bool::__init)
        );

        API->create_class_method(
            cls,
            "__real_bool",
            snowball::get_llvm_type_from_sn_type(
                snowball::BuildinTypes::NUMBER,
                API->get_compiler()->builder
            ),
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair("Bool", class_type)
            },
            false,
            (void*)static_cast<snowball_int_t(*)(Bool*)>(Bool::__real_bool)
        );

        API->create_class_method(
            cls,
            "__str",
            string_class,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair("Bool", class_type)
            },
            true,
            (void*)static_cast<String*(*)(Bool*)>(Bool::__str)
        );

        API->create_class_method(
            cls,
            "__not",
            class_type,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair("Bool", class_type)
            },
            true,
            (void*)static_cast<Bool*(*)(Bool*)>(Bool::__not)
        );

        API->create_class_method(
            cls,
            "__eqeq",
            class_type,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair("Bool", class_type),
                std::make_pair("Bool", class_type)
            },
            true,
            (void*)static_cast<Bool*(*)(Bool*, Bool*)>(Bool::__eqeq)
        );

    });
}