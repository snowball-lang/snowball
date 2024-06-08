
#include <vector>
#include <string>

#include "compiler/globals.h"
#include "compiler/backend/llvm/linker/args.h"

namespace snowball {
namespace backend {

std::vector<std::string> LldArgsBuilder::build() {
  add_default_args();
  add_platform_args();
  add_object_files();
  return ArgsBuilder::build();
}

void LldArgsBuilder::add_default_args() {
  add("lld");
  add({ "-o", output_file });
}

void LldArgsBuilder::add_user_switches() {
#define RELATIVE_OPT(opt, val) \
  if (global.opt) { add(val); }
  RELATIVE_OPT(static_link, "-static")
  else add(std::vector{"-shared", "-dynamic-linker"});

  RELATIVE_OPT(verbose, "-v")

  add(std::vector{"--eh-frame-hdr", "--gc-sections"});
  if (global.debug_opt()) {
    add("--gdb-index");
  }
}

void LldArgsBuilder::add_object_files() {
  add(obj_file);
}

void LldArgsBuilder::add_platform_args() {
  bool add_soname = false;
  auto triple = target_machine->getTargetTriple();
  switch (triple.getOS()) {
    case llvm::Triple::Linux: {
      // Note: We dont add any -lm or -lpthread here because
      //  that is already defined by the std package.
      add("-lunwind");
      add("-lrt");
      add("-ldl");
    } [[fallthrough]];
    case llvm::Triple::Darwin:
    case llvm::Triple::MacOSX:
    case llvm::Triple::FreeBSD:
    case llvm::Triple::NetBSD:
    case llvm::Triple::OpenBSD:
    case llvm::Triple::DragonFly:
      add_soname = true;
      break;
    default: break;
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
}

} // namespace backend
} // namespace snowball
