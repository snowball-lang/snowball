
#include "../../Transformer.h"

namespace snowball {
namespace Syntax {

Transformer::CastType Transformer::canCast(types::Type* from, types::Type* to) {
  // We check auto deref and auto ref first, because they are more specific
  // we don't return valid cast if they are the same type, because that is not a cast

  // Check auto deref
  if (auto ptr = utils::cast<types::ReferenceType>(from)) {
    if (ptr->getPointedType()->is(to)) { return CastType::AutoDeref; }
  }

  // Check auto ref
  if (auto ptr = utils::cast<types::ReferenceType>(to)) {
    if (ptr->getPointedType()->is(from)) { return CastType::AutoRef; }
  }

  // same thing but for pointers

  // Check auto deref or "*void to *x"
  if (auto ptr = utils::cast<types::PointerType>(from)) {
    // if (ptr->getPointedType()->is(to)) { return CastType::AutoDeref; }
    if (utils::cast<types::VoidType>(ptr->getPointedType()) && utils::cast<types::PointerType>(to)) {
      return CastType::Valid;
    }
  }

  // Check auto ref or "*x to *void"
  if (auto ptr = utils::cast<types::PointerType>(to)) {
    if (ptr->getPointedType()->is(from)) {
      return CastType::ToPointer;
    } else if (utils::cast<types::VoidType>(ptr->getPointedType()) && utils::cast<types::PointerType>(from)) {
      return CastType::Valid;
    }
  }

  // Check valid cast
  if (from->canCast(to)) return CastType::Valid;
  return CastType::NoCast;
}

} // namespace Syntax
} // namespace snowball
