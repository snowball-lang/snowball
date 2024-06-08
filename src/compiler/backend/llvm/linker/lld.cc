

#include "compiler/backend/llvm/builder.h"
#include "compiler/backend/llvm/linker/args.h"

#include <lld/Common/Driver.h>
#if LDC_LLVM_VER >= 1700
LLD_HAS_DRIVER(coff)
LLD_HAS_DRIVER(elf)
LLD_HAS_DRIVER(macho)
LLD_HAS_DRIVER(wasm)
#endif

namespace snowball {
namespace backend {

bool LLVMBuilder::run_linker(
  const Ctx& ctx, std::filesystem::path obj, std::filesystem::path output,
  llvm::TargetMachine* target_machine
) {
  // can_exit == true means that LLD can and will call `exit()` when
  // errors occur. (always false for now)
  bool can_exit = false;

  const auto& triple = target_machine->getTargetTriple();
  LldArgsBuilder args_builder(target_machine, output, obj);
  const auto args = args_builder.build_c();

  if (triple.isOSBinFormatELF()) {
    return lld::elf::link(args, llvm::outs(), llvm::errs(),
                        can_exit, false);
  } else if (triple.isOSBinFormatMachO()) {
    return lld::macho::link(args, llvm::outs(), llvm::errs(),
                          can_exit, false);
  } else if (triple.isOSBinFormatCOFF()) {
    return lld::coff::link(args, llvm::outs(), llvm::errs(),
                        can_exit, false);
  } else if (triple.isOSBinFormatWasm()) {
    return lld::wasm::link(args, llvm::outs(), llvm::errs(),
                        can_exit, false);
  }
  return error(F("Unsupported target ({}) for LLD found!", triple.str()));
}

}
} // namespace snowball

