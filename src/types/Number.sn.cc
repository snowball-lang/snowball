
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

extern "C" snowball_int_t __sn_number__init(snowball_int_t num) { return num; }
extern "C" int __sn_number__bool(snowball_int_t self)           { return self == 1; }

extern "C" String* __sn_number__str (snowball_int_t self) {
    return __sn_string__init(std::to_string(self).data());
}

void register_number(snowball::SNAPI* API) {

    API->create_class("Number", std::map<std::string, llvm::Type*> {}, [API](snowball::ScopeValue* cls) {
        llvm::Type* class_type = snowball::TypeChecker::type2llvm(API->get_compiler()->builder, (*cls->llvm_struct)->getPointerTo());
        llvm::Type* bool_class = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::BOOL, API->get_compiler()->builder);
        llvm::Type* string_class = (*API->get_compiler()->get_enviroment()->get(snowball::STRING_TYPE->mangle(), nullptr)->llvm_struct)->getPointerTo();

        API->create_class_method( // new Number(2)
            cls,
            "__init",
            class_type,
            std::vector<std::pair<snowball::Type*, llvm::Type*>> {
                std::make_pair(snowball::NUMBER_TYPE, class_type)
            },
            true,
            "__sn_number__init"
        );

        API->create_class_method( // new Number(2)
            cls,
            "__bool",
            bool_class,
            std::vector<std::pair<snowball::Type*, llvm::Type*>> {
                std::make_pair(snowball::NUMBER_TYPE, class_type)
            },
            true,
            "__sn_number__bool"
        );

        API->create_class_method(
            cls,
            "__str",
            string_class,
            std::vector<std::pair<snowball::Type*, llvm::Type*>> {
                std::make_pair(snowball::NUMBER_TYPE, class_type)
            },
            true,
            "__sn_number__str"
        );
    });
}