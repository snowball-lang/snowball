
#include "../../../utils/utils.h"
#include "../../Transformer.h"

namespace snowball {

using namespace utils;
namespace Syntax {

types::Type* Transformer::transformTypeAlias(
        const std::string& uuid, cacheComponents::Types::TypeStore& base, Expression::TypeRef* typeRef) {
  auto ty = utils::cast<Statement::TypeAlias>(base.type);
  assert(ty);

  // These are the generics generated outside of the type alias
  // context. Note that the default class generics WILL be generated
  // inside the class context.
  auto generics = typeRef != nullptr ? vector_iterate<Expression::TypeRef*, types::Type*>(
                                               typeRef->getGenerics(), [&](auto t) { return transformType(t); })
                                     : std::vector<types::Type*>{};

  // TODO: check if typeRef generics match class generics
  types::Type* transformedType;
  ctx->withState(base.state, [&]() {
    ctx->withScope([&] {
      auto backupClass = ctx->getCurrentClass();
      auto classGenerics = ty->getGenerics();

      // Fill out the remaining non-required tempalte parameters
      if (classGenerics.size() > generics.size()) {
        for (auto i = generics.size(); i < classGenerics.size(); ++i) {
          generics.push_back(transformType(classGenerics[i]->type));
        }
      }

      for (int genericCount = 0; genericCount < generics.size(); genericCount++) {
        auto generic = classGenerics.at(genericCount);
        auto generatedGeneric = generics.at(genericCount);
        auto item = std::make_shared<transform::Item>(generatedGeneric);
        // TODO:
        // item->setDBGInfo(generic->getDBGInfo());
        ctx->addItem(generic->getName(), item);
        executeGenericTests(generic->getWhereClause(), generatedGeneric, generic->getName());
      }

      auto aliasedType = transformType(ty->getType());
      auto alias = getBuilder().createTypeAlias(ty->getDBGInfo(), ty->getIdentifier(), aliasedType);
      alias->setPrivacy(ty->getPrivacy());
      alias->setGenerics(generics);
      alias->unsafeSetUUID(uuid);
      alias->setMutable(aliasedType->isMutable());
      transformedType = alias;
      // auto item = std::make_shared<transform::Item>(alias);
      // ctx->cache->setTransformedType(uuid, item);
    });
  });

  return transformedType;
}

} // namespace Syntax
} // namespace snowball
