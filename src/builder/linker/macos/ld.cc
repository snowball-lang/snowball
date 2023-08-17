// only generate for macos
#if defined(__APPLE__) || defined(__MACH__) || defined(__DARWIN__) || defined(__darwin__) || defined(__APPLE_CC__) ||  \
        defined(__OSX__) || defined(__MACH) || defined(__MACOS__)

#include "../../../constants.h"
#include "../Linker.h"

#include <filesystem>
namespace fs = std::filesystem;

namespace snowball {
namespace linker {

void Linker::constructLinkerArgs(std::string& input, std::string& output, std::vector<std::string>& args) {
  const bool isIAMCU = target.isOSIAMCU();
  linkerArgs.clear();
  linkerArgs.push_back("-demangle");
  linkerArgs.push_back("-lto_library");
  linkerArgs.push_back("/opt/homebrew/Cellar/llvm/" _SNOWBALL_LLVM_PACKAGE_VERSION "/lib/libLTO.dylib");
  linkerArgs.push_back("-syslibroot");
  linkerArgs.push_back("/Library/Developer/CommandLineTools/SDKs/MacOSX13.sdk");
  for (auto& lib : linkedLibraries) {
    linkerArgs.push_back("-l:" + lib);
    DEBUG_CODEGEN("Linking library: %s", lib.c_str());
  }
  if (ctx->withCXXStd) {
    auto libs = utils::get_lib_folder() / ".." / _SNOWBALL_LIBRARY_OBJ;
    linkerArgs.push_back("-L" + libs.string());
    linkerArgs.push_back("-lsnowballrt");
  } else {
    linkerArgs.push_back("--no-dynamic-linker");
    linkerArgs.push_back("-z");
    linkerArgs.push_back("text");
  }
  linkerArgs.push_back(input);
  for (auto& arg : args) linkerArgs.push_back(arg);
  if (ctx->withStd) {
    for (auto llvmArg : utils::split(LLVM_LDFLAGS, " ")) { linkerArgs.push_back(llvmArg); }
  }
  if (!ctx->isDynamic)
    linkerArgs.push_back("-static");
  else
    linkerArgs.push_back("-dynamic");

  linkerArgs.push_back("-arch");
  // TODO: check this out: https://codebrowser.dev/llvm/clang/lib/Driver/ToolChain.cpp.html
  linkerArgs.push_back(target.getArchName().str());

  linkerArgs.push_back("-L.");
  linkerArgs.push_back("-L/opt/homebrew/lib");
  linkerArgs.push_back("-L/usr/local/lib");
  linkerArgs.push_back("-L/usr/lib");
  linkerArgs.push_back("-L/opt/homebrew/opt/zstd/lib");

  // TODO: we might not find it and we will need to search for System.B
  linkerArgs.push_back("-lSystem");

  for (auto& rpath : rpaths) {
    linkerArgs.push_back("-rpath");
    linkerArgs.push_back(rpath);
  }

  linkerArgs.push_back("-o");
  linkerArgs.push_back(output);
#if _SNOWBALL_CODEGEN_DEBUG
  linkerArgs.push_back("--verbose");
#endif
}

std::string Linker::getSharedLibraryName(std::string& library) { return library + ".dylib"; }

} // namespace linker
} // namespace snowball

#endif