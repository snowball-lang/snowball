
#include "../../ast/errors/error.h"
#include "../../ir/values/Argument.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>

using namespace snowball::utils;

namespace snowball {
namespace codegen {

llvm::Function* LLVMBuilder::createLLVMFunction(ir::Func* func) {
  auto innerFnType = cast<types::FunctionType>(func->getType());
  assert(innerFnType != nullptr);

  if (auto x = module->getFunction(func->getMangle()); x != nullptr) { return x; }

  auto fnType = llvm::cast<llvm::FunctionType>(getLLVMFunctionType(innerFnType));
  auto name = func->getMangle();
  auto fn = llvm::Function::Create(fnType,
          ((func->isStatic() && (!func->hasParent())) || func->hasAttribute(Attributes::INTERNAL_LINKAGE))
                  ? llvm::Function::InternalLinkage
                  : llvm::Function::ExternalLinkage,
          name,
          module.get());

  auto callee = (llvm::Function*)fn;
  auto attrSet = callee->getAttributes();

  if (func->hasAttribute(Attributes::INLINE)) {
    auto newAttrSet = attrSet.addFnAttribute(callee->getContext(), llvm::Attribute::AlwaysInline);
    callee->setAttributes(newAttrSet);
    // TODO: other attributes
  } else if (func->hasAttribute(Attributes::NO_INLINE)) {
    auto newAttrSet = attrSet.addFnAttribute(callee->getContext(), llvm::Attribute::NoInline);
    callee->setAttributes(newAttrSet);
  }

  if (!func->isDeclaration()) {
    auto DISubprogram = getDISubprogramForFunc(func);
    callee->setSubprogram(DISubprogram);
  }

  return callee;
}

} // namespace codegen
} // namespace snowball
