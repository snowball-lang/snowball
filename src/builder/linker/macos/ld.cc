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
  for (auto& lib : linkedLibraries) {
    linkerArgs.push_back("-l:" + lib);
    DEBUG_CODEGEN("Linking library: %s", lib.c_str());
  }
  if (ctx.withCXXStd) {
    auto libs = utils::get_lib_folder() / ".." / _SNOWBALL_LIBRARY_OBJ;
    linkerArgs.push_back("-L" + libs.string());
    linkerArgs.push_back("-lsnowballrt");
  }
  linkerArgs.push_back(input);
  for (auto& arg : args) linkerArgs.push_back(arg);
  if (ctx.withStd) {
    for (auto llvmArg : utils::split(LLVM_LDFLAGS, " ")) { linkerArgs.push_back(llvmArg); }
  }
  if (!ctx.isDynamic)
    linkerArgs.push_back("-static");
  linkerArgs.push_back("-arch");
  // TODO: check this out: https://codebrowser.dev/llvm/clang/lib/Driver/ToolChain.cpp.html
  linkerArgs.push_back(target.getArchName().str());
  linkerArgs.push_back("-L.");
  linkerArgs.push_back("-L/opt/homebrew/lib");
  // TODO: we might not find it and we will need to search for System.B
  for (auto& rpath : rpaths) {
    linkerArgs.push_back("-L" + rpath);
    linkerArgs.push_back("-Wl,-rpath," + rpath);
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