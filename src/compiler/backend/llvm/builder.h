
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
  std::unordered_map<uint64_t, llvm::Value*> value_map;

  std::unordered_map<uint64_t, sil::Inst*> inst_map;
  llvm::Function* current_func = nullptr;
  const sil::FuncDecl* current_sil_func = nullptr;

public:
  std::unique_ptr<llvm::Module> module;
  llvm::TargetMachine* target_machine = nullptr;  

  bool dont_load = false;

  LLVMBuilderContext(std::unique_ptr<llvm::LLVMContext>& ctx, std::unordered_map<uint64_t, sil::Inst*>& inst_map) 
    : module(std::make_unique<llvm::Module>("main", *ctx)), inst_map(inst_map) {}

  llvm::Value* get_value(uint64_t id) { return value_map.at(id); }
  sil::Inst* get_inst(uint64_t id) { return inst_map.at(id); }

  void set_current_func(llvm::Function* func, const sil::FuncDecl* sil_func) 
    { current_func = func; current_sil_func = sil_func; }
  llvm::Function* get_current_func() { return current_func; }
  const sil::FuncDecl* get_current_sil_func() { return current_sil_func; }
  void set_value(uint64_t id, llvm::Value* value) { value_map[id] = value; }
};

class LLVMBuilder : public sil::Builder {
  struct BuilderCache {
    std::map<uint64_t, llvm::StructType*> struct_map;
    std::map<uint64_t, llvm::DIType*> ditype_map;
  };

  std::unique_ptr<llvm::LLVMContext> llvm_ctx;
  std::unique_ptr<llvm::IRBuilder<>> builder;
  LLVMBuilderContext builder_ctx;
  BuilderCache builder_cache;

  llvm::Value* value = nullptr; // The current value being built

#define SN_REGISTER_ACCEPT(n) void emit(const sil::n* node) override;
#include "compiler/sil/insts.def"
#undef SN_REGISTER_ACCEPT

  llvm::Value* build(sil::Inst* inst);
  llvm::Value* expr(sil::Inst* inst);
  llvm::Value* load(llvm::Value* ptr, types::Type* type);
  llvm::AllocaInst* alloc(types::Type* type, const std::string& name = "");

  void set_debug_info(const sil::Inst* node);

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

  void check_and_optimize();
public:
  LLVMBuilder(const Ctx& ctx, std::unordered_map<uint64_t, sil::Inst*>& inst_map);

  void build(std::vector<std::shared_ptr<sil::Module>>& modules) override;
  void dump(llvm::raw_ostream& os = llvm::errs()) override;
  int emit(std::filesystem::path path) override;

  static void link(const Ctx& ctx, std::vector<std::filesystem::path>& paths, std::filesystem::path output);
};

}
}

#endif // __SNOWBALL_BACKEND_LLVM_BUILDER_H__
