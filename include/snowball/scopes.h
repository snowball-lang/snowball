
#include <map>
#include <string>
#include <experimental/optional>

#include "snowball/nodes.h"
#include "snowball/source_info.h"

#include "llvm/IR/Value.h"

#ifndef __SNOWBALL_ENVIROMENT_SCOPES_H_
#define __SNOWBALL_ENVIROMENT_SCOPES_H_

namespace snowball {

    struct ScopeValue;

    class Scope {

        public:
            Scope() {};
            Scope(std::string p_scope_name, SourceInfo* p_source_info);

            ScopeValue get(std::string p_name, Node p_node);
            void set(std::string p_name, ScopeValue p_value);
            std::experimental::optional<ScopeValue> get_optional(std::string p_name);

            ~Scope() {};

        private:

            std::string _scope_name;
            SourceInfo* _source_info;
            std::map<std::string, ScopeValue> _data;

    };

    enum ScopeType {
        SCOPE,
        LLVM,
    };

    struct ScopeValue {
        ScopeType type;

        llvm::Value* llvm_value;
        Scope scope_value;

        ~ScopeValue() = default;
    };

}

#endif // __SNOWBALL_ENVIROMENT_SCOPES_H_


