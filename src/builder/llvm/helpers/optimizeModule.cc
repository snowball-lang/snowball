
#include "../../../common.h"
#include "../../../utils/utils.h"
#include "../LLVMBuilder.h"

#include <llvm/ADT/SmallVector.h>
#include <llvm/Analysis/TargetTransformInfo.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DebugInfo.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/InlineAsm.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Passes/OptimizationLevel.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Support/CodeGen.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/Host.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Scalar/Reassociate.h>
#include <llvm/Transforms/Utils.h>

namespace snowball {

namespace {
void applyDebugTransformations(llvm::Module* module, bool debug) {
  if (debug) {
    // remove tail calls and fix linkage for stack traces
    for (auto& f : *module) {
      //#ifdef __APPLE__
      //f.setLinkage(llvm::GlobalValue::ExternalLinkage);
      //#endif
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

#ifndef PERFORM_SIMPLE_OPTS
#define PERFORM_SIMPLE_OPTS 1
#endif

namespace codegen {

void LLVMBuilder::optimizeModule() {
  llvm::LoopAnalysisManager loop_analysis_manager;
  llvm::FunctionAnalysisManager function_analysis_manager;
  llvm::CGSCCAnalysisManager c_gscc_analysis_manager;
  llvm::ModuleAnalysisManager module_analysis_manager;
  // Create the new pass manager builder.
  // Take a look at the PassBuilder constructor parameters for more
  // customization, e.g. specifying a TargetMachine or various
  // debugging options.
  llvm::PassBuilder pass_builder;
  // Register all the basic analyses with the managers.
  pass_builder.registerModuleAnalyses(module_analysis_manager);
  pass_builder.registerCGSCCAnalyses(c_gscc_analysis_manager);
  pass_builder.registerFunctionAnalyses(function_analysis_manager);
  pass_builder.registerLoopAnalyses(loop_analysis_manager);
  llvm::Triple moduleTriple(module->getTargetTriple());
  llvm::TargetLibraryInfoImpl tlii(moduleTriple);
  // cross register them too?
  pass_builder.crossRegisterProxies(
                loop_analysis_manager, function_analysis_manager, c_gscc_analysis_manager, module_analysis_manager
              );
  function_analysis_manager.registerPass([&] { return llvm::TargetLibraryAnalysis(tlii); });
  llvm::OptimizationLevel level;
  switch (ctx->optimizationLevel) {
    case app::Options::Optimization::OPTIMIZE_O0: level = llvm::OptimizationLevel::O0; break;
    case app::Options::Optimization::OPTIMIZE_O1: level = llvm::OptimizationLevel::O1; break;
    case app::Options::Optimization::OPTIMIZE_O2: level = llvm::OptimizationLevel::O2; break;
    case app::Options::Optimization::OPTIMIZE_O3: level = llvm::OptimizationLevel::O3; break;
    case app::Options::Optimization::OPTIMIZE_Os: level = llvm::OptimizationLevel::Os; break;
    case app::Options::Optimization::OPTIMIZE_Oz: level = llvm::OptimizationLevel::Oz; break;
    default: assert(false && "during code optimization");
  }
  std::vector<std::function<void(llvm::ModulePassManager&, llvm::OptimizationLevel)>> PipelineStartEPCallbacks;
  std::vector<std::function<void(llvm::ModulePassManager&, llvm::OptimizationLevel)>> OptimizerLastEPCallbacks;
  PipelineStartEPCallbacks.push_back([](llvm::ModulePassManager & MPM, llvm::OptimizationLevel Level) {
                                       MPM.addPass(llvm::VerifierPass());
                                     });
  for (const auto& C : PipelineStartEPCallbacks) pass_builder.registerPipelineStartEPCallback(C);
  for (const auto& C : OptimizerLastEPCallbacks) pass_builder.registerOptimizerLastEPCallback(C);
  llvm::ModulePassManager mpm;
  if (dbg.debug) {
    mpm = pass_builder.buildThinLTODefaultPipeline(level, nullptr);
  } else {
#if PERFORM_SIMPLE_OPTS
    {
      // simple optimizations done for each function. It does not depend on the optimization level.
      std::unique_ptr<llvm::legacy::FunctionPassManager> functionPassManager =
      std::make_unique<llvm::legacy::FunctionPassManager>(module.get());

      // Promote allocas to registers.
      functionPassManager->add(llvm::createPromoteMemoryToRegisterPass());
      // Do simple "peephole" optimizations
      functionPassManager->add(llvm::createInstructionCombiningPass());
      // Reassociate expressions.
      functionPassManager->add(llvm::createReassociatePass());
      // Eliminate Common SubExpressions.
      functionPassManager->add(llvm::createGVNPass());
      // Simplify the control flow graph (deleting unreachable blocks etc).
      functionPassManager->add(llvm::createCFGSimplificationPass());

      functionPassManager->doInitialization();

      for (auto& function : module->getFunctionList()) { functionPassManager->run(function); }
    }
    llvm::legacy::PassManager codegen_pm;
    codegen_pm.add(llvm::createTargetTransformInfoWrapperPass(target->getTargetIRAnalysis()));
    codegen_pm.run(*module);
#endif
    mpm = pass_builder.buildLTOPreLinkDefaultPipeline(level);
  }
  mpm.run(*module, module_analysis_manager);
  applyDebugTransformations(module.get(), dbg.debug);
}

} // namespace codegen
} // namespace snowball
