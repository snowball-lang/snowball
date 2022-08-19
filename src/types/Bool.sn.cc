#include "snowball/api.h"
#include "snowball/types.h"
#include "snowball/scopes.h"
#include "snowball/snowball.h"
#include "snowball/types/Bool.h"
#include "snowball/types/String.h"
#include "snowball/types.h"

#include "snowball/export.hpp"

#include <vector>
#include <utility>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "snowball/constants.h"

extern "C" String* __sn_bool__str(int self) {
    return __sn_string__init(self ? (char*)"true" : (char*)"false");
}

void register_bool(snowball::SNAPI* API) {

    API->create_class("Bool", std::map<std::string, llvm::Type*> {}, [API](snowball::ScopeValue* cls) {

        llvm::Type* string_class = (*API->get_compiler()->get_enviroment()->get(snowball::STRING_TYPE->mangle(), nullptr)->llvm_struct)->getPointerTo();
        llvm::Type* number_class = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::NUMBER, API->get_compiler()->builder);
        llvm::Type* class_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::BOOL, API->get_compiler()->builder);

        API->create_class_method(
            cls,
            "__str",
            string_class,
            std::vector<std::pair<snowball::Type*, llvm::Type*>> {
                std::make_pair(snowball::BOOL_TYPE, class_type)
            },
            true,
            "__sn_bool__str"
        );
    });
}