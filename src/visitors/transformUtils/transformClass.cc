#include "../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::shared_ptr<types::DefinedType>
Transformer::transformClass(const std::string& uuid,
                            cacheComponents::Types::TypeStore& classStore,
                            Expression::TypeRef* typeRef) {
    auto ty = utils::cast<Statement::ClassDef>(classStore.type);
    assert(ty);

    // These are the generics generated outside of the class context.
    // for example, this "Test" type woudn't be fetched inside the class
    // context:
    //
    //   class Hello<T> { ... }
    //   Hello<?Test> // Test is not being transformed from the "Hello
    //   context".
    //
    // Note that the default class generics WILL be generated inside the
    // class context.
    auto generics = typeRef != nullptr
            ? vector_iterate<Expression::TypeRef*, std::shared_ptr<types::Type>>(
                      typeRef->getGenerics(), [&](auto t) { return transformType(t); })
            : std::vector<std::shared_ptr<types::Type>>{};

    // TODO: check if typeRef generics match class generics
    std::shared_ptr<types::DefinedType> transformedType;
    ctx->withState(classStore.state, [&]() {
        ctx->withScope([&] {
            auto backupClass = ctx->getCurrentClass();
            // TODO: maybe not reset completly, add nested classes in
            // the future
            ctx->setCurrentClass(nullptr);
            auto baseUuid = ctx->createIdentifierName(ty->getName());
            auto existantTypes = ctx->cache->getTransformedType(uuid);
            auto _uuid = baseUuid + ":" +
                    utils::itos(existantTypes.has_value() ? existantTypes->size() : 0);
            auto basedName = getNameWithBase(ty->getName());
            transformedType =
                    std::make_shared<types::DefinedType>(basedName, _uuid, ctx->module, ty);
            auto item = std::make_shared<transform::Item>(transformedType);
            ctx->cache->setTransformedType(_uuid, item);
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
            std::shared_ptr<types::DefinedType> parentType = nullptr;
            if (auto x = ty->getParent()) {
                auto parent = transformType(x);
                parentType = utils::dyn_cast<types::DefinedType>(parent);
                if (!parentType) {
                    E<TYPE_ERROR>(ty,
                                  FMT("Can't inherit from '%s'", parent->getPrettyName().c_str()),
                                  {.info = "This is not a defined type!",
                                   .help = "Classes can only inherit from other "
                                           "classes or "
                                           "structs meaning\n that you can't "
                                           "inherit from `i32` "
                                           "(for example) because it's\n a "
                                           "primitive type."});
                }
            }
            auto baseFields =
                    vector_iterate<Statement::VariableDecl*, types::DefinedType::ClassField*>(
                            ty->getVariables(), [&](auto v) {
                                auto varTy = transformType(v->getDefinedType());
                                auto field = new types::DefinedType::ClassField(
                                        v->getName(),
                                        varTy,
                                        v->getPrivacy(),
                                        v->getValue(),
                                        v->isMutable());
                                field->setDBGInfo(v->getDBGInfo());
                                return field;
                            });
            auto fields = getMemberList(ty->getVariables(), baseFields, parentType);
            transformedType->setParent(parentType);
            transformedType->setFields(fields);
            transformedType->setGenerics(generics);
            transformedType->setDBGInfo(ty->getDBGInfo());
            transformedType->setSourceInfo(ty->getSourceInfo());
            if (parentType != nullptr) ctx->cache->performInheritance(transformedType, parentType);
            ctx->setCurrentClass(transformedType);
            for (auto fn : ty->getFunctions()) { fn->accept(this); }
            for (int allowPointer = 0; allowPointer < 2; ++allowPointer) {
                // Set the default '=' operator for the class
                auto fn = builder.createFunction(
                        ty->getDBGInfo(),
                        services::OperatorService::getOperatorMangle(services::OperatorService::EQ),
                        true,
                        false);
                auto arg = std::make_shared<ir::Argument>("other");
                auto typeArgs = std::vector<std::shared_ptr<types::Type>>{
                        transformedType->getPointerTo(),
                        allowPointer ? transformedType->getPointerTo() : transformedType};
                auto type = std::make_shared<types::FunctionType>(typeArgs, transformedType);
                arg->setType(allowPointer ? transformedType->getPointerTo() : transformedType);
                fn->setArgs({{"other", arg}});
                fn->setType(type);
                fn->setPrivacy(PrivacyStatus::PUBLIC);
                /// @see Transformer::defineFunction
                auto name = ctx->createIdentifierName(fn->getName(true));
                auto item = ctx->cache->getTransformedFunction(name);
                if (item) {
                    assert((*item)->isFunc());
                    (*item)->addFunction(fn);
                } else {
                    auto i = std::make_shared<transform::Item>(fn);
                    ctx->cache->setTransformedFunction(name, i);
                }
            }

            ctx->setCurrentClass(backupClass);
        });
    });
    return transformedType;
}

} // namespace Syntax
} // namespace snowball