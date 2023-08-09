
#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::shared_ptr<ir::Func> Transformer::shouldReturnOverload(std::shared_ptr<ir::Func> fn, std::deque<std::shared_ptr<ir::Func>> overloads) {
    for (auto overload : overloads) {
        bool equals = fn->getType()->is(overload->getType());
        // check generic parameters too
        if (fn->getGenerics().size() == overload->getGenerics().size()) {
            for (auto i = 0; i < fn->getGenerics().size() && equals; i++) {
                auto fnGeneric = fn->getGenerics().at(i);
                auto overloadGeneric = overload->getGenerics().at(i);
                equals = fnGeneric.second->is(overloadGeneric.second);
            }

            if (equals)
                return overload;
        }
    }

    return nullptr;
}

} // namespace Syntax
} // namespace snowball