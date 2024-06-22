
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::NewExpr* node) {
  auto callee = get_type(node->get_target(), true);
  if (auto as_class = callee->as_class()) {
    if (as_class->is_interface_decl()) {
      err(node->get_location(), F("Cannot instantiate interface '{}'", as_class->get_printable_name()), Error::Info {
        .highlight = F("Interface '{}' cannot be instantiated", as_class->get_printable_name()),
        .help = F("Did you mean to instantiate a class that implements the interface '{}'?", as_class->get_printable_name()),
        .note = "Interfaces cannot be instantiated, only classes can."
      });
    }
    auto base = node->get_target().get_name();
    auto index = ast::MemberAccess::create(node->get_location(), base, 
      ast::Ident::create(node->get_location(), op_to_string(
        Operator::New
      )), ast::MemberAccess::AccessType::Static);
    node->set_caller(index);
    visit(node->as<ast::Call>());
  }
  err(node->get_location(), F("Cannot instantiate type '{}'", callee->get_printable_name()), Error::Info {
    .highlight = F("Type '{}' cannot be instantiated", callee->get_printable_name()),
    .help = F("Did you mean to instantiate a class?")
  });
}

}
}
}
