#include "../../Transformer.h"

#include "generate_equilizers.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

types::EnumType* Transformer::transformEnum
(
  const std::string& uuid, cacheComponents::Types::TypeStore& classStore, Expression::TypeRef* typeRef
) {
  auto ty = utils::cast<Statement::EnumTypeDef>(classStore.type);
  assert(ty);
  // These are the generics generated outside of the class context.
  // for example, this "Test" type woudn't be fetched inside the class
  // context:
  //
  // class Hello<T> { ... }
  // Hello<?Test> // Test is not being transformed from the "Hello
  // context".
  //
  // Note that the default class generics WILL be generated inside the
  // class context.
  auto generics = typeRef != nullptr ? vector_iterate<Expression::TypeRef*, types::Type*>(
                    typeRef->getGenerics(), [&](auto t) { return transformType(t); }
                  ) :
                  std::vector<types::Type*> {};
  // TODO: check if typeRef generics match class generics
  types::EnumType* transformedType;
  ctx->withState(classStore.state, [&]() {
                   ctx->withScope([&] {
                                    std::vector<types::Type*> defaultGenerics;
                                    int defaultGenericStart = 0;
                                    auto backupClass = ctx->getCurrentClass();
                                    // TODO: maybe not reset completly, add nested classes in
                                    // the future
                                    ctx->setCurrentClass(nullptr);
                                    auto baseUuid = ctx->createIdentifierName(ty->getName());
                                    auto existantTypes = ctx->cache->getTransformedType(uuid);
                                    auto _uuid = baseUuid + ":" + utils::itos(existantTypes.has_value() ? existantTypes->size() : 0);
                                    transformedType = new types::EnumType(ty->getName(), _uuid, ctx->module, ty->getPrivacy());
  transformedType->addImpl(ctx->getBuiltinTypeImpl("Sized"));
  auto item = std::make_shared<transform::Item>(transformedType);
  ctx->cache->setTransformedType(baseUuid, item, _uuid);

  auto classGenerics = ty->getGenerics();
  auto selfType = std::make_shared<Item>(transformedType);
  ctx->addItem("Self", selfType);
  for (size_t genericCount = 0; genericCount < generics.size(); genericCount++) {
    auto generic = classGenerics.at(genericCount);
    auto generatedGeneric = generics.at(genericCount);
    auto item = std::make_shared<transform::Item>(generatedGeneric->copy());
    // TODO:
    // item->setDBGInfo(generic->getDBGInfo());
    ctx->addItem(generic->getName(), item);
    executeGenericTests(generic->getWhereClause(), generatedGeneric, generic->getName());
  }

  // Append the default generic types
  for (auto generic : ty->getGenerics()) {
    if (generic->getType()) { // has default type
        defaultGenerics.push_back(transformType(generic->getType()));
        continue;
      }
      defaultGenericStart++;
    }

  // Fill out the remaining non-required tempalte parameters
  if (classGenerics.size() > generics.size()) {
  for (auto i = generics.size(); i < classGenerics.size(); ++i) {
      auto generic = classGenerics[i];
      auto generatedGeneric = transformType(generic->type);
      auto item = std::make_shared<transform::Item>(generatedGeneric->copy());
      // TODO:
      // item->setDBGInfo(generic->getDBGInfo());
      ctx->addItem(generic->getName(), item);
      executeGenericTests(generic->getWhereClause(), generatedGeneric, generic->getName());
      generics.push_back(generatedGeneric);
    }
  }
  transformedType->setGenerics(generics);
  transformedType->setDefaultGenerics(defaultGenerics);
  transformedType->setDefaultGenericStart(defaultGenericStart);
  transformedType->setPrivacy(ty->getPrivacy());
  transformedType->setDBGInfo(ty->getDBGInfo());
  transformedType->setSourceInfo(ty->getSourceInfo());
  auto backupGenerateFunction = ctx->generateFunction;
                                ctx->generateFunction = false;
                                ctx->setCurrentClass(transformedType);
                                GENERATE_EQUALIZERS
  for (auto field : ty->getFields()) {
  auto fieldTypes = vector_iterate<Expression::TypeRef*, types::Type*>(
                      field.second, [&](auto t) { return transformType(t); }
                    );
    auto enumField = types::EnumType::EnumField(field.first, fieldTypes);
    transformedType->addField(enumField);
  }

  for (auto fn : ty->getMethods())
  trans(fn);
  ctx->generateFunction = backupGenerateFunction;
                          ctx->setCurrentClass(backupClass);

                          // Create function definitions
                          ctx->setCurrentClass(transformedType);
                          ctx->module->typeInformation.insert({transformedType->getId(), std::shared_ptr<types::BaseType>(transformedType)});
                          // Generate the function bodies
                          ctx->generateFunction = true;
                          GENERATE_EQUALIZERS
                          for (auto fn : ty->getMethods())
                            trans(fn);
                            ctx->generateFunction = backupGenerateFunction;
                            ctx->setCurrentClass(backupClass);
                                    });
                   });
  return transformedType;
}

} // namespace Syntax
} // namespace snowball