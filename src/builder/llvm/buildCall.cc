
#include "../../ir/values/Call.h"
#include "../../services/OperatorService.h"
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

    if (auto constructor = utils::dyn_cast<ir::Func>(call->getCallee());
        constructor->isConstructor()) {
        assert(constructor->hasParent());
        auto p = constructor->getParent();

        args.insert(args.begin(), allocateObject(p));
    }

    // TODO: invoke if it's inside a try block
    auto f      = llvm::cast<llvm::Function>(callee);
    this->value = builder->CreateCall(f, args);
}

} // namespace codegen
} // namespace snowball
