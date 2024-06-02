
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::Ident* node) {
  auto item = get_item(node).item;
  if (!item.has_value()) {
    auto dym = get_did_you_mean(node->get_name());
    err(node->get_location(), fmt::format("use of undeclared identifier '{}'", node->get_name()), Error::Info {
      .highlight = 
        fmt::format("Variable '{}' not found. {}", node->get_name(), 
        dym.has_value() ? fmt::format("Did you mean '{}'?", dym.value()) : ""),
      .help = fmt::format("Did you mean to declare a variable with the name '{}'?", node->get_name())
    }, Error::Type::Err, false);
    unify(node->get_type(), get_error_type());
    return;
  }
  if (item.value().is_type()) {
    err(node->get_location(), fmt::format("use of type '{}' is not allowed", item.value().get_type()->get_printable_name()), Error::Info {
      .highlight = fmt::format("Expected a value but '{}' is a type", node->get_name()),
      .help = fmt::format("Did you mean to use a variable with the name '{}'?", node->get_name()),
      .note = "You cant access types and use them as values in this context."
    }, Error::Type::Err, false);
    unify(node->get_type(), get_error_type());
    return;
  }
  if (item.value().is_module()) {
    err(node->get_location(), fmt::format("cannot call module '{}'", node->get_name()), Error::Info {
      .highlight = fmt::format("Module '{}' cannot be called", node->get_name()),
      .help = fmt::format("Did you mean to call a function or access a variable in the module '{}'?", node->get_name())
    }, Error::Type::Err, false);
    return;
  }
  if (item.value().is_var()) {
    auto var = item.value().get_var();
    var->set_used();
    node->set_var_id(var->get_id());
    unify(node->get_type(), var->get_type(), node->get_location());
    return;
  }
  auto fn_decls = item.value().get_funcs();
  auto fn = get_best_match(fn_decls, {}, node->get_location(), node->get_generics(), true);
  // todo: set function as used
  node->set_var_id(fn->get_id());
  unify(node->get_type(), fn->get_type(), node->get_location());
}

}
}
}
