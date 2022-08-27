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
#include "snowball/utils/api.h"

extern "C" char* sn_Bool__str(int self) {
    return self ? (char*)"true" : (char*)"false";
}

void register_bool(snowball::SNAPI* API) {

    API->create_class("Bool", std::map<std::string, llvm::Type*> {}, [API](snowball::ScopeValue* CLASS) {

        llvm::Type* string_class = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::STRING, API->get_compiler()->builder);
        llvm::Type* class_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::BOOL, API->get_compiler()->builder);

        METHOD("__str", string_class, { METHOD_ARGUMENT(snowball::BOOL_TYPE, class_type) }, "sn_Bool__str")
    });
}