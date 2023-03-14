
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm-14/llvm/IR/DerivedTypes.h>
#include <llvm-14/llvm/IR/Type.h>
#include <llvm-14/llvm/IR/Value.h>

using namespace snowball::utils;

namespace snowball {
namespace codegen {

ptr<llvm::Function> LLVMBuilder::createLLVMFunction(ptr<ir::Func> func) {
    auto innerFnType = cast<types::FunctionType>(func->getType().get());
    assert(innerFnType != nullptr);

    auto fnType =
        llvm::cast<llvm::FunctionType>(getLLVMFunctionType(innerFnType));

    auto name = func->getMangle();

    auto fn     = module->getOrInsertFunction(name, fnType);
    auto callee = llvm::cast<llvm::Function>(fn.getCallee());

    if (!ir::Func::isExternal(func->getMangle()) ||
        func->getMangle() == "main") {
        callee->setSubprogram(getDISubprogramForFunc(func));
    }

    return callee;
}

} // namespace codegen
} // namespace snowball