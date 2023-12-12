// only generate for linux
#if defined(__linux__) || defined(__gnu_linux__) || defined(__linux) || defined(__LINUX__)

#include "../../../ast//errors/error.h"
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
    // linkerArgs.push_back("-pic");
    linkerArgs.push_back("--export-dynamic");
    linkerArgs.push_back("-m");
    linkerArgs.push_back("elf_x86_64");

    // linkerArgs.push_back("-Bdynamic");
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

    fs::path ld_linux_path;

    void* ld_linux_handle = dlopen("ld-linux-x86-64.so.2", RTLD_LAZY);
    if (!ld_linux_handle) { Syntax::E<LINKER_ERR>(FMT("Error getting library path: %s", dlerror())); }

    Dl_info ld_linux_info;
    if (dladdr(ld_linux_handle, &ld_linux_info)) {
      ld_linux_path = ld_linux_info.dli_fname;
    } else {
      Syntax::E<LINKER_ERR>(FMT("Error getting library path: %s", dlerror()));
    }
    
    linkerArgs.push_back(ld_linux_path);

    auto path = std::string("/usr") + PATH_SEPARATOR + _SNOWBALL_LIBRARY_OBJ;
    auto triple = getPlatformTriple();
    assert(!triple.empty() && "Unsupported platform for linking!");

    if (!dlopen("crt1.o", RTLD_LAZY)) {
      // dlopen returns `<absolute path>/crt1.o: only ET_DYN and ET_EXEC can be loaded`
      // this is abusing that fact to get the absolute path
      std::string err = dlerror();
      std::size_t delim = err.find(':');
      if (delim != std::string::npos) {
        linkerArgs.push_back(err.substr(0, delim));
      } else {
        Syntax::E<LINKER_ERR>(err);
      }
    } else {
      Syntax::E<LINKER_ERR>("crt1.o was loaded as a shared library");
    }

    if (!dlopen("crti.o", RTLD_LAZY)) {
      // dlopen returns `<absolute path>/crt1.o: only ET_DYN and ET_EXEC can be loaded`
      // this is abusing that fact to get the absolute path
      std::string err = dlerror();
      std::size_t delim = err.find(':');
      if (delim != std::string::npos) {
        linkerArgs.push_back(err.substr(0, delim));
      } else {
        Syntax::E<LINKER_ERR>(err);
      }
    } else {
      Syntax::E<LINKER_ERR>("crti.o was loaded as a shared library");
    }

    if (!isIAMCU) {
      if (!dlopen("crtn.o", RTLD_LAZY)) {
        // dlopen returns `<absolute path>/crt1.o: only ET_DYN and ET_EXEC can be loaded`
        // this is abusing that fact to get the absolute path
        std::string err = dlerror();
        std::size_t delim = err.find(':');
        if (delim != std::string::npos) {
          linkerArgs.push_back(err.substr(0, delim));
        } else {
          Syntax::E<LINKER_ERR>(err);
        }
      } else {
        Syntax::E<LINKER_ERR>("crtn.o was loaded as a shared library");
      }
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
  for (auto& rpath : rpaths) linkerArgs.push_back("--rpath=" + rpath);
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