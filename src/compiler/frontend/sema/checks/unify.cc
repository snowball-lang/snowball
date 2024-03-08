
#include <cassert>

#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

#define SUCCESS just_check ? true : (a = b, true)

bool TypeChecker::unify(ast::types::Type*& a, ast::types::Type* b, const SourceLocation& loc, bool just_check) {
  if (!a) return (a = b);
  if (a->is_int() && b->is_int()) {
    if (a->as_int()->get_bits() == b->as_int()->get_bits() &&
        a->as_int()->is_signed() == b->as_int()->is_signed()) {
      return SUCCESS;
    }
  } else if (a->is_float() && b->is_float()) {
    if (a->as_float()->get_bits() == b->as_float()->get_bits()) {
      return SUCCESS;
    }
  } else if (a->is_func() && b->is_func()) {
    auto a_func = a->as_func();
    auto b_func = b->as_func();
    if (a_func->get_param_types().size() == b_func->get_param_types().size()) {
      bool match = true;
      for (size_t i = 0; i < a_func->get_param_types().size(); i++) {
        if (!unify(a_func->get_param_types()[i], b_func->get_param_types()[i], loc, true)) {
          match = false;
          break;
        }
      }
      unify(a_func->get_return_type(), b_func->get_return_type(), loc, true);
      return SUCCESS;
    }
  } else if (a->is_generic() && b->is_generic()) {
    if (a->get_printable_name() == b->get_printable_name()) {
      return SUCCESS;
    }
  } else if (a->is_error() || b->is_error()) {
    return SUCCESS;
  } else if (a->is_unknown()) {
    return unify(universe.get_constraints().at(a->as_unknown()->get_id()), b, loc, just_check);
  }
  if (just_check) return false;
  err(loc, fmt::format("Type mismatch between '{}' and '{}'", 
    a->get_printable_name(), b->get_printable_name()), Error::Info {
      .highlight = fmt::format("Expected '{}', found '{}'", 
        a->get_printable_name(), b->get_printable_name()),
      .help = "Try casting the type to the expected type by using a cast expression",
      .see = "https://snowball-lang.gitbook.io/docs/language-reference/casting"
    }, Error::Type::Err, false);
  a = get_error_type();
  return false;
}

bool TypeChecker::type_match(ast::types::Type* a, ast::types::Type* b) {
  return unify(a, b, SourceLocation::dummy(), true);
}

}
}
}
