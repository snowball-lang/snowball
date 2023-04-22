#include "../../utils/utils.h"
#include "../../ir/values/Constants.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::addGlobalVariable(std::shared_ptr<ir::VariableDeclaration> var) {
    auto ty = getLLVMType(var->getType());
    std::string name = "gvar." + iModule->getUniqueName() + "::" + var->getIdentifier();
    if (utils::dyn_cast<ir::ConstantValue>(var->getValue())) {
        auto c = build(var->getValue().get());
        auto gvar = new llvm::GlobalVariable(/*Module=*/*module,
            /*Type=*/ty,
            /*isConstant=*/!var->isMutable(),
            /*Linkage=*/llvm::GlobalValue::ExternalLinkage,
            /*Initializer=*/0, // has initializer, specified below
            /*Name=*/name);
        gvar->setInitializer(llvm::cast<llvm::Constant>(c));
        return;
    }

    auto ctor = getGlobalCTOR();

    auto& ctorBody = ctor->getEntryBlock();
    builder->SetInsertPoint(ctorBody.back().getNextNode());

    auto gvar = new llvm::GlobalVariable(/*Module=*/*module,
        /*Type=*/ty,
        /*isConstant=*/!var->isMutable(),
        /*Linkage=*/llvm::GlobalValue::CommonLinkage,
        /*Initializer=*/0, // has initializer, specified below
        /*Name=*/name);

    gvar->setInitializer(llvm::Constant::getNullValue(ty));
    auto val = build(var->getValue().get());
    builder->CreateStore(val, gvar);
}

} // namespace codegen
} // namespace snowball