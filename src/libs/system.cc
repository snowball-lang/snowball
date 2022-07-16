
#include "snowball/api.h"
#include "snowball/snowball.h"
#include "snowball/constants.h"
#include "snowball/libs/system.h"
#include "snowball/types/String.h"

#include <vector>
#include <utility>

namespace snowball {
    ScopeValue* sn_system_export(SNAPI* API) {
        llvm::Type* string_class = (*API->get_compiler()->get_enviroment()->get("String", nullptr)->llvm_struct)->getPointerTo();
        ScopeValue* system_module = API->create_module("System", {});

        API->create_class_method(
            system_module,
            "print",
            API->get_compiler()->get_builder().getVoidTy(),
            { std::make_pair("String", string_class) },
            true
        );

        API->create_class_method(
            system_module,
            "println",
            API->get_compiler()->get_builder().getVoidTy(),
            { std::make_pair("String", string_class) },
            true
        );

        return system_module;
    }
}

extern "C" DLLEXPORT void _MN6SystemN7printlnA6StringP(String* str) {
    printf("%s\n", str->buffer);
}

extern "C" DLLEXPORT void _MN6SystemN5printA6StringP(String* str) {
    printf("%s", str->buffer);
}
