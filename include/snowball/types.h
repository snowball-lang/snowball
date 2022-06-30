
#include <memory>
#include <algorithm>

#include <llvm/IR/IRBuilder.h>

#ifndef __SNOWBALL_BUILDIN_TYPES_H_
#define __SNOWBALL_BUILDIN_TYPES_H_

namespace snowball {
    enum BuildinTypes {
        NUMBER,
    };

    struct SnowballBuildinTypes {
        llvm::Function* sn_number__new;
        llvm::Function* sn_number__sum;
    };

    llvm::Type* get_llvm_type_from_sn_type(BuildinTypes type, llvm::IRBuilder<> builder);
}

#endif // __SNOWBALL_BUILDIN_TYPES_H_
