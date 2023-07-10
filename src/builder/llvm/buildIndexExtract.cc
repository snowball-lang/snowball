
#include "../../ir/values/IndexExtract.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::IndexExtract* index) {
    auto valueType = index->getValue()->getType();
    if (auto x = utils::dyn_cast<types::ReferenceType>(valueType)) valueType = x->getBaseType();
    auto defiendType = utils::dyn_cast<types::DefinedType>(valueType);
    if (auto alias = utils::dyn_cast<types::TypeAlias>(valueType)) {
        assert( !"Found a local type alias in the index extract!" );
    }
    assert(defiendType);
    auto baseType = getLLVMType(valueType);
    auto v = build(index->getValue().get());
    // We add "1" becasue index #0 is a pointer to the virtual
    // table.
    // TODO: support for structs without vtable.
    auto i = index->getIndex() + defiendType->hasVtable();
    auto g = builder->CreateStructGEP(
            baseType->isPointerTy() ? baseType->getPointerElementType() : baseType, v, i);
    this->value = builder->CreateLoad(g->getType()->getPointerElementType(), g);
}

} // namespace codegen
} // namespace snowball
