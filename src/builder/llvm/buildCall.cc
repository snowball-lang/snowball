
#include "../../ir/values/Call.h"
#include "../../ir/values/Dereference.h"
#include "../../ir/values/ReferenceTo.h"
#include "../../services/OperatorService.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::Call* call) {
    bool isConstructor = false;
    if (buildOperator(call)) return; // TODO: maybe jump to cleanup?

    auto calleeValue = call->getCallee();
    auto callee = build(calleeValue.get());
    auto fnType = utils::cast<types::FunctionType>(calleeValue->getType());
    auto calleeType = getLLVMFunctionType(fnType);
    setDebugInfoLoc(call);

    auto args = utils::vector_iterate<std::shared_ptr<ir::Value>, llvm::Value*>(
            call->getArguments(), [&](std::shared_ptr<ir::Value> arg) { return build(arg.get()); });
    llvm::Value* llvmCall = nullptr;
    llvm::Value* allocatedValue = nullptr;
    llvm::Type* allocatedValueType = nullptr;
    if (auto c = utils::cast<types::FunctionType>(calleeValue->getType());
        c != nullptr && utils::cast<types::BaseType>(c->getRetType())) {
        auto retType = c->getRetType();
        allocatedValueType = getLLVMType(retType);
        // It's a function returning a type that's not a pointer
        // We need to allocate the value
        allocatedValue = builder->CreateAlloca(allocatedValueType);
    }

    setDebugInfoLoc(call);
    if (auto c = utils::dyn_cast<ir::Func>(calleeValue); c != nullptr && c->isConstructor()) {
        auto instance = utils::cast<ir::ObjectInitialization>(call);
        auto instanceType = getLLVMType(instance->getType());
        isConstructor = true;
        assert(instance);
        assert(c->hasParent());
        auto p = c->getParent();

        llvm::Value* object = nullptr;
        if (instance->createdObject) {
            object = build(instance->createdObject.get());
            object = builder->CreatePointerCast(object, instanceType);
        } else {
            object = allocateObject(p, instance->initializeAtHeap);
        }

        args.insert(args.begin(), object);
        llvmCall = createCall(calleeType, callee, args);
        this->value = instance->initializeAtHeap
                ? object
                : builder->CreateLoad(instanceType, object);;
    } else if (auto c = utils::dyn_cast<ir::Func>(calleeValue); c != nullptr && c->inVirtualTable()) {
        assert(c->hasParent());

        auto index = c->getVirtualIndex();
        auto parent = c->getParent();

        auto f = llvm::cast<llvm::Function>(callee);
        auto parentValue = args.at(/* self = */ 0);
        auto parentType = call->getArguments().at(/* self = */ 0)->getType();
        auto loadedVtable = builder->CreateLoad(parentValue->getType(), parentValue);
        auto pointer = builder->CreateInBoundsGEP(loadedVtable->getType(), loadedVtable, {builder->getInt32(index)});
        auto calleePointer = builder->CreateLoad(pointer->getType(), pointer);
        llvmCall = createCall(calleeType,
                                       (llvm::Function*)calleePointer,
                                       args);
        if (allocatedValue) {
            builder->CreateStore(llvmCall, allocatedValue);
            this->value = allocatedValue;
        } else {
            this->value = llvmCall;
        }
    } else {
        // TODO: invoke if it's inside a try block
        llvmCall = createCall(calleeType, callee, args);
        if (allocatedValue) {
            builder->CreateStore(llvmCall, allocatedValue);
            this->value = builder->CreateLoad(allocatedValueType, allocatedValue);
        } else {
            this->value = llvmCall;
        }
    }

    if (llvm::isa<llvm::CallInst>(llvmCall)) {
        auto call = llvm::cast<llvm::CallInst>(llvmCall);
        auto calledFunction = call->getCalledFunction();
        if (calledFunction) {
            auto attrSet = calledFunction->getAttributes();
            call->setAttributes(attrSet);
        }
    } else if (llvm::isa<llvm::InvokeInst>(llvmCall)) {
        auto call = llvm::cast<llvm::InvokeInst>(llvmCall);
        auto calledFunction = call->getCalledFunction();
        if (calledFunction) {
            auto attrSet = calledFunction->getAttributes();
            call->setAttributes(attrSet);
        }
    } else {
        assert(false);
    }
}

} // namespace codegen
} // namespace snowball
