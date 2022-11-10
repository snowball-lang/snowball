
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
    llvm::Value* Generator::generate_function(FunctionNode* p_node, bool generate) {
        #define IS_ENTRY_POINT() (p_node->name == _SNOWBALL_FUNCTION_ENTRY && p_node->is_lop_level)

        // Skip if the function contains a template

        // TODO: check if generics name already exist as a class or smth

        std::vector<Type*> arg_tnames;
        std::vector<llvm::Type*> arg_types;

        for (ArgumentNode* argument : p_node->arguments) {

            // check if argument is actualy a generic
            auto it = std::find_if(p_node->generics.begin(), p_node->generics.end(), [&](Type* arg) {
                return arg->equals(argument->arg_type);
            });

            if (it == p_node->generics.end()) {

                // check if type exists
                ScopeValue* value = TypeChecker::get_type(_enviroment, argument->arg_type, argument);
                if (!TypeChecker::is_class(value)) {
                    COMPILER_ERROR(ARGUMENT_ERROR, Logger::format("'%s' must be a referece to a class", p_node->name.c_str()))
                }

                llvm::StructType* type = *value->llvm_struct;
                arg_types.push_back(TypeChecker::type2llvm(_builder, type));
                arg_tnames.push_back(argument->arg_type);
            } else {
                arg_tnames.push_back(*it);
            }
        }

        if (_context._current_class != nullptr && !p_node->is_static) {
            // We asume that the class has already been assigned
            arg_types.insert(
                arg_types.begin(),
                ((llvm::Type*)*_enviroment->get(_context._current_class->name, p_node)->llvm_struct)->getPointerTo()
            );

            arg_tnames.insert(arg_tnames.begin(), TypeChecker::to_type(_context._current_class->name).first);
        }

        Enviroment::FunctionStore* store = new Enviroment::FunctionStore();
        store->current_class = _context._current_class;
        store->current_module = _context._current_module;
        store->current_namespace = _context._current_namespace;

        store->node = p_node;

        std::string fname = ADD_MODULE_NAME_IF_EXISTS(".") ADD_NAMESPACE_NAME_IF_EXISTS(".") (_context._current_class == nullptr? p_node->name :
            (
                mangle(((ADD_MODULE_NAME_IF_EXISTS(".") ADD_NAMESPACE_NAME_IF_EXISTS(".")

                (store->current_class == nullptr ? store->node->name : Logger::format(
                    "%s.%s", store->current_class->name.c_str(),
                    store->node->name.c_str()
                )))), arg_tnames, store->node->is_public)
            ));

        if ((IS_ENTRY_POINT() && (!_tests_enabled)) || generate) {
            return paste_function(store);
        }

        _enviroment->set_function(fname, store);

        // Function prototype for return statement

        ScopeValue* returnType = TypeChecker::get_type(_enviroment, store->node->return_type, store->node);
        auto retType =
            IS_ENTRY_POINT()
                ? get_llvm_type_from_sn_type(BuildinTypes::NUMBER, _builder)
                : TypeChecker::type2llvm(_builder, *returnType->llvm_struct);

        auto prototype = llvm::FunctionType::get(retType, arg_types, store->node->has_vargs);
        llvm::Function *function = llvm::Function::Create(
            prototype,
            llvm::Function::ExternalLinkage,
            IS_ENTRY_POINT() ? _SNOWBALL_FUNCTION_ENTRY : (
                store->node->is_extern ? store->node->extern_name : mangle((
                (ADD_MODULE_NAME_IF_EXISTS(".") ADD_NAMESPACE_NAME_IF_EXISTS(".")

                (store->current_class == nullptr ? store->node->name : Logger::format(
                    "%s.%s", store->current_class->name.c_str(),
                    store->node->name.c_str()
                )))), arg_tnames, store->node->is_public)
            ),
            _module);

        return function;

        #undef IS_ENTRY_POINT
    }
}