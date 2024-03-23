
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

Binder::Binder(const Ctx& ctx, std::vector<frontend::Module>& modules, sema::Universe<sema::TypeCheckItem>& universe)
  : AstVisitor(ctx), Reporter(), ast_modules(modules), types(universe.get_types()), constraints(universe.get_constraints()),
    fn_decls(universe.get_fn_decls()), current_module(std::make_shared<sil::Module>(NamespacePath::dummy())) {
    }

void Binder::bind(const std::map<uint64_t, std::vector<sema::MonorphosizedFn>>& generic_registry) {
  try {
    for (char i = 1; i >= 0; i--) {
      for (auto& [_, reg] : generic_registry) {
        for (auto& func : reg) func.decl->accept(this);
      }
      for (auto& module : ast_modules) {
        current_module = std::make_shared<sil::Module>(module.get_path());
        for (auto& item : module.get_ast()) {
          item->accept(this);
        }
        if (generate_bodies)
          sil_modules.push_back(current_module);
      }
      generate_bodies = (bool)i;
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
    auto knwon = constraints.at(type->as_unknown()->get_id());
    if (knwon->is_unknown()) {
      err(node->get_location(), "Type should be known at this point", Error::Info {
        .highlight = fmt::format("Type '{}' should be known at this point", type->get_printable_name()),
        .help = "Maybe you forgot to set a type to a variable or forgot a generic parameter?",
        .note = "The type '_' is used to represent an unknown type"
      });
    }
    type = knwon;
  }
  assert(!type->is_error());
  return type;
}

void Binder::err(const LocationHolder& holder, const std::string& message, 
    const Error::Info& info, Error::Type type, bool fatal) {
  if (ctx.ast_current_func && ctx.ast_current_func.value()->is_generic_instanced()) {
    return; // skip duplicated errors from generic insatnce intantiations
  }
  add_error(E(message, holder.get_location(), info, type));
  if (fatal && type != Error::Type::Warn)
    throw StopBindingIR();
}

}
}
