
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::check_implementations(ast::ClassDecl* class_decl) {
  for (auto& impl : class_decl->get_implemented_interfaces()) {
    auto type = impl.get_internal_type();
    assert(type.has_value());
    auto interface_ty = type.value()->as_class();
    auto interface = interface_ty->get_decl();
    for (auto& method : interface->get_funcs()) {
      auto found = false;
      for (auto& class_method : class_decl->get_funcs()) {
        if (method->get_name() == class_method->get_name() 
          && type_match(method->get_type(), class_method->get_type(), true)) {
          // note: Repeated function declarations are checked in the global scope
          if (!class_method->get_virtual()) {
            err(class_method->get_location(), fmt::format("Method '{}' is expected to be virtual", class_method->get_name()), Error::Info {
              .highlight = fmt::format("Method is not virtual", class_method->get_name()),
              .help = fmt::format("Methods that are implemented from interfaces must be virtual"),
              .note = fmt::format("This method is implemented from interface '{}'", interface_ty->get_printable_name())
            }, Error::Type::Err, false);
          }
          found = true;
          break;
        }
      }
      if (!found) {
        err(impl.get_location(), fmt::format("Class '{}' does not implement method '{}'", class_decl->get_name(), method->get_name()), Error::Info {
          .highlight = fmt::format("Method '{}' is not implemented", method->get_name()),
          .help = fmt::format("Implement method '{}' in class '{}'", method->get_name(), class_decl->get_type()->get_printable_name()),
          .note = fmt::format("Expected a method with signature: '{}'", method->get_type()->get_printable_name())
        });
      }
    }
  }
}

}
}
}
