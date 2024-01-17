#include "../../../constants.h"
#include "../../../utils/utils.h"
#include "../Linker.h"

#include <llvm/Support/Host.h>

namespace snowball {
namespace linker {

Linker::Linker(GlobalContext ctx, std::string ldPath) : ctx(ctx), ldPath(ldPath) {
  target = llvm::Triple(llvm::sys::getProcessTriple());
}
void Linker::addLibrary(std::string& library) { linkedLibraries.push_back(library); }

int Linker::link(std::string& input, std::string& output, std::vector<std::string>& args) {
  auto current = utils::get_lib_folder();
  rpaths.insert(rpaths.begin(), (current / ".." / "lib").string());

  constructLinkerArgs(input, output, args);
  linkerArgs.insert(linkerArgs.begin(), ldPath);
  DEBUG_CODEGEN("Invoking linker (" LD_PATH " with stdlib at " STATICLIB_DIR ")");
  DEBUG_CODEGEN("Linker command: %s", utils::join(linkerArgs.begin(), linkerArgs.end(), " ").c_str());
  int ldstatus = os::Driver::run(linkerArgs);
  if (ldstatus) { throw SNError(LINKER_ERR, Logger::format("Linking with " LD_PATH " failed with code %d", ldstatus)); }

#if __APPLE__
  if (ctx.opt == app::Options::Optimization::OPTIMIZE_O0) os::Driver::run({"dsymutil", output});
#endif

  return EXIT_SUCCESS;
}

std::string Linker::getPlatformTriple() {
  switch (target.getArch()) {
    case llvm::Triple::arm:
    case llvm::Triple::thumb: return "arm-linux-gnueabi";
    case llvm::Triple::armeb:
    case llvm::Triple::thumbeb: return "armeb-linux-gnueabi";
    case llvm::Triple::x86: return "i386-linux-gnu";
    case llvm::Triple::x86_64: return "x86_64-linux-gnu";
    case llvm::Triple::aarch64: return "aarch64-linux-gnu";
    case llvm::Triple::aarch64_be: return "aarch64_be-linux-gnu";
    default: return "";
  };

  return "";
}

} // namespace linker
} // namespace snowball
