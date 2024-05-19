
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

TypeChecker::CastType TypeChecker::can_cast(ast::types::Type* from, ast::types::Type* to) {
  if (type_match(from, to)) {
    return CastType::NoCast;
  } else if (from->reference_depth() < to->reference_depth()) {
    return CastType::AutoRef;
  } else if (from->reference_depth() > to->reference_depth()) {
    return CastType::AutoDeref;
  }
  return CastType::Invalid;
}

bool TypeChecker::try_cast(ast::Node* node, ast::types::Type* to) {
  auto from = node->get_type();
  auto cast = can_cast(from, to);
  switch (cast) {
    case CastType::NoCast:
      break;
    case CastType::AutoRef:
      sn_assert(false, "AutoRef not implemented");
    case CastType::AutoDeref:
      sn_assert(false, "AutoDeref not implemented");
    case CastType::Cast:
      sn_assert(false, "Cast not implemented");
    case CastType::Invalid:
      return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

}
}
}
