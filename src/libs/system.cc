
#include "snowball/api.h"
#include "snowball/snowball.h"
#include "snowball/constants.h"
#include "snowball/libs/system.h"
#include "snowball/types/String.h"

#include <vector>
#include <utility>
#include <string>

namespace snowball {
    ScopeValue* sn_system_export(SNAPI* API) {
        ScopeValue* string_class = API->get_compiler()->get_enviroment()->get("String", nullptr);
        API->create_module("System", {}, [&](ScopeValue* system_module) {
            llvm::Type* class_type = (*system_module->llvm_struct)->getPointerTo();

            API->create_class_method(
                system_module,
                "print",
                API->get_compiler()->builder.getVoidTy(),
                std::vector<std::pair<std::string, llvm::Type*>> {
                    std::make_pair("String", *string_class->llvm_struct)
                },
                true,
                nullptr
            );

            API->create_class_method(
                system_module,
                "println",
                API->get_compiler()->builder.getVoidTy(),
                std::vector<std::pair<std::string, llvm::Type*>> {
                    std::make_pair("String", *string_class->llvm_struct)
                },
                true,
                nullptr
            );
        });
    }
}

extern "C" DLLEXPORT void _MN6SystemN7printlnA6StringP(String* str) {
    printf("%s\n", str->buffer);
}

extern "C" DLLEXPORT void _MN6SystemN5printA6StringP(String* str) {
    printf("%s", str->buffer);
}
