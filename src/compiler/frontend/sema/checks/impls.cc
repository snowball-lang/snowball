
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
            err(class_method->get_location(), F("Method '{}' is expected to be virtual", printable_op(class_method->get_name())), Error::Info {
              .highlight = F("Method is not virtual", printable_op(class_method->get_name())),
              .help = F("Methods that are implemented from interfaces must be virtual"),
              .note = F("This method is implemented from interface '{}'", interface_ty->get_printable_name())
            }, Error::Type::Err, false);
          }
          found = true;
          break;
        }
      }
      if (!found && !method->get_default()) {
        err(impl.get_location(), F("Class '{}' does not implement method '{}'", class_decl->get_name(), method->get_name()), Error::Info {
          .highlight = F("Method '{}' is not implemented", method->get_name()),
          .help = F("Implement method '{}' in class '{}'", method->get_name(), class_decl->get_type()->get_printable_name()),
          .note = F("Expected a method with signature: '{}'", method->get_type()->get_printable_name())
        });
      }
    }
  }
}

void TypeChecker::check_generic_impls(ast::types::Type* x, const std::vector<ast::types::Type*> impls, const SourceLocation& loc) {
  for (auto& impl : impls) {
    bool satisfies_interface = false;
    if (check_builtin_type(impl, x)) {
      satisfies_interface = true;
    } else if (auto as_class = x->as_class()) {
      auto class_decl = as_class->get_decl();
      for (auto class_impl : class_decl->get_implemented_interfaces()) {
        if (auto class_impl_ty = class_impl.get_internal_type()) {
          if (type_match(impl, class_impl_ty.value())) {
            satisfies_interface = true;
            break;
          }
        }
      }
    } else if (auto as_generic = x->as_generic()) {
      for (auto generic_impl : as_generic->get_constraints()) {
        if (type_match(impl, generic_impl)) {
          satisfies_interface = true;
          break;
        }
      }
    }
    if (!satisfies_interface) {
      check_builtin_type(x, impl);
      err(loc, fmt::format("Type '{}' does not implement interface '{}'", x->get_printable_name(), impl->get_printable_name()), Error::Info {
        .highlight = "Invalid generic instantiation",
        .help = fmt::format("Implement interface '{}' in type '{}'", impl->get_printable_name(), x->get_printable_name()),
        .note = fmt::format("Expected a type that implements interface '{}'", impl->get_printable_name())
      });
    }
  }
}

bool TypeChecker::check_builtin_type(ast::types::Type* impl, ast::types::Type* x) {
  if (auto impl_class = impl->as_class()) {
    auto builtin_name = impl_class->get_decl()->get_builtin_name();
    if (builtin_name.empty()) return false;
    return check_builtin_type(x, builtin_name);
  } else if (auto impl_generic = impl->as_generic()) {
    for (auto& impl_interface : impl_generic->get_constraints()) {
      if (type_match(x, impl_interface)) {
        return true;
      }
    }
  }
  return false;
}

bool TypeChecker::check_builtin_type(ast::types::Type* x, const std::string& builtin_name) {
  if (builtin_name == "sized") {
    if (auto as_generic = x->as_generic()) {
      for (auto& constraint : as_generic->get_constraints()) {
        if (auto as_class = constraint->as_class()) {
          if (as_class->get_decl()->get_builtin_name() == "sized") {
            return true;
          }
        }
      }
      return false;
    }
    return !x->is_void(); // TODO: maybe check here if generics also implement Sized?
  } else if (builtin_name == "copy") {
    return x->is_copyable();
  }
  sn_unreachable();
}

}
}
}
