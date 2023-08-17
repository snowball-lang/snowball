
#include "LLVMBuilder.h"

#include "../../errors.h"

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/InitializePasses.h>
#include <llvm/PassRegistry.h>
#include <llvm/Support/TargetSelect.h>

#include <llvm/IR/Argument.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/DebugInfo.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstIterator.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LLVMRemarkStreamer.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/LegacyPassNameParser.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/InitializePasses.h>
#include <llvm/LinkAllIR.h>
#include <llvm/LinkAllPasses.h>
#include <llvm/Linker/Linker.h>
#include <llvm/MC/SubtargetFeature.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Support/Allocator.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/Debug.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/FormatVariadic.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/InitLLVM.h>
#include <llvm/Support/Memory.h>
#include <llvm/Support/Process.h>
#include <llvm/Support/RecyclingAllocator.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/SystemUtils.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/ToolOutputFile.h>
#include <llvm/Support/YAMLTraits.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetLoweringObjectFile.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/IPO/AlwaysInliner.h>
#include <llvm/Transforms/IPO/GlobalDCE.h>
#include <llvm/Transforms/IPO/Internalize.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#include <llvm/Transforms/IPO/StripDeadPrototypes.h>
#include <llvm/Transforms/IPO/StripSymbols.h>
#include <llvm/Transforms/IPO/WholeProgramDevirt.h>
#include <llvm/Transforms/Utils/Cloning.h>
#include <llvm/Transforms/Utils/Debugify.h>

