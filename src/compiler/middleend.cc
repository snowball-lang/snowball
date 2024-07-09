
#include "compiler/compiler.h"
#include "compiler/sil/binder.h"
#include "compiler/frontend/lint/linter.h"

namespace snowball {

Compiler::MiddleEndResult Compiler::run_middleend() {
  print_compiling_bar(modules);

  frontend::sema::TypeChecker type_checker(ctx, modules);
  timer.start("Type Checking", true);
  type_checker.check();
  timer.stop("Type Checking");
  if (type_checker.handle_errors()) {
    stop_compilation();
  }

  run_visitors();

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

using Visitors = llvm::SmallVector<frontend::GenericVisitor*, SNOWBALL_DEFAULT_VISITOR_COUNT>;

void Compiler::run_visitors() {
  for (auto& visitor : get_visitors()) {
    visitor->visit();
    if (visitor->handle_errors()) {
      stop_compilation();
    }
    delete visitor;
  }
}

Visitors Compiler::get_visitors() {
  Visitors visitors;
  visitors.push_back(new frontend::lint::Linter(ctx, modules));
  return visitors;
}

} // namespace snowball
