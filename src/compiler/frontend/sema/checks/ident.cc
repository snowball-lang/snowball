
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::Ident* node) {
  auto item = get_item(node).first;
  if (!item.has_value()) {
    auto dym = get_did_you_mean(node->get_name());
    err(node->get_location(), fmt::format("use of undeclared identifier '{}'", node->get_name()), Error::Info {
      .highlight = 
        fmt::format("Variable '{}' not found. {}", node->get_name(), 
        dym.has_value() ? fmt::format("Did you mean '{}'?", dym.value()) : ""),
      .help = fmt::format("Did you mean to declare a variable with the name '{}'?", node->get_name())
    }, Error::Type::Err, false);
    unify(node->get_type(), ast::types::ErrorType::create());
    return;
  }
  if (item.value().is_type()) {
    err(node->get_location(), fmt::format("use of type '{}' is not allowed", node->get_name()), Error::Info {
      .highlight = fmt::format("Type '{}' not found", node->get_name()),
      .help = fmt::format("Did you mean to use a variable with the name '{}'?", node->get_name()),
      .note = "You cant access types and use them as values in this context."
    }, Error::Type::Err, false);
    unify(node->get_type(), ast::types::ErrorType::create());
    return;
  }
  // TODO: check for generics if it's a function?
  unify(node->get_type(), item.value().get_type());
}

}
}
}
