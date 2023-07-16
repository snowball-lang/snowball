
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
    setDebugInfoLoc(call);

    auto args = utils::vector_iterate<std::shared_ptr<ir::Value>, llvm::Value*>(
            call->getArguments(), [&](std::shared_ptr<ir::Value> arg) { return build(arg.get()); });
    llvm::CallInst* llvmCall = nullptr;
    llvm::Value* allocatedValue = nullptr;
    if (auto c = utils::dyn_cast<types::FunctionType>(calleeValue->getType());
        c != nullptr && utils::dyn_cast<types::BaseType>(c->getRetType())) {
        auto retType = c->getRetType();
        auto retTypeLLVM = getLLVMType(retType);
        // It's a function returning a type that's not a pointer
        // We need to allocate the value
        allocatedValue = builder->CreateAlloca(retTypeLLVM);
    }

    setDebugInfoLoc(call);
    if (auto c = utils::dyn_cast<ir::Func>(calleeValue); c != nullptr && c->isConstructor()) {
        auto instance = utils::cast<ir::ObjectInitialization>(call);
        isConstructor = true;
        assert(instance);
        assert(c->hasParent());
        auto p = c->getParent();

        llvm::Value* object = nullptr;
        if (instance->createdObject) {
            object = build(instance->createdObject.get());
            object = builder->CreatePointerCast(object, getLLVMType(instance->getType()));
        } else if (instance->initializeAtHeap) {
            object = allocateObject(p);
        } else {
            object = builder->CreateAlloca(getLLVMType(instance->getType()));
        }

        args.insert(args.begin(), object);
        llvmCall = builder->CreateCall((llvm::FunctionType*)callee->getType()->getPointerElementType(), callee, args);
        this->value = instance->initializeAtHeap
                ? object
                : builder->CreateLoad(object->getType()->getPointerElementType(), object);
    } else if (auto c = utils::dyn_cast<ir::Func>(calleeValue); c != nullptr && c->inVirtualTable()) {
        assert(c->hasParent());

        auto index = c->getVirtualIndex();
        auto parent = c->getParent();

        auto f = llvm::cast<llvm::Function>(callee);
        auto parentValue = args.at(/* self = */ 0);
        auto vtable = builder->CreateStructGEP(parentValue->getType()->getPointerElementType(), parentValue, 0);
        auto loadedVtable = builder->CreateLoad(vtable->getType()->getPointerElementType(), vtable);
        auto pointer = builder->CreateStructGEP(loadedVtable->getType()->getPointerElementType(), loadedVtable, index);
        auto pointerLoad = builder->CreateLoad(pointer->getType()->getPointerElementType(), pointer);
        llvmCall = builder->CreateCall((llvm::FunctionType*)pointerLoad->getType()->getPointerElementType(),
                                       (llvm::Function*)pointerLoad,
                                       args);
        if (allocatedValue) {
            builder->CreateStore(llvmCall, allocatedValue);
            this->value = allocatedValue;
        } else {
            this->value = llvmCall;
        }
    } else {
        // TODO: invoke if it's inside a try block
        llvmCall = builder->CreateCall((llvm::FunctionType*)callee->getType()->getPointerElementType(), callee, args);
        if (allocatedValue) {
            builder->CreateStore(llvmCall, allocatedValue);
            this->value = allocatedValue;
        } else {
            this->value = llvmCall;
        }
    }

    auto calledFunction = llvmCall->getCalledFunction();
    if (calledFunction) {
        auto attrSet = calledFunction->getAttributes();
        llvmCall->setAttributes(attrSet);
    }
}

} // namespace codegen
} // namespace snowball
