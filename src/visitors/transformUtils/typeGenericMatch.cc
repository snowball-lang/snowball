
#include "../Transformer.h"

#include <algorithm>
#include <llvm-14/llvm/IR/Attributes.h>

namespace snowball {
namespace Syntax {

bool Transformer::typeGenericsMatch(ptr<Expression::TypeRef> ty,
                                    std::shared_ptr<types::DefinedType> comp) {
    std::vector<std::shared_ptr<types::Type>> generatedGenerics;
    for (auto x : ty->getGenerics()) {
        generatedGenerics.emplace_back(transformType(x));
    }

    bool theyEqual = true;
    bool sizeEqual = generatedGenerics.size() == comp->getGenerics().size();

    int gIndex = 0;
    while (theyEqual && sizeEqual && (generatedGenerics.size() > 0)) {
        theyEqual =
            generatedGenerics.at(gIndex)->is(comp->getGenerics().at(gIndex));
        gIndex++;
    }

    return theyEqual && sizeEqual;
}

} // namespace Syntax
} // namespace snowball