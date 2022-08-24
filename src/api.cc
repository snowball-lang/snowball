
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

#include <llvm/Support/DynamicLibrary.h>

#include "snowball/api.h"
#include "snowball/compiler.h"

namespace snowball {
    ScopeValue* SNAPI::create_class(std::string p_name, std::map<std::string, llvm::Type*> p_properties, std::function<void(ScopeValue*)> cb, bool is_module) {
        llvm::StructType* llvm_struct = llvm::StructType::create(_compiler->global_context, mangle(p_name, {}, true, true));

        std::vector<llvm::Type*> properties;
        for (auto const& pair : p_properties) {
            properties.push_back(pair.second);
        }

        llvm_struct->setBody(properties);

        Scope* class_scope = new Scope(mangle(p_name, {}, true, true), _compiler->get_source_info());
        ScopeValue* class_value = new ScopeValue(class_scope, std::make_shared<llvm::StructType*>(llvm_struct));

        if (cb != nullptr && !_init_mode)
            cb(class_value);

        if (!is_module)
            add_to_enviroment(mangle(p_name, {}, true, true), std::make_unique<ScopeValue*>(class_value));

        if (_init_mode) {
            _types.emplace(class_value, cb);
        }

        return class_value;
    }

    void SNAPI::init_mode() {
        _init_mode = true;
    }

    void SNAPI::register_all() {
        std::map<ScopeValue*, std::function<void(ScopeValue*)>>::iterator it;

        for (it = _types.begin(); it != _types.end(); it++) {
            it->second(it->first);
        }

        _init_mode = false;
    }

    ScopeValue* SNAPI::create_module(std::string p_name, std::map<std::string, llvm::Type*> p_properties, std::function<void(ScopeValue*)> cb) {
        ScopeValue* mod = create_class(p_name, p_properties, nullptr, true);

        mod->type = ScopeType::MODULE;

        if (cb != nullptr)
            cb(mod);

        return mod;
    }

    void SNAPI::create_class_method(ScopeValue* p_class, std::string p_name, llvm::Type* p_return_type, std::vector<std::pair<Type*, llvm::Type*>> p_args, std::string p_pointer) {
        std::string llvm_error;
        llvm::raw_string_ostream message_stream(llvm_error);

        std::vector<llvm::Type*> arguments;
        std::vector<Type*> arguments_types;
        for (auto const& pair : p_args) {
            arguments.push_back(pair.second);
            arguments_types.push_back(pair.first);
        }

        std::string C_name = p_pointer.empty() ? Logger::format("sn_%s__%s", TypeChecker::to_type(p_class->scope_value->name()).first->name.c_str(), p_name.c_str()) : p_pointer;
        auto function_prototype = llvm::FunctionType::get(p_return_type, arguments, false);
        auto function =
            llvm::Function::Create(
                function_prototype,
                llvm::Function::ExternalLinkage,
                C_name,
                _compiler->get_module()
            );

        std::shared_ptr<llvm::Function*> function_ptr = std::make_shared<llvm::Function*>(function);
        std::unique_ptr<ScopeValue*> scope_value = std::make_unique<ScopeValue*>(new ScopeValue(function_ptr));

        (*scope_value)->isPublic = true;
        (*scope_value)->arguments = arguments_types;

        p_class->scope_value->set(mangle(p_name, arguments_types, true), std::move(scope_value));

        llvm::verifyFunction(*function, &message_stream);

        if (!llvm_error.empty())
            throw SNError(Error::LLVM_INTERNAL, llvm_error);
    }

    void SNAPI::add_to_enviroment(std::string p_name, std::unique_ptr<ScopeValue*> p_scope_value) {
        _compiler->get_enviroment()->current_scope()->set(p_name, std::move(p_scope_value));
    }
}
