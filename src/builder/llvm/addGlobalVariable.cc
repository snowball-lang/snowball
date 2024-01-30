#include "../../ir/values/Constants.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::addGlobalVariable(std::shared_ptr<ir::VariableDeclaration> var, types::DefinedType* parent) {
  auto ty = getLLVMType(var->getType());
  std::string name;
  if (parent) {
    name = "const." + parent->getUUID() + ":" + utils::gen_random<32>() + ":" + var->getIdentifier();
  } else {
    name = "gvar." + iModule->getUniqueName() + ":" + utils::gen_random<32>() + ":" + var->getIdentifier();
  }

  auto srcInfo = var->getDBGInfo();
  auto file = dbg.getFile(var->getSourceInfo()->getPath());
  auto debugVar = dbg.builder->createGlobalVariableExpression(
          dbg.unit, var->getIdentifier(), var->getIdentifier(), file, srcInfo->line, getDIType(var->getType()), var->isExternDecl()
  );

  if (var->isExternDecl()) {
    auto gvar = new llvm::GlobalVariable(
            /*Module=*/*module,
            /*Type=*/ty,
            /*isConstant=*/!var->getVariable()->isMutable(),
            /*Linkage=*/llvm::GlobalValue::ExternalLinkage,
            /*Initializer=*/nullptr, 
            /*Name=*/var->getIdentifier()
    );
    ctx->addSymbol(var->getId(), gvar);
    gvar->addDebugInfo(debugVar);
    return;
  }

  if (utils::dyn_cast<ir::ConstantValue>(var->getValue())) {
    auto c = build(var->getValue().get());
    auto gvar = new llvm::GlobalVariable(
            /*Module=*/*module,
            /*Type=*/ty,
            /*isConstant=*/!var->getVariable()->isMutable(),
            /*Linkage=*/llvm::GlobalValue::InternalLinkage,
            /*Initializer=*/llvm::cast<llvm::Constant>(c), // has initializer, specified below
            /*Name=*/name
    );
    gvar->setDSOLocal(true);
    ctx->addSymbol(var->getId(), gvar);
    gvar->addDebugInfo(debugVar);
    return;
  }

  auto ctor = getGlobalCTOR();

  auto& ctorBody = ctor->getEntryBlock();
  builder->SetInsertPoint(&ctorBody);

  auto gvar = new llvm::GlobalVariable(
          /*Module=*/*module,
          /*Type=*/ty,
          /*isConstant=*/0,// !var->getVariable()->isMutable(), note: this doesn't work because we are not fully detecting constant values (2 + 2 is not a constant)
          /*Linkage=*/llvm::GlobalValue::InternalLinkage,
          /*Initializer=*/llvm::Constant::getNullValue(ty), // has initializer, specified below
          /*Name=*/name
  );
  gvar->setDSOLocal(true);
  ctx->addSymbol(var->getId(), gvar);
  ctx->setCurrentFunction(ctor);

  auto val = expr(var->getValue().get());

  builder->CreateStore(val, gvar);
  ctx->clearCurrentFunction();
  gvar->addDebugInfo(debugVar);
}

} // namespace codegen
} // namespace snowball
