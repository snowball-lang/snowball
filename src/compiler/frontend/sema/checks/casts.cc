
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

TypeChecker::CastType TypeChecker::can_cast(ast::types::Type* from, ast::types::Type* to, bool is_implicit) {
  if (type_match(from, to)) {
    return CastType::NoCast;
  } else if (from->reference_depth() < to->reference_depth()) {
    return CastType::AutoRef;
  } else if (from->reference_depth() > to->reference_depth()) {
    return CastType::AutoDeref;
  }
  // Casting integer to another integer
  if (from->is_int() && to->is_int()) {
    auto from_int = from->as_int();
    auto to_int = to->as_int();
    if (from_int->is_signed() != to_int->is_signed() && !is_implicit) {
      // We can't cast signed to unsigned in an implicit cast
      return CastType::Invalid;
    }
    return CastType::Cast;
  }
  return CastType::Invalid;
}

bool TypeChecker::try_cast(ast::Expr*& node, ast::types::Type* to) {
  auto from = node->get_type();
  auto cast = can_cast(from, to);
  switch (cast) {
    case CastType::NoCast:
      break;
    case CastType::AutoRef:
      node = ast::Reference::create(node->get_location(), node);
      node->accept(this);
      node->get_type() = to;
      break;
    case CastType::AutoDeref:
      sn_assert(false, "AutoDeref not implemented");
    case CastType::Cast:
      node = ast::Cast::create(node->get_location(), node);
      node->get_type() = to;
      node->accept(this);
      break;  
    case CastType::Invalid:
      return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

void TypeChecker::visit(ast::Cast* node) {
  if (auto type = node->get_target()) {
    sn_assert(false, "TODO: Explicit cast not implemented");
    return;
  }
  assert(node->get_type() != nullptr && "Type not set");
}

}
}
}
