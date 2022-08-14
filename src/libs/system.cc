
#include "snowball/api.h"
#include "snowball/types.h"
#include "snowball/snowball.h"
#include "snowball/constants.h"
#include "snowball/libs/system.h"
#include "snowball/types/String.h"

#include <vector>
#include <utility>
#include <string>

namespace snowball {
    ScopeValue* sn_system_export(SNAPI* API) {
        llvm::Type* string_class = (*API->get_compiler()->get_enviroment()->get(STRING_TYPE->mangle(), nullptr)->llvm_struct)->getPointerTo();

        return API->create_module("System", {}, [&](ScopeValue* system_module) {

            API->create_class_method(
                system_module,
                "print",
                API->get_compiler()->builder.getVoidTy(),
                std::vector<std::pair<Type*, llvm::Type*>> {
                    std::make_pair(STRING_TYPE, string_class)
                },
                true,
                (void*)static_cast<void(*)(String*)>(System::print)
            );

            API->create_class_method(
                system_module,
                "println",
                API->get_compiler()->builder.getVoidTy(),
                std::vector<std::pair<Type*, llvm::Type*>> {
                    std::make_pair(STRING_TYPE, string_class)
                },
                true,
                (void*)static_cast<void(*)(String*)>(System::println)
            );
        });
    }
}
