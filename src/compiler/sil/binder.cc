
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

Binder::Binder(const Ctx& ctx, std::vector<frontend::Module>& modules, sema::Universe<sema::TypeCheckItem>& universe)
  : AstVisitor(ctx), Reporter(), ast_modules(modules), types(universe.get_types()), constraints(universe.get_constraints()),
    fn_decls(universe.get_fn_decls()), current_module(std::make_shared<sil::Module>(NamespacePath::dummy())) {
    }

void Binder::bind() {
  try {
    for (size_t j = 0; j < ast_modules.size(); j++) {
      auto module = ast_modules[j];
      current_module = std::make_shared<sil::Module>(module.get_path(), module.is_main);
      current_module->parent_crate = module.parent_crate;
      for (size_t i = 0; i < module.get_ast().size(); i++) {
        module.get_ast()[i]->accept(this);
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

#define THROW_ERROR(t) \
  err(loc, "Type should be known at this point", Error::Info { \
    .highlight = fmt::format("Type '{}' should be known at this point", type->get_printable_name()), \
    .help = "Maybe you forgot to set a type to a variable or forgot a generic parameter?", \
    .note = "The type '_' is used to represent an unknown type" \
  }, Error::Type::Err, t); 

ast::types::Type* Binder::check_type(ast::types::Type*& type, const SourceLocation& loc) {
  if (type->is_unknown()) {
    auto knwon = constraints.at(type->as_unknown()->get_id());
    if (knwon->is_unknown()) {
      THROW_ERROR(false)
    }
    type = knwon;
  } else if (type->is_deep_unknown()) {
    THROW_ERROR(true) // deep unknown is a fatal error
  }
  assert(!type->is_error());
  return type;
}

#undef THROW_ERROR

ast::types::Type* Binder::get_type(ast::Node* node) {
  return check_type(node->get_type(), node->get_location());
}

void Binder::err(const LocationHolder& holder, const std::string& message, 
    const Error::Info& info, Error::Type type, bool fatal) {
  if ((ctx.ast_current_func && ctx.ast_current_func.value()->is_generic_instanced()) ||
      (ctx.ast_current_class && ctx.ast_current_class.value()->is_generic_instanced())) {
    return; // skip duplicated errors from generic insatnce intantiations
  }
  add_error(E(message, holder.get_location(), info, type));
  if (fatal && type != Error::Type::Warn)
    throw StopBindingIR();
}

}
}
