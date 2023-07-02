#include "../../../ir/values/IndexExtract.h"
#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::Index) {
    auto [r, _] = getFromIndex(p_node->getDBGInfo(), p_node, p_node->isStatic);
    auto [value, type, functions, overloads, mod, canBePrivate] = r;
    auto name = p_node->getIdentifier()->getNiceName();
    auto checkIfContextEqual =
            [&p_node = p_node, name = name, canBePrivate = canBePrivate]<typename T>(T item) -> T {
        if ((!canBePrivate) && item->isPrivate()) {
            E<TYPE_ERROR>(p_node->getDBGInfo(),
                          FMT("Variable '%s' is a private method and "
                              "it cant be accessed from this context!",
                              name.c_str()));
        }
        return item;
    };

    if (value) {
        // TODO: it should not be getValue, it should have it's own
        // value
        auto val = *value;
        if (auto casted = utils::dyn_cast<ir::Variable>(val)) {
            assert(casted != nullptr);

            // TODO: check for variable privacy
            auto var = ctx->module->N<ir::ValueExtract>(p_node->getDBGInfo(), casted);
            var->setType(casted->getType());
            this->value = var;
            return;
        } else if (auto indexExtract = utils::dyn_cast<ir::IndexExtract>(val)) {
            checkIfContextEqual(indexExtract->getField());
        } else {
            assert(false);
        }

        this->value = val;
        return;
    } else if (type) {
        E<VARIABLE_ERROR>(p_node, "Can't use types as values!");
    } else if (mod) {
        E<VARIABLE_ERROR>(p_node, "Can't use modules as values!");
    } else if (overloads || functions) {
        if ((overloads.has_value() && overloads->size() > 1) ||
            (functions.has_value() && functions->size() > 1)) {
            E<VARIABLE_ERROR>(p_node, "Index points to a function with multiple overloads!");
        }

        // There can only be 1 function overload without casting
        // TODO: maybe avoid this if the function has default generics?
        auto function = checkIfContextEqual(getFunction(p_node, r, name, {}, {}));
        bool inModule = false;
        if (auto b = utils::cast<Expression::Identifier>(p_node->getBase())) {
            auto r = getFromIdentifier(b);
            auto m = std::get<4>(r);
            utils::assert_value_type<std::shared_ptr<ir::Module>&, decltype(*m)>();

            inModule = m.has_value();
        } else if (auto b = utils::cast<Expression::Index>(p_node->getBase())) {
            auto [r, _] = getFromIndex(b->getDBGInfo(), b, b->isStatic);
            auto m = std::get<4>(r);
            utils::assert_value_type<std::shared_ptr<ir::Module>&, decltype(*m)>();

            inModule = m.has_value();
        }

        // TODO: actually check if base is a module with:
        // "getFromIdentifier" of the module
        if ((p_node->isStatic && (!function->isStatic())) && (!inModule)) {
            E<TYPE_ERROR>(p_node,
                          FMT("Can't access class method '%s' "
                              "that's not static as if it was one!",
                              function->getNiceName().c_str()));
        } else if ((!function->isStatic()) && (!inModule)) {
            E<TYPE_ERROR>(p_node,
                          "Reference to non-static member function must be "
                          "called.",
                          {.info = "did you mean to call it with no arguments?"});
        } else if ((!p_node->isStatic) && function->isStatic()) {
            E<TYPE_ERROR>(p_node,
                          FMT("Can't access static class method '%s' "
                              "as with a non-static index expression!",
                              function->getNiceName().c_str()));
        }

        auto var = ctx->module->N<ir::ValueExtract>(p_node->getDBGInfo(), function);
        var->setType(function->getType());

        this->value = var;
        return;
    }

    E<VARIABLE_ERROR>(p_node, "Cannot find index value!", {.info = "this name is not defined"});
}

} // namespace Syntax
} // namespace snowball