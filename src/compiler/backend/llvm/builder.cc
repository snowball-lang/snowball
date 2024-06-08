
#include "compiler/backend/llvm/builder.h"
#include "compiler/backend/llvm/llvm.h"

#include "compiler/globals.h"

namespace snowball {
namespace backend {

LLVMBuilder::LLVMBuilder(const Ctx& ctx, std::unordered_map<uint64_t, sil::Inst*>& inst_map, frontend::NamespacePath parent_crate) : Builder(ctx),
  llvm_ctx(std::make_unique<llvm::LLVMContext>()), builder_ctx(llvm_ctx, inst_map, parent_crate) {
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
  llvm::initializeMergeICmpsLegacyPassPass(registry);
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
  builder = std::make_unique<llvm::IRBuilder<>>(*llvm_ctx);
  builder_ctx.module = std::make_unique<llvm::Module>(parent_crate.get_path_string(), *llvm_ctx);

  dbg.debug = global.opt_level == OptLevel::Debug 
            || global.opt_level == OptLevel::ReleaseWithDebug;

  dbg.builder = std::make_unique<llvm::DIBuilder>(*builder_ctx.module);
  auto input_file = ctx.package_config.value().project.path;
  llvm::DIFile* file = dbg.get_file(input_file);
  dbg.unit = dbg.builder->createCompileUnit(
    llvm::dwarf::DW_LANG_C_plus_plus,
    file,
    ("Snowball version " _SNOWBALL_VERSION),
    !dbg.debug,
    {},
    /*RV=*/0
  );
  builder_ctx.module->addModuleFlag(llvm::Module::Warning, "Debug Info Version", llvm::DEBUG_METADATA_VERSION);
  builder_ctx.module->addModuleFlag(llvm::Module::Warning, "Snowball Compiler ID", _SNOWBALL_VERSION_NUMBER);
  builder_ctx.module->addModuleFlag(
    llvm::Module::Warning,
    "Snowball Compiler Version",
    llvm::ConstantDataArray::getString(*llvm_ctx, _SNOWBALL_VERSION, true)
  );
  auto engine = llvm::EngineBuilder();
  auto target = get_target_triple();
  // Set the target triple
  builder_ctx.target_machine = engine.selectTarget(llvm::Triple(target), "", "", llvm::SmallVector<std::string, 0>());
  builder_ctx.module->setTargetTriple(target);
  // darwin only supports dwarf2
  if (llvm::Triple(builder_ctx.module->getTargetTriple()).isOSDarwin()) { 
    builder_ctx.module->addModuleFlag(llvm::Module::Warning, "Dwarf Version", 2); 
  }
}

std::string LLVMBuilder::get_target_triple() {
  std::string target;
  switch (global.arch) {
    case Arch::X86_64:
      target = "x86_64";
      break;
    case Arch::Arm64:
      target = "aarch64";
      break;
    default: sn_unreachable();
  }
  switch (global.target) {
    case Target::Linux:
      target += "-linux-gnu";
      break;
    case Target::MacOS:
      target += "-apple-darwin";
      break;
    case Target::Windows:
      target += "-pc-windows-msvc";
      break;
    default: sn_unreachable();
  }
  return target;
}

void LLVMBuilder::build(std::vector<std::shared_ptr<sil::Module>>& modules) {
  for (auto module : modules) {
    for (auto& fn : module->get_fn_decls()) {
      build(fn);
    }
  }
  just_declare = false;
  for (auto module : modules) {
    for (auto& fn : module->get_fn_decls()) {
      build(fn);
    }
  }
  dbg.builder->finalize();
  auto err = llvm::verifyModule(*builder_ctx.module, &llvm::errs());
  sn_assert(!err, "Module verification failed");
}

void LLVMBuilder::dump(llvm::raw_ostream& os) {
  builder_ctx.module->print(os, new CommentWriter(), false, true);
}

llvm::DIFile* LLVMBuilder::DebugUtils::get_file(const std::string& path) {
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

llvm::Value* LLVMBuilder::build(sil::Inst* inst) {
  builder_ctx.dont_load = false;
  set_debug_info(inst);
  inst->emit(this);
  return value;
}

void LLVMBuilder::set_debug_info(const sil::Inst* node) {
  if (node) {
    auto info = node->get_location();
    if (auto f = builder_ctx.get_current_func()) {
      auto loc = llvm::DILocation::get(*llvm_ctx, info.line, info.column, f->getSubprogram());
      builder->SetCurrentDebugLocation(loc);
      return;
    }
  }
  builder->SetCurrentDebugLocation(llvm::DebugLoc());
}

llvm::Value* LLVMBuilder::expr(sil::Inst* inst) {
  builder_ctx.dont_load = false;
  return load(build(inst), inst->get_type());
}

llvm::Value* LLVMBuilder::load(llvm::Value* ptr, types::Type* type) {
  auto ll = get_type(type);
  if (builder_ctx.dont_load || !ptr->getType()->isPointerTy()) {
    builder_ctx.dont_load = false;
    return ptr;
  }
  return builder->CreateLoad(ll, ptr, ll->isPointerTy() ? "" : "loadtmp");
}

llvm::AllocaInst* LLVMBuilder::alloc(types::Type* type, const std::string& name) {
  auto bb = builder->GetInsertBlock();
  auto ll = get_type(type);
  auto entry = bb->getParent()->getEntryBlock().getTerminator();
  if (entry) {
    builder->SetInsertPoint(entry);
  }
  auto alloca = builder->CreateAlloca(ll, nullptr, name);
  builder->SetInsertPoint(bb);
  return alloca;
}

llvm::DISubprogram* LLVMBuilder::get_disubprogram(const sil::FuncDecl* node) {
  auto loc = node->get_location();
  auto file = dbg.get_file(loc.file->get_path());
  auto derive = llvm::cast<llvm::DIDerivedType>(get_ditype(node->get_type()));
  auto type = llvm::cast<llvm::DISubroutineType>(derive->getRawBaseType());
  return dbg.builder->createFunction(
    dbg.unit, node->get_printable_name(), node->get_mangled_name(), file, loc.line, type, loc.line, llvm::DINode::FlagPrototyped, 
    llvm::DISubprogram::toSPFlags(
      /*IsLocalToUnit=*/true,
      /*IsDefinition=*/true,
      /*IsOptimized=*/!dbg.debug
    )
  );
}

int LLVMBuilder::error(const std::string& msg) {
  auto ef = std::make_shared<frontend::SourceFile>();
  auto err = E(msg, frontend::SourceLocation(0, 0, 0, ef));
  err.print();
  return 1;
}

}
}
