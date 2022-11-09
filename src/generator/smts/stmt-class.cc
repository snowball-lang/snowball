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
    llvm::Value* Generator::generate_class(ClassNode* p_node) {
        Type* class_type = new Type(p_node->name);

        // TODO: check for generics
        // TODO: class name mangled if module exists
        Scope* class_scope = new Scope(p_node->name, _source_info);

        auto class_struct = llvm::StructType::create(_builder->getContext(), class_type->mangle());
        ScopeValue* class_scope_val = new ScopeValue(class_scope, std::make_shared<llvm::StructType*>(class_struct));

        std::vector<llvm::Type*> var_types;
        for (VarNode* var : p_node->vars) {
            ScopeValue* type = TypeChecker::get_type(_enviroment, var->vtype, p_node);
            if (!TypeChecker::is_class(type)) {
                COMPILER_ERROR(TYPE_ERROR, Logger::format("'%s' does not reference a class", var->vtype->name.c_str()))
            }

            class_scope_val->properties.push_back({ .name = var->name, .is_public = var->isPublic });
            var_types.push_back(TypeChecker::type2llvm(_builder, (llvm::Type*)(*type->llvm_struct)));
        }

        for (Type* parent : p_node->parents) {
            // COMPILER_ERROR(TODO, "Parents not yet supported!")
            ScopeValue* type = TypeChecker::get_type(_enviroment, parent, p_node);
            if (!TypeChecker::is_class(type)) {
                COMPILER_ERROR(TYPE_ERROR, Logger::format("'%s' does not reference a class", parent->name.c_str()))
            }

            class_scope_val->parents.push_back(parent);
            var_types.insert(var_types.begin(), TypeChecker::type2llvm(_builder, (llvm::Type*)(*type->llvm_struct)));
        }

        std::unique_ptr<ScopeValue*> class_value = std::make_unique<ScopeValue*>(class_scope_val);
        SET_TO_GLOBAL_OR_CLASS(class_type->mangle(), class_value)

        class_struct->setBody(var_types);

        p_node->_llvm_struct = class_struct;
        _context._current_class = p_node;
        _context._current_class->name = class_type->mangle();

        for (FunctionNode* func : p_node->functions) {
            generate(func);
        }

        for (OperatorNode* func : p_node->operators) {
            generate(func);
        }

        _context._current_class = nullptr;
        return (llvm::Value*)class_struct;
    }
}