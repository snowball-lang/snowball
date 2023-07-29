// only generate for linux
#if defined(__linux__) || defined(__unix__) || defined(__unix)

#include "../../../constants.h"
#include "../Linker.h"

#include <filesystem>
namespace fs = std::filesystem;

namespace snowball {
namespace linker {

void Linker::constructLinkerArgs(std::string& input, std::string& output, std::vector<std::string>& args) {
  const bool isIAMCU = target.isOSIAMCU();
  linkerArgs.clear();
  if (ctx->withStd) {
    // TODO: check if this works for all platforms
    linkerArgs.push_back("-dynamic-linker");
    linkerArgs.push_back("/lib64/ld-linux-x86-64.so.2");

    auto path = std::string("/usr") + PATH_SEPARATOR + _SNOWBALL_LIBRARY_OBJ;
    auto triple = getPlatformTriple();
    assert(!triple.empty() && "Unsupported platform for linking!");
    auto platformPath = fs::path(path) / triple;
    linkerArgs.push_back(platformPath / "crt1.o");
    linkerArgs.push_back(platformPath / "crti.o");
    if (!isIAMCU) {
      linkerArgs.push_back(platformPath / "crtn.o");
    } else {
      // TODO: add crtbegin.o and crtend.o
    }
  }
  for (auto& lib : linkedLibraries) {
    linkerArgs.push_back("-l:" + lib);
    DEBUG_CODEGEN("Linking library: %s", lib.c_str());
  }
  if (ctx->withCXXStd) {
    linkerArgs.push_back("-lm");
    linkerArgs.push_back("-lunwind");
    linkerArgs.push_back("-lc");
    linkerArgs.push_back("-L" STATICLIB_DIR PATH_SEPARATOR _SNOWBALL_LIBRARY_OBJ);
    linkerArgs.push_back("-lSnowballRuntime");
  }
  linkerArgs.push_back(input);
  if (ctx->isThreaded) linkerArgs.push_back("-lpthread");
  for (auto& arg : args) linkerArgs.push_back(arg);
  if (ctx->withStd) {
    linkerArgs.push_back("--eh-frame-hdr");
    for (auto llvmArg : utils::split(LLVM_LDFLAGS, " ")) { linkerArgs.push_back(llvmArg); }
  }
  if (!ctx->isDynamic) linkerArgs.push_back("-static");
  linkerArgs.push_back("-o");
  linkerArgs.push_back(output);
#if _SNOWBALL_CODEGEN_DEBUG
  linkerArgs.push_back("--verbose");
#endif
}

std::string Linker::getSharedLibraryName(std::string& library) { return library + ".so"; }

} // namespace linker
} // namespace snowball

#endif