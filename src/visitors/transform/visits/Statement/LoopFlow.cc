#include "../../../../ir/values/Cast.h"
#include "../../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::LoopFlow) {
  this->value = getBuilder().createLoopFlow(
                  p_node->getDBGInfo(),
                  p_node->getFlowType()
                );
}

} // namespace Syntax
} // namespace snowball