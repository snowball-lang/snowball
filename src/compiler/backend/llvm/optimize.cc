
#include "compiler/globals.h"
#include "compiler/backend/llvm/builder.h"

#ifndef NDEBUG
#define SNOWBALL_LLVM_DUMP_ON_FAIL 1
#else
// Do not change this value
#define SNOWBALL_LLVM_DUMP_ON_FAIL 0
#endif

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

void LLVMBuilder::finalize_and_run_lto() {
  dbg.builder->finalize();
  auto err = llvm::verifyModule(*builder_ctx.module, &llvm::errs());
#if SNOWBALL_LLVM_DUMP_ON_FAIL
  if (err) dump();
#endif
  sn_assert(!err, "Module verification failed");

  llvm::LoopAnalysisManager loop_analysis_manager;
  llvm::FunctionAnalysisManager function_analysis_manager;
  llvm::CGSCCAnalysisManager c_gscc_analysis_manager;
  llvm::ModuleAnalysisManager module_analysis_manager;

  llvm::PassBuilder pass_builder;
  pass_builder.registerFunctionAnalyses(function_analysis_manager);
  pass_builder.registerModuleAnalyses(module_analysis_manager);
  pass_builder.registerCGSCCAnalyses(c_gscc_analysis_manager);
  pass_builder.registerLoopAnalyses(loop_analysis_manager);
  llvm::Triple module_triple(builder_ctx.module->getTargetTriple());
  llvm::TargetLibraryInfoImpl tlii(module_triple);
  // cross register them too?
  pass_builder.crossRegisterProxies(
    loop_analysis_manager, function_analysis_manager, 
    c_gscc_analysis_manager, module_analysis_manager
  );
  function_analysis_manager.registerPass([&] { return llvm::TargetLibraryAnalysis(tlii); });
  llvm::OptimizationLevel lopt_level;
  switch (global.opt_level) {
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

  llvm::ModulePassManager mpm;
  if (global.opt_level == OptLevel::Debug) {
    mpm = pass_builder.buildO0DefaultPipeline(lopt_level);
  } else {
    mpm = pass_builder.buildLTOPreLinkDefaultPipeline(lopt_level);
  }
  mpm.run(*builder_ctx.module, module_analysis_manager);
  applyDebugTransformations(builder_ctx.module.get(), dbg.debug);
}

void LLVMBuilder::optimize(llvm::Module* module) {
  auto opt_level = global.opt_level;
  
  llvm::legacy::PassManager pass_manager;

  pass_manager.add(llvm::createStripDeadPrototypesPass());
  pass_manager.add(llvm::createGlobalDCEPass());
  pass_manager.add(llvm::createGlobalOptimizerPass());
  pass_manager.add(llvm::createGlobalDCEPass());

  if (opt_level != OptLevel::Debug) {
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
  }

  pass_manager.run(*module);
}

}
}
