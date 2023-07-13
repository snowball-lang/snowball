
#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

bool Transformer::isInClassContext(std::shared_ptr<types::Type> ty) {
    auto cls = ctx->getCurrentClass();
    if (cls == nullptr) return false;

    return cls->is(ty.get());
}

} // namespace Syntax
} // namespace snowball