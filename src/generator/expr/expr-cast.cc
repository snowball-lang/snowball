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
    llvm::Value* Generator::generate_cast(CastNode* p_node) {
        auto original_value = generate(p_node->expr);
        auto cast_type = TypeChecker::get_type(_enviroment, p_node->cast_type, p_node);

        if (!TypeChecker::is_class(cast_type)) {
            COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Type '%s' does not point to a class!", p_node->cast_type->to_string().c_str()))
        }

        auto [cast, succ] = TypeChecker::implicit_cast(_builder, TypeChecker::type2llvm(_builder, *cast_type->llvm_struct), original_value);
        if (!succ) {
            COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Can't cast type '%s' to '%s'!", TypeChecker::to_type(TypeChecker::get_type_name(original_value->getType())).first->to_string().c_str(), p_node->cast_type->to_string().c_str()))
        }

        return cast;
    }
}