
#include <memory>
#include <algorithm>

#include <llvm/IR/IRBuilder.h>
#include "snowball/types.h"

namespace snowball {
    llvm::Type* get_llvm_type_from_sn_type(BuildinTypes type, llvm::IRBuilder<> builder) {
        switch (type)
        {
            #define RETURN_LLVM_TYPE_IF_SN_TYPE_IS(type, llvm_type) case BuildinTypes::type: {return llvm_type; };
                RETURN_LLVM_TYPE_IF_SN_TYPE_IS(NUMBER, builder.getInt64Ty())
            #undef RETURN_LLVM_TYPE_IF_SN_TYPE_IS
            default:
                // TODO: throw error
                abort();
        }
    }
}
