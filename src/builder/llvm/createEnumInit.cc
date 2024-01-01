
#include "../../ir/values/WhileLoop.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"
#include "../../ir/values/EnumInit.h"
#include "../../ir/values/Call.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::Value* LLVMBuilder::createEnumInit(ir::Call* call) {
    auto enumInit = utils::dyn_cast<ir::EnumInit>(call->getCallee());
    auto enumType = utils::cast<types::EnumType>(enumInit->getType());
    auto enumTypeLLVM = createEnumFieldType(enumType, enumInit->getName());

    int idx = 0;
    for (auto field : enumType->getFields()) {
        if (field->name == enumInit->getName()) break;
        idx++;
    }

    auto enumInitLLVM = createAlloca(enumTypeLLVM, ".enum-init");
    auto enumInitPtr = builder->CreateStructGEP(enumTypeLLVM, enumInitLLVM, 0, ".enum-init-ptr");
    builder->CreateStore(builder->getInt8(idx), enumInitPtr);

    int i = 1;
    for (auto& arg : call->getArguments()) {
        auto gep = builder->CreateStructGEP(enumTypeLLVM, enumInitLLVM, i, ".enum-init-gep");
        builder->CreateStore(expr(arg.get()), gep);
        i++;
    }
}

} // namespace codegen
} // namespace snowball
