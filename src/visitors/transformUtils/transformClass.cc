#include "../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::shared_ptr<types::DefinedType>
Transformer::transformClass(const std::string& uuid,
                            cacheComponents::Types::TypeStore& classStore,
                            Expression::TypeRef *typeRef) {
    auto ty = classStore.type;
    if (ty->getGenerics().size() > 0) {
        assert(false && "TODO: class generics");
    }

    // TODO: check if typeRef generics match class generics
    std::shared_ptr<types::DefinedType> transformedType;
    ctx->withState(classStore.state, [&]() {
        auto backupClass = ctx->getCurrentClass();

        // TODO: maybe not reset completly, add nested classes in the future
        ctx->setCurrentClass(nullptr);

        std::shared_ptr<types::DefinedType> parentType = nullptr;
        if (auto x = ty->getParent()) {
            parentType = utils::dyn_cast<types::DefinedType>(transformType(x));
        }

        auto generics =
            typeRef != nullptr ? vector_iterate<Expression::TypeRef *, std::shared_ptr<types::Type>>(
                typeRef->getGenerics(),
                [&](auto t) { return transformType(t); }) : std::vector<std::shared_ptr<types::Type>>{};

        auto basedName  = getNameWithBase(ty->getName());
        auto baseFields = vector_iterate<Statement::VariableDecl *,
                                         types::DefinedType::ClassField *>(
            ty->getVariables(), [&](auto v) {
                auto varTy = transformType(v->getDefinedType());
                return new types::DefinedType::ClassField(v->getName(), varTy);
            });

        auto fields = getMemberList(ty->getVariables(), baseFields, parentType);

        auto baseUuid      = ctx->createIdentifierName(ty->getName());
        auto existantTypes = ctx->cache->getTransformedType(uuid);

        auto _uuid =
            baseUuid + ":" +
            utils::itos(existantTypes.has_value() ? existantTypes->size() : 0);

        transformedType = std::make_shared<types::DefinedType>(
            basedName, _uuid, ctx->module, fields, parentType, generics);

        transformedType->setDBGInfo(ty->getDBGInfo());
        transformedType->setSourceInfo(ty->getSourceInfo());
        ctx->setCurrentClass(transformedType);

        auto item = std::make_shared<transform::Item>(transformedType);
        ctx->cache->setTransformedType(_uuid, item);
        for (auto fn : ty->getFunctions()) {
            fn->accept(this);
        }

        ctx->setCurrentClass(backupClass);
        // assert(false && "TODO: class");
    });

    return transformedType;
}

} // namespace Syntax
} // namespace snowball