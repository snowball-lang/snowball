
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::check_extends(ast::ClassDecl* class_decl) {
  auto node = class_decl->as<ast::ExtensionDecl>();
  assert(node && "Expected ExtensionDecl node");
  auto base = node->get_extended_type();
  auto type = get_type(base);
  bool type_is_class = type->is_class();
  type->add_extension(node);
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
