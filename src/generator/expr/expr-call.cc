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
    llvm::Value* Generator::generate_call(CallNode* p_node) {
        #define FUNCTION_NAME() ( \
            ADD_MODULE_NAME_IF_EXISTS(".") ( \
                (!((!base_struct.empty()) && (class_value->type == ScopeType::CLASS || class_value->type == ScopeType::NAMESPACE || class_value->type == ScopeType::MODULE))) ? \
                    p_node->method : \
                    Logger::format("%s.%s", base_struct.c_str(), p_node->method.c_str()) \
            ) \
        )

        std::string method_name = p_node->method + "("; // TODO: move "stringified" function to a typechecker function
        std::vector<Type*> arg_types;
        std::vector<std::string> arg_types_str;
        std::vector<llvm::Value*> args;

        std::string base_struct = MODULE_NAME_IF_EXISTS("");
        llvm::Value* base_value;
        ScopeValue* class_value = new ScopeValue();

        // TODO: generics
        if (p_node->base != nullptr && !p_node->is_static_call) {
            base_value = generate(p_node->base);

            if (dynamic_cast<IdentifierNode*>(p_node->base) != nullptr) {

                std::string base_name = dynamic_cast<IdentifierNode*>(p_node->base)->name;
                std::string mangled_base_name = (new Type(base_name))->mangle();

                if (_enviroment->item_exists(mangled_base_name)) {
                    class_value = _enviroment->get(mangled_base_name, p_node);
                } else if (_enviroment->item_exists(base_name)) {
                    class_value = _enviroment->get(base_name, p_node);
                } else {
                    COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Identifier %s does not exist (in function call base)!", p_node->method.c_str()))
                }

                if (class_value->type == ScopeType::LLVM) {
                    class_value = _enviroment->get(TypeChecker::get_type_name((*class_value->llvm_value)->getType()), p_node->base);
                }
            } else {
                class_value = _enviroment->get(TypeChecker::get_type_name(base_value->getType()), p_node->base);
            }

            if (!base_struct.empty()) base_struct += ".";
            base_struct += TypeChecker::get_type_name(*class_value->llvm_struct);
            if (class_value->type == ScopeType::MODULE) {
                p_node->is_static_call = true;
            } else {
                args.push_back(base_value);
                arg_types.push_back(TypeChecker::to_type(base_struct).first); // demangle types
                arg_types_str.push_back(base_struct);

                method_name += "self";
                if ((p_node->arguments.size() > 0))
                    method_name += ", ";
            }
        } else if (p_node->base != nullptr && p_node->is_static_call) {
            base_value = generate(p_node->base);

            if (dynamic_cast<IdentifierNode*>(p_node->base) != nullptr) {
                std::string base_name = dynamic_cast<IdentifierNode*>(p_node->base)->name;
                std::string mangled_base_name = (new Type(base_name))->mangle();

                if (_enviroment->item_exists(mangled_base_name)) {
                    class_value = _enviroment->get(mangled_base_name, p_node);
                } else if (_enviroment->item_exists(base_name)) {
                    class_value = _enviroment->get(base_name, p_node);
                } else {
                    COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Identifier %s does not exist (in function call base)!"))
                }

                if (class_value->type == ScopeType::LLVM) {
                    class_value = _enviroment->get(TypeChecker::get_type_name((*class_value->llvm_value)->getType()), p_node);
                }
            } else {
                class_value = _enviroment->get(TypeChecker::get_type_name(base_value->getType()), p_node);
            }

            if (!base_struct.empty()) base_struct += ".";
            base_struct += TypeChecker::get_type_name(*class_value->llvm_struct);
        }

        int arg_index = 0;
        for (Node* arg : p_node->arguments) {
            llvm::Value* result = generate(arg);
            arg_types.push_back(TypeChecker::to_type(TypeChecker::get_type_name(result->getType())).first);

            args.push_back(result);
            method_name += TypeChecker::to_type(TypeChecker::get_type_name(result->getType())).first->to_string();

            if ((p_node->arguments.size() > 1) && (arg_index < (p_node->arguments.size() - 1)))
                method_name += ", ";

            arg_index++;
        }

        method_name += ")";

        // Todo: check if method is private / public
        std::string method_call =
            ADD_MODULE_NAME_IF_EXISTS(".") (p_node->base == nullptr ?
            mangle( p_node->method, arg_types) :
            GET_FUNCTION_FROM_CLASS( base_struct.c_str(), p_node->method, arg_types));

        ScopeValue* function;
        Enviroment::FunctionStore* function_store;

        // First, look for private methods
        bool private_method_used = false;
        bool private_method_exists = false;
        if (_enviroment->item_exists(method_call)) {
            ScopeValue* private_function = _enviroment->get(method_call, p_node); // it will exist... right?
            if ((_context._current_module != nullptr && _context._current_module->module_name == base_struct) || (_context._current_class != nullptr && _context._current_class->name == base_struct) || (private_function->parent_scope->name() == SN_GLOBAL_SCOPE)) {
                function = private_function;
                private_method_used = true;
            } else {
                private_method_exists = true;
            }
        } else if ((function_store = _enviroment->find_function_if(FUNCTION_NAME(), [=](auto store) -> std::pair<bool, bool> {
            auto node_args = store.node->arguments;

            if ((!base_struct.empty()) && class_value->type == ScopeType::CLASS) {
                ArgumentNode* arg = new ArgumentNode("self", TypeChecker::to_type(base_struct).first);
                node_args.insert(node_args.begin(), arg);
            }

            if (store.node->is_public) return {false, false};
            if ((node_args.size() <= arg_types.size()) && store.node->has_vargs) {}
            else if (node_args.size() != arg_types.size()) return {false, false};
            if (!store.node->generics.empty()) return {true, true};// If it's generic, return it because it is the only function with the specified name and argument amount in the list (this might be a canditate)
            return TypeChecker::functions_equal(
                store.node->name,
                store.node->name,
                TypeChecker::args2types(node_args),
                arg_types,
                false,
                store.node->is_public,
                store.node->has_vargs);
        }, p_node))) {

            auto [_args, succ] = TypeChecker::deduce_template_args(function_store->node, arg_types, p_node->generics);
            if (succ) {
                for (int i = 0; i < function_store->node->arguments.size(); i++) {

                    ScopeValue* arg_ty = TypeChecker::get_type(_enviroment, function_store->node->arguments[i]->arg_type, p_node);
                    if (!TypeChecker::is_class(arg_ty)) {
                        COMPILER_ERROR(TYPE_ERROR, Logger::format("Type %s does not point to a valid type.", _args[i]->to_string().c_str()))
                    }

                    auto real_type = TypeChecker::type2llvm(_builder, *arg_ty->llvm_struct);

                    auto [new_value, succ] = TypeChecker::implicit_cast(_builder,  real_type, args[i]);
                    if (!succ) {
                        COMPILER_ERROR(BUG, Logger::format("Unexpected error while casting '%i' and '%i'", real_type->getTypeID(), args[i]->getType()->getTypeID()))
                    }

                    args[i] = new_value;
                    function_store->node->arguments[i]->arg_type = TypeChecker::llvm2type(new_value->getType());
                }
            } else {
                COMPILER_ERROR(TYPE_ERROR, Logger::format("Coudn't deduce arguments for '%s'", p_node->method.c_str()))
            }

            ASSERT(arg_types.size() <= function_store->node->arguments.size())

            paste_function(function_store);
            ScopeValue* private_function = _enviroment->get(method_call, nullptr); // it will exist... right?

            if ((_context._current_module != nullptr && _context._current_module->module_name == base_struct) || (_context._current_class != nullptr && _context._current_class->name == base_struct) || (private_function->parent_scope->name() == SN_GLOBAL_SCOPE)) {
                function = private_function;
                private_method_used = true;
            } else {
                private_method_exists = true;
            }
        }

        if (!private_method_used) {
            method_call =
                (p_node->base == nullptr ?
                mangle(ADD_MODULE_NAME_IF_EXISTS(".") p_node->method, arg_types, true) :
                GET_FUNCTION_FROM_CLASS((ADD_MODULE_NAME_IF_EXISTS(".") base_struct).c_str(), p_node->method, arg_types, true));


            // Look for public
            if (_enviroment->item_exists(method_call)) {
                function = _enviroment->get(method_call, p_node);
            } else if ((function_store = _enviroment->find_function_if(FUNCTION_NAME(), [=](auto store) -> std::pair<bool, bool> {
                // TODO: check if generic is private
                auto node_args = store.node->arguments;

                if ((!base_struct.empty()) && class_value->type == ScopeType::CLASS) {
                    ArgumentNode* arg = new ArgumentNode("self", TypeChecker::to_type(base_struct).first);

                    // TODO: arguments are added after each iteration \_(0_0)_/
                    node_args.insert(node_args.begin(), arg);
                }

                if ((node_args.size() <= arg_types.size()) && store.node->has_vargs) {}
                else if (node_args.size() != arg_types.size()) return {false, false};
                if (!store.node->generics.empty()) return {true, true};// If it's generic, return it because it is the only function with the specified name and argument amount in the list (this might be a canditate)
                return TypeChecker::functions_equal(
                    store.node->name,
                    store.node->name,
                    TypeChecker::args2types(node_args),
                    arg_types,
                    true,
                    store.node->is_public,
                    store.node->has_vargs);
            }, p_node))) {

                auto [_args, succ] = TypeChecker::deduce_template_args(function_store->node, arg_types, p_node->generics);
                if (succ) {
                    for (int i = 0; i < function_store->node->arguments.size(); i++) {

                        ScopeValue* arg_ty = TypeChecker::get_type(_enviroment, function_store->node->arguments[i]->arg_type, p_node);
                        if (!TypeChecker::is_class(arg_ty)) {
                            COMPILER_ERROR(TYPE_ERROR, Logger::format("Type %s does not point to a valid type.", _args[i]->to_string().c_str()))
                        }

                        auto real_type = TypeChecker::type2llvm(_builder, *arg_ty->llvm_struct);

                        auto [new_value, succ] = TypeChecker::implicit_cast(_builder,  real_type, args[i]);
                        if (!succ) {
                            COMPILER_ERROR(BUG, Logger::format("Unexpected error while casting '%i' and '%i'", real_type->getTypeID(), args[i]->getType()->getTypeID()))
                        }

                        args[i] = new_value;
                        function_store->node->arguments[i]->arg_type = TypeChecker::llvm2type(new_value->getType());
                    }
                } else {
                    COMPILER_ERROR(TYPE_ERROR, Logger::format("Coudn't deduce arguments for '%s'", p_node->method.c_str()))
                }

                ASSERT(arg_types.size() <= function_store->node->arguments.size())

                paste_function(function_store);

                // TODO: error, function not found if it is extern
                function = _enviroment->get(method_call, p_node); // it will exist... right?
            } else {
                FUNCTION_CALL_NOT_FOUND()
            }
        }

        if (function->type != ScopeType::FUNC) {
            COMPILER_ERROR(SYNTAX_ERROR, Logger::format("'%s' is not a function", p_node->method.c_str()))
        }

        ASSERT(args.size() == arg_types.size())
        return _builder->CreateCall(*function->llvm_function, args);

        #undef FUNCTION_NAME
    }
}