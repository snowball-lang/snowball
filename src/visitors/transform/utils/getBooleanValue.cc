
#include "../../../ir/values/Cast.h"
#include "../../Transformer.h"

#include <algorithm>
#include <llvm/IR/Attributes.h>

namespace snowball {
namespace Syntax {

std::shared_ptr<ir::Value> Transformer::getBooleanValue(std::shared_ptr<ir::Value> value) {
  auto boolType = ctx->getBoolType();
  if (types::isIntType(value->getType(), 1)) { return value; }
  if (auto v = tryCast(value, boolType); v != nullptr) { return utils::dyn_cast<ir::Value>(v); }

  assert(false && "TODO: booleans for non-numeric types");
}

} // namespace Syntax
} // namespace snowball
