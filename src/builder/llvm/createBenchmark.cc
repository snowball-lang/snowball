
#include "../../errors.h"
#include "../../ir/values/Argument.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::createBenchmark(llvm::Function* mainFunction) {
  assert(ctx->benchmarkMode);
  auto printFunction = getPrintfFunction();

  mainFunction->addFnAttr(llvm::Attribute::NoInline);
  mainFunction->addFnAttr(llvm::Attribute::OptimizeNone);

  builder->CreateCall(printFunction,
                      {builder->CreateGlobalStringPtr(
                              FMT("\nExecuting %s%i%s benchmark(s)... \n %snote:%s this can take a while! you wont see any output until benchmarks are done.\n", BBLU, ctx->benchmarks.size(), RESET, BOLD, RESET), "bench.msg")});

  if (ctx->benchmarks.empty()) {
    builder->CreateCall(printFunction, {builder->CreateGlobalStringPtr(FMT(" %soh no!%s No benchmarks found! 😿\n\n", BOLD, RESET), "bench.msg")});
    builder->CreateRet(builder->getInt32(0));
    return;
  }

  auto benchFunc = module->getFunction("sn.bench.run"); // Always match this
  auto llvmBenchmarks = std::vector<llvm::Constant*>(); 
  auto benchmarkNames = std::vector<llvm::Constant*>();
  for (auto [fn, llvmFunc] : ctx->benchmarks) {
    llvmBenchmarks.push_back(llvmFunc);
    benchmarkNames.push_back(builder->CreateGlobalStringPtr(fn->getNiceName(), "bench.name"));
  }  

  auto array = llvm::ConstantArray::get(llvm::ArrayType::get(builder->getInt8PtrTy(), llvmBenchmarks.size()), llvmBenchmarks);
  auto arrayGlobal = new llvm::GlobalVariable(*module, array->getType(), true, llvm::GlobalValue::PrivateLinkage, array, "bench.array");

  auto nameArray = llvm::ConstantArray::get(llvm::ArrayType::get(builder->getInt8PtrTy(), benchmarkNames.size()), benchmarkNames);
  auto globalNameArray = new llvm::GlobalVariable(*module, nameArray->getType(), true, llvm::GlobalValue::PrivateLinkage, nameArray, "bench.name.array");

  auto call = builder->CreateCall(
          benchFunc,
          {arrayGlobal, globalNameArray, builder->getInt32(llvmBenchmarks.size())});

  // TODO: dynamic if tests fail
  builder->CreateRet(builder->getInt32(0));

  std::string module_error_string;
  llvm::raw_string_ostream module_error_stream(module_error_string);
  llvm::verifyFunction(*mainFunction, &module_error_stream);

  if (!module_error_string.empty()) {
#ifdef _SNOWBALL_BYTECODE_DEBUG
    dump();
#endif
    throw SNError(Error::LLVM_INTERNAL, module_error_string);
  }
}

} // namespace codegen
} // namespace snowball
