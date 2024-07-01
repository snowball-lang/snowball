
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::check_extends(ast::ClassDecl* class_decl) {
  auto node = class_decl->as<ast::ExtensionDecl>();
  assert(node && "Expected ExtensionDecl node");
  auto base = node->get_extended_type();
  auto type = get_type(base, /*no_unknown=*/true, /*no_generic_check=*/true);
  if (!type->is_extensible()) {
    err(base.get_location(), "Cannot extend this type", Error::Info {
      .highlight = "Cannot extend this type",
      .help = "Only classes and interfaces can be extended",
      .see = "https://snowball-lang.gitbook.io/docs/language-reference/classes/extensions"
    });
  }
  auto as_extension = type->as_extensible();
  assert(as_extension && "Expected ExtensionType");
  extension_registry[as_extension->get_id()].push_back(node);
  bool type_is_class = type->is_class();
  unify(class_decl->get_type(), type);
  for (auto& func : node->get_funcs()) {
    if (func->get_virtual() && !type_is_class) {
      err(func->get_location(), "Only classes can have virtual functions", Error::Info {
        .highlight = "Only classes can have virtual functions",
        .help = "Virtual functions are functions that can be overridden by subclasses",
        .see = "https://snowball-lang.gitbook.io/docs/language-reference/classes/virtual-functions"
      });
    }
  }
  if (type_is_class) {
    auto as_class = type->as_class();
    sn_assert(as_class->get_generics().size() == 0, "TODO: Implement generic classes in extensions");
    if (as_class->is_interface_decl()) {
      err(node->get_location(), "Interfaces cannot be extended", Error::Info {
        .highlight = "Interfaces cannot be extended",
        .help = "Interfaces are a special type of class that cannot be instantiated and can only contain abstract methods",
        .see = "https://snowball-lang.gitbook.io/docs/language-reference/classes/interfaces"
      }, Error::Type::Err, false);
    }
  }
}

}
}
}
