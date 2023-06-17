#include "../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Block) {
    ctx->withScope([&]() {
        std::vector<std::shared_ptr<ir::Value>> insts;
        for (auto inst : p_node->getStmts()) {
            inst->accept(this);
            insts.push_back(this->value);
        }

        auto val = ctx->module->N<ir::Block>(p_node->getDBGInfo(), insts);
        this->value = val;
    });
}

} // namespace Syntax
} // namespace snowball