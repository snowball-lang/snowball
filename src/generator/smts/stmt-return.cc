#include "snowball/libs.h"

#include "snowball/types.h"
#include "snowball/nodes.h"
#include "snowball/token.h"
#include "snowball/errors.h"
#include "snowball/generator.h"

#include "snowball/utils/utils.h"
#include "snowball/utils/mangle.h"
#include "snowball/operators.h"

#include <cstdio>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Intrinsics.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/Attributes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>

#include <memory>
#include <pthread.h>
#include <sstream>
#include <optional>
#include <fstream>

#include <dlfcn.h>

namespace snowball {
    llvm::Value* Generator::generate_return(ReturnNode* p_node) {
        llvm::Value* value = generate(p_node->value);
        ScopeValue* ret_value = TypeChecker::get_type(_enviroment, p_node->parent->return_type, p_node);
        llvm::Type* left_type; // Function's return type

        std::string ret_type;
        if (TypeChecker::is_class(ret_value)) {
            left_type = TypeChecker::type2llvm(_builder, *ret_value->llvm_struct);
            ret_type = TypeChecker::get_type_name(left_type);
        } else if (ret_value->type == ScopeType::LLVM) {
            left_type = TypeChecker::type2llvm(_builder, (*ret_value->llvm_value)
                ->getType());
            ret_type = TypeChecker::get_type_name(left_type);
        }

        llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, value).first;
        llvm::Type* new_right_type = new_right->getType();

        if ((TypeChecker::get_type_name(new_right_type) == ret_type) ||
            (TypeChecker::is_number(left_type) || TypeChecker::is_float(left_type) || TypeChecker::is_bool(left_type)) &&
            (TypeChecker::is_number(new_right_type) || TypeChecker::is_float(new_right_type) || TypeChecker::is_bool(new_right_type))) {
            return _builder->CreateRet(new_right);
        } else {
            COMPILER_ERROR(
                TYPE_ERROR,
                Logger::format(
                    "Mismatched types between '%s' and '%s'",
                    TypeChecker::get_type_name(value->getType()).c_str(),
                    ret_type.c_str()
                )
            )
        }
    }
}