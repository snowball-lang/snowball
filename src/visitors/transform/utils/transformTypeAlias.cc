
#include "../../../utils/utils.h"
#include "../../Transformer.h"

namespace snowball {

using namespace utils;
namespace Syntax {

types::Type* Transformer::transformTypeAlias(
const std::string& uuid, cacheComponents::Types::TypeStore& base, Expression::TypeRef* typeRef
) {
  auto ty = utils::cast<Statement::TypeAlias>(base.type);
  assert(ty);
  // These are the generics generated outside of the type alias
  // context. Note that the default class generics WILL be generated
  // inside the class context.
  auto generics = typeRef != nullptr ? vector_iterate<Expression::TypeRef*, types::Type*>(
                  typeRef->getGenerics(), [&](auto t) { return transformType(t); }
                  ) :
                  std::vector<types::Type*> {};
  // TODO: check if typeRef generics match class generics
  types::Type* transformedType;
  ctx->withState(base.state, [&]() {
                 ctx->withScope([&] {
                                std::vector<types::Type*> defaultGenerics;
                                int defaultGenericStart = 0;
                                auto classGenerics = ty->getGenerics();
                                for (size_t genericCount = 0; genericCount < generics.size(); genericCount++) {
                                auto generic = classGenerics.at(genericCount);
                                auto generatedGeneric = generics.at(genericCount);
                                auto item = std::make_shared<transform::Item>(generatedGeneric);
                                // TODO:
                                // item->setDBGInfo(generic->getDBGInfo());
                                ctx->addItem(generic->getName(), item);
                                executeGenericTests(generic->getWhereClause(), generatedGeneric, generic->getName());
                                }

  if (classGenerics.size() > generics.size()) {
    auto s = generics.size();
      defaultGenericStart = s;
      for (auto i = s; i < classGenerics.size(); ++i) {
        auto generic = classGenerics[i];
        auto generatedGeneric = transformType(generic->type);
        auto item = std::make_shared<transform::Item>(generatedGeneric->copy());
        // TODO:
        // item->setDBGInfo(generic->getDBGInfo());
        ctx->addItem(generic->getName(), item);
        executeGenericTests(generic->getWhereClause(), generatedGeneric, generic->getName());
        generics.push_back(generatedGeneric);
        defaultGenerics.push_back(generatedGeneric);
      }
    }

  if (auto identifier = utils::cast<Syntax::Expression::Identifier>(ty->getType()->_getInternalAST())) {
  if (identifier->getIdentifier() == ty->getIdentifier()) {
      E<VARIABLE_ERROR>(
      ty, FMT("Type alias '%s' cannot be recursive!", ty->getIdentifier().c_str()), {
        .info = "Same type alias name used here",
        .note = "Recursive type aliases are not allowed, consider using a type\nalias with a different name or declare it inside a namespace"
      }
      );
    }
  }

  auto aliasedType = transformType(ty->getType());
                     auto alias = getBuilder().createTypeAlias(ty->getDBGInfo(), ty->getIdentifier(), aliasedType);
                     alias->setPrivacy(ty->getPrivacy());
                     alias->setGenerics(generics);
                     alias->unsafeSetUUID(uuid);
                     alias->setMutable(aliasedType->isMutable());
                     alias->setDefaultGenerics(defaultGenerics);
                     alias->setDefaultGenericStart(defaultGenericStart);
                     transformedType = alias;
                     // auto item = std::make_shared<transform::Item>(alias);
                     // ctx->cache->setTransformedType(uuid, item);
                                });
                 });
  return transformedType;
}

} // namespace Syntax
} // namespace snowball
