#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::Identifier) {
    auto name = p_node->getIdentifier();
    auto [value, type, functions, overloads, mod] =
        getFromIdentifier(p_node->getDBGInfo(), name);

    if (value) {
        // TODO: it should not be getValue, it should have it's own value
        auto val    = *value;
        auto casted = std::dynamic_pointer_cast<ir::Variable>(val);
        assert(casted != nullptr);

        auto var =
            ctx->module->N<ir::ValueExtract>(p_node->getDBGInfo(), casted);
        var->setType(casted->getType());

        this->value = var;
        return;
    } else if (functions) {
        // TODO: check if parent node is a cast
        if (functions->size() > 1) {
            E<VARIABLE_ERROR>(p_node, FMT("Identifier '%s' points to a "
                                          "function with multiple overloads!",
                                          name.c_str()));
        }

        // There can only be 1 function overload without casting
        auto function = functions->at(0);
        auto var =
            ctx->module->N<ir::ValueExtract>(p_node->getDBGInfo(), function);
        var->setType(function->getType());

        this->value = var;
        return;
    } else if (type) {
        E<VARIABLE_ERROR>(p_node, "Can't use types as values!");
    } else if (mod) {
        E<VARIABLE_ERROR>(p_node, "Can't use modules as values!");
    } else if (overloads) {
        if (overloads->size() > 1) {
            E<VARIABLE_ERROR>(
                p_node,
                FMT("Identifier points to a function with multiple overloads!",
                    p_node->getIdentifier().c_str()));
        }

        // There can only be 1 function overload without casting
        auto function = overloads->at(0);

        // TODO: maybe avoid this if the function has default generics?
        if (function.function->getGenerics().size() > 0) {
            E<VARIABLE_ERROR>(p_node,
                              FMT("Function '%s' requires to have generics!",
                                  p_node->getIdentifier().c_str()));
        }

        auto ptr = transformFunction(function, {});

        auto var = ctx->module->N<ir::ValueExtract>(p_node->getDBGInfo(), ptr);
        var->setType(ptr->getType());

        this->value = var;
        return;
    }

    E<VARIABLE_ERROR>(p_node, FMT("Cannot find identifier `%s`!", name.c_str()),
                      "this name is not defined");
}

} // namespace Syntax
} // namespace snowball