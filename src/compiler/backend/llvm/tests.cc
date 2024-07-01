
#include "compiler/globals.h"
#include "compiler/backend/llvm/builder.h"

#include "runtime/common.h"

namespace snowball {
namespace backend {

void LLVMTestsBuilder::build_tests(llvm::IRBuilder<>* builder, llvm::Module* module) {
  if (!global.test_mode) return;
  auto tests_type = llvm::FunctionType::get(
    builder->getVoidTy(), {
      builder->getPtrTy(),
      builder->getPtrTy(),
      builder->getInt32Ty(),
      builder->getInt32Ty(),
      builder->getPtrTy()
    }, false
  );
  auto pre_run_type = llvm::FunctionType::get(
    builder->getVoidTy(), {
      builder->getInt32Ty(),
    }, false
  );
  auto post_run_type = llvm::FunctionType::get(
    builder->getVoidTy(), {
      builder->getInt32Ty(),
      builder->getInt32Ty(),
    }, false
  );
  auto pre_run_fn = module->getOrInsertFunction(SNOWBALL_TEST_PRE_RUN, pre_run_type);
  auto post_run_fn = module->getOrInsertFunction(SNOWBALL_TEST_POST_RUN, post_run_type);
  auto tests_fn = module->getOrInsertFunction(SNOWBALL_TEST_EXPORT, tests_type);
  auto main_fn = module->getOrInsertFunction("main", llvm::FunctionType::get(
    builder->getInt32Ty(), { builder->getInt32Ty(), builder->getInt8PtrTy()->getPointerTo() }, false
  ));
  auto entry = llvm::BasicBlock::Create(module->getContext(), "tests.entry", (llvm::Function*)main_fn.getCallee());
  builder->SetInsertPoint(entry);
  auto success_count = builder->CreateAlloca(builder->getInt32Ty());
  builder->CreateStore(builder->getInt32(0), success_count);
  builder->CreateCall(pre_run_fn, { builder->getInt32(tests.size()) });
  size_t i = 0;
  for (auto& [node, llfunc] : tests) {
    builder->CreateCall(tests_fn, {
      llfunc,
      builder->CreateGlobalStringPtr(node->get_printable_name()),
      builder->getInt32(i++),
      builder->getInt32(tests.size()),
      success_count
    });
  }
  builder->CreateCall(post_run_fn, { 
    builder->CreateLoad(builder->getInt32Ty(), success_count), 
    builder->getInt32(tests.size()) 
  });
  auto success = builder->CreateLoad(builder->getInt32Ty(), success_count);
  // TODO: call sn.test.exit  
  builder->CreateRet(success);
}

} // namespace backend
} // namespace snowball


