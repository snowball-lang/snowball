#include "../../../ir/values/Cast.h"
#include "../../Transformer.h"

#include <algorithm>
#include <llvm/IR/Attributes.h>

namespace snowball {
namespace Syntax {

const DBGSourceInfo* Transformer::getExpansionData(const DBGSourceInfo* defaultDBG) {
  if (auto[dbg, call] = ctx->getFirstMacro(); dbg && call) {
    return dbg;
  }
  return defaultDBG;
}

} // namespace Syntax
} // namespace snowball
