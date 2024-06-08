
#include <vector>
#include <string>

#include "compiler/globals.h"
#include "compiler/backend/llvm/linker/args.h"

#include "compiler/utils/utils.h"
#include "compiler/utils/logger.h"

namespace snowball {
namespace backend {

std::vector<std::string> LldArgsBuilder::build() {
  add_default_args();
  add_platform_args();
  add_object_files();
  add_user_switches();
  if (global.verbose) {
    utils::Logger::debug(F("LLD args: {}", utils::join(args, " ")));
  }
  return ArgsBuilder::build();
}

void LldArgsBuilder::add_default_args() {
  add("lld");
  add({ "-o", output_file });
}

void LldArgsBuilder::add_user_switches() {
#define RELATIVE_OPT(opt, val) \
  if (global.opt) { add(val); }
  auto target = target_machine->getTargetTriple();
  RELATIVE_OPT(static_link, "-static")
  RELATIVE_OPT(verbose, "-v")
  if (target.isOSBinFormatMachO()) {
    add("-macosx_version_min");
    add("10.15");
  } else if (target.isOSBinFormatELF()) {
    add(std::vector{"--eh-frame-hdr", "--gc-sections"});
  add("--hash-style=gnu");
    if (global.debug_opt()) {
      add("--gdb-index");
    }
  }
}

void LldArgsBuilder::add_object_files() {
  add(obj_file);
}

void LldArgsBuilder::add_platform_args() {
  bool add_soname = false;
  bool is_pie = false;
  auto triple = target_machine->getTargetTriple();
  switch (triple.getOS()) {
    case llvm::Triple::Linux: {
      // Note: We dont add any -lm or -lpthread here because
      //  that is already defined by the std package.
      add("-lrt");
      add("-ldl");
    } [[fallthrough]];
    case llvm::Triple::FreeBSD:
    case llvm::Triple::NetBSD:
    case llvm::Triple::OpenBSD:
    case llvm::Triple::DragonFly: {
      auto multi_arch = get_multi_arch_triple();
      add("-L/usr/lib/" + multi_arch);
      if (std::filesystem::exists("/lib/" + multi_arch)) {
        add("-L/lib/" + multi_arch);
        std::string crt1 = is_pie ? "Scrt1.o" : "crt1.o";
        add("/lib/" + multi_arch + "/" + crt1);
        add("/lib/" + multi_arch + "/crti.o");
        add("/lib/" + multi_arch + "/crtn.o");
      }
      add("-lc");
      add_dynamic_linker();
    } [[fallthrough]];
    case llvm::Triple::Darwin:
    case llvm::Triple::MacOSX: {
      add(std::vector{"-L/usr/lib", "-L/usr/local/lib", "-L/lib"});
      add_soname = true;
    } break;
    default: break;
  }
  if (triple.isOSDarwin()) {
    add("-lSystem");
    add("-arch");
    add(triple.getArchName().str());
    add("-platform_version");
    add(std::vector{"macos", "10.15", "0"});
  }
  if (triple.isWindowsGNUEnvironment()) {
    // This is really more of a kludge, as linking in the Winsock functions
    // should be handled by the pragma(lib, ...) in std.socket, but it
    // makes LDC behave as expected for now.
    add("-lws2_32");
  }
  if (add_soname && false) {
    add("-soname"); // TODO: --soname option
  }
  if (is_pie) add("-pie");
  else add(triple.isOSDarwin() ? "-no_pie" : "-no-pie");
}

std::string LldArgsBuilder::get_multi_arch_triple() {
  // NOTE: Only call on linux targets!
  auto triple = target_machine->getTargetTriple();
  switch (triple.getArch()) {
    case llvm::Triple::x86:
      return "i386-linux-gnu";
    case llvm::Triple::x86_64:
      return "x86_64-linux-gnu";
    case llvm::Triple::arm:
      return "arm-linux-gnueabi";
    case llvm::Triple::aarch64:
      return "aarch64-linux-gnu";
    case llvm::Triple::ppc:
      return "powerpc-linux-gnu";
    case llvm::Triple::ppc64:
      return "powerpc64-linux-gnu";
    case llvm::Triple::ppc64le:
      return "powerpc64le-linux-gnu";
    case llvm::Triple::mips:
      return "mips-linux-gnu";
    case llvm::Triple::mipsel:
      return "mipsel-linux-gnu";
    case llvm::Triple::mips64:
      return "mips64-linux-gnu";
    default: {
      utils::Logger::warn(F("Unknown architecture '{}' please open an issue at "
        "https://github.com/snowball-lang/snowball/issues to correctly support your target!", triple.getArchName().str()));
      return triple.str();
    }
  }
}

void LldArgsBuilder::add_dynamic_linker() {
  auto triple = target_machine->getTargetTriple();
  switch (triple.getOS()) {
    case llvm::Triple::Linux: {
      switch (triple.getArch()) {
        case llvm::Triple::x86:
          add("-dynamic-linker");
          add("/lib/ld-linux.so.2");
          break;
        case llvm::Triple::x86_64:
          add("-dynamic-linker");
          add("/lib64/ld-linux-x86-64.so.2");
          break;
        case llvm::Triple::aarch64:
          add("-dynamic-linker");
          add("/lib/ld-linux-aarch64.so.1");
          break;
        case llvm::Triple::arm:
          add("-dynamic-linker");
          add("/lib/ld-linux-armhf.so.3");
          break;
        default: break;
      }
    } break;
    case llvm::Triple::FreeBSD:
    case llvm::Triple::NetBSD:
    case llvm::Triple::OpenBSD:
    case llvm::Triple::DragonFly: {
      add("-dynamic-linker");
      add("/libexec/ld-elf.so.1");
    } break;
    case llvm::Triple::Darwin:
    case llvm::Triple::MacOSX: {
      add("-dynamic-linker");
      add("/usr/lib/dyld");
    } break;
    default: 
      utils::Logger::warn(F("Unknown OS found for dynamic linker: {}. Please open an issue at "
        "https://github.com/snowball-lang/snowball/issues to correctly support your target!", triple.getOSName().str()));
      break;
  }
}

} // namespace backend
} // namespace snowball
