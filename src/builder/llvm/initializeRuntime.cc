
#include "../../utils/utils.h"
#include "../../../runtime/libs/runtime.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

#define CALL_INITIALIZERS \
  builder->CreateCall(f, {flagsInt}); \
  if (envArgv) \
    builder->CreateCall(envArgv, {argc, argv});

void LLVMBuilder::initializeRuntime() {
  auto ty = llvm::FunctionType::get(builder->getVoidTy(), {builder->getInt32Ty()}, false);
  auto f = llvm::cast<llvm::Function>(
           module->getOrInsertFunction(getSharedLibraryName("sn.runtime.initialize"), ty).getCallee()
           );
  f->addFnAttr(llvm::Attribute::AlwaysInline);
  f->addFnAttr(llvm::Attribute::NoUnwind);
  const int flags = (dbg.debug ? SNOWBALL_FLAG_DEBUG : 0) | 0;
  auto envArgv = module->getFunction("sn.env.set_argv");
  auto mainFunction = module->getFunction(_SNOWBALL_FUNCTION_ENTRY);
  bool buildReturn = false;
  llvm::BasicBlock* body;
  auto fnType = llvm::FunctionType::get(builder->getInt32Ty(), {builder->getInt32Ty(), builder->getInt8PtrTy()->getPointerTo()},
                                        false);
  if (mainFunction) {
    if (ctx->testMode) {
      mainFunction->eraseFromParent();
      mainFunction = (llvm::Function*) module->getOrInsertFunction(_SNOWBALL_FUNCTION_ENTRY, fnType).getCallee();
      setPersonalityFunction(mainFunction);
      body = llvm::BasicBlock::Create(builder->getContext(), "test_entry", mainFunction);
    } else if (ctx->benchmarkMode) {
      mainFunction->eraseFromParent();
      mainFunction = (llvm::Function*) module->getOrInsertFunction(_SNOWBALL_FUNCTION_ENTRY, fnType).getCallee();
      setPersonalityFunction(mainFunction);
      body = llvm::BasicBlock::Create(builder->getContext(), "benchmark_entry", mainFunction);
    } else {
      body = &mainFunction->front();
    }
  } else {
    mainFunction = (llvm::Function*) module->getOrInsertFunction(_SNOWBALL_FUNCTION_ENTRY, fnType).getCallee();
    setPersonalityFunction(mainFunction);
    body = llvm::BasicBlock::Create(builder->getContext(), "entry", mainFunction);
    buildReturn = !ctx->testMode;
  }
  builder->SetInsertPoint(body);
  auto flagsInt = builder->getInt32(flags);
  auto argc = mainFunction->arg_begin();
  argc->setName("argc");
  auto argv = std::next(mainFunction->arg_begin());
  argv->setName("argv");
  if (buildReturn) {
    CALL_INITIALIZERS
    builder->CreateRet(builder->getInt32(0));
  } else if (ctx->testMode) {
    CALL_INITIALIZERS
    createTests(mainFunction);
  } else if (ctx->benchmarkMode) {
    CALL_INITIALIZERS
    createBenchmark(mainFunction);
  } else {
    llvm::CallInst::Create(f, {flagsInt}, "", &body->front());
    if (envArgv) {
      auto debugLoc = llvm::DebugLoc(llvm::DILocation::get(*context, 0, 0, mainFunction->getSubprogram()));
      llvm::CallInst::Create(envArgv, {argc, argv}, "", &body->front())->setDebugLoc(debugLoc);
    }
  }
}

} // namespace codegen
} // namespace snowball
