
#include "compiler/sil/binder.h"
#include "compiler/utils/logger.h"

#include "compiler/compiler.h"

namespace snowball {
namespace sil {

Binder::Binder(const Ctx& ctx, std::vector<frontend::Module>& modules, sema::Universe<sema::TypeCheckItem>& universe)
  : AstVisitor(ctx), Reporter(), ast_modules(modules), types(universe.get_types()), constraints(universe.get_constraints()),
    current_module(std::make_shared<sil::Module>(NamespacePath::dummy())) {
    }

void Binder::bind() {
  try {
    // TODO: Do a second pass to fully forward declare each function!
    for (size_t j = 0; j < ast_modules.size(); j++) {
      just_declare = true;
      auto& module = ast_modules[j];
      current_module = std::make_shared<sil::Module>(module.get_path(), module.is_main);
      current_module->parent_crate = module.parent_crate;
      auto ast = module.get_ast();
      size_t i = 0;
      for (; i < ast.size(); i++) {
        auto& node = ast[i];
        if (node->is<ast::FnDecl>() ||
            node->is<ast::ClassDecl>() ||
            node->is<ast::VarDecl>()) {
          node->accept(this);
        }
      }
      just_declare = false;
      for (i = 0; i < ast.size(); i++) {
        ast[i]->accept(this);
      }
      module.set_generated(true);
      sil_modules.push_back(current_module);
      Compiler::print_compiling_bar(ast_modules);
    }
  } catch (const StopBindingIR&) {
    // Do nothing
  }
}

Inst* Binder::accept(ast::Node* node) {
  node->accept(this);
  return value;
}

std::optional<Inst*> Binder::accept(std::optional<ast::Node*> node) {
  if (node.has_value()) {
    return accept(node.value());
  }
  return std::nullopt;
}

#define THROW_ERROR(t) \
  err(loc, "Type should be known at this point", Error::Info { \
    .highlight = fmt::format("Type '{}' should be known at this point", type->get_printable_name()), \
    .help = "Maybe you forgot to set a type to a variable or forgot a generic parameter?", \
    .note = "The type '_' is used to represent an unknown type" \
  }, Error::Type::Err, t); 

ast::types::Type* Binder::check_type(ast::types::Type* type, const SourceLocation& loc) {
  if (auto as_func = type->as_func(); as_func && !as_func->is_cached()) {
    as_func->set_cached();
    as_func->recalibrate_cache();
    as_func->mutate_return_type(get_type(as_func->get_return_type(), loc));
  }
  if (type->is_unknown()) {
    auto knwon = constraints.at(type->as_unknown()->get_id());
    if (knwon->is_unknown()) {
      THROW_ERROR(false)
    }
    type = knwon;
  } else if (type->is_deep_unknown()) {
    THROW_ERROR(true) // deep unknown is a fatal error
  }
  if (type->is_error()) {
    err(loc, "Type is an error type", Error::Info {
      .highlight = fmt::format("Type '{}' is an error type", type->get_printable_name()),
      .help = "This type is an error type and should not be used",
      .note = "Error types are used to represent an error in the type system"
    }, Error::Type::Err, true);
  }
  return type;
}

#undef THROW_ERROR

ast::types::Type* Binder::get_type(ast::Node* node) {
  return check_type(node->get_type(), node->get_location());
}

ast::types::Type* Binder::get_type(ast::types::Type* type, const SourceLocation& loc) {
  return check_type(type, loc);
}

bool Binder::in_generic_context() const {
  return (ctx.ast_current_func && ctx.ast_current_func.value()->is_generic_instanced()) ||
      (ctx.ast_current_class && ctx.ast_current_class.value()->is_generic_instanced());
}

void Binder::err(const LocationHolder& holder, const std::string& message, 
    const Error::Info& info, Error::Type type, bool fatal) {
  if (in_generic_context()) {
    return; // skip duplicated errors from generic insatnce intantiations
  }
  add_error(E(message, holder.get_location(), info, type));
  if (fatal && type != Error::Type::Warn)
    throw StopBindingIR();
}

}
}
