
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::MemberAccess* node) {
  auto [item, name, ignore_self] = get_item(node);
  assert(!ignore_self);
  if (!item.has_value()) {
    err(node->get_location(), fmt::format("use of undeclared identifier '{}'", name), Error::Info {
      .highlight = 
        fmt::format("Variable '{}' not found.", name),
      .help = fmt::format("Did you mean to declare a variable with the name '{}'?", name)
    }, Error::Type::Err, false);
    unify(node->get_type(), get_error_type());
    return;
  }
  if (item.value().is_type()) {
    err(node->get_location(), fmt::format("use of type '{}' is not allowed", item.value().get_type()->get_printable_name()), Error::Info {
      .highlight = fmt::format("Expected a value but '{}' is a type", name),
      .help = fmt::format("Did you mean to use a variable with the name '{}'?", name),
      .note = "You cant access types and use them as values in this context."
    }, Error::Type::Err, false);
    unify(node->get_type(), get_error_type());
    return;
  }
  if (item.value().is_module()) {
    err(node->get_location(), fmt::format("cannot call module '{}'", name), Error::Info {
      .highlight = fmt::format("Module '{}' cannot be called", name),
      .help = fmt::format("Did you mean to call a function or access a variable in the module '{}'?", name)
    }, Error::Type::Err, false);
    return;
  }
  if (item.value().is_var()) {
    auto var = item.value().get_var();
    var->set_used();
    if (auto idx = item.value().get_index()) {
      node->set_index(idx.value());
    } else {
      node->set_var_id(var->get_id());
    }
    node->get_object()->accept(this);
    unify(node->get_type(), var->get_type(), node->get_location());
    return;
  }
  auto fn_decls = item.value().get_funcs();
  auto member = node->get_member();
  auto fn = get_best_match(fn_decls, {}, node->get_location(), member->get_generics(), true);
  // todo: set function as used
  node->set_var_id(fn->get_id());
  unify(node->get_type(), fn->get_type(), node->get_location());
}

}
}
}

