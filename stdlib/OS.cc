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
#include <typeinfo>

#include "snowball/constants.h"
#include "snowball/utils/api.h"

#include "OS.h"

// == Exports

char* OS::name() {
    return "TODO";
}


// == Definitions
extern "C" snowball::ScopeValue* sn_export(snowball::SNAPI* API) {

    return API->create_module("OS", std::map<std::string, llvm::Type*> {}, [API](snowball::ScopeValue* CLASS) {

        llvm::Type* void_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::VOID, API->compiler->builder);
        llvm::Type* float_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::FLOAT, API->compiler->builder);
        llvm::Type* bool_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::BOOL, API->compiler->builder);
        llvm::Type* string_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::STRING, API->compiler->builder);
        llvm::Type* double_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::DOUBLE, API->compiler->builder);
        llvm::Type* int16_type = API->compiler->builder->getInt16Ty();
        llvm::Type* int32_type = API->compiler->builder->getInt32Ty();
        llvm::Type* int64_type = API->compiler->builder->getInt64Ty();

        METHOD("name", string_type, {},  "_ZN2OS4nameEv")
    });
}