
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
    llvm::Value* Generator::generate_new(NewNode* p_node) {
        std::vector<Type*> arg_types;
        std::vector<llvm::Value*> args;

        int arg_index = 0;
        for (Node* arg : p_node->arguments) {
            llvm::Value* result = generate(arg);
            arg_types.push_back(TypeChecker::to_type(TypeChecker::get_type_name(result->getType())).first);
            args.push_back(result);

            arg_index++;
        }

        Type* class_type = new Type(p_node->method);

        // Check if type exists
        TypeChecker::get_type(_enviroment, new Type(ADD_MODULE_NAME_IF_EXISTS(".") p_node->method), p_node);

        // TODO: check if there are generics
        // TODO: check if class exist and throw custom error
        #define FNAME() GET_FUNCTION_FROM_CLASS(\
            (ADD_MODULE_NAME_IF_EXISTS(".") class_type->mangle()).c_str(), \
                (((std::string)"#") + op2str(OperatorType::CONSTRUCTOR)).c_str(), arg_types, true)
        #define FNAME_NO_MANGLE() GET_FUNCTION_FROM_CLASS_NO_MANGLE( \
            (ADD_MODULE_NAME_IF_EXISTS(".") class_type->mangle()), \
                (((std::string)"#") + op2str(OperatorType::CONSTRUCTOR)))

        Enviroment::FunctionStore* function_store;
        llvm::Function* function;

        // TODO: check for private constructors first
        auto unmangled = unmangle(mangle(FNAME_NO_MANGLE(), arg_types, true));
        unmangled.isPublic = true;

        auto fn = _enviroment->find_function_if(FNAME_NO_MANGLE(), [=](auto store) -> std::pair<bool, bool> {
            if ((store.node->arguments.size() <= unmangled.arguments.size()) && store.node->has_vargs) {}
            else if (store.node->arguments.size() != unmangled.arguments.size()) return {false, false};
            return TypeChecker::functions_equal(
                store.node->name,
                store.node->name,
                TypeChecker::args2types(store.node->arguments),
                unmangled.arguments,
                unmangled.isPublic,
                store.node->is_public,
                store.node->has_vargs);
        }, p_node);

        if (fn == nullptr) {
            function = *_enviroment->get(
            FNAME(), p_node, Logger::format(
                "constructor for '%s' (%s)",
                    class_type->to_string().c_str(),
                    TypeChecker::args_to_string(arg_types).c_str()
                )
            )->llvm_function;
        } else {
            function = (llvm::Function*)paste_function(fn);
        }

        return _builder->CreateCall(function, args);

        #undef FNAME
        #undef FNAME_NO_MANGLE
    }
}