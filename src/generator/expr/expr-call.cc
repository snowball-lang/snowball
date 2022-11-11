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
        #define FUNCTION_NAME() ADD_MODULE_NAME_IF_EXISTS(".") ADD_NAMESPACE_NAME_IF_EXISTS(".") ( \
            (!((!base_struct.empty()) && (class_value->type == ScopeType::CLASS || class_value->type == ScopeType::MODULE))) ? \
                p_node->method : \
                Logger::format("%s.%s", base_struct.c_str(), p_node->method.c_str()) \
        )

        std::string method_name = p_node->method + "("; // TODO: move "stringified" function to a typechecker function
        std::vector<Type*> arg_types;
        std::vector<std::string> arg_types_str;
        std::vector<llvm::Value*> args;

        std::string base_struct;
        llvm::Value* base_value;
        ScopeValue* class_value = new ScopeValue();

        // TODO: generics

        // Check if there is a function class and it's not static
        if (p_node->base != nullptr) {
            base_value = generate(p_node->base);

            // If it's an identifier, what we want to do is to
            // check for the identifier, either mangled or not.
            if (p_node->base->type == Node::Ty::IDENTIFIER) {

                std::string base_name = dynamic_cast<IdentifierNode*>(p_node->base)->name;
                std::string mangled_base_name = (new Type(base_name))->mangle();

                if (_enviroment->item_exists(base_name)) {
                    class_value = _enviroment->get(base_name, p_node);
                } else if (_enviroment->item_exists(mangled_base_name)) {
                    class_value = _enviroment->get(mangled_base_name, p_node);
                } else {
                    COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Identifier %s does not exist (in function call base)!", p_node->method.c_str()))
                }

                // If the returned value is an llvm value and not a type,
                // we will need to get the type of that value
                if (class_value->type == ScopeType::LLVM) {
                    class_value = _enviroment->get(TypeChecker::get_type_name((*class_value->llvm_value)->getType()), p_node->is_static_call ? p_node : p_node->base);
                }
            } else {
                class_value = _enviroment->get(TypeChecker::get_type_name(base_value->getType()), p_node->is_static_call ? p_node : p_node->base);
            }

            // Append/Set a base struct
            if (!base_struct.empty()) base_struct += ".";
            base_struct += TypeChecker::get_type_name(*class_value->llvm_struct);

            // This section is reserved for non-static calls.
            if (!p_node->is_static_call) {
                // note: we can call modules by using the "." separator.
                //   this is just syntax sugar and it does not have any
                //   sort of "difference" to "::".
                if (class_value->type == ScopeType::MODULE) {
                    p_node->is_static_call = true;
                } else {

                    // We need to implicitly set the "self" argument.
                    args.push_back(base_value);
                    arg_types.push_back(TypeChecker::to_type(base_struct).first); // demangle types
                    arg_types_str.push_back(base_struct);

                    method_name += "self";
                    if ((p_node->arguments.size() > 0))
                        method_name += ", ";
                }
            }
        }

        // MARK: argument parsing

        int arg_index = 0;

        for (auto arg : p_node->arguments) {
            llvm::Value* result = generate(arg);
            auto type = TypeChecker::to_type(TypeChecker::get_type_name(result->getType())).first;

            arg_types.push_back(type);

            args.push_back(result);
            method_name += type->to_string();

            // Add a "," to each argument if the list is > than 1
            // and it's not the last argument
            if ((p_node->arguments.size() > 1) && (arg_index < (p_node->arguments.size() - 1)))
                method_name += ", ";

            arg_index++;
        }

        // Finished generating the statement :relieved:
        // Time to actually call the function :scared:
        method_name += ")";

        // Todo: check if method is private / public
        std::string method_call =
            (p_node->base == nullptr ?
            mangle( p_node->method, arg_types) :
            GET_FUNCTION_FROM_CLASS( base_struct.c_str(), p_node->method, arg_types));

        ScopeValue* function;
        Enviroment::FunctionStore* function_store;

        bool function_is_used = false;
        bool private_method_exists = false;

        // TODO: IF FUNCTION IS INSIDE A MODULE,
        // SET THE MODULE TO CONTEXT AND SET IT'S SCOPES,
        // THIS IS VERY IMPORTANT.

        for (int i = 0; i < 2; i++) {
            bool can_private = !i;

            method_call =
                (p_node->base == nullptr ?
                mangle(p_node->method, arg_types, can_private) :
                GET_FUNCTION_FROM_CLASS((base_struct).c_str(), p_node->method, arg_types, can_private));

            if (_enviroment->item_exists(method_call)) {
                function = _enviroment->get(method_call, p_node);

                if (!(can_private)) {
                    if ((_context._current_module != nullptr && _context._current_module->module_name == base_struct) || (_context._current_class != nullptr && _context._current_class->name == base_struct) || (function->parent_scope->name() == _enviroment->global_scope()->name())) {
                        function_is_used = true;
                    } else {
                        private_method_exists = true;
                    }
                } else {
                    function_is_used = true;
                }
            } else if ((function_store = _enviroment->find_function_if(FUNCTION_NAME(), [=](auto store) -> std::pair<bool, bool> {
                auto node_args = store.node->arguments;

                if ((!base_struct.empty()) && class_value->type == ScopeType::CLASS) {
                    ArgumentNode* arg = new ArgumentNode("self", TypeChecker::to_type(base_struct).first);

                    // TODO: arguments are added after each iteration \_(0_0)_/
                    node_args.insert(node_args.begin(), arg);
                }

                if ((!can_private) && store.node->is_public) return {false, false};
                if ((node_args.size() <= arg_types.size()) && store.node->has_vargs) {}
                else if (node_args.size() != arg_types.size()) return {false, false};
                if (!store.node->generics.empty()) return {true, true};// If it's generic, return it because it is the only function with the specified name and argument amount in the list (this might be a canditate)
                return TypeChecker::functions_equal(
                    store.node->name,
                    store.node->name,
                    TypeChecker::args2types(node_args),
                    arg_types,
                    can_private,
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

                auto bk_scopes = _enviroment->save_state();
                paste_function(function_store);
                _enviroment->restore_state(bk_scopes);

                function = _enviroment->get(method_call, p_node); // it will exist... right?

                if (!(can_private)) {
                    if ((_context._current_module != nullptr && _context._current_module->module_name == base_struct) || (_context._current_class != nullptr && _context._current_class->name == base_struct) || (function->parent_scope->name() == _enviroment->global_scope()->name())) {
                        function_is_used = true;
                    } else {
                        private_method_exists = true;
                    }
                } else {
                    function_is_used = true;
                }
            }
        }

        // checking for errors!
        if (!function_is_used) {
            if (private_method_exists) {
                COMPILER_ERROR(
                    VARIABLE_ERROR,
                    Logger::format("Function named '%s' is a private method that can't be accessed outside it's class or module",
                        p_node->base != nullptr ?
                            Logger::format("%s.%s", base_struct.c_str(), method_name.c_str()).c_str()
                            : method_name.c_str()
                    )
                )
            } else {
                COMPILER_ERROR(
                    VARIABLE_ERROR,
                    Logger::format("No function found with name: %s",
                        p_node->base != nullptr ?
                            Logger::format("%s.%s", base_struct.c_str(), method_name.c_str()).c_str()
                            : method_name.c_str()
                    )
                )
            }
        } else if (function->type != ScopeType::FUNC) {
            COMPILER_ERROR(SYNTAX_ERROR, Logger::format("'%s' is not a function", p_node->method.c_str()))
        }

        ASSERT(args.size() == arg_types.size())
        return _builder->CreateCall(*function->llvm_function, args);

        #undef FUNCTION_NAME
    }
}