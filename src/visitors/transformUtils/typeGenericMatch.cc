
#include "../Transformer.h"

#include <algorithm>

namespace snowball {
namespace Syntax {

bool Transformer::typeGenericsMatch(Expression::TypeRef *ty,
                                    std::shared_ptr<types::Type> comp) {
    std::vector<std::shared_ptr<types::Type>> generatedGenerics;
    for (auto x : ty->getGenerics()) {
        generatedGenerics.emplace_back(transformType(x));
    }

    auto compAsDefinedType = utils::dyn_cast<types::DefinedType>(comp);
    auto compGenerics = compAsDefinedType == nullptr
                            ? std::vector<std::shared_ptr<types::Type>>{}
                            : compAsDefinedType->getGenerics();

    bool theyEqual = true;
    bool sizeEqual = generatedGenerics.size() == compGenerics.size();

    int gIndex = 0;
    while (theyEqual && sizeEqual && (generatedGenerics.size() > 0) &&
           (gIndex < generatedGenerics.size())) {
        theyEqual = generatedGenerics.at(gIndex)->is(compGenerics.at(gIndex));
        gIndex++;
    }

    return theyEqual && sizeEqual;
}

} // namespace Syntax
} // namespace snowball
