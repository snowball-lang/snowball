
#include "../../ast/errors/error.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <memory>

using namespace snowball::utils;

namespace snowball {
namespace codegen {

void LLVMBuilder::setPersonalityFunction(llvm::Function* func) {
  auto ty = llvm::FunctionType::get(
  builder->getInt32Ty(), {
    builder->getInt32Ty(),
    builder->getInt32Ty(),
    builder->getInt64Ty(),
    builder->getInt8PtrTy(),
    builder->getInt8PtrTy()
  },
  false
            );
  auto c = module->getOrInsertFunction(getSharedLibraryName("sn.eh.personality"), ty).getCallee();
  auto f = llvm::cast<llvm::Constant>(c);
  func->setPersonalityFn(f);
}

} // namespace codegen
} // namespace snowball
