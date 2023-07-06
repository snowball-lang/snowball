
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::initializeRuntime() {
    auto ty = llvm::FunctionType::get(builder->getVoidTy(), {}, false);
    auto f = llvm::cast<llvm::Function>(
            module->getOrInsertFunction("sn.runtime.initialize", ty).getCallee());
    f->addFnAttr(llvm::Attribute::AlwaysInline);
    auto mainFunction = module->getFunction(_SNOWBALL_FUNCTION_ENTRY);
    bool buildReturn = false;
    llvm::BasicBlock* body;
    if (mainFunction) {
        body = &mainFunction->front();
    } else {
        auto fnType = llvm::FunctionType::get(builder->getInt32Ty(), {});
        mainFunction =
                (llvm::Function*)module->getOrInsertFunction(_SNOWBALL_FUNCTION_ENTRY, fnType)
                        .getCallee();
        body = llvm::BasicBlock::Create(builder->getContext(), "entry", mainFunction);
        buildReturn = true;
    }

    builder->SetInsertPoint(body);
    llvm::CallInst::Create(f, {}, "", &body->front());
    if (buildReturn) builder->CreateRet(builder->getInt32(0));
}

} // namespace codegen
} // namespace snowball
