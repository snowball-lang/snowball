
#include "../../Transformer.h"

#include <algorithm>

namespace snowball {
namespace Syntax {

using namespace Statement;

bool Transformer::typeGenericsMatch(Expression::TypeRef* ty, types::Type* comp) {
  std::vector<types::Type*> generatedGenerics;
  for (auto x : ty->getGenerics()) { generatedGenerics.push_back(transformType(x)); }
  auto compAsDefinedType = utils::cast<Statement::GenericContainer<types::Type*>>(comp);
  auto compGenerics = compAsDefinedType == nullptr ? std::vector<types::Type*>{} : compAsDefinedType->getGenerics();

  if (generatedGenerics.size() < compGenerics.size()) {
    for (auto i = generatedGenerics.size(); i < compGenerics.size(); ++i) {
      generatedGenerics.push_back(compGenerics.at(i));
    }
  }

  bool theyEqual = true;
  bool sizeEqual = generatedGenerics.size() == compGenerics.size();
  int gIndex = 0;
  while (theyEqual && sizeEqual && (generatedGenerics.size() > 0) && (gIndex < generatedGenerics.size())) {
    auto generated = generatedGenerics.at(gIndex);
    auto comp = compGenerics.at(gIndex);
    theyEqual = generated->is(comp);
    // We also check by mutability
    if (theyEqual) {
      theyEqual = generated->isMutable() == comp->isMutable();
    }
    gIndex++;
  }
  return theyEqual && sizeEqual;
}

} // namespace Syntax
} // namespace snowball
