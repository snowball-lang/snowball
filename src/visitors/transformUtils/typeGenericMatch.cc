
#include "../Transformer.h"

#include <algorithm>

namespace snowball {
namespace Syntax {

using namespace Statement;

bool Transformer::typeGenericsMatch(Expression::TypeRef* ty, std::shared_ptr<types::Type> comp) {
    std::vector<std::shared_ptr<types::Type>> generatedGenerics;
    for (auto x : ty->getGenerics()) { generatedGenerics.push_back(transformType(x)); }
    auto compAsDefinedType = utils::cast<Statement::GenericContainer<std::shared_ptr<types::Type>>>(comp.get());
    auto compGenerics = compAsDefinedType == nullptr ? std::vector<std::shared_ptr<types::Type>>{}
                                                     : compAsDefinedType->getGenerics();

    if (generatedGenerics.size() < compGenerics.size()) {
        for (auto i = generatedGenerics.size(); i < compGenerics.size(); ++i) {
            generatedGenerics.push_back(compGenerics.at(i));
        }
    }

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
