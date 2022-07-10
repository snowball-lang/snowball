
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

    struct SnowballBuildinTypes {
        std::shared_ptr<llvm::Function*> sn_number__init_i;
        std::shared_ptr<llvm::Function*> sn_number__sum_n_n;
        std::shared_ptr<llvm::StructType*> sn_number_struct;

        std::shared_ptr<llvm::Function*> sn_string__init_s;
        std::shared_ptr<llvm::StructType*> sn_string_struct;

        std::shared_ptr<llvm::Function*> sn_gc__alloca;
        std::shared_ptr<llvm::Function*> sn_gc__realloca;
    };

    llvm::Type* get_llvm_type_from_sn_type(BuildinTypes type, llvm::IRBuilder<> builder);
}

#endif // __SNOWBALL_BUILDIN_TYPES_H_
