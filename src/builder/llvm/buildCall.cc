
#include "../../ir/values/Call.h"
#include "../../ir/values/Dereference.h"
#include "../../ir/values/ReferenceTo.h"
#include "../../services/OperatorService.h"
#include "../../services/ImportService.h"
#include "../../visitors/Transformer.h"
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
  if (utils::is<ir::ZeroInitialized>(call)) {
    this->value = llvm::Constant::getNullValue(getLLVMType(call->getType()));
    return;
  }

  if (utils::is<ir::ObjectInitialization>(call)) {
    auto instance = utils::cast<ir::ObjectInitialization>(call);
    if (instance->isConstantStruct()) {
      auto instanceType = getLLVMType(instance->getType());
      assert(utils::cast<types::DefinedType>(instance->getType()) && "Instance type is not a defined type!");
      auto alloca = ctx->callStoreValue ? ctx->callStoreValue : createAlloca(instanceType);
      int i = 0;
      for (auto& arg : instance->getArguments()) {
        auto gep = builder->CreateStructGEP(instanceType, alloca, i++);
        auto value = expr(arg.get());
        builder->CreateStore(value, gep); 
      }
      this->value = builder->CreateLoad(instanceType, alloca);
      return;
    }
  }

  auto calleeValue = call->getCallee();
  auto fnType = Syntax::Transformer::getFunctionType(calleeValue->getType());
  auto asFunction = utils::dyn_cast<ir::Func>(calleeValue);
  auto isLambda = !utils::is<types::FunctionType>(calleeValue->getType()) ? utils::startsWith(utils::cast<types::DefinedType>(calleeValue->getType())->getUUID(), services::ImportService::CORE_UUID + "Core.Function") : false;
  auto calleeType = getLLVMFunctionType(fnType, asFunction.get());

  llvm::Value* llvmCall = nullptr;
  llvm::Value* allocatedValue = nullptr;
  llvm::Type* allocatedValueType = nullptr;
  //setDebugInfoLoc(nullptr);
  if ((fnType && utils::cast<types::BaseType>(fnType->getRetType())) || ctx->callStoreValue) {
    if (ctx->callStoreValue) {
      allocatedValue = ctx->callStoreValue;
      ctx->callStoreValue = nullptr;
    } else {
      auto retType = fnType->getRetType();
      allocatedValueType = getLLVMType(retType);
      if (ctx->retValueUsedFromArg) {
        allocatedValue = ctx->getCurrentFunction()->getArg(0);
        ctx->retValueUsedFromArg = false;
      } else {
        // It's a function returning a type that's not a pointer
        // We need to allocate the value
        allocatedValue = createAlloca(getLLVMType(retType), ".ret-temp");
      }
    }
  }

  auto callee = build(calleeValue.get());
  auto args = utils::vector_iterate<std::shared_ptr<ir::Value>, llvm::Value*>(
    call->getArguments(), [this](std::shared_ptr<ir::Value> arg) { return expr(arg.get()); }
  );

  bool doNotAddAnonContext = false;

  if (isLambda && asFunction && asFunction->usesParentScope()) {
    auto closure = ctx->closures.at(ctx->getCurrentIRFunction()->getId());
    args.insert(args.begin(), closure.closure);
    doNotAddAnonContext = true;
  }

  if (allocatedValue) 
    args.insert(args.begin(), allocatedValue);

  setDebugInfoLoc(nullptr);
  if (asFunction != nullptr && asFunction->isConstructor()) {
    auto instance = utils::cast<ir::ObjectInitialization>(call);
    auto instanceType = getLLVMType(instance->getType());
    isConstructor = true;
    assert(instance);
    assert(asFunction->hasParent());

    llvm::Value* object = allocatedValue;
    if (instance->createdObject) {
      object = build(instance->createdObject.get());
    } else if (!allocatedValue) {
      auto classType = utils::cast<types::DefinedType>(instance->getType());
      assert(classType && "Class type is not a defined type!");
      object = allocateObject(classType);
      ctx->doNotLoadInMemory = true;
    }

    if (!allocatedValue)
      args.insert(args.begin(), load(object, instance->getType()->getReferenceTo()));
    setDebugInfoLoc(call); // TODO:
    llvmCall = createCall(calleeType, callee, args);
    this->value = object;
  } else if (asFunction != nullptr && asFunction->inVirtualTable()) {
    assert(asFunction->hasParent());

    auto index = asFunction->getVirtualIndex() + 2; // avoid class info
    auto parent = asFunction->getParent();

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
    auto vtable = builder->CreateLoad(vtableType->getPointerTo(), parentValue);
    auto fn = builder->CreateLoad(
            calleeType->getPointerTo(), builder->CreateConstInBoundsGEP1_32(vtableType->getPointerTo(), vtable, index)
    );
    builder->CreateAssumption(builder->CreateIsNotNull(fn));
    setDebugInfoLoc(call);
    llvmCall = createCall(calleeType, (llvm::Function*) fn, args);
    // builder->CreateStore(llvmCall, allocatedValue);
    // auto alloca = createAlloca(allocatedValueType);
    // builder->CreateStore(llvmCall, alloca);
    // builder->CreateMemCpy(alloca, llvm::MaybeAlign(), allocatedValue, llvm::MaybeAlign(),
    //         module->getDataLayout().getTypeAllocSize(allocatedValueType), 0);
    // this->value = allocatedValue;
    this->value = allocatedValue ? allocatedValue : llvmCall;
  } else {
    setDebugInfoLoc(call);
    if (!isLambda) {
      if (!llvm::isa<llvm::Function>(callee)) {
        // we are calling a value instead of a direct function.
        // this means we need to dereference the value first
        // and then call it.
        callee = load(callee, fnType);
      }
      llvmCall = createCall(calleeType, callee, args);
    } else {
      auto loadFunction = builder->CreateStructGEP(getLambdaContextType(), callee, 0);
      auto loadFunctionValue = builder->CreateLoad(calleeType->getPointerTo(), loadFunction);
      llvm::FunctionType* newType = nullptr;
      if (!doNotAddAnonContext) {
        if (allocatedValue) {
          auto oldArgs = calleeType->params().vec();
          // second arg, first is the sret arg
          oldArgs.insert(oldArgs.begin() + 1, getLambdaContextType()->getPointerTo());
          newType = llvm::FunctionType::get(calleeType->getReturnType(), oldArgs, calleeType->isVarArg());

          args.insert(args.begin() + 1, callee);
        } else {
          auto oldArgs = calleeType->params().vec();
          oldArgs.insert(oldArgs.begin(), getLambdaContextType()->getPointerTo());
          newType = llvm::FunctionType::get(calleeType->getReturnType(), oldArgs, calleeType->isVarArg());

          args.insert(args.begin(), callee);
        }
      }
      
      if (asFunction && asFunction->isAnon()) {
        newType = calleeType; // We've already added the context in getLLVMFunctionType
      }

      llvmCall = createCall(newType, loadFunctionValue, args);
    }

    this->value = allocatedValue ? allocatedValue : llvmCall;
  }


