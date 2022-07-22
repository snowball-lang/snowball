
#include <llvm-10/llvm/IR/DerivedTypes.h>
#include <memory>
#include <vector>
#include <algorithm>

#include <llvm/IR/IRBuilder.h>

#include "snowball/types.h"
#include "snowball/constants.h"
#include "snowball/utils/mangle.h"

namespace snowball {

    llvm::Value* get_alloca(llvm::Module* p_module, llvm::IRBuilder<> p_builder) {
        llvm::FunctionType* function_type = llvm::FunctionType::get(p_builder.getInt8PtrTy(), { p_builder.getInt32Ty() }, false);
        return p_module->getOrInsertFunction(mangle("__sn__alloca__", { "i32" }, true), function_type).getCallee();
    }

    llvm::Type* get_llvm_type_from_sn_type(BuildinTypes type, llvm::IRBuilder<> builder) {

        switch (type)
        {
            #define RETURN_LLVM_TYPE_IF_SN_TYPE_IS(type, llvm_type) case BuildinTypes::type: {return llvm_type; };
                #if _SNOWBALL_ENABLE_INT64
                    RETURN_LLVM_TYPE_IF_SN_TYPE_IS(NUMBER, builder.getInt64Ty())
                #else
                    RETURN_LLVM_TYPE_IF_SN_TYPE_IS(NUMBER, builder.getInt32Ty())
                #endif
                RETURN_LLVM_TYPE_IF_SN_TYPE_IS(STRING, builder.getInt8PtrTy())
            #undef RETURN_LLVM_TYPE_IF_SN_TYPE_IS
            default:
                // TODO: throw error
                abort();
        }
    }
}
