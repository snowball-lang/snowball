
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

void register_number(snowball::SNAPI* API) {
    API->create_class("Number", std::map<std::string, llvm::Type*> {
        {
            "__number",
            snowball::get_llvm_type_from_sn_type(
                snowball::BuildinTypes::NUMBER,
                API->get_compiler()->builder
            ),
        },
    }, [&](snowball::ScopeValue* cls) {
        llvm::Type* class_type = (*cls->llvm_struct)->getPointerTo();

        API->create_class_method(
            cls,
            "__init",
            class_type,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair(
                    "i",
                    snowball::get_llvm_type_from_sn_type(
                        snowball::BuildinTypes::NUMBER,
                        API->get_compiler()->builder
                    )
                )
            },
            true,
            (void*)static_cast<Number*(*)(snowball_int_t)>(Number::__init)
        );

        API->create_class_method(
            cls,
            "__sum",
            class_type,
            std::vector<std::pair<std::string, llvm::Type*>> {
                std::make_pair("Number", class_type),
                std::make_pair("Number", class_type)
            },
            true,
            (void*)static_cast<Number*(*)(Number*, Number*)>(Number::__sum)
        );
    });
}