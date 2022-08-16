
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

snowball_int_t Number::__init(snowball_int_t num) {
    return num;
}

String* Number::__str(snowball_int_t self) {
    std::ostringstream s;
    s << (int)self;

    return String::__init(s.str().c_str());
}

Bool* Number::__eqeq(snowball_int_t self, snowball_int_t comp) {
    return Bool::__init(self == comp);
}

Bool* Number::__bool(snowball_int_t self) {
    return Bool::__init(self);
}

Bool* Number::__not(snowball_int_t self) {
    return Bool::__init(!(self != 0));
}

Bool* Number::__lteq(snowball_int_t self, snowball_int_t comp) {
    return Bool::__init(self <= comp);
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
        llvm::Type* class_type = snowball::TypeChecker::type2llvm(API->get_compiler()->builder, (*cls->llvm_struct)->getPointerTo());
        llvm::Type* bool_class = (*API->get_compiler()->get_enviroment()->get(snowball::BOOL_TYPE->mangle(), nullptr)->llvm_struct)->getPointerTo();
        llvm::Type* string_class = (*API->get_compiler()->get_enviroment()->get(snowball::STRING_TYPE->mangle(), nullptr)->llvm_struct)->getPointerTo();

        API->create_class_method(
            cls,
            "__init",
            class_type,
            std::vector<std::pair<snowball::Type*, llvm::Type*>> {
                std::make_pair(
                    new snowball::Type("&i"),
                    snowball::get_llvm_type_from_sn_type(
                        snowball::BuildinTypes::NUMBER,
                        API->get_compiler()->builder
                    )
                )
            },
            true,
            (void*)static_cast<snowball_int_t(*)(snowball_int_t)>(Number::__init)
        );

        API->create_class_method( // new Number(2)
            cls,
            "__init",
            class_type,
            std::vector<std::pair<snowball::Type*, llvm::Type*>> {
                std::make_pair(snowball::NUMBER_TYPE, class_type)
            },
            true,
            (void*)static_cast<snowball_int_t(*)(snowball_int_t)>(Number::__init)
        );

        API->create_class_method(
            cls,
            "__not",
            bool_class,
            std::vector<std::pair<snowball::Type*, llvm::Type*>> {
                std::make_pair(snowball::NUMBER_TYPE, class_type)
            },
            true,
            (void*)static_cast<Bool*(*)(snowball_int_t)>(Number::__not)
        );

        API->create_class_method(
            cls,
            "__str",
            string_class,
            std::vector<std::pair<snowball::Type*, llvm::Type*>> {
                std::make_pair(snowball::NUMBER_TYPE, class_type)
            },
            true,
            (void*)static_cast<String*(*)(snowball_int_t)>(Number::__str)
        );

        API->create_class_method(
            cls,
            "__bool",
            bool_class,
            std::vector<std::pair<snowball::Type*, llvm::Type*>> {
                std::make_pair(snowball::NUMBER_TYPE, class_type)
            },
            true,
            (void*)static_cast<Bool*(*)(snowball_int_t)>(Number::__bool)
        );

        API->create_class_method(
            cls,
            "__eqeq",
            bool_class,
            std::vector<std::pair<snowball::Type*, llvm::Type*>> {
                std::make_pair(snowball::NUMBER_TYPE, class_type),
                std::make_pair(snowball::NUMBER_TYPE, class_type)
            },
            true,
            (void*)static_cast<Bool*(*)(snowball_int_t, snowball_int_t)>(Number::__eqeq)
        );

        API->create_class_method(
            cls,
            "__lteq",
            bool_class,
            std::vector<std::pair<snowball::Type*, llvm::Type*>> {
                std::make_pair(snowball::NUMBER_TYPE, class_type),
                std::make_pair(snowball::NUMBER_TYPE, class_type)
            },
            true,
            (void*)static_cast<Bool*(*)(snowball_int_t, snowball_int_t)>(Number::__lteq)
        );
    });
}