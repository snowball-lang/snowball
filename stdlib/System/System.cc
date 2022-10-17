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

#include "../_include/System.h"

// == Exports

void System::println(char*   __msg) { printf("%s\n",  __msg); }
void System::println(bool    __msg) { printf("%i\n",  __msg); }
void System::println(int16_t __msg) { printf("%d\n",  __msg); }
void System::println(int32_t __msg) { printf("%d\n",  __msg); }
void System::println(int64_t __msg) { printf("%ld\n", __msg); }
void System::println(float   __msg) { printf("%f\n",  __msg); }
void System::println(double  __msg) { printf("%f\n",  __msg); }

void System::print(char*   __msg) { printf("%s",  __msg); }
void System::print(bool    __msg) { printf("%i",  __msg); }
void System::print(int16_t __msg) { printf("%d",  __msg); }
void System::print(int32_t __msg) { printf("%d",  __msg); }
void System::print(int64_t __msg) { printf("%ld", __msg); }
void System::print(float   __msg) { printf("%f",  __msg); }
void System::print(double  __msg) { printf("%f",  __msg); }

char* System::input() {
    int size = 10;
    char *str;
    int ch;
    size_t len = 0;
    str = (char*)realloc(NULL, sizeof(*str)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(stdin)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = (char*)realloc(str, sizeof(*str)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return (char*)realloc(str, sizeof(*str)*len);
}

// oh, no... who would've had expected naming confusion?
void real_exit(int __code) { exit(__code); }
void System::exit(int code) {
    real_exit(code);
}

// == Definitions
extern "C" snowball::ScopeValue* sn_export(snowball::SNAPI* API) {

    return API->create_module("System", std::map<std::string, llvm::Type*> {}, [API](snowball::ScopeValue* CLASS) {

        llvm::Type* void_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::VOID, API->compiler->builder);
        llvm::Type* float_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::FLOAT, API->compiler->builder);
        llvm::Type* bool_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::BOOL, API->compiler->builder);
        llvm::Type* string_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::STRING, API->compiler->builder);
        llvm::Type* double_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::DOUBLE, API->compiler->builder);
        llvm::Type* int16_type = API->compiler->builder->getInt16Ty();
        llvm::Type* int32_type = API->compiler->builder->getInt32Ty();
        llvm::Type* int64_type = API->compiler->builder->getInt64Ty();

        METHOD("println", void_type, { METHOD_ARGUMENT(snowball::STRING_TYPE, string_type) },  "puts")
        METHOD("println", void_type, { METHOD_ARGUMENT(snowball::BOOL_TYPE, bool_type) },      "_ZN6System7printlnEb")
        METHOD("println", void_type, { METHOD_ARGUMENT(snowball::INT16_TYPE, int16_type) },    "_ZN6System7printlnEs")
        METHOD("println", void_type, { METHOD_ARGUMENT(snowball::INT32_TYPE, int32_type) },    "_ZN6System7printlnEi")
        METHOD("println", void_type, { METHOD_ARGUMENT(snowball::INT64_TYPE, int64_type) },    "_ZN6System7printlnEl")
        METHOD("println", void_type, { METHOD_ARGUMENT(snowball::FLOAT32_TYPE, float_type) },  "_ZN6System7printlnEf")
        METHOD("println", void_type, { METHOD_ARGUMENT(snowball::FLOAT64_TYPE, double_type) }, "_ZN6System7printlnEd")

        METHOD("print", void_type, { METHOD_ARGUMENT(snowball::STRING_TYPE, string_type) },  "_ZN6System5printEPc")
        METHOD("print", void_type, { METHOD_ARGUMENT(snowball::BOOL_TYPE, bool_type) },      "_ZN6System5printEb")
        METHOD("print", void_type, { METHOD_ARGUMENT(snowball::INT16_TYPE, int16_type) },    "_ZN6System5printEs")
        METHOD("print", void_type, { METHOD_ARGUMENT(snowball::INT32_TYPE, int32_type) },    "_ZN6System5printEi")
        METHOD("print", void_type, { METHOD_ARGUMENT(snowball::INT64_TYPE, int64_type) },    "_ZN6System5printEl")
        METHOD("print", void_type, { METHOD_ARGUMENT(snowball::FLOAT32_TYPE, float_type) },  "_ZN6System5printEf")
        METHOD("print", void_type, { METHOD_ARGUMENT(snowball::FLOAT64_TYPE, double_type) }, "_ZN6System5printEd")

        METHOD("input", string_type, { /* TODO: default string for prompts */ }, "_ZN6System5inputEv")
        METHOD("exit", string_type, { METHOD_ARGUMENT(snowball::INT32_TYPE, int32_type) /* TODO: default code = 0 */ }, "_ZN6System4exitEi")
    });
}