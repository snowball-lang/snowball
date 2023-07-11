
#include "../../utils/utils.h"
#include "../Transformer.h"

namespace snowball {

using namespace utils;
namespace Syntax {

std::shared_ptr<types::Type>
Transformer::transformTypeAlias(const std::string& uuid,
                                cacheComponents::Types::TypeStore& base,
                                Expression::TypeRef* typeRef) {
    auto ty = utils::cast<Statement::TypeAlias>(base.type);
    assert(ty);

    // These are the generics generated outside of the type alias
    // context. Note that the default class generics WILL be generated
    // inside the class context.
    auto generics = typeRef != nullptr
            ? vector_iterate<Expression::TypeRef*, std::shared_ptr<types::Type>>(
                      typeRef->getGenerics(), [&](auto t) { return transformType(t); })
            : std::vector<std::shared_ptr<types::Type>>{};

    // TODO: check if typeRef generics match class generics
    std::shared_ptr<types::Type> transformedType;
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
                executeGenericTests(generic->getWhereClause(), generatedGeneric);
            }

            auto aliasedType = transformType(ty->getType());
            auto alias =
                    builder.createTypeAlias(ty->getDBGInfo(), ty->getIdentifier(), aliasedType);
            alias->setPrivacy(ty->getPrivacy());
            alias->setGenerics(generics);
            alias->setUUID(uuid);
            transformedType = alias;
            // auto item = std::make_shared<transform::Item>(alias);
            // ctx->cache->setTransformedType(uuid, item);
        });
    });

    return transformedType;
}

} // namespace Syntax
} // namespace snowball
