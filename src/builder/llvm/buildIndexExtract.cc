
#include "../../ir/values/IndexExtract.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ptr<ir::IndexExtract> index) {
    auto v = build(index->getValue().get());
    // We add "1" becasue index #0 is a pointer to the virtual
    // table.
    // TODO: support for structs without vtable.
    auto i = index->getIndex() + 1;
    auto g = builder->CreateStructGEP(v->getType()->getPointerElementType(), v, i);
    this->value = builder->CreateLoad(g->getType()->getPointerElementType(), g);
}

} // namespace codegen
} // namespace snowball
