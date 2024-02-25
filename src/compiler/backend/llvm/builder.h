
#ifndef __SNOWBALL_BACKEND_LLVM_BUILDER_H__
#define __SNOWBALL_BACKEND_LLVM_BUILDER_H__

#include <iostream>

#include "compiler/ctx.h"
#include "compiler/sil/module.h"
#include "compiler/sil/insts.h"
#include "compiler/sil/visitor.h"
#include "compiler/frontend/ast/types.h"

#include "compiler/backend/llvm/llvm.h"

namespace snowball {
namespace backend {
namespace types {
using namespace frontend::ast::types;
}

class LLVMBuilder : public sil::SilVisitor {
  std::unique_ptr<llvm::LLVMContext> llvm_ctx;
  std::unique_ptr<llvm::IRBuilder<>> builder;
  std::unique_ptr<llvm::Module> module;
  std::map<size_t, llvm::Function*> func_map;

  llvm::Value* value = nullptr; // The current value being built

#define SN_REGISTER_ACCEPT(n) void emit(sil::n* node) override;
#include "compiler/sil/insts.def"
#undef SN_REGISTER_ACCEPT

  llvm::Value* build(sil::Inst* inst);
  llvm::Value* expr(sil::Inst* inst);
  llvm::AllocaInst* alloc(sil::Inst* inst);

  llvm::Type* get_type(types::Type* type);
  llvm::FunctionType* get_func_type(types::FuncType* type);

  bool just_declare = true;

  struct {
    bool debug = false;
  } dbg;

public:
  LLVMBuilder(const Ctx& ctx);

  void build(std::vector<sil::Module>& modules);
  void dump(llvm::raw_ostream& os = llvm::errs());
};

}
}

#endif // __SNOWBALL_BACKEND_LLVM_BUILDER_H__