namespace snowball {
namespace codegen {

LLVMBuilder::LLVMBuilder(std::shared_ptr<ir::MainModule> mod, bool testMode) : iModule(mod) {
  ctx->testMode = testMode;
  llvm::InitializeAllTargetInfos();
  llvm::InitializeAllTargets();
  llvm::InitializeAllTargetMCs();
  llvm::InitializeAllAsmParsers();
  llvm::InitializeAllAsmPrinters();
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();

  // Initialize passes
  auto& registry = *llvm::PassRegistry::getPassRegistry();
  llvm::initializeCore(registry);
  llvm::initializeScalarOpts(registry);
  llvm::initializeVectorization(registry);
  llvm::initializeIPO(registry);
  llvm::initializeAnalysis(registry);
  llvm::initializeTransformUtils(registry);
  llvm::initializeInstCombine(registry);
  llvm::initializeXRayInstrumentationPass(registry);
  llvm::initializeTarget(registry);

  llvm::initializeExpandMemCmpPassPass(registry);
  llvm::initializeScalarizeMaskedMemIntrinLegacyPassPass(registry);
  llvm::initializeSelectOptimizePass(registry);
  llvm::initializeCodeGenPreparePass(registry);
  llvm::initializeAtomicExpandPass(registry);
  llvm::initializeRewriteSymbolsLegacyPassPass(registry);
  llvm::initializeWinEHPreparePass(registry);
  llvm::initializeDwarfEHPrepareLegacyPassPass(registry);
  llvm::initializeSafeStackLegacyPassPass(registry);
  llvm::initializeSjLjEHPreparePass(registry);
  llvm::initializePreISelIntrinsicLoweringLegacyPassPass(registry);
  llvm::initializeGlobalMergePass(registry);
  llvm::initializeIndirectBrExpandPassPass(registry);
  llvm::initializeInterleavedLoadCombinePass(registry);
  llvm::initializeInterleavedAccessPass(registry);
  llvm::initializeUnreachableBlockElimLegacyPassPass(registry);
  llvm::initializeExpandReductionsPass(registry);
  llvm::initializeExpandVectorPredicationPass(registry);
  llvm::initializeWasmEHPreparePass(registry);
  llvm::initializeWriteBitcodePassPass(registry);
  llvm::initializeHardwareLoopsPass(registry);
  llvm::initializeReplaceWithVeclibLegacyPass(registry);
  llvm::initializeTypePromotionLegacyPass(registry);

  newContext();
  module = newModule();
}

std::unique_ptr<llvm::Module> LLVMBuilder::newModule() {
  auto m = std::make_unique<llvm::Module>("snowball compiled project", *context);

  auto engine = llvm::EngineBuilder();
  target = engine.selectTarget();

  m->setDataLayout(target->createDataLayout());
  m->setTargetTriple(target->getTargetTriple().str());

  builder = std::make_unique<llvm::IRBuilder<>>(*context);

  auto srcInfo = iModule->getSourceInfo();
  m->setSourceFileName(srcInfo->getPath());

  // debug info setup
  dbg.builder = std::make_unique<llvm::DIBuilder>(*m);
  llvm::DIFile* file = dbg.getFile(srcInfo->getPath());
  dbg.unit = dbg.builder->createCompileUnit(llvm::dwarf::DW_LANG_C,
                                            file,
                                            ("Snowball version " _SNOWBALL_VERSION),
                                            !dbg.debug,
                                            {},
                                            /*RV=*/0);

  m->addModuleFlag(llvm::Module::Warning, "Debug Info Version", llvm::DEBUG_METADATA_VERSION);
  m->addModuleFlag(llvm::Module::Warning, "Snowball Compiler ID", _SNOWBALL_VERSION_NUMBER);
  m->addModuleFlag(llvm::Module::Warning,
                   "Snowball Compiler Version",
                   llvm::ConstantDataArray::getString(*context, _SNOWBALL_VERSION, true));
  // darwin only supports dwarf2
  if (llvm::Triple(m->getTargetTriple()).isOSDarwin()) { m->addModuleFlag(llvm::Module::Warning, "Dwarf Version", 2); }

  return m;
}

void LLVMBuilder::newContext() { context = std::make_unique<llvm::LLVMContext>(); }

llvm::DIFile* LLVMBuilder::DebugInfo::getFile(const std::string& path) {
  std::string filename;
  std::string directory;
  auto pos = path.find_last_of("/");
  if (pos != std::string::npos) {
    filename = path.substr(pos + 1);
    directory = path.substr(0, pos);
  } else {
    filename = path;
    directory = ".";
  }
  return builder->createFile(filename, directory);
}

void LLVMBuilder::dump() { this->print(llvm::errs()); }
void LLVMBuilder::print(llvm::raw_fd_ostream& s) { module->print(s, nullptr); }

#define ITERATE_FUNCTIONS for (auto fn = functions.rbegin(); fn != functions.rend(); ++fn)
void LLVMBuilder::codegen() {
  auto generateModule = [&](std::shared_ptr<ir::Module> m) {
    this->iModule = m;

    // Generate the functions from the end to the front.
    auto functions = m->getFunctions();

    // Iterate every function with a reversed iterator.
    // This first loop will declare all of the functions
    // to the module, it does not matter whether they are
    // bodied or not.
    ITERATE_FUNCTIONS { visit(fn->get()); }

    // Generate all the variables defined in this module.
    for (auto v : m->getVariables()) { addGlobalVariable(v); }

    // Terminate the global ctor if exists
    if (auto x = getGlobalCTOR(false)) {
      auto& ctorBody = x->getEntryBlock();
      builder->SetInsertPoint(&ctorBody);

      builder->CreateRetVoid();
    }

    // This second loop will generate all the functions that
    // are bodied. We do 2 loops in order to prevent any weird
    // situation when a function calls an undefined function that
    // has not been generated yet.
    ITERATE_FUNCTIONS {
      auto f = fn->get();
      if (!f->isDeclaration() && !f->hasAttribute(Attributes::BUILTIN)) {
        auto llvmFn = funcs.at(f->getId());
        if (f->hasAttribute(Attributes::LLVM_FUNC)) {
          auto old = buildLLVMFunction(llvmFn, f);
          funcs.at(f->getId()) = old;
        } else {
          buildBodiedFunction(llvmFn, f);

          setPersonalityFunction(llvmFn);
          std::string module_error_string;
          llvm::raw_string_ostream module_error_stream(module_error_string);
          llvm::verifyFunction(*llvmFn, &module_error_stream);

          if (!module_error_string.empty()) {
#ifdef _SNOWBALL_BYTECODE_DEBUG
            dump();
#endif
            throw SNError(Error::LLVM_INTERNAL, module_error_string);
          }
        }
      }
    }
  };

  auto mainModule = utils::dyn_cast<ir::MainModule>(iModule);
  assert(mainModule);

  for (auto m : mainModule->getModules()) generateModule(m);
  generateModule(mainModule);

  initializeRuntime();
  dbg.builder->finalize();

  DEBUG_CODEGEN("Finished codegen, proceeding to verify module");
  std::string module_error_string;
  llvm::raw_string_ostream module_error_stream(module_error_string);
  llvm::verifyModule(*module.get(), &module_error_stream);

  if (!module_error_string.empty()) {
#ifdef _SNOWBALL_BYTECODE_DEBUG
    dump();
#endif
    throw SNError(Error::LLVM_INTERNAL, module_error_string);
  }

  DEBUG_CODEGEN("Finished verifying module, proceeding to optimize module (if requested)");
}
#undef LOOP_FUNCTIONS

} // namespace codegen
} // namespace snowball
