// only generate for macos
#if defined(__APPLE__) || defined(__MACH__) || defined(__DARWIN__) || defined(__darwin__) \
   || defined(__APPLE_CC__) || defined(__OSX__) || defined(__MACH) || defined(__MACOS__)

#include "../../../constants.h"
#include "../Linker.h"

#include <filesystem>
namespace fs = std::filesystem;

namespace snowball {
namespace linker {

void Linker::constructLinkerArgs(std::string& input, std::string& output, std::vector<std::string>& args) {
  const bool isIAMCU = target.isOSIAMCU();
  linkerArgs.clear();
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
    for (auto llvmArg : utils::split(LLVM_LDFLAGS, " ")) { linkerArgs.push_back(llvmArg); }
  }
  if (!ctx->isDynamic) linkerArgs.push_back("-static");
  else linkerArgs.push_back("-dynamic");

  switch (target.getArch()) {
    case llvm::Triple::ArchType::arm:
      linkerArgs.push_back("-arch");
      linkerArgs.push_back("arm");
      break;
    case llvm::Triple::ArchType::aarch64:
      linkerArgs.push_back("-arch");
      linkerArgs.push_back("arm64");
      break;
    case llvm::Triple::ArchType::x86:
      linkerArgs.push_back("-arch");
      linkerArgs.push_back("i386");
      break;
    case llvm::Triple::ArchType::x86_64:
      linkerArgs.push_back("-arch");
      linkerArgs.push_back("x86_64");
      break;
    default:
      break;
  }

  linkerArgs.push_back("-macosx_version_min");
  linkerArgs.push_back("10.15.0");
  linkerArgs.push_back("-syslibroot");
  linkerArgs.push_back("/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk");

  linkerArgs.push_back("-L.");
  linkerArgs.push_back("-L/opt/homebrew/lib");
  linkerArgs.push_back("-L/opt/homebrew/opt/zstd/lib");
  linkerArgs.push_back("-L/opt/homebrew/lib");
  linkerArgs.push_back("-lSystem");

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