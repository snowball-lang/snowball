
#include "scopes.h"

#include <memory>
#include <algorithm>

#include <llvm/IR/IRBuilder.h>

#ifndef __SNOWBALL_BUILDIN_TYPES_H_
#define __SNOWBALL_BUILDIN_TYPES_H_

namespace snowball {
    enum BuildinTypes {
        NUMBER,
        STRING,
    };

    llvm::Type* get_llvm_type_from_sn_type(BuildinTypes type, llvm::IRBuilder<> builder);
    llvm::Value* get_alloca(llvm::Module* p_module, llvm::IRBuilder<> p_builder);
}

#endif // __SNOWBALL_BUILDIN_TYPES_H_
