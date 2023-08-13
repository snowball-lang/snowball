
#include "../../Transformer.h"

namespace snowball {
namespace Syntax {

Transformer::CastType Transformer::canCast(types::Type* from, types::Type* to) {
    // We check auto deref and auto ref first, because they are more specific
    // we don't return valid cast if they are the same type, because that is not a cast

    // Check auto deref
    if (auto ptr = utils::cast<types::ReferenceType>(from)) {
        if (ptr->getPointedType()->is(to)) {
            return CastType::AutoDeref;
        }
    }

    // Check auto ref
    if (auto ptr = utils::cast<types::ReferenceType>(to)) {
        if (ptr->getPointedType()->is(from)) {
            return CastType::AutoRef;
        }
    }

    // Check valid cast
    if (from->canCast(to))
        return CastType::Valid;
    return CastType::NoCast;
}

} // namespace Syntax
} // namespace snowball
