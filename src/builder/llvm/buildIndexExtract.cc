
#include "../../ir/values/IndexExtract.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::IndexExtract* index) {
  auto indexValue = index->getValue();
  auto valueType = indexValue->getType();
  auto basedType = valueType;
  if (auto x = utils::cast<types::ReferenceType>(basedType)) basedType = x->getPointedType();
  auto defiendType = utils::cast<types::DefinedType>(basedType);
  if (auto alias = utils::cast<types::TypeAlias>(basedType)) {
    assert(!"Found a local type alias in the index extract!");
  }
  assert(defiendType);
  auto v = build(indexValue.get());
  // We add "1" becasue index #0 is a pointer to the virtual
  // table.
  // TODO: support for structs without vtable.
  auto i = index->getIndex() + defiendType->hasVtable();
  auto extract = builder->CreateStructGEP(getLLVMType(basedType), v, i);
  this->value = builder->CreateLoad(getLLVMType(index->getType()), extract);
}

} // namespace codegen
} // namespace snowball
