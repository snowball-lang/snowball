
#include <map>
#include <string>

#include "llvm/IR/Value.h"

#ifndef __SNOWBALL_ENVIROMENT_SCOPES_H_
#define __SNOWBALL_ENVIROMENT_SCOPES_H_

namespace snowball {

    struct ScopeValue;

    class Scope {

        public:
            Scope() {};
            ~Scope() {};

        private:

            std::string _name;
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


