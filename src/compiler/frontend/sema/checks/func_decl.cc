
#include <cassert>

#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::FnDecl* node) {
  assert(node->get_type());
  assert(node->get_type()->is_func());
  auto fn_type = node->get_type()->as_func();
  auto path = get_namespace_path(node->get_name());
  universe.add_scope();
  assert(fn_type->get_param_types().size() == node->get_params().size());
  for (size_t i = 0; i < node->get_generics().size(); ++i) {
    auto generic = node->get_generics()[i];
    universe.add_item(generic.get_name(), ast::types::GenericType::create(generic.get_name()));
  }
  auto typed_args = fn_type->get_param_types();
  for (size_t i = 0; i < node->get_params().size(); ++i) {
    assert(node->get_params().at(i)->get_type() != nullptr);
    define_variable(node->get_params()[i], node->get_params()[i]->get_location());
  }
  node->get_body()->accept(this);
  universe.remove_scope();
}

}
}
}
