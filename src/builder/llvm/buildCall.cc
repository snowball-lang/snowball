
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
    setDebugInfoLoc(call);

    auto args =
        utils::vector_iterate<std::shared_ptr<ir::Value>, ptr<llvm::Value>>(
            call->getArguments(),
            [&](std::shared_ptr<ir::Value> arg) { return build(arg.get()); });

    setDebugInfoLoc(call);
    if (auto c = utils::dyn_cast<ir::Func>(call->getCallee());
        c != nullptr && c->isConstructor()) {
        assert(c->hasParent());
        auto p = c->getParent();

        args.insert(args.begin(), allocateObject(p));
    } else if (auto c = utils::dyn_cast<ir::Func>(call->getCallee());
               c != nullptr && c->inVirtualTable()) {
        assert(c->hasParent());

        auto index  = c->getVirtualIndex();
        auto parent = c->getParent();

        auto f           = llvm::cast<llvm::Function>(callee);
        auto parentValue = args.at(/* self = */ 0);

        auto vtable = builder->CreateStructGEP(
            parentValue->getType()->getPointerElementType(), parentValue, 0);

        auto loadedVtable = builder->CreateLoad(
            vtable->getType()->getPointerElementType(), vtable);
        auto pointer = builder->CreateStructGEP(
            loadedVtable->getType()->getPointerElementType(), loadedVtable,
            index);

        auto pointerLoad = builder->CreateLoad(
            pointer->getType()->getPointerElementType(), pointer);
        this->value =
            builder->CreateCall((ptr<llvm::FunctionType>)pointerLoad->getType()
                                    ->getPointerElementType(),
                                (ptr<llvm::Function>)pointerLoad, args);
        return;
    }

    // TODO: invoke if it's inside a try block
    this->value = builder->CreateCall((ptr<llvm::FunctionType>)callee->getType()
        ->getPointerElementType(), callee, args);
}

} // namespace codegen
} // namespace snowball
