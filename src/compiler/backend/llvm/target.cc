
#include "compiler/globals.h"
#include "compiler/utils/utils.h"
#include "compiler/backend/llvm/builder.h"

#include <llvm/CodeGen/CommandFlags.h>

namespace snowball {
namespace backend {

static llvm::Triple get_target_triple() {
  llvm::Triple triple;
  // TODO: Make the user be more descriptive about the target
  switch (global.target) {
    case Target::Windows:
      triple.setOS(llvm::Triple::Win32);
      triple.setEnvironment(llvm::Triple::MSVC);
      triple.setObjectFormat(llvm::Triple::COFF);
      triple.setVendor(llvm::Triple::PC);
      break;
    case Target::Linux:
      triple.setOS(llvm::Triple::Linux);
      triple.setEnvironment(llvm::Triple::GNU);
      break;
    case Target::MacOS:
      triple.setOS(llvm::Triple::MacOSX);
      triple.setVendor(llvm::Triple::Apple);
      break;
    default: sn_unreachable();
  }
  switch (global.arch) {
    case Arch::Arm64:
      triple.setArch(llvm::Triple::aarch64);
      break;
    case Arch::X86_64:
      triple.setArch(llvm::Triple::x86_64);
      break;
    default: sn_unreachable();
  }
  switch (global.explicit_bitness) {
    case ExplicitBitness::Bit64:
      triple = triple.get64BitArchVariant();
      break;
    case ExplicitBitness::Bit32:
      triple = triple.get32BitArchVariant();
      if (triple.getArch() == llvm::Triple::ArchType::x86)
        triple.setArchName("i686"); // not i386
      break;
    case ExplicitBitness::None: break;
    default: sn_unreachable();
  }
  return triple;
}

static llvm::CodeGenOpt::Level get_opt_level() {
  switch (global.opt_level) {
    case OptLevel::Debug:
      return llvm::CodeGenOpt::None;
    case OptLevel::Release:
    case OptLevel::ReleaseFast:
    case OptLevel::ReleaseWithDebug:
      return llvm::CodeGenOpt::Aggressive;
    default: sn_unreachable();
  }
}

static llvm::Reloc::Model get_reloc_model(const llvm::Triple& triple) {
  if (triple.isOSLinux() || triple.isOSDarwin() || triple.isOSFreeBSD())
    return llvm::Reloc::PIC_;
  switch (triple.getArch()) {
    case llvm::Triple::arm:
    case llvm::Triple::armeb:
    case llvm::Triple::thumb:
    case llvm::Triple::thumbeb:
      return llvm::Reloc::Static;
    default: break;
  }
  return llvm::Reloc::PIC_;
}

static auto get_code_model(const llvm::Triple& triple) {
  return llvm::codegen::getExplicitCodeModel();
}

static bool has_feature(const std::string& feature, const std::vector<std::string>& features) {
  return std::find(features.begin(), features.end(), "+"+feature) != features.end();
}

static std::string get_target_cpu(const llvm::Triple& triple, const std::vector<std::string>& features) {
  switch (triple.getArch()) {
    case llvm::Triple::x86:
    case llvm::Triple::x86_64: {
      if (triple.isOSDarwin()) {
        return triple.isArch64Bit() ? "core2" : "yonah";
      } else if (triple.isArch64Bit()) {
        if (has_feature("avx512f", features))
          return "skylake-avx512";
        if (has_feature("avx2", features))
          return "haswell";
        if (has_feature("avx", features))
          return "sandybridge";
        return "x86-64";
      } else if (triple.getOSName().startswith("haiku")) {
        return "i586";
      } else if (triple.getOSName().startswith("openbsd")) {
        return "i486";
      } else if (triple.getOSName().startswith("freebsd")) {
        return "i486";
      } else if (triple.getOSName().startswith("netbsd")) {
        return "i486";
      } else if (triple.getOSName().startswith("openbsd")) {
        return "i486";
      } else if (triple.getOSName().startswith("dragonfly")) {
        return "i486";
      }
      if (has_feature("avx", features))
        return "sandybridge";
      return "pentium4";
    }
    case llvm::Triple::riscv32:
      return "generic-rv32";
    case llvm::Triple::riscv64:
      return "generic-rv64";
    case llvm::Triple::loongarch32:
      return "generic-la32";
    case llvm::Triple::loongarch64:
      return "generic-la64";
    case llvm::Triple::aarch64: // AArch64
    case llvm::Triple::aarch64_be: 

    case llvm::Triple::arm: // ARM
    case llvm::Triple::armeb:
    case llvm::Triple::thumb: // Can't be bothered right now, let's just use the default
    default: 
      return "generic";
  }
}

const char* get_target_abi(const llvm::Triple& triple, const std::vector<std::string>& features) {
  switch (triple.getArch()) {
    case llvm::Triple::mips64:
    case llvm::Triple::mips64el:
      return "n32";
    case llvm::Triple::ppc64:
      return "elfv1";
    case llvm::Triple::ppc64le:
      return "elfv2";
    case llvm::Triple::riscv32:
    case llvm::Triple::riscv64:
      return "ilp32";
    case llvm::Triple::loongarch32:
      if (has_feature("d", features))
        return "ilp32d";
      if (has_feature("f", features))
        return "ilp32f";
      return "ilp32s";
    case llvm::Triple::loongarch64:
      if (has_feature("f", features))
        return "lp64f";
      return "lp64d";
    default:
      return ""; // TODO: Add more ABIs
  }
}

static llvm::FloatABI::ABIType get_float_abi(std::vector<std::string>& features) {
  auto float_abi = global.float_abi;
  if (float_abi == FloatABI::Default)
    float_abi = FloatABI::Soft; // TODO: Stop being lazy!
  switch (float_abi) {
    case FloatABI::Hard:
      return llvm::FloatABI::Hard;
    case FloatABI::Soft:
      return llvm::FloatABI::Soft;
    case FloatABI::SoftFP: {
      features.push_back("+soft-float");
      return llvm::FloatABI::Soft;
    }
    default: sn_unreachable();
  }
}

llvm::TargetMachine* get_target_machine() {
  static llvm::TargetMachine* target_machine = nullptr;
  if (target_machine)
    return target_machine;
  auto target_triple = get_target_triple();
  std::vector<std::string> features;
  auto target_options = llvm::codegen::InitTargetOptionsFromCodeGenFlags(target_triple);
  if (target_options.MCOptions.ABIName.empty())
    target_options.MCOptions.ABIName = get_target_abi(target_triple, features);
  if (!target_triple.isOSBinFormatMachO()) {
    target_options.FunctionSections = true;
    target_options.DataSections = true;
  }
  target_options.FloatABIType = get_float_abi(features);
  auto cpu = get_target_cpu(target_triple, features); // TODO: let user decide too!
  auto opt_level = get_opt_level();
  auto reloc_model = get_reloc_model(target_triple);
  auto code_model = get_code_model(target_triple);
  std::string error;
  auto target = llvm::TargetRegistry::lookupTarget(target_triple.normalize(), error);
  target_machine = target->createTargetMachine(
    target_triple.normalize(), cpu, utils::join(features, ","), target_options, 
    reloc_model, code_model, opt_level);
  return target_machine;
}

}
} // namespace snowball
