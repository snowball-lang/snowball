
#include "../../../utils/utils.h"
#include "../LLVMBuilder.h"

#include <llvm-14/llvm/IR/Type.h>
#include <llvm-14/llvm/IR/Value.h>
#include <llvm/Passes/OptimizationLevel.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar/Reassociate.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Support/CodeGen.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/Module.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/InlineAsm.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Support/FormattedStream.h>

#include <llvm/Transforms/IPO.h>
#include <llvm/IR/LegacyPassManager.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::optimizeModule(exec::Options::Optimization o) {
    llvm::LoopAnalysisManager loop_analysis_manager;
    llvm::FunctionAnalysisManager function_analysis_manager;
    llvm::CGSCCAnalysisManager c_gscc_analysis_manager;
    llvm::ModuleAnalysisManager module_analysis_manager;

    // Create the new pass manager builder.
    // Take a look at the PassBuilder constructor parameters for more
    // customization, e.g. specifying a TargetMachine or various debugging
    // options.
    llvm::PassBuilder pass_builder;

    // Register all the basic analyses with the managers.
    pass_builder.registerModuleAnalyses(module_analysis_manager);
    pass_builder.registerCGSCCAnalyses(c_gscc_analysis_manager);
    pass_builder.registerFunctionAnalyses(function_analysis_manager);
    pass_builder.registerLoopAnalyses(loop_analysis_manager);

    // cross register them too?
    pass_builder.crossRegisterProxies(loop_analysis_manager, function_analysis_manager,
                                    c_gscc_analysis_manager, module_analysis_manager);

    // todo: let user decide
    llvm::OptimizationLevel level;
    switch(o)
    {
        case exec::Options::Optimization::OPTIMIZE_O0: level = llvm::OptimizationLevel::O0; break;
        case exec::Options::Optimization::OPTIMIZE_O1: level = llvm::OptimizationLevel::O1; break;
        case exec::Options::Optimization::OPTIMIZE_O2: level = llvm::OptimizationLevel::O2; break;
        case exec::Options::Optimization::OPTIMIZE_O3: level = llvm::OptimizationLevel::O3; break;
        case exec::Options::Optimization::OPTIMIZE_Os: level = llvm::OptimizationLevel::Os; break;
        case exec::Options::Optimization::OPTIMIZE_Oz: level = llvm::OptimizationLevel::Oz; break;
        default: assert(false && "during code optimization");
    }

    if (level == llvm::OptimizationLevel::O0) { return; }

    llvm::ModulePassManager MPM = pass_builder.buildPerModuleDefaultPipeline(level);
    MPM.run(*module.get(), module_analysis_manager);

    llvm::legacy::FunctionPassManager fpm(module.get());

    fpm.add(new llvm::InstructionCombiningPass());
    fpm.add(llvm::createCFGSimplificationPass());

    fpm.doInitialization();
    for (auto& function : module->functions()) {
        fpm.run(function);
    }

    fpm.doFinalization();
}

} // namespace codegen
} // namespace snowball
