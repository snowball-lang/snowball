
#include "../../ir/values/Constants.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::StringValue *value) {
    this->value =
        builder->CreateGlobalStringPtr(value->getConstantValue(), ".str");
}

void LLVMBuilder::visit(ir::BooleanValue *value) {
    this->value = builder->getInt1(value->getConstantValue());
}

void LLVMBuilder::visit(ir::CharValue *value) {
    this->value = builder->getInt8(value->getConstantValue());
}

void LLVMBuilder::visit(ir::NumberValue *value) {
    this->value = builder->getInt32(value->getConstantValue());
}

void LLVMBuilder::visit(ir::FloatValue *value) {
    this->value = llvm::ConstantFP::get(builder->getDoubleTy(),
                                        value->getConstantValue());
}

void LLVMBuilder::visit(ir::NullValue *value) {
    assert(false && "TODO: null value");
}

} // namespace codegen
} // namespace snowball
