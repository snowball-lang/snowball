
#include <cassert>

#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

using Extern = frontend::ast::AttributedNode::Extern;

void TypeChecker::visit(ast::FnDecl* node) {
  if (node->is_generic_instanced()) {
    // Skip generic instanced functions
    return;
  }
  assert(node->get_type());
  assert(node->get_type()->is_func());
  auto fn_type = node->get_type()->as_func();
  auto path = get_namespace_path(node->get_name());
  debug(F("Checking function declaration '{}'", path));
  auto backup = ctx.current_function;
  ctx.current_function = node;
  enter_scope();
  assert(fn_type->get_param_types().size() == node->get_params().size());
  for (size_t i = 0; i < node->get_generics().size(); ++i) {
    auto generic = node->get_generics()[i];
    universe.add_item(generic.get_name(), create_generic_type(generic));
  }
  auto typed_args = fn_type->get_param_types();
  for (size_t i = 0; i < node->get_params().size(); ++i) {
    assert(node->get_params().at(i)->get_type() != nullptr);
    auto param = node->get_params().at(i);
    param->mutate_arg_for(node);
    define_variable(param, param->get_location(), true);
    if (node->get_external() != Extern::None) {
      param->set_used();
    }
  }
  if (auto block = node->get_body()) {
    block.value()->accept(this);
  }
  ctx.current_function = backup;
  (void)exit_scope();
}

}
}
}
