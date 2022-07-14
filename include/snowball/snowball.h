
#ifndef __SNOWBALL_H_
#define __SNOWBALL_H_

#include "types.h"
#include "nodes.h"
#include "token.h"
#include "lexer.h"
#include "scopes.h"
#include "parser.h"
#include "logger.h"
#include "errors.h"
#include "constants.h"
#include "dbg_info.h"
#include "compiler.h"
#include "generator.h"
#include "enviroment.h"
#include "source_info.h"
#include "unittesting.h"

// utils
#include "utils/mangle.h"

// Types
#include "types/Number.h"
#include "types/String.h"

// Extra imports
#include <llvm-10/llvm/IR/DerivedTypes.h>
#include <map>
#include <memory>

// LLVM imports
#include <llvm/IR/Type.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/ExecutionEngine/GenericValue.h>

#ifdef __cplusplus
extern "C" {
#endif

namespace snowball {
    class SNAPI {
        public:
            SNAPI(Compiler* p_compiler) : _compiler(p_compiler) {};

            std::unique_ptr<ScopeValue*> create_class(std::string p_name, std::map<std::string, llvm::Type*> p_properties = {}) {
                llvm::StructType* llvm_struct = llvm::StructType::create(_compiler->global_context, Logger::format("Class.%s", p_name.c_str()));

                std::vector<llvm::Type*> properties;
                for (auto const& pair : p_properties) {
                    properties.push_back(pair.second);
                }

                llvm_struct->setBody(properties);

                Scope* class_scope = new Scope(p_name, _compiler->get_source_info());
                ScopeValue* class_scope_val = new ScopeValue(class_scope, std::make_shared<llvm::StructType*>(llvm_struct));

                return std::make_unique<ScopeValue*>(class_scope_val);
            }

            void append_function_to_class(std::unique_ptr<ScopeValue*> p_class, std::string p_name, llvm::Type* p_return_type, std::map<std::string, llvm::Type*> p_args = {}) {

                std::vector<llvm::Type*> properties;
                std::vector<std::string> propertie_types;
                for (auto const& pair : p_args) {
                    properties.push_back(pair.second);
                    propertie_types.push_back(pair.second->getStructName());
                }

                auto function_prototype = llvm::FunctionType::get(p_return_type, properties, false);
                auto function = llvm::Function::Create(function_prototype, llvm::Function::ExternalLinkage, mangle(p_name.c_str(), propertie_types), _compiler->get_module().get());

                std::shared_ptr<llvm::Function*> function_ptr = std::make_shared<llvm::Function*>(function);\
                ScopeValue* scope_value = new ScopeValue(function_ptr);\
                std::unique_ptr<ScopeValue*> fn_value = std::make_unique<ScopeValue*>(scope_value);\
                (*p_class)->scope_value->set(p_name, std::move(fn_value));

            }

            ~SNAPI() {};

        private:
            Compiler* _compiler;
            SourceInfo* _source_info;
    };
}

#ifdef __cplusplus
}
#endif



#endif // __SNOWBALL_H_
