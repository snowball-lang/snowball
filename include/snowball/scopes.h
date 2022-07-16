
#include <map>
#include <string>
#include <experimental/optional>

#include "nodes.h"
#include "source_info.h"

#include <llvm/IR/Value.h>
#include <llvm-10/llvm/IR/DerivedTypes.h>

#ifndef __SNOWBALL_ENVIROMENT_SCOPES_H_
#define __SNOWBALL_ENVIROMENT_SCOPES_H_

namespace snowball {

    struct ScopeValue;

    class Scope {

        public:
            Scope() {};
            Scope(std::string p_scope_name, SourceInfo* p_source_info);

            ScopeValue* get(std::string p_name, Node* p_node, std::string p_o_name = "");
            void set(std::string p_name, std::unique_ptr<ScopeValue*> p_value);

            bool item_exists(std::string p_name);

            std::string name() { return _scope_name; }

            std::map<std::string, std::unique_ptr<ScopeValue*>> data() { return std::move(_data); }

            ~Scope() {};

        private:

            std::string _scope_name;
            SourceInfo* _source_info;
            std::map<std::string, std::unique_ptr<ScopeValue*>> _data;

    };

    enum ScopeType {
        SCOPE,
        CLASS,
        MODULE,
        FUNC,
        LLVM,
    };

    typedef struct ScopeValue {
        ScopeType type;

        std::shared_ptr<llvm::Value*> llvm_value;
        std::shared_ptr<llvm::StructType*> llvm_struct;
        std::shared_ptr<llvm::Function*> llvm_function;

        // Function params
        bool isStaticFunction = false;

        Scope* scope_value;

        ScopeValue(std::shared_ptr<llvm::Value*> p_value) {
            type = ScopeType::LLVM;
            llvm_value = p_value;
        }

        ScopeValue(std::shared_ptr<llvm::Function*> p_value) {
            type = ScopeType::FUNC;
            llvm_function = p_value;
        }

        ScopeValue(Scope* p_value, std::shared_ptr<llvm::StructType*> p_struct) {
            type = ScopeType::CLASS;
            llvm_struct = p_struct;
            scope_value = p_value;
        }

        ScopeValue(Scope* p_value) {
            type = ScopeType::SCOPE;
            scope_value = p_value;
        }
    } ScopeValue;

}

#endif // __SNOWBALL_ENVIROMENT_SCOPES_H_


