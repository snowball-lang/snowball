
#include "../../ast/errors/error.h"
#include "../../visitors/Transformer.h"
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

namespace {
void setDereferenceableAttribute(llvm::Argument& arg, unsigned bytes) {
  auto dereferenceable = llvm::Attribute::get(arg.getContext(), llvm::Attribute::Dereferenceable, bytes);
  auto noundef = llvm::Attribute::get(arg.getContext(), llvm::Attribute::NoUndef);
  auto nonull = llvm::Attribute::get(arg.getContext(), llvm::Attribute::NonNull);
  arg.addAttr(dereferenceable);
  arg.addAttr(noundef);
  arg.addAttr(nonull);
}
} // namespace

llvm::Function* LLVMBuilder::createLLVMFunction(ir::Func* func) {
  auto innerFnType = Syntax::Transformer::getFunctionType(func->getType());
  assert(innerFnType != nullptr);

  if (auto x = module->getFunction(func->getMangle()); x != nullptr) { return x; }

  auto fnType = llvm::cast<llvm::FunctionType>(getLLVMFunctionType(innerFnType, func));
  if (func->getMangle() == "main") {
    fnType = llvm::FunctionType::get(builder->getInt32Ty(), {builder->getInt32Ty(), builder->getInt8PtrTy()->getPointerTo()}, false);
  }
  auto name = func->getMangle();
  auto fn = llvm::Function::Create(
          fnType,
          ((func->isStatic() && (!func->hasParent())) ||
           (func->hasAttribute(Attributes::INTERNAL_LINKAGE) && !func->isDeclaration())) ?
                  llvm::Function::InternalLinkage :
                  llvm::Function::ExternalLinkage,
          name,
          module.get()
  );

  auto callee = (llvm::Function*) fn;
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

  bool retIsArg = utils::is<types::BaseType>(func->getRetTy());
  if (retIsArg) {
    auto arg = fn->arg_begin();
    auto attrBuilder = llvm::AttrBuilder(*context);
    attrBuilder.addStructRetAttr(getLLVMType(func->getRetTy()));
    attrBuilder.addAttribute(llvm::Attribute::NoUndef);
    attrBuilder.addAttribute(llvm::Attribute::NonNull);
    arg->addAttrs(attrBuilder);
  }

  for (int i = 0; i < (int)func->getArgs().size(); ++i) {
    auto llvmArg = fn->arg_begin() + i + retIsArg + func->isAnon();
    auto arg = utils::at(func->getArgs(), i);
    if (utils::is<types::ReferenceType>((arg).second->getType())) {
      setDereferenceableAttribute(*llvmArg, (arg).second->getType()->sizeOf());
    }
  }

  return callee;
}

} // namespace codegen
} // namespace snowball
