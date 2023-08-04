// only generate for linux
#if defined(__linux__) || defined(__gnu_linux__) || defined(__linux) || defined(__LINUX__)

#include "../../../constants.h"
#include "../Linker.h"

#include <filesystem>
namespace fs = std::filesystem;

namespace snowball {
namespace linker {

void Linker::constructLinkerArgs(std::string& input, std::string& output, std::vector<std::string>& args) {
  const bool isIAMCU = target.isOSIAMCU();
  linkerArgs.clear();
  if (ctx->isDynamic) {
    linkerArgs.push_back("--export-dynamic");
    //linkerArgs.push_back("-Bdynamic");
  } else {
    linkerArgs.push_back("-static");
    linkerArgs.push_back("-pie");
    linkerArgs.push_back("--no-dynamic-linker");
    linkerArgs.push_back("-z");
    linkerArgs.push_back("text");
  }
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
    auto libs = utils::get_lib_folder() / ".." / _SNOWBALL_LIBRARY_OBJ;
    linkerArgs.push_back("-L/usr/lib/../lib64");
    linkerArgs.push_back("-L/lib/../lib64");
    linkerArgs.push_back("-L/usr/bin/../lib/gcc/x86_64-linux-gnu/12");
    linkerArgs.push_back("-L/usr/lib/x86_64-linux-gnu");
    linkerArgs.push_back("-L/lib/x86_64-linux-gnu");
    linkerArgs.push_back("-L/lib");
    linkerArgs.push_back("-L/usr/lib");
    linkerArgs.push_back("-lsnowballrt");
    linkerArgs.push_back("-lm");
    linkerArgs.push_back("-lc");
    linkerArgs.push_back("-L" + libs.string());
  }
  linkerArgs.push_back(input);
  if (ctx->isThreaded) linkerArgs.push_back("-lpthread");
  for (auto& arg : args) linkerArgs.push_back(arg);
  // TODO: should this be with ctc->withStd?
  linkerArgs.push_back("--eh-frame-hdr");
  if (ctx->withStd) {
    for (auto llvmArg : utils::split(LLVM_LDFLAGS, " ")) { linkerArgs.push_back(llvmArg); }
  }
  if (!ctx->isDynamic) linkerArgs.push_back("-static");
  for (auto& rpath : rpaths)
    linkerArgs.push_back("--rpath=" + rpath);
  linkerArgs.push_back("-o");
  linkerArgs.push_back(output);
#if _SNOWBALL_CODEGEN_DEBUG
  linkerArgs.push_back("--verbose");
#endif
}

std::string Linker::getSharedLibraryName(std::string& library) 
  { return library + ".so"; }

} // namespace linker
} // namespace snowball

#endif