
#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::GenericIdentifier) {
    auto generics = utils::vector_iterate<Expression::TypeRef *,
                                          std::shared_ptr<types::Type>>(
        p_node->getGenerics(),
        [&](Expression::TypeRef *ty) { return transformType(ty); });

    auto name = p_node->getIdentifier();
    auto [value, type, functions, overloads, mod] =
        getFromIdentifier(p_node->getDBGInfo(), name, p_node->getGenerics());

    if (value) {
        E<VARIABLE_ERROR>(p_node, "Values cant contain generics!");
    } else if (functions || overloads) {
        auto c =
            getFunction(p_node, {value, type, functions, overloads, mod, /*TODO: test this: */false}, name, {},
                        p_node->getGenerics(), true);

        auto var = ctx->module->N<ir::ValueExtract>(p_node->getDBGInfo(), c);
        var->setType(c->getType());

        this->value = var;
        return;
    } else if (type) {
        E<VARIABLE_ERROR>(p_node, "Can't use types as values!");
    } else if (mod) {
        E<VARIABLE_ERROR>(p_node, "Can't use modules as values!");
    }

    assert(false && "BUG: Unhandled value type!");
}

} // namespace Syntax
} // namespace snowball
