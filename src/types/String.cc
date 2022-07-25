
#include "snowball/export.hpp"
#include "snowball/types/String.h"
#include "snowball/api.h"

#include <vector>
#include <utility>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "snowball/constants.h"

void register_string(snowball::SNAPI* API) {
    API->create_class("String", std::map<std::string, llvm::Type*> {
        {
            "__buffer",
            snowball::get_llvm_type_from_sn_type(
                snowball::BuildinTypes::STRING,
                API->get_compiler()->builder
            ),
        },
        {
            "__length",
            snowball::get_llvm_type_from_sn_type(
                snowball::BuildinTypes::NUMBER,
                API->get_compiler()->builder
            ),
        }
    }, [&](snowball::ScopeValue* cls) {
        llvm::Type* class_type = (*cls->llvm_struct)->getPointerTo();

        API->create_class_method(
            cls,
            "__init",
            class_type,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair(
                    "s",
                    snowball::get_llvm_type_from_sn_type(
                        snowball::BuildinTypes::STRING,
                        API->get_compiler()->builder
                    )
                )
            },
            true,
            (void*)static_cast<String*(*)(const char*)>(String::__init)
        );

        API->create_class_method(
            cls,
            "__sum",
            class_type,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair("String", class_type),
                std::make_pair("String", class_type)
            },
            true,
            (void*)static_cast<String*(*)(String*, String*)>(String::__sum)
        );
    });
}
