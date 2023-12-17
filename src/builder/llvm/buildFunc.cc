
#include "../../ast/errors/error.h"
#include "../../errors.h"
#include "../../ir/values/Argument.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::Func* func) {
  if (func->hasAttribute(Attributes::BUILTIN)) {
    this->value = nullptr;
    return;
  }

  if (auto it = funcs.find(func->getId()); it != funcs.end()) {
    if (!func->isAnon()) 
      this->value = it->second;
    else {
      auto layout = module->getDataLayout();
      auto alloca = builder->CreateCall(getAllocaFunction(), {builder->getInt32(layout.getTypeAllocSize(getLambdaContextType()))});
      
      auto funcGep = builder->CreateStructGEP(getLambdaContextType(), alloca, 0, ".func.use.gep");
      builder->CreateStore(it->second, funcGep);

      llvm::Value* body = nullptr;
      if (func->isAnon() && func->usesParentScope()) {
        auto closure = ctx->closures.at(ctx->getCurrentIRFunction()->getId());
        body = closure.closure;
      } else {
        body = llvm::Constant::getNullValue(builder->getPtrTy());
      }

      auto bodyGep = builder->CreateStructGEP(getLambdaContextType(), alloca, 1, ".func.use.gep");
      builder->CreateStore(body, bodyGep);
      this->value = alloca;
    }
    return;
  }

  setDebugInfoLoc(func);
  auto fn = createLLVMFunction(func);
  if (func->hasAttribute(Attributes::ALLOW_FOR_TEST)) {
    fn->addFnAttr(llvm::Attribute::NoInline);
    ctx->tests.insert(std::make_pair(func, fn));
  } else if (func->hasAttribute(Attributes::ALLOW_FOR_BENCH)) {
    fn->addFnAttr(llvm::Attribute::NoInline);
    ctx->benchmarks.insert(std::make_pair(func, fn));
  }

  funcs.insert({func->getId(), fn});
  this->value = fn;
}

