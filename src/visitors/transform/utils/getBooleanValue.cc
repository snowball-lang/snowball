
#include "../../../ir/values/Cast.h"
#include "../../Transformer.h"

#include <algorithm>
#include <llvm/IR/Attributes.h>

namespace snowball {
namespace Syntax {

std::shared_ptr<ir::Value> Transformer::getBooleanValue(std::shared_ptr<ir::Value> value) {
    auto boolType = ctx->getBoolType();
    if (value->getType()->canCast(boolType)) {
        auto v = builder.createCast(value->getDBGInfo(), value, boolType);
        return utils::dyn_cast<ir::Value>(v);
    }

    assert(false && "TODO: booleans for non-numeric types");
}

} // namespace Syntax
} // namespace snowball
