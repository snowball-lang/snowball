
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::ClassDecl* node) {
  assert(node->get_type());
  assert(node->get_type()->is_class());
  auto class_type = node->get_type()->as_class();
  auto path = get_namespace_path(node->get_name());
  sn_assert(class_type->get_path() == path, "class path mismatch");
  auto backup = ctx.current_class;
  ctx.current_class = node;
  universe.add_scope();
  assert(class_type->get_generics().size() == node->get_generics().size());
  for (const auto& generic : class_type->get_generics()) {
    sn_assert(generic->is_generic(), "generic type is not generic");
    auto as_generic = generic->as_generic();
    universe.add_item(as_generic->get_name(), as_generic);
  }
  for (auto& var : node->get_vars()) {
    var->accept(this);
    if (var->get_type()->is_deep_unknown()) {
      err(var->get_location(), "Class variable cannot be of unknown type", Error::Info {
        .highlight = fmt::format("Variable with type: {}", var->get_type()->get_printable_name()),
        .note = "Unknown types are represented as '_'",
      });
    }
  }
  for (auto& method : node->get_funcs()) {
    method->accept(this);
  }
  universe.remove_scope();
  ctx.current_class = backup;
}

}
}
}
