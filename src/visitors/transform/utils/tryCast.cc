
#include "../../Transformer.h"

namespace snowball {
namespace Syntax {

std::shared_ptr<ir::Value> Transformer::tryCast(std::shared_ptr<ir::Value> value, types::Type* type) {
    if (value->getType()->canCast(type)) {
        auto v = builder.createCast(value->getDBGInfo(), value, type);
        return utils::dyn_cast<ir::Value>(v);
    }

    return nullptr;
}

} // namespace Syntax
} // namespace snowball