llvm::Function* LLVMBuilder::buildBodiedFunction(llvm::Function* llvmFn, ir::Func* fn) {
  ctx->setCurrentFunction(llvmFn);
  ctx->setCurrentIRFunction(fn);
  ctx->doNotLoadInMemory = false;

  auto returnType = getLLVMType(fn->getRetTy());
  bool retIsArg = false;
  bool anon = fn->isAnon();
  if (utils::cast<types::DefinedType>(fn->getRetTy())) {
    returnType = builder->getVoidTy();
    retIsArg = true;
  }

  auto entry = h.create<llvm::BasicBlock>(*context, "entry", llvmFn);
  auto body = h.create<llvm::BasicBlock>(*context, "body", llvmFn);

  // mark: entry block
  builder->SetInsertPoint(entry);
  setDebugInfoLoc(nullptr);

  auto fnArgs = fn->getArgs();
  auto llvmArgsIter = llvmFn->arg_begin() + retIsArg + anon;
  auto selfArg = (llvm::Value*) nullptr;
  auto selfArgVal = std::shared_ptr<ir::Value>(nullptr);
  for (auto varIter = fnArgs.begin(); varIter != fnArgs.end(); ++varIter) {
    auto var = varIter->second;
    auto storage = builder->CreateAlloca(getLLVMType(var->getType()), nullptr, "arg." + var->getName());
    builder->CreateStore(llvmArgsIter, storage);

    if (var->getName() == "self" && var->getIndex() == 0) {
      selfArg = storage;
      selfArgVal = varIter->second;
    }

    // note: We sum "1" to the ID because each "Variable" has the
    // argument stored.
    //  variable searches for it's ID and not the argument ID (aka:
    //  var id - 1). basically, we sum 1 because thats the ID when
    //  we store it as a variable.
    ctx->addSymbol(var->getId() + 1, storage);

    // debug info
    auto src = var->getSourceInfo();
    auto dbgInfo = var->getDBGInfo();

    auto file = dbg.getFile(src->getPath());
    auto scope = llvmFn->getSubprogram();
    auto debugVar = dbg.builder->createParameterVariable(
            scope,
            var->getName(),
            var->getIndex() + 1 + retIsArg + anon, // lua vibes... :]
            file,
            dbgInfo->line,
            getDIType(var->getType()),
            dbg.debug
    );
    dbg.builder->insertDeclare(
            storage,
            debugVar,
            dbg.builder->createExpression(),
            llvm::DILocation::get(*context, dbgInfo->line, dbgInfo->pos.second, scope),
            entry
    );
    ++llvmArgsIter;
  }

  llvm::StructType* closureType = nullptr;

  for (auto v : fn->getSymbols()) {
    auto llvmType = getLLVMType(v->getType());
    if (v->getVariable()->isUsedInLambda()) {
      if (closureType == nullptr) {
        closureType = llvm::StructType::create(*context, "_closure." + fn->getMangle());
        auto body = closureType->elements().vec();
        body.push_back(llvmType);
        closureType->setBody(body);
        auto layout = module->getDataLayout();
        auto alloca = builder->CreateCall(getAllocaFunction(), {builder->getInt32(layout.getTypeAllocSize(closureType))});
        //auto structAlloca = createAlloca(closureType->getPointerTo());
        alloca->setDebugLoc(llvm::DILocation::get(*context, 0, 0, llvmFn->getSubprogram()));
        //builder->CreateStore(alloca, structAlloca);
        ctx->closures.insert({fn->getId(), LLVMBuilderContext::ClosureContext {
          .closure = alloca,
          .closureType = closureType,
        }});
      }

      auto& closure = ctx->closures.at(fn->getId());
      closure.variables.push_back(v->getVariable()->getId());
    }
  }

  // Generate all the used variables
  for (auto v : fn->getSymbols()) {
    auto llvmType = getLLVMType(v->getType());
    llvm::Value* storage = nullptr;
    if (v->getVariable()->isUsedInLambda()) {
      auto closure = ctx->closures.at(fn->getId());
      auto index = std::distance(
        closure.variables.begin(),
        std::find_if(
          closure.variables.begin(),
          closure.variables.end(),
          [v](auto v2) { return v2 == v->getVariable()->getId(); }
        )
      );
      storage = builder->CreateStructGEP(closureType, closure.closure, index);
    } else {
      storage = builder->CreateAlloca(llvmType, nullptr, "var." + v->getIdentifier());
      ctx->addSymbol(v->getId(), storage);
    }

    if (utils::is<types::DefinedType>(v->getType())) {
      initializeVariable(storage, llvmType, v->getType()->sizeOf());
    }
  }

  if (fn->isConstructor()) {
    assert(selfArg != nullptr);
    assert(selfArgVal != nullptr);
    auto self = selfArgVal->getType();
    if (utils::is<types::ReferenceType>(self)) { self = utils::cast<types::ReferenceType>(self)->getPointedType(); }

    if (fn->superCall) {
      auto superBranch = h.create<llvm::BasicBlock>(*context, "super-call", llvmFn);
      builder->CreateBr(superBranch);
      builder->SetInsertPoint(superBranch);
      (void) build((ir::Value*) fn->superCall.get());
    }

    assert(utils::is<types::DefinedType>(self) && "Constructor self type is not a defined type!");
    if (ctx->typeInfo.at(utils::cast<types::BaseType>(self)->getId())->hasVtable) {
      auto storeBranch = h.create<llvm::BasicBlock>(*context, "vtable-store", llvmFn);
      builder->CreateBr(storeBranch);
      builder->SetInsertPoint(storeBranch);
      auto ty = utils::cast<types::DefinedType>(self);
      if (!ty) { Syntax::E<BUG>("Constructor self type is not a defined type!"); }
      auto llvmType = llvm::cast<llvm::StructType>(getLLVMType(ty));
      auto cast = builder->CreateLoad(llvmType->getPointerTo(), selfArg);

      llvm::Value* vtablePointer = nullptr;
      if (auto v = ctx->getVtable(ty->getId())) {
        vtablePointer = v;
      } else {
        auto t = ctx->getVtableTy(ty->getId());
        if (!t) { t = getVtableType(ty); }

        vtablePointer = createVirtualTable(ty, t);
        // insert vtable to the start of the type declaration
        auto body = llvm::cast<llvm::StructType>(llvmType)->elements().vec();
        llvm::cast<llvm::StructType>(llvmType)->setBody(body);
      }

      auto numElements =
              llvm::cast<llvm::ArrayType>(llvm::cast<llvm::StructType>(ctx->getVtableTy(ty->getId()))->elements()[0])
                      ->getNumElements();
      //auto element = llvm::ConstantExpr::getGetElementPtr(
      //        llvm::StructType::get(llvm::ArrayType::get(builder->getInt8PtrTy(), numElements)),
      //        (llvm::Constant*) vtablePointer,
      //        llvm::ArrayRef<llvm::Constant*>{builder->getInt32(0), builder->getInt32(0), builder->getInt32(2)},
      //        true,
      //        1
      //);
      //auto vtableLoad = llvm::ConstantExpr::getBitCast(
      //        element, llvm::FunctionType::get(builder->getInt32Ty(), {}, true)->getPointerTo()->getPointerTo()
      //);
      //builder->CreateStore(
      //        vtableLoad,
      //        builder->CreateBitCast(
      //                cast,
      //                llvm::FunctionType::get(builder->getInt32Ty(), {}, true)
      //                        ->getPointerTo()
      //                        ->getPointerTo()
      //                        ->getPointerTo(),
      //                ".vtable-store-load"
      //        )
      //);
      auto vtableSpot = builder->CreateStructGEP(llvmType, cast, 0);
      builder->CreateStore(vtablePointer, vtableSpot);
    }
  }

  builder->CreateBr(body);

  // mark: body block
  builder->SetInsertPoint(body);

  // Codegen for the current body
  (void) build(fn->getBody().get());
  setDebugInfoLoc(nullptr);

  // Create return type
  if (!builder->GetInsertBlock()->getTerminator()) {
    if (utils::cast<types::VoidType>(fn->getRetTy()) || utils::cast<types::DefinedType>(fn->getRetTy())) {
      builder->CreateRetVoid();
    } else if (fn->isConstructor()) {
      // note: 0 should be always the "self" parameter
      assert(!llvmFn->args().empty());
      builder->CreateRet(llvmFn->getArg(0));
    } else {
      // TODO: warning
      builder->CreateRet(llvm::Constant::getNullValue(returnType));
    }
  }

  // mark: clean up
  ctx->clearCurrentFunction();
  ctx->clearCurrentIRFunction();

  auto DISubprogram = llvmFn->getSubprogram();
  dbg.builder->finalizeSubprogram(DISubprogram);

  return llvmFn;
}

} // namespace codegen
} // namespace snowball
