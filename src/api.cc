
#include <llvm-10/llvm/IR/DerivedTypes.h>
#include <llvm-10/llvm/IR/Verifier.h>
#include <map>
#include <memory>

#include <functional>

#include <llvm/IR/Type.h>
#include <llvm/ADT/Twine.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/ExecutionEngine/GenericValue.h>

#include "snowball/api.h"
#include "snowball/compiler.h"

namespace snowball {
    ScopeValue* SNAPI::create_class(std::string p_name, std::map<std::string, llvm::Type*> p_properties, std::function<void(ScopeValue*)> cb, bool is_module) {
        llvm::StructType* llvm_struct = llvm::StructType::create(_compiler->global_context, p_name);

        std::vector<llvm::Type*> properties;
        for (auto const& pair : p_properties) {
            properties.push_back(pair.second);
        }

        llvm_struct->setBody(properties);

        Scope* class_scope = new Scope(p_name, _compiler->get_source_info());
        ScopeValue* class_value = new ScopeValue(class_scope, std::make_shared<llvm::StructType*>(llvm_struct));

        if (cb != nullptr)
            cb(class_value);

        if (!is_module)
            add_to_enviroment(p_name, std::make_unique<ScopeValue*>(class_value));
        return class_value;
    }

    ScopeValue* SNAPI::create_module(std::string p_name, std::map<std::string, llvm::Type*> p_properties, std::function<void(ScopeValue*)> cb) {
        ScopeValue* mod = create_class(p_name, p_properties, nullptr, true);

        mod->type = ScopeType::MODULE;

        if (cb != nullptr)
            cb(mod);

        add_to_enviroment(p_name, std::make_unique<ScopeValue*>(mod));
        return mod;
    }

    // ScopeValue* SNAPI::create_function(std::string p_name, llvm::Type* p_return_type, std::vector<std::pair<std::string, llvm::Type*>> p_args, bool is_public) {
    //     std::string llvm_error;
    //     llvm::raw_string_ostream message_stream(llvm_error);

    //     std::vector<llvm::Type*> properties;
    //     std::vector<std::string> propertie_types;
    //     for (auto const& pair : p_args) {
    //         properties.push_back(pair.second);
    //         propertie_types.push_back(pair.first);
    //     }

    //     auto function_prototype = llvm::FunctionType::get(p_return_type, properties, false);
    //     auto function =
    //         llvm::Function::Create(
    //             function_prototype,
    //             llvm::Function::ExternalLinkage,
    //             mangle(
    //                 p_name,
    //                 propertie_types,
    //                 is_public
    //             ),
    //             _compiler->get_module()
    //         );

    //     std::shared_ptr<llvm::Function*> function_ptr = std::make_shared<llvm::Function*>(function);
    //     ScopeValue* scope_value = new ScopeValue(function_ptr);

    //     llvm::verifyFunction(*function, &message_stream);

    //     if (!llvm_error.empty())
    //         throw SNError(Error::LLVM_INTERNAL, llvm_error);

    //     return scope_value;
    // }


    void SNAPI::create_class_method(ScopeValue* p_class, std::string p_name, llvm::Type* p_return_type, std::vector<std::pair<std::string, llvm::Type*>> p_args, bool is_public, std::function<void(Compiler*)> cb) {
        std::string llvm_error;
        llvm::raw_string_ostream message_stream(llvm_error);

        std::vector<llvm::Type*> properties;
        std::vector<std::string> propertie_types;
        for (auto const& pair : p_args) {
            properties.push_back(pair.second);
            propertie_types.push_back(pair.first);
        }

        auto function_prototype = llvm::FunctionType::get(p_return_type, properties, false);
        auto function =
            llvm::Function::Create(
                function_prototype,
                llvm::Function::ExternalLinkage,
                mangle(
                    Logger::format(
                        "%s.%s",
                        (*p_class->llvm_struct)->getStructName().str().c_str(),
                        p_name.c_str()
                    ),
                    propertie_types,
                    is_public
                ),
                _compiler->get_module()
            );

        if (cb != nullptr) {
            llvm::BasicBlock *body = llvm::BasicBlock::Create(_compiler->builder.getContext(), "body", function);
            _compiler->builder.SetInsertPoint(body);

            cb(_compiler);
        }

        std::shared_ptr<llvm::Function*> function_ptr = std::make_shared<llvm::Function*>(function);
        p_class->scope_value->set(mangle(p_name, propertie_types, is_public), std::make_unique<ScopeValue*>(new ScopeValue(function_ptr)));

        llvm::verifyFunction(*function, &message_stream);

        if (!llvm_error.empty())
            throw SNError(Error::LLVM_INTERNAL, llvm_error);
    }

    void SNAPI::add_to_enviroment(std::string p_name, std::unique_ptr<ScopeValue*> p_scope_value) {
        _compiler->get_enviroment()->current_scope()->set(p_name, std::move(p_scope_value));
    }
}
