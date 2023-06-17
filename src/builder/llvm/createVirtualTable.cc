
#include "../../ir/values/Call.h"
#include "../../services/OperatorService.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Metadata.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::GlobalVariable *LLVMBuilder::createVirtualTable(types::DefinedType *ty,
                                                      llvm::StructType *vtableType) {
    auto structName = (std::string)_SN_VTABLE_PREFIX + ty->getMangledName();

    std::vector<llvm::Constant *> functions;
    for (auto fn : ty->getVTable()) {
        fn->visit(this);
        auto c = llvm::cast<llvm::Constant>(this->value);

        functions.push_back(c);
    }

    module->getOrInsertGlobal(structName, vtableType);

    auto vTable = module->getNamedGlobal(structName);

    auto s = llvm::ConstantStruct::get(vtableType, functions);
    vTable->setInitializer(s);
    return vTable;
}

} // namespace codegen
} // namespace snowball
