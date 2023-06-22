
#include "../../../../ast/errors/error.h"
#include "../../../../errors.h"
#include "../../DefinitveAssigment.h"

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Expression::Index) {
    auto x = p_node->getIdentifier();

    if (!p_node->isStatic) {
        auto base = p_node->getBase();
        if (auto i = utils::cast<Expression::Identifier>(base);
            i != nullptr && i->getIdentifier() == "self" && this->insideClass) {
            if (auto variable = getIdentifier("$self::" + x->getIdentifier())) {
                if (variable->second == NotInitialized) {
                    E<VARIABLE_ERROR>(p_node->getDBGInfo(),
                                      FMT("Class variable '%s' is used before "
                                          "being assigned.",
                                          x->getIdentifier().c_str()),
                                      {.info = FMT("Class variable 'self::%s' has been "
                                                   "declared but not assigned!.",
                                                   x->getIdentifier().c_str())});
                }

                return;
            }

            /* ~ error at the transformer ~ */
        } else {
            p_node->getBase()->accept(this);
        }
    }
}

} // namespace Syntax
} // namespace snowball
