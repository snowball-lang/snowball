
#include "../../ir/values/Constants.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm-14/llvm/IR/Type.h>
#include <llvm-14/llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ptr<ir::StringValue> value) {
    this->value =
        builder->CreateGlobalString(value->getConstantValue(), ".str");
}

void LLVMBuilder::visit(ptr<ir::BooleanValue> value) {
    this->value = builder->getInt1(value->getConstantValue());
}

void LLVMBuilder::visit(ptr<ir::NumberValue> value) {
    this->value = builder->getInt32(value->getConstantValue());
}

void LLVMBuilder::visit(ptr<ir::FloatValue> value) {
    this->value = llvm::ConstantFP::get(builder->getDoubleTy(),
                                        value->getConstantValue());
}

void LLVMBuilder::visit(ptr<ir::NullValue> value) {
    assert(false && "TODO: null value");
}

} // namespace codegen
} // namespace snowball
