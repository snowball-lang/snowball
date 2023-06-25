
#include "../../ir/values/IndexExtract.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm-14/llvm/IR/Instructions.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::IndexExtract* index) {
    auto baseType = getLLVMType(index->getValue()->getType());
    auto v = build(index->getValue().get());
    // We add "1" becasue index #0 is a pointer to the virtual
    // table.
    // TODO: support for structs without vtable.
    auto i = index->getIndex() + 1;
    auto g = builder->CreateStructGEP(baseType->getPointerElementType(), v, i);
    this->value = builder->CreateLoad(g->getType()->getPointerElementType(), g);
}

} // namespace codegen
} // namespace snowball
