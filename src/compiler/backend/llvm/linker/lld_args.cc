
#include <vector>
#include <string>

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
      add_soname = true;
      add("-lunwind");
      add("-lrt");
      add("-ldl");
    } break;
    default: break;
  }
  if (add_soname) {
    add("--soname");
  }
}

} // namespace backend
} // namespace snowball
