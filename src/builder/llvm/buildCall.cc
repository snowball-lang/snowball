
#include "../../ir/values/Call.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm-14/llvm/IR/DerivedTypes.h>
#include <llvm-14/llvm/IR/Function.h>
#include <llvm-14/llvm/IR/Type.h>
#include <llvm-14/llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ptr<ir::Call> call) {
    auto callee = build(call->getCallee().get());

    auto args =
        utils::vector_iterate<std::shared_ptr<ir::Value>, ptr<llvm::Value>>(
            call->getArguments(),
            [&](std::shared_ptr<ir::Value> arg) { return build(arg.get()); });

    // TODO: invoke if it's inside a try block
    this->value = builder->CreateCall(llvm::cast<llvm::Function>(callee), args);
}

} // namespace codegen
} // namespace snowball
