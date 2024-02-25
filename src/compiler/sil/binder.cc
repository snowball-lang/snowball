
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

Binder::Binder(const Ctx& ctx, std::vector<frontend::Module>& modules, sema::Universe<sema::TypeCheckItem>& universe)
  : AstVisitor(ctx), Reporter(), ast_modules(modules), types(universe.get_types()), constraints(universe.get_constraints()),
    fn_decls(universe.get_fn_decls()), current_module(sil::Module(NamespacePath::dummy())) {
    }

void Binder::bind() {
  try {
    for (auto& module : ast_modules) {
      current_module = sil::Module(module.get_path());
      for (auto& item : module.get_ast()) {
        item->accept(this);
      }
      sil_modules.push_back(current_module);
    }
  } catch (const StopBindingIR&) {
    // Do nothing
  }
}

Inst* Binder::accept(ast::Node* node) {
  node->accept(this);
  return value;
}

ast::types::Type* Binder::get_type(ast::Node* node) {
  auto type = node->get_type();
  if (type->is_unknown()) {
    err(node->get_location(), "Type should be known at this point", Error::Info {
      .highlight = fmt::format("Type '{}' should be known at this point", type->get_printable_name()),
      .help = "Maybe you forgot to set a type to a variable or forgot a generic parameter?"
    });
  }
  assert(!type->is_error());
  return type;
}

void Binder::err(const LocationHolder& holder, const std::string& message, 
    const Error::Info& info, Error::Type type, bool fatal) {
  add_error(E(message, holder.get_location(), info, type));
  if (fatal && type != Error::Type::Warn)
    throw StopBindingIR();
}

}
}
