
#include "../../ir/values/TryCatch.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#include "../../../runtime/libs/exceptions.h"

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::TryCatch* node) {
  auto parentFunc = ctx->getCurrentFunction();
  auto padType = llvm::StructType::get(builder->getInt8PtrTy(), builder->getInt32Ty());
  auto unwindType = llvm::StructType::get(builder->getInt64Ty());
  auto execType = llvm::StructType::get(getTypeInfoType(), builder->getInt8PtrTy());

  auto ourExceptionThrownState = llvm::ConstantInt::get(llvm::Type::getInt8Ty(*context), 1);
  
  // Create the try block
  auto tryBlock = llvm::BasicBlock::Create(*context, "try", parentFunc);
  builder->CreateBr(tryBlock);

  TryCatchInfo info;
  info.catchBlock = llvm::BasicBlock::Create(*context, "catch", parentFunc);
  info.catchRouteBlock = llvm::BasicBlock::Create(*context, "catch.route", parentFunc);

  llvm::Value* exceptionCaughtFlag = NULL;
  llvm::Value* exceptionStorage = NULL;
  llvm::Value* caughtResultStorage = NULL;

  auto externalExcBlock = llvm::BasicBlock::Create(*context, "catch.external", parentFunc);
  auto unwindResumeBlock = llvm::BasicBlock::Create(*context, "catch.unwind", parentFunc);
  auto endBlock = llvm::BasicBlock::Create(*context, "try.end", parentFunc);

  // MARK: entry block
  builder->SetInsertPoint(parentFunc->getEntryBlock().getTerminator());

  exceptionCaughtFlag = builder->CreateAlloca(builder->getInt8Ty());
  exceptionStorage = builder->CreateAlloca(builder->getInt8PtrTy());
  caughtResultStorage = builder->CreateAlloca(builder->getInt8PtrTy());

  info.exceptionPad = builder->CreateAlloca(padType);
  builder->CreateStore(llvm::ConstantAggregateZero::get(padType), info.exceptionPad);

  auto catchInstances = node->getCatchBlocks();
  auto catchVars = node->getCatchVars();
  assert(catchInstances.size() == catchVars.size());

  // MARK: try block
  builder->SetInsertPoint(tryBlock);
  tryCatchStack.push_back(std::move(info));
  build(node->getBlock().get());
  tryCatchStack.pop_back();

  for (int i = 0; i < (int)catchInstances.size(); i++) {
    auto catchBlock = catchInstances[i];
    auto catchVar = catchVars[i];
    auto catchBlockBB = llvm::BasicBlock::Create(*context, "catch.block", parentFunc);

    info.handlers.push_back(catchBlockBB);
    info.catchVars.push_back(catchVar);
  }

  builder->CreateBr(endBlock);

  // MARK: unwind resume block
  builder->SetInsertPoint(unwindResumeBlock);
  builder->CreateResume(builder->CreateLoad(padType, info.exceptionPad));

  // MARK: catch block
  std::vector<llvm::Value*> typeIndices;
  builder->SetInsertPoint(info.catchBlock);

  auto caughtException = builder->CreateLandingPad(padType, catchInstances.size());
  caughtException->setCleanup(true);

  for (auto catchVar : info.catchVars) {
    auto varName = "snowball.typeidx." + catchVar->getType()->getMangledName();
    llvm::GlobalVariable* tidx = module->getGlobalVariable(varName);
    if (!tidx) {
      tidx = new llvm::GlobalVariable(
              *module,
              llvm::StructType::get(builder->getInt32Ty()),
              /*isConstant=*/true,
              llvm::GlobalValue::PrivateLinkage,
              llvm::ConstantStruct::get(
                      getTypeInfoType(), builder->getInt32(typeIdxLookup(catchVar->getType()->getMangledName()))
              ),
              varName
      );
      tidx->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);
    }
    caughtException->addClause(tidx);
  }

  auto unwindException = builder->CreateExtractValue(caughtException, 0);
  builder->CreateStore(caughtException, info.exceptionPad);

  builder->CreateStore(caughtResultStorage, caughtResultStorage);
  builder->CreateStore(unwindException, exceptionStorage);
  builder->CreateStore(ourExceptionThrownState, exceptionCaughtFlag);

  // auto depthMax = builder->getInt64(trycatch.size());
  // builder->CreateStore(depthMax, tc.delegateDepth);

  auto unwindExceptionClass = builder->CreateLoad(
          builder->getInt64Ty(),
          builder->CreateStructGEP(
                  unwindType, builder->CreatePointerCast(unwindException, unwindType->getPointerTo()), 0
          )
  );
  createCondBr(
          builder->CreateICmpEQ(unwindExceptionClass, builder->getInt64(exception_class())),
          info.catchRouteBlock,
          externalExcBlock
  );

  // MARK: external exception block
  builder->SetInsertPoint(externalExcBlock);
  builder->CreateUnreachable();

  // MARK: catch route block
  builder->SetInsertPoint(info.catchRouteBlock);
  unwindException = builder->CreateExtractValue(builder->CreateLoad(padType, info.exceptionPad), 0);
  llvm::Value* execVal = builder->CreatePointerCast(
          builder->CreateConstGEP1_64(builder->getInt8Ty(), unwindException, (uint64_t) exception_offset()),
          execType->getPointerTo()
  );

  auto loadedExc = builder->CreateLoad(execType, execVal);
  auto objType = builder->CreateExtractValue(loadedExc, 0);
  objType = builder->CreateExtractValue(objType, 0);
  auto objPtr = builder->CreateExtractValue(loadedExc, 1);

  auto defaultRouteBlock = llvm::BasicBlock::Create(*context, "trycatch.fdepth", parentFunc);
  builder->SetInsertPoint(defaultRouteBlock);
  builder->CreateBr(endBlock);

  builder->SetInsertPoint(info.catchRouteBlock);
  auto castSwitch = builder->CreateSwitch(objType, defaultRouteBlock, (unsigned) catchInstances.size());

  // TODO: support for "catch all"
  for (int i = 0; i < (int)info.handlers.size(); i++) {
    // set finally depth
    auto mangledType = catchVars[i]->getType()->getMangledName();
    auto type = getLLVMType(catchVars[i]->getType());
    auto BBlock = info.handlers[i];
    // builder->CreateBr((i < info.handlers.size()) ? info.handlers[i] : endBlock);
    castSwitch->addCase(builder->getInt32((uint64_t) typeIdxLookup(mangledType)), BBlock);
    auto block = catchInstances[i];
    builder->SetInsertPoint(BBlock);
    auto var = catchVars[i];

    if (var) {
      auto obj = builder->CreateLoad(type, objPtr);
      auto varPtr = ctx->getSymbol(var->getId());
      builder->CreateStore(obj, varPtr);
    }

    build(block.get());
    if (BBlock->getTerminator() == nullptr) builder->CreateBr(endBlock);
  }

  builder->SetInsertPoint(endBlock);
}

} // namespace codegen
} // namespace snowball