#define SET_CALL_ATTRIBUTES(type)                                                                                      \
  if (llvm::isa<type>(llvmCall)) {                                                                                     \
    auto call = llvm::cast<type>(llvmCall);                                                                            \
    auto calledFunction = call->getCalledFunction();                                                                   \
    bool retIsReference = false;                                                                                       \
    if (auto f = utils::dyn_cast<ir::Func>(calleeValue); f && llvm::isa<llvm::Function>(callee)) {                                                             \
      auto valBackup = this->value;                                                                                    \
      retIsReference = utils::cast<types::ReferenceType>(f->getRetTy()) != nullptr;                                    \
      calledFunction = llvm::cast<llvm::Function>(callee);                                                     \
      this->value = valBackup;                                                                                         \
    }                                                                                                                  \
    if (calledFunction) {                                                                                              \
      auto attrSet = calledFunction->getAttributes();                                                                  \
      if (retIsReference) { attrSet = attrSet.addRetAttribute(*context, llvm::Attribute::NonNull); }                   \
      call->setAttributes(attrSet);                                                                                    \
    }                                                                                                                  \
  }

  SET_CALL_ATTRIBUTES(llvm::CallInst)
  else SET_CALL_ATTRIBUTES(llvm::InvokeInst) else { assert(false); }

  if (!allocatedValue && !isConstructor) ctx->doNotLoadInMemory = true;
}

} // namespace codegen
} // namespace snowball
