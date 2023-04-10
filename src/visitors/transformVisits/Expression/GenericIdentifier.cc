
#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::GenericIdentifier) {
    auto generics = utils::vector_iterate<Expression::TypeRef*,
                                          std::shared_ptr<types::Type>>(
        p_node->getGenerics(),
        [&](Expression::TypeRef* ty) { return transformType(ty); });

    auto name = p_node->getIdentifier();
    auto [value, type, functions, overloads, mod] =
        getFromIdentifier(p_node->getDBGInfo(), name, p_node->getGenerics());

    if (value) {
        E<VARIABLE_ERROR>(p_node, "Values cant contain generics!");
    } else if (functions) {
        assert(false && "TODO: Function value with generic identifire!");
    } else if (type) {
        E<VARIABLE_ERROR>(p_node, "Can't use types as values!");
    } else if (mod) {
        E<VARIABLE_ERROR>(p_node, "Can't use modules as values!");
    } else if (overloads) {
        // TODO: check if parent node is a cast
        if (overloads->size() > 1) {
            E<VARIABLE_ERROR>(
                p_node,
                FMT("Identifier points to a function with multiple overloads!",
                    p_node->getIdentifier().c_str()));
        }

        // There can only be 1 function overload without casting
        auto function = overloads->at(0);

        auto [deduced, message] = deduceFunction(function, {}, generics);
        if (!message.empty()) {
            E<VARIABLE_ERROR>(p_node, message);
        }

        auto ptr = transformFunction(function, deduced);

        auto var = ctx->module->N<ir::ValueExtract>(p_node->getDBGInfo(), ptr);
        var->setType(ptr->getType());

        this->value = var;
        return;
    }

    assert(false && "BUG: Unhandled value type!");
}

} // namespace Syntax
} // namespace snowball
