
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

namespace {
void applyDebugTransformations(llvm::Module* module, bool debug) {
  if (debug) {
    // remove tail calls and fix linkage for stack traces
    for (auto& f : *module) {
      if (!f.hasFnAttribute(llvm::Attribute::AttrKind::AlwaysInline))
        f.addFnAttr(llvm::Attribute::AttrKind::NoInline);
      f.setUWTableKind(llvm::UWTableKind::Default);
      f.addFnAttr("no-frame-pointer-elim", "true");
      f.addFnAttr("no-frame-pointer-elim-non-leaf");
      f.addFnAttr("no-jump-tables", "false");
    }
  } else {
    llvm::StripDebugInfo(*module);
  }
}
} // namespace

void LLVMBuilder::check_and_optimize(llvm::Module* module, llvm::TargetMachine* target_machine, OptLevel opt_level) {
  auto debug = opt_level == OptLevel::Debug 
            || opt_level == OptLevel::ReleaseWithDebug;
  
  llvm::legacy::PassManager pass_manager;
  pass_manager.add(llvm::createPromoteMemoryToRegisterPass());
  pass_manager.add(llvm::createInstructionCombiningPass());
  pass_manager.add(llvm::createReassociatePass());
  pass_manager.add(llvm::createGVNPass());
  pass_manager.add(llvm::createCFGSimplificationPass());
  pass_manager.add(llvm::createDeadStoreEliminationPass());
  pass_manager.add(llvm::createDeadCodeEliminationPass());
  pass_manager.add(llvm::createAggressiveDCEPass());
  pass_manager.add(llvm::createCFGSimplificationPass());
  pass_manager.add(llvm::createInstructionCombiningPass());
  pass_manager.add(llvm::createReassociatePass());
  pass_manager.add(llvm::createGVNPass());
  pass_manager.add(llvm::createCFGSimplificationPass());
  pass_manager.add(llvm::createDeadStoreEliminationPass());
  pass_manager.add(llvm::createDeadCodeEliminationPass());
  pass_manager.add(llvm::createAggressiveDCEPass());
  pass_manager.add(llvm::createCFGSimplificationPass());
  pass_manager.add(llvm::createInstructionCombiningPass());
  
  pass_manager.run(*module);
  applyDebugTransformations(module, debug);

  if (opt_level == OptLevel::ReleaseWithDebug) {
    llvm::legacy::PassManager debug_pass_manager;
    debug_pass_manager.add(llvm::createStripDeadPrototypesPass());
    debug_pass_manager.add(llvm::createGlobalDCEPass());
    debug_pass_manager.add(llvm::createGlobalOptimizerPass());
    debug_pass_manager.add(llvm::createGlobalDCEPass());

    debug_pass_manager.run(*module);
  }

  llvm::LoopAnalysisManager loop_analysis_manager;
  llvm::FunctionAnalysisManager function_analysis_manager;
  llvm::CGSCCAnalysisManager c_gscc_analysis_manager;
  llvm::ModuleAnalysisManager module_analysis_manager;

  llvm::PassBuilder pass_builder;
  pass_builder.registerFunctionAnalyses(function_analysis_manager);
  pass_builder.registerModuleAnalyses(module_analysis_manager);
  pass_builder.registerCGSCCAnalyses(c_gscc_analysis_manager);
  pass_builder.registerLoopAnalyses(loop_analysis_manager);

  llvm::OptimizationLevel lopt_level;
  switch (opt_level) {
    case OptLevel::Debug:
      lopt_level = llvm::OptimizationLevel::O0;
      break;
    case OptLevel::Release:
    case OptLevel::ReleaseWithDebug:
      lopt_level = llvm::OptimizationLevel::O2;
      break;
    case OptLevel::ReleaseFast:
      lopt_level = llvm::OptimizationLevel::O3;
      break;
  }

  if (!debug) {
    llvm::ModulePassManager module_pass_manager = pass_builder.buildLTOPreLinkDefaultPipeline(lopt_level);
    //module_pass_manager.run(*builder_ctx.module, module_analysis_manager);
  }
}

}
}
