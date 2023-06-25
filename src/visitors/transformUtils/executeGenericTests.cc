#include "../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

void Transformer::executeGenericTests(Syntax::Expression::WhereClause* clause,
                                      std::shared_ptr<types::Type> generic) {
    if (clause == nullptr) { return; }
    for (auto test : clause->getChecks()) {
        auto genericsCopy = test->getGenerics();
        auto generics = genericsCopy;
        generics.insert(generics.begin(), generic->toRef());
        test->setGenerics(generics);

        transformType(test);

        // Reset generics
        test->setGenerics(genericsCopy);
    }
}

} // namespace Syntax
} // namespace snowball