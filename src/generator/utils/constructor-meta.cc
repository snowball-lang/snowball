
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
    void Generator::generate_contructor_meta(ClassNode* current_class) {
        ASSERT(current_class != nullptr)

        auto class_scope = _enviroment->get(current_class->name, current_class);
        auto type = *class_scope->llvm_struct;
        int size = _module->getDataLayout().getTypeStoreSize(type);
        llvm::ConstantInt* size_constant = llvm::ConstantInt::get(_builder->getInt32Ty(), size);

        llvm::Value* alloca_value = _builder->CreateCall(get_alloca(_module, _builder), {size_constant});
        llvm::Value* pointerCast = _builder->CreatePointerCast(alloca_value, type->getPointerTo(), "self");

        std::unique_ptr<ScopeValue*> scope_value = std::make_unique<ScopeValue*>(new ScopeValue(std::make_unique<llvm::Value *>(pointerCast)));
        _enviroment->current_scope()->set("self", std::move(scope_value));

        if (class_scope->has_vtable) {
            llvm::Value* pointer = _builder->CreateInBoundsGEP(pointerCast->getType()->getPointerElementType(), pointerCast, {llvm::ConstantInt::get(_builder->getInt32Ty(), 0), llvm::ConstantInt::get(_builder->getInt32Ty(), 0)});
            _builder->CreateStore(class_scope->vtable, pointer);
        }

        int var_index = class_scope->has_vtable + current_class->_parent_props_count;

        for (VarNode* var : current_class->vars) {
            auto p_node = var; // for compiler errors

            auto var_type = TypeChecker::get_type(_enviroment, var->vtype, var);
            if (!TypeChecker::is_class(var_type)) {
                COMPILER_ERROR(TYPE_ERROR, Logger::format("Type %s does not point to a valid type.", var->vtype->to_string().c_str()))
            }

            llvm::Value* value = generate(var->value);

            if (TypeChecker::to_type(TypeChecker::get_type_name(value->getType())).first != var->vtype) {
                auto [cast, succ] = TypeChecker::implicit_cast(_builder, TypeChecker::type2llvm(_builder, *var_type->llvm_struct), value);
                if (!succ) {
                    COMPILER_ERROR(TYPE_ERROR, Logger::format("Can't cast type '%s' to '%s'!", TypeChecker::to_type(TypeChecker::get_type_name(value->getType())).first->to_string().c_str(), var->vtype->to_string().c_str()))
                }

                value = cast;
            }

            llvm::Value* pointer = _builder->CreateInBoundsGEP(
                pointerCast->getType()->getPointerElementType(),
                pointerCast,
                {
                    llvm::ConstantInt::get(_builder->getInt32Ty(), 0),
                    llvm::ConstantInt::get(_builder->getInt32Ty(), var_index)
                });

            _builder->CreateStore(value, pointer);

            var_index++;
        }
    }
}