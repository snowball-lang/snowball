#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Block) {
  ctx->withScope([&]() {
                 std::vector<std::shared_ptr<ir::Value>> insts;
                 for (auto inst : p_node->getStmts()) { insts.push_back(trans(inst)); }
                 auto val = getBuilder().createBlock(p_node->getDBGInfo(), insts);
                 val->setAttributes(p_node);
                 this->value = val;
                 });
}

} // namespace Syntax
} // namespace snowball