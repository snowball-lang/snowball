
#include "LLVMBuilder.h"

#include "../../errors.h"

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/InitializePasses.h>
#include <llvm/PassRegistry.h>
#include <llvm/Support/TargetSelect.h>

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
    llvm::initializeObjCARCOpts(registry);
    llvm::initializeVectorization(registry);
    llvm::initializeIPO(registry);
    llvm::initializeAnalysis(registry);
    llvm::initializeTransformUtils(registry);
    llvm::initializeInstCombine(registry);
    llvm::initializeAggressiveInstCombine(registry);
    llvm::initializeInstrumentation(registry);
    llvm::initializeTarget(registry);

    llvm::initializeExpandMemCmpPassPass(registry);
    llvm::initializeScalarizeMaskedMemIntrinLegacyPassPass(registry);
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
    llvm::initializeTypePromotionPass(registry);
    llvm::initializeReplaceWithVeclibLegacyPass(registry);

    newContext();
    module = newModule();
}

std::unique_ptr<llvm::Module> LLVMBuilder::newModule() {
    auto m = std::make_unique<llvm::Module>("snowball compiled project", *context);

    target = llvm::EngineBuilder().selectTarget();

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
    if (llvm::Triple(m->getTargetTriple()).isOSDarwin()) {
        m->addModuleFlag(llvm::Module::Warning, "Dwarf Version", 2);
    }

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

        // Generate all the variables defined in this module.
        for (auto v : m->getVariables()) { addGlobalVariable(v); }

        // Terminate the global ctor if exists
        if (auto x = getGlobalCTOR(false)) {
            auto& ctorBody = x->getEntryBlock();
            builder->SetInsertPoint(&ctorBody);

            builder->CreateRetVoid();
        }

        // Generate the functions from the end to the front.
        auto functions = m->getFunctions();

        // Iterate every function with a reversed iterator.
        // This first loop will declare all of the functions
        // to the module, it does not matter whether they are
        // bodied or not.
        ITERATE_FUNCTIONS { visit(fn->get()); }

        // This second loop will generate all the functions that
        // are bodied. We do 2 loops in order to prevent any weird
        // situation when a function calls an undefined function that
        // has not been generated yet.
        ITERATE_FUNCTIONS {
            auto f = fn->get();
            if (!f->isDeclaration()) {
                auto llvmFn = funcs.at(f->getId());
                f->hasAttribute(Attributes::LLVM_FUNC) ? buildLLVMFunction(llvmFn, f)
                                                       : buildBodiedFunction(llvmFn, f);

                setPersonalityFunction(llvmFn);
            }
        }
    };

    auto mainModule = utils::dyn_cast<ir::MainModule>(iModule);
    assert(mainModule);

    for (auto m : mainModule->getModules()) generateModule(m);
    generateModule(mainModule);

    initializeRuntime();
    dbg.builder->finalize();

    std::string module_error_string;
    llvm::raw_string_ostream module_error_stream(module_error_string);
    llvm::verifyModule(*module.get(), &module_error_stream);

    if (!module_error_string.empty()) {
#ifdef _SNOWBALL_BYTECODE_DEBUG
        dump();
#endif
        throw SNError(Error::LLVM_INTERNAL, module_error_string);
    }
}
#undef LOOP_FUNCTIONS

} // namespace codegen
} // namespace snowball
