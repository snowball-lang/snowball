
#include "../../ir/values/Call.h"
#include "../../services/OperatorService.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ptr<ir::Call> call) {
    auto callee = build(call->getCallee().get());

    auto args =
        utils::vector_iterate<std::shared_ptr<ir::Value>, ptr<llvm::Value>>(
            call->getArguments(),
            [&](std::shared_ptr<ir::Value> arg) { return build(arg.get()); });

    if (auto c = utils::dyn_cast<ir::Func>(call->getCallee());
        c->isConstructor()) {
        assert(c->hasParent());
        auto p = c->getParent();

        args.insert(args.begin(), allocateObject(p));
    }

    // TODO: invoke if it's inside a try block
    auto f      = llvm::cast<llvm::Function>(callee);
    this->value = builder->CreateCall(f, args);
}

} // namespace codegen
} // namespace snowball
