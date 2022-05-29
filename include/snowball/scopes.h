
#include <map>
#include <string>
#include <experimental/optional>

#include "llvm/IR/Value.h"

#ifndef __SNOWBALL_ENVIROMENT_SCOPES_H_
#define __SNOWBALL_ENVIROMENT_SCOPES_H_

namespace snowball {

    struct ScopeValue;

    class Scope {

        public:
            Scope() {};
            Scope(std::string p_scope_name, ScopeValue p_scope_value);

            ScopeValue get(std::string p_name);
            void set(std::string p_name, ScopeValue p_value);
            std::experimental::optional<ScopeValue> get_optional(std::string p_name);

            ~Scope() {};

        private:

            std::map<std::string, ScopeValue> _data;

    };

    enum ScopeType {
        SCOPE,
        LLVM,

        OTHER
    };

    struct ScopeValue {
        ScopeType type;

        llvm::Value* llvm_value;
        Scope scope_value;

        ~ScopeValue() = default;
    };

}

#endif // __SNOWBALL_ENVIROMENT_SCOPES_H_


