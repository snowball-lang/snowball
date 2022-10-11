
#include "snowball/export.hpp"
#include "snowball/types/String.h"
#include "snowball/api.h"
#include "snowball/types.h"

#include <vector>
#include <utility>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "snowball/constants.h"
#include "snowball/utils/api.h"

int String::_eqeq(char* self, char* second) {
    return strcmp(self, second) == 0;
}

int String::_bool(char* self) {
    return strlen(self) > 0;
}

char* String::_sum(char* self, char* sum) {

    char *result = (char*)malloc(strlen(self) + strlen(sum) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, self);
    strcat(result, sum);

    return result;
}

void register_string(snowball::SNAPI* API) {
    API->create_class("String", std::map<std::string, llvm::Type*> {}, [API](snowball::ScopeValue* CLASS) {
        llvm::Type* class_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::STRING, API->compiler->builder);
        llvm::Type* bool_class = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::BOOL, API->compiler->builder);

        OEPRATOR(snowball::OperatorType::BOOL, bool_class, {METHOD_ARGUMENT(snowball::STRING_TYPE, class_type)}, "_ZN6String5_boolEPc")
        OEPRATOR(snowball::OperatorType::PLUS,  class_type, {
            METHOD_ARGUMENT(snowball::STRING_TYPE, class_type),
            METHOD_ARGUMENT(snowball::STRING_TYPE, class_type)
        }, "_ZN6String4_sumEPcS0_")

        OEPRATOR(snowball::OperatorType::EQEQ,  bool_class, {
            METHOD_ARGUMENT(snowball::STRING_TYPE, class_type),
            METHOD_ARGUMENT(snowball::STRING_TYPE, class_type)
        }, "_ZN6String5_eqeqEPcS0_")
    });
}
