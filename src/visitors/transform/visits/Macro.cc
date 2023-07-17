#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Macro) {
    auto macroName = p_node->getName();
    if (ctx->getItem(macroName).second)
        Syntax::E<VARIABLE_ERROR>(p_node, FMT("Macro with name '%s' is already defined!", macroName.c_str()));
    auto item = std::make_shared<Item>(p_node);
    // TODO: export to module
    ctx->addItem(macroName, item);
}

} // namespace Syntax
} // namespace snowball