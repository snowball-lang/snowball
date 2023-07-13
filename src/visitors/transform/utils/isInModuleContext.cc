
#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

bool Transformer::isInModuleContext(std::shared_ptr<ir::Module> m) {
    return ctx->module->getUniqueName() == m->getUniqueName();
}

} // namespace Syntax
} // namespace snowball