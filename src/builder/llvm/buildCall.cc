
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
          call->getArguments(), [&](std::shared_ptr<ir::Value> arg) { return load(build(arg.get()), arg->getType()); });
  llvm::Value* llvmCall = nullptr;
  llvm::Value* allocatedValue = nullptr;
  llvm::Type* allocatedValueType = nullptr;
  if (auto c = utils::cast<types::FunctionType>(calleeValue->getType());
          c != nullptr && utils::cast<types::BaseType>(c->getRetType())) {
    auto retType = c->getRetType();
    allocatedValueType = getLLVMType(retType);
    // It's a function returning a type that's not a pointer
    // We need to allocate the value
    allocatedValue = createAlloca(allocatedValueType);
    args.insert(args.begin(), allocatedValue);
  }

  setDebugInfoLoc(call);
  if (auto c = utils::dyn_cast<ir::Func>(calleeValue); c != nullptr && c->isConstructor()) {
    auto instance = utils::cast<ir::ObjectInitialization>(call);
    auto instanceType = getLLVMType(instance->getType());
    isConstructor = true;
    assert(instance);
    assert(c->hasParent());
    auto parent = c->getParent();

    llvm::Value* object = nullptr;
    if (instance->createdObject) {
      object = build(instance->createdObject.get());
    } else {
      auto classType = utils::cast<types::DefinedType>(parent);
      assert(classType && "Class type is not a defined type!");
      object = allocateObject(classType);
    }

    args.insert(args.begin(), object);
    setDebugInfoLoc(call);
    llvmCall = createCall(calleeType, callee, args);
    this->value = object;
  } else if (auto c = utils::dyn_cast<ir::Func>(calleeValue); c != nullptr && c->inVirtualTable()) {
    assert(c->hasParent());

    auto index = c->getVirtualIndex(); // avoid class info
    auto parent = c->getParent();

    auto f = llvm::cast<llvm::Function>(callee);
    // note: allocatedValue != nullptr is because there are 2 possible cases:
    // 1. The function returns a type that's not a pointer (meaning self is at index 1)
    // 2. The function does not return a type that's not a pointer (meaning self is at index 0)
    auto parentValue = args.at(/* self = */ allocatedValue != nullptr);
    auto parentIR = call->getArguments().at(/* self = */ 0);
    auto parentType = parentIR->getType();
    auto definedType = utils::cast<types::DefinedType>(parentType);
    if (auto x = utils::cast<types::ReferenceType>(parentType))
      definedType = utils::cast<types::DefinedType>(x->getPointedType());
    else
      assert(false && "Parent type is not a reference type!");
    assert(definedType && "Parent type is not a defined type!");
    getVtableType(definedType); // generate vtable type (if not generated yet)
    auto vtableType = ctx->getVtableTy(definedType->getId());
    // vtable structure:
    // class instance = { [0] = vtable, ... }
    // vtable = { [size x ptr] } { [0] = fn1, [1] = fn2, ... } }
    auto vtable = builder->CreateLoad(vtableType->getPointerTo(),
            builder->CreateConstInBoundsGEP1_32(
                    vtableType, builder->CreatePointerCast(parentValue, vtableType->getPointerTo()), 0));
    auto fn = builder->CreateLoad(vtableType->getPointerTo(),
            builder->CreateConstInBoundsGEP2_32(vtableType->elements()[0], vtable, 0, index));
    builder->CreateAssumption(builder->CreateIsNotNull(fn));
    llvmCall = createCall(calleeType, (llvm::Function*)fn, args);
    if (allocatedValue) {
      // builder->CreateStore(llvmCall, allocatedValue);
      // auto alloca = createAlloca(allocatedValueType);
      // builder->CreateStore(llvmCall, alloca);
      // builder->CreateMemCpy(alloca, llvm::MaybeAlign(), allocatedValue, llvm::MaybeAlign(),
      //         module->getDataLayout().getTypeAllocSize(allocatedValueType), 0);
      // this->value = allocatedValue;
      this->value = builder->CreateLoad(allocatedValueType, allocatedValue);
    } else {
      this->value = llvmCall;
    }
  } else {
    if (!llvm::isa<llvm::Function>(callee)) {
      // we are calling a value instead of a direct function.
      // this means we need to dereference the value first
      // and then call it.
      callee = load(callee, fnType);
    }
    llvmCall = createCall(calleeType, callee, args);
    if (allocatedValue) {
      // builder->CreateStore(llvmCall, allocatedValue);
      this->value = builder->CreateLoad(allocatedValueType, allocatedValue);
    } else {
      this->value = llvmCall;
    }
  }

#define SET_CALL_ATTRIBUTES(type)                                                                                      \
  if (llvm::isa<type>(llvmCall)) {                                                                                     \
    auto call = llvm::cast<type>(llvmCall);                                                                            \
    auto calledFunction = call->getCalledFunction();                                                                   \
    bool retIsReference = false;                                                                                       \
    if (auto f = utils::dyn_cast<ir::Func>(calleeValue)) {                                                             \
      auto valBackup = this->value;                                                                                    \
      retIsReference = utils::cast<types::ReferenceType>(f->getRetTy()) != nullptr;                                    \
      calledFunction = llvm::cast<llvm::Function>(build(f.get()));                                                     \
      this->value = valBackup;                                                                                         \
    }                                                                                                                  \
    if (calledFunction) {                                                                                              \
      auto attrSet = calledFunction->getAttributes();                                                                  \
      if (retIsReference) {                                                                                            \
        attrSet = attrSet.addRetAttribute(*context, llvm::Attribute::NonNull);                                         \
      }                                                                                                                \
      call->setAttributes(attrSet);                                                                                    \
    }                                                                                                                  \
  }

  SET_CALL_ATTRIBUTES(llvm::CallInst)
  else SET_CALL_ATTRIBUTES(llvm::InvokeInst) else { assert(false); }
}

} // namespace codegen
} // namespace snowball
