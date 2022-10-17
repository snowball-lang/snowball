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
    llvm::Value* Generator::generate_module(ModuleNode* p_node) {

        // TODO: check if module already exists
        auto module_name = TypeChecker::string_mangle(p_node->name);

        ScopeValue* module_scope = new ScopeValue(new Scope(module_name, _source_info));
        auto class_struct = llvm::StructType::create(_builder->getContext(),  ADD_NAMESPACE_NAME_IF_EXISTS(".") module_name);
        class_struct->setBody({}, true);
        module_scope->llvm_struct = std::make_shared<llvm::StructType *>(class_struct);
        module_scope->module_name = ADD_NAMESPACE_NAME_IF_EXISTS(".") module_name;
        module_scope->type = ScopeType::MODULE;
        module_scope->type = ScopeType::NAMESPACE;


        if (_context._current_namespace != nullptr) {
            _enviroment->get((ADD_MODULE_NAME_IF_EXISTS(".") _context._current_namespace->module_name), nullptr)->scope_value->set(module_name, std::make_unique<ScopeValue*>(module_scope));
            _enviroment->current_scope()->set(module_name, std::make_unique<ScopeValue*>(module_scope));
        } else if (_context._current_module != nullptr) {
            _enviroment->get(MODULE_NAME_IF_EXISTS("."), nullptr)->scope_value->set(module_name, std::make_unique<ScopeValue*>(module_scope));
            _enviroment->current_scope()->set(module_name, std::make_unique<ScopeValue*>(module_scope));
        } else {
            _enviroment->global_scope()->set(module_name, std::make_unique<ScopeValue*>(module_scope));
        }

        auto namespace_bk = _context._current_namespace;
        _context._current_namespace = module_scope;

        _enviroment->create_scope(module_name);

        for (Node* node : p_node->nodes) {
            generate(node);
        }
        _enviroment->delete_scope();

        _context._current_namespace = namespace_bk;

        // Just return anything
        return llvm::ConstantInt::get(_builder->getInt8Ty(), 0);
    }
}