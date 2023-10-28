
#include "../../ir/values/Constants.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::StringValue* value) {
  ctx->doNotLoadInMemory = true;
  auto str = builder->CreateGlobalStringPtr(value->getConstantValue(), ".str__" + utils::gen_random<30>());
  auto arr = llvm::ArrayType::get(builder->getInt8Ty(), value->getConstantValue().size() + 1);
  this->value = builder->CreateConstInBoundsGEP1_32(arr, str, 0);
}

void LLVMBuilder::visit(ir::BooleanValue* value) { this->value = builder->getInt1(value->getConstantValue()); }

void LLVMBuilder::visit(ir::CharValue* value) { this->value = builder->getInt8(value->getConstantValue()); }

void LLVMBuilder::visit(ir::NumberValue* value) { this->value = builder->getInt32(value->getConstantValue()); }

void LLVMBuilder::visit(ir::FloatValue* value) {
  this->value = llvm::ConstantFP::get(builder->getDoubleTy(), value->getConstantValue());
}

} // namespace codegen
} // namespace snowball
