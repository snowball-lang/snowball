
#include "compiler/compiler.h"
#include "compiler/sil/binder.h"

namespace snowball {

Compiler::MiddleEndResult Compiler::run_middleend() {
  print_compiling_bar();
  frontend::sema::TypeChecker type_checker(ctx, modules);
  timer.start("Type Checking", true);
  type_checker.check();
  timer.stop("Type Checking");
  if (type_checker.handle_errors()) {
    stop_compilation();
  }
  print_compiling_bar();
  sil::Binder binder(ctx, modules, type_checker.get_universe());
  timer.start("Binding", true);
  binder.bind();
  timer.stop("Binding");
  if (binder.handle_errors()) {
    stop_compilation();
  }
  auto& sil_modules = binder.get_modules();
  // Add an output module since we need to have a main/general module to link everything to.
  auto output_namespace_path = frontend::NamespacePath(".libroot");
  sil_modules.push_back(std::make_shared<sil::Module>(output_namespace_path));
  module_paths.push_back(output_namespace_path);
  return {
    .sil_modules = sil_modules,
    .sil_insts = binder.get_insts()
  };
}

} // namespace snowball
