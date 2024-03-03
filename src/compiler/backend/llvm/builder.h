
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

class LLVMBuilderContext {
  std::map<uint64_t, llvm::Function*> func_map;
  std::map<uint64_t, llvm::Value*> value_map;

  std::map<uint64_t, sil::Inst*> inst_map;
  llvm::Function* current_func = nullptr;

public:
  std::unique_ptr<llvm::Module> module;
  bool dont_load = false;

  LLVMBuilderContext(std::unique_ptr<llvm::LLVMContext>& ctx, std::map<uint64_t, sil::Inst*>& inst_map) 
    : module(std::make_unique<llvm::Module>("main", *ctx)), inst_map(inst_map) {}

  llvm::Function* get_func(uint64_t id) { return func_map.at(id); }
  llvm::Value* get_value(uint64_t id) { return value_map.at(id); }

  sil::Inst* get_inst(uint64_t id) { return inst_map.at(id); }

  void set_current_func(llvm::Function* func) { current_func = func; }
  llvm::Function* get_current_func() { return current_func; }

  void set_func(uint64_t id, llvm::Function* func) { 
    func_map[id] = func; 
    set_value(id, func);
  }

  void set_value(uint64_t id, llvm::Value* value) { value_map[id] = value; }
};

class LLVMBuilder : public sil::SilVisitor {
  std::unique_ptr<llvm::LLVMContext> llvm_ctx;
  std::unique_ptr<llvm::IRBuilder<>> builder;
  LLVMBuilderContext builder_ctx;

  llvm::Value* value = nullptr; // The current value being built

#define SN_REGISTER_ACCEPT(n) void emit(const sil::n* node) override;
#include "compiler/sil/insts.def"
#undef SN_REGISTER_ACCEPT

  llvm::Value* build(sil::Inst* inst);
  llvm::Value* expr(sil::Inst* inst);
  llvm::Value* load(llvm::Value* ptr, types::Type* type);
  llvm::AllocaInst* alloc(types::Type* type, const std::string& name = "");

  llvm::Type* get_type(types::Type* type);
  llvm::DIType* get_ditype(types::Type* type);
  llvm::FunctionType* get_func_type(types::FuncType* type);

  llvm::DISubprogram* get_disubprogram(const sil::FuncDecl* node);

  bool just_declare = true;

  struct DebugUtils {
    /// Current compilation unit
    llvm::DICompileUnit* unit = nullptr;
    /// Debug info builder
    std::unique_ptr<llvm::DIBuilder> builder = nullptr;
    // Debug flag
    bool debug = false;
    // Current scope
    llvm::DIScope* scope = nullptr;
    // Create a new DIFile for llvm
    llvm::DIFile* get_file(const std::string& path);
  } dbg;

public:
  LLVMBuilder(const Ctx& ctx, std::map<uint64_t, sil::Inst*>& inst_map);

  void build(std::vector<sil::Module>& modules);
  void dump(llvm::raw_ostream& os = llvm::errs());
};

}
}

#endif // __SNOWBALL_BACKEND_LLVM_BUILDER_H__
