
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
    llvm::Value* Generator::paste_function(Enviroment::FunctionStore* store) {
        #define IS_ENTRY_POINT() (store->node->name == _SNOWBALL_FUNCTION_ENTRY && store->node->is_lop_level)
        #define _MODULE_NAME_IF_EXISTS(_sufix) (store->current_module != nullptr ? (store->current_module->module_name + _sufix) : "")
        #define _ADD_MODULE_NAME_IF_EXISTS(_sufix) _MODULE_NAME_IF_EXISTS(_sufix) +
        #define _SET_TO_GLOBAL_OR_CLASS(_name, value) \
            if (store->current_class != nullptr) { \
                _enviroment->get(_ADD_MODULE_NAME_IF_EXISTS(".") store->current_class->name, nullptr)->scope_value->set(_name, std::move(value)); \
            } else if (store->current_namespace != nullptr) { \
                store->current_namespace->scope_value->set(_name, std::move(value)); \
            } else if (store->current_module != nullptr) { \
                store->current_module->scope_value->set(_name, std::move(value)); \
            } else { \
                _enviroment->global_scope()->set(_name, std::move(value)); \
            }

        auto bb_backup = _builder->GetInsertBlock();
        auto cls_backup = _context._current_class;
        auto mod_backup = _context._current_module;
        auto namespace_backup = _context._current_namespace;

        _context._current_class = store->current_class;
        _context._current_module = store->current_module;
        _context._current_namespace = store->current_namespace;
        // Skip if the function contains a template

        std::string llvm_error;
        llvm::raw_string_ostream message_stream(llvm_error);

        ScopeValue* returnType = TypeChecker::get_type(_enviroment, store->node->return_type, store->node);
        auto retType =
            IS_ENTRY_POINT()
                ? get_llvm_type_from_sn_type(BuildinTypes::NUMBER, _builder)
                : TypeChecker::type2llvm(_builder, *returnType->llvm_struct);

        std::vector<Type*> arg_tnames;
        std::vector<llvm::Type*> arg_types;
        for (ArgumentNode* argument : store->node->arguments) {

            // check if type exists
            ScopeValue* value = TypeChecker::get_type(_enviroment, argument->arg_type, argument);
            if (!TypeChecker::is_class(value)) {
                FunctionNode* p_node = store->node; // for DBGInfo
                COMPILER_ERROR(ARGUMENT_ERROR, Logger::format("'%s' must be a referece to a class", store->node->name.c_str()))
            }

            llvm::StructType* type = *value->llvm_struct;

            arg_types.push_back(TypeChecker::type2llvm(_builder, type));
            arg_tnames.push_back(TypeChecker::to_type(type->getName().str()).first);
        }

        if (store->current_class != nullptr && store->node->name != op2str(OperatorType::CONSTRUCTOR) && !store->node->is_static) {
            // We asume that the class has already been assigned
            arg_types.insert(
                arg_types.begin(),
                ((llvm::Type*)*_enviroment->get(store->current_class->name, store->node)->llvm_struct)->getPointerTo()
            );
            arg_tnames.insert(arg_tnames.begin(), TypeChecker::to_type(store->current_class->name).first);
        }

        std::string fname = IS_ENTRY_POINT() ? _SNOWBALL_FUNCTION_ENTRY : (store->node->is_extern ? store->node->extern_name : mangle(
            (_ADD_MODULE_NAME_IF_EXISTS(".")
                ADD_NAMESPACE_NAME_IF_EXISTS(".")

                (store->current_class == nullptr ? store->node->name : Logger::format(
                    "%s.%s", store->current_class->name.c_str(),
                    store->node->name.c_str()
                ))), arg_tnames, store->node->is_public));


        auto prototype = llvm::FunctionType::get(retType, arg_types, store->node->has_vargs);
        auto function = (llvm::Function*)_module->getOrInsertFunction(fname, prototype).getCallee();

        std::unique_ptr<ScopeValue*> func_scopev = std::make_unique<ScopeValue*>(new ScopeValue(std::make_shared<llvm::Function*>(function)));
        (*func_scopev)->isStaticFunction = store->node->is_static;
        (*func_scopev)->hasVArg = store->node->has_vargs;
        (*func_scopev)->isPublic = store->node->is_public;
        (*func_scopev)->arguments = arg_tnames;
        _SET_TO_GLOBAL_OR_CLASS(mangle(
                store->node->name, arg_tnames, store->node->is_public), func_scopev);

        Scope* current_scope = _enviroment->create_scope(store->node->name);

        int parameter_index = (store->current_class != nullptr && store->node->name != op2str(OperatorType::CONSTRUCTOR)) ? 0 : 1;
        for (auto& arg : function->args()) {
            std::string name;
            if (store->current_class != nullptr && store->node->name != op2str(OperatorType::CONSTRUCTOR) && parameter_index == 0 && !store->node->is_static) /* self argument */ {
                name = "self";
            } else {
                name = store->node->arguments.at(parameter_index == 0 ? 0 : parameter_index-1)->name;
            }

            if (store->current_class != nullptr && parameter_index>0 && name == "self") {
                FunctionNode* p_node = store->node; // for DBGInfo
                COMPILER_ERROR(SYNTAX_ERROR, "Class method can't contain self as a parameter")
            }

            arg.setName(name);

            std::unique_ptr<ScopeValue*> param_scope_value = std::make_unique<ScopeValue*>(new ScopeValue(std::make_unique<llvm::Value*>(&arg)));
            current_scope->set(name, std::move(param_scope_value));

            parameter_index++;
        }

        // BODY GENERATION

        if (!store->node->is_foward) {
            llvm::BasicBlock *body = llvm::BasicBlock::Create(_builder->getContext(), "body", function);
            _builder->SetInsertPoint(body);

            if (store->current_class != nullptr && store->node->name == op2str(OperatorType::CONSTRUCTOR) && !store->node->is_static) {
                generate_contructor_meta(store->current_class);
            }

            for (auto expr : store->node->body->exprs) {
                generate(expr);
            }

            auto bb = _builder->GetInsertBlock();

            if (bb->size() == 0 || !bb->back().isTerminator()) {
                // TODO: return 0 if it's a number
                if (IS_ENTRY_POINT()) {
                    llvm::Type * i32 = _builder->getInt32Ty();
                    _builder->CreateRet(llvm::ConstantInt::get(i32, 0));
                } else if (store->current_class != nullptr && store->node->name == op2str(OperatorType::CONSTRUCTOR)) {
                    _builder->CreateRet(*current_scope->get("self", nullptr)->llvm_value);
                } else if (retType->isVoidTy()) {
                    _builder->CreateRet(nullptr);
                } else {
                    FunctionNode* p_node = store->node; // for DBGInfo
                    COMPILER_ERROR(FUNCTION_RET_ERR, Logger::format("Function '%s' does not have a return statement for all paths!", p_node->name.c_str()))
                }
            }
        }

        llvm::verifyFunction(*function, &message_stream);
        if (!llvm_error.empty()) {
            FunctionNode* p_node = store->node; // for DBGInfo
            COMPILER_ERROR(LLVM_INTERNAL, llvm_error)
        }

        _enviroment->delete_scope();
        _builder->SetInsertPoint(bb_backup);

        _context._current_class = cls_backup;
        _context._current_module = mod_backup;
        _context._current_namespace = namespace_backup;
        return function;

        #undef _MODULE_NAME_IF_EXISTS
        #undef _ADD_MODULE_NAME_IF_EXISTS
        #undef _SET_TO_GLOBAL_OR_CLASS
        #undef IS_ENTRY_POINT

    }
}