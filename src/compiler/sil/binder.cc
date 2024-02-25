
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

Binder::Binder(const Ctx& ctx, std::vector<frontend::Module>& modules, sema::Universe<sema::TypeCheckItem>& universe)
  : AstVisitor(ctx), Reporter(), ast_modules(modules), types(universe.get_types()), constraints(universe.get_constraints()),
    fn_decls(universe.get_fn_decls()), current_module(sil::Module(NamespacePath::dummy())) {
    }

void Binder::bind() {
  for (auto& module : ast_modules) {
    current_module = sil::Module(module.get_path());
    for (auto& item : module.get_ast()) {
      item->accept(this);
    }
  }
}

Inst* Binder::accept(ast::Node* node) {
  node->accept(this);
  return value;
}

}
}
