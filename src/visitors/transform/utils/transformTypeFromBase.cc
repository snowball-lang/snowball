
#include "../../Transformer.h"

namespace snowball {
namespace Syntax {

types::Type* Transformer::transformTypeFromBase(
        const std::string& uuid, cacheComponents::Types::TypeStore& base, Expression::TypeRef* typeRef
) {
  Statement::GenericContainer<>::GenericList generics;
  // TODO: check if there's another way to avoid repetition of code

  if (auto c = utils::cast<Statement::DefinedTypeDef>(base.type)) {
    generics = c->getGenerics();
  } else if (auto c = utils::cast<Statement::TypeAlias>(base.type)) {
    generics = c->getGenerics();
  } else {
    assert(false);
  }

  auto requiredArguments = 0;
  for (auto arg : generics) {
    // Check for if there's no default type
    if (arg->type == nullptr) { requiredArguments++; }
  }

  if (typeRef->getGenerics().size() < requiredArguments || typeRef->getGenerics().size() > generics.size()) {
    E<TYPE_ERROR>(
            typeRef,
            FMT("Type '%s' require to have %i generic "
                "argument(s) but %i where given!",
                typeRef->getPrettyName().c_str(),
                requiredArguments,
                typeRef->getGenerics().size())
    );
  }

  if (auto x = utils::cast<Statement::TypeAlias>(base.type)) {
    return transformTypeAlias(uuid, base, typeRef);
  } else if (auto x = utils::cast<Statement::DefinedTypeDef>(base.type)) {
    return transformClass(uuid, base, typeRef);
  }

  assert(false);
}

} // namespace Syntax
} // namespace snowball
