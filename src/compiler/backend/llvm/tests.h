

#ifndef __SNOWBALL_BACKEND_LLVM_TESTER_H__
#define __SNOWBALL_BACKEND_LLVM_TESTER_H__

#include <iostream>

#include "compiler/ctx.h"
#include "compiler/frontend/ast/types.h"
#include "compiler/sil/insts.h"
#include "compiler/sil/module.h"
#include "compiler/sil/visitor.h"

#include "compiler/llvm_stl.h"

namespace snowball {
namespace backend {

class LLVMTestsBuilder final {
  llvm::DenseMap<const sil::FuncDecl*, llvm::Function*> tests;

public:
  LLVMTestsBuilder() = default;
  virtual ~LLVMTestsBuilder() = default;

  void register_test(const sil::FuncDecl* test, llvm::Function* func) {
    tests[test] = func;
  }

  void build_tests(llvm::IRBuilder<>* builder, llvm::Module* module); 
};
 
} // namespace backend
} // namespace snowball

#endif // __SNOWBALL_BACKEND_LLVM_TESTER_H__

