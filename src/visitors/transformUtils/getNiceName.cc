#include "../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::string
Transformer::getNameWithBase(const std::string name) {
    // TODO: class
    std::string base;
    if (!ctx->module->isMain()) { base += ctx->module->getName() + "::"; }

    return base + name;
}

} // namespace Syntax
} // namespace snowball