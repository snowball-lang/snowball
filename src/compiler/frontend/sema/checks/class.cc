
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::ClassDecl* node) {
  if (node->is_generic_instanced()) {
    // We don't need to check the class if it's already instanced
    return;
  }
  assert(node->get_type());
  assert(node->get_type()->is_class());
  auto class_type = node->get_type()->as_class();
  auto path = get_namespace_path(node->get_name());
  sn_assert(class_type->get_path() == path, "class path mismatch");
  auto backup = ctx.current_class;
  ctx.current_class = node;
  universe.add_scope();
  assert(class_type->get_generics().size() == node->get_generics().size());
  size_t generic_index = 0;
  for (auto& generic : class_type->get_generics()) {
    sn_assert(generic->is_generic(), "generic type is not generic");
    auto as_generic = generic->as_generic();
    universe.add_item(as_generic->get_name(), as_generic);
    auto& constraints = node->get_generics()[generic_index].get_constraints();
    for (auto& constraint : constraints) {
      as_generic->add_constraints(get_type(constraint));
    }
    generic_index++;
  }
  for (auto& impl : node->get_implemented_interfaces()) {
    auto interface = get_type(impl);
    impl.set_internal_type(interface);
    bool is_interface = false;
    if (auto as_class = interface->as_class()) {
      is_interface = as_class->is_interface_decl();
    }
    if (!is_interface) {
      err(impl.get_location(), "Implemented interface is not an interface", Error::Info {
        .highlight = fmt::format("Implemented interface is of type: {}", interface->get_printable_name()),
        .note = "Interfaces are represented as 'interface' keyword",
      });
    }
  }
  check_implementations(node);
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
    debug(F("\tChecking method ({}): '{}' with type: {}", node->get_type()->get_printable_name(), 
      method->get_name(), method->get_type()->get_printable_name()));
    method->set_parent_type(node->get_type());
    method->accept(this);
  }
  universe.remove_scope();
  ctx.current_class = backup;
}

}
}
}
