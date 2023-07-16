#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::shared_ptr<types::DefinedType> Transformer::transformClass(const std::string& uuid,
                                                                cacheComponents::Types::TypeStore& classStore,
                                                                Expression::TypeRef* typeRef) {
    auto ty = utils::cast<Statement::DefinedTypeDef>(classStore.type);
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
    auto generics = typeRef != nullptr ? vector_iterate<Expression::TypeRef*, std::shared_ptr<types::Type>>(
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
            auto _uuid = baseUuid + ":" + utils::itos(existantTypes.has_value() ? existantTypes->size() : 0);
            auto basedName = ty->getName();
            transformedType = std::make_shared<types::DefinedType>(basedName,
                                                                   _uuid,
                                                                   ctx->module,
                                                                   ty,
                                                                   std::vector<types::DefinedType::ClassField*>{},
                                                                   nullptr,
                                                                   std::vector<std::shared_ptr<types::Type>>{},
                                                                   ty->isStruct());
            transformedType->setModule(ctx->module);
            transformedType->setUUID(_uuid);
            auto item = std::make_shared<transform::Item>(transformedType);
            ctx->cache->setTransformedType(baseUuid, item, _uuid);
            auto classGenerics = ty->getGenerics();
            // Fill out the remaining non-required tempalte parameters
            if (classGenerics.size() > generics.size()) {
                for (auto i = generics.size(); i < classGenerics.size(); ++i) {
                    generics.push_back(transformType(classGenerics[i]->type));
                }
            }
            auto selfType = std::make_shared<Item>(transformedType);
            ctx->addItem("Self", selfType);
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
            auto baseFields = vector_iterate<Statement::VariableDecl*, types::DefinedType::ClassField*>(
                    ty->getVariables(), [&](auto v) {
                        auto definedType = v->getDefinedType();
                        if (!definedType)
                            E<SYNTAX_ERROR>(v->getDBGInfo(),
                                            "Can't infer type!",
                                            {.info = "The type of this variable can't be inferred!",
                                             .note = "This rule only applies to variables inside classes.",
                                             .help = "You can't infer the type of a variable "
                                                     "without specifying it's type.\n"
                                                     "For example, you can't do this:\n"
                                                     "   let a = 10\n"
                                                     "You have to do this:\n"
                                                     "   let a: i32 = 10\n"
                                                     "Or this:\n"
                                                     "   let a = 10: i32"});
                        auto varTy = transformType(definedType);
                        auto field = new types::DefinedType::ClassField(v->getName(), varTy, v->getPrivacy(),
                                                                        v->getValue(), v->isMutable());
                        field->setDBGInfo(v->getDBGInfo());
                        return field;
                    });
            auto fields = getMemberList(ty->getVariables(), baseFields, parentType);
            transformedType->setParent(parentType);
            transformedType->setFields(fields);
            transformedType->setGenerics(generics);
            transformedType->setPrivacy(ty->getPrivacy());
            transformedType->setDBGInfo(ty->getDBGInfo());
            transformedType->setSourceInfo(ty->getSourceInfo());
            bool allowConstructor = (!ty->hasConstructor) && baseFields.size() == 0;
            if (parentType != nullptr) ctx->cache->performInheritance(transformedType, parentType, allowConstructor);
            ctx->setCurrentClass(transformedType);
            assert(!ty->isStruct() || (ty->isStruct() && ty->getFunctions().size() == 0));
            // Create function definitions
            auto backupGenerateFunction = ctx->generateFunction;
            ctx->generateFunction = false;
            for (auto ty : ty->getTypeAliases()) { trans(ty); }
            for (auto fn : ty->getFunctions()) {
                if (services::OperatorService::opEquals<OperatorType::CONSTRUCTOR>(fn->getName())) {
                    transformedType->hasConstructor = true;
                }

                trans(fn);
            }
            // Generate the function bodies
            ctx->generateFunction = true;
            for (auto ty : ty->getTypeAliases()) { trans(ty); }
            for (auto fn : ty->getFunctions()) { trans(fn); }
            ctx->generateFunction = backupGenerateFunction;
            for (int allowPointer = 0; allowPointer < 2; ++allowPointer) {
                auto argType = allowPointer ? transformedType->getPointerTo() : transformedType;
                // Set the default '=' operator for the class
                auto fn = builder.createFunction(
                        ty->getDBGInfo(), services::OperatorService::getOperatorMangle(OperatorType::EQ), true, false);
                auto arg = builder.createArgument(NO_DBGINFO, "other", argType);
                auto typeArgs = std::vector<std::shared_ptr<types::Type>>{transformedType->getPointerTo(), argType};
                auto type = builder.createFunctionType(typeArgs, transformedType);
                fn->setArgs({{"other", arg}});
                fn->setType(type);
                fn->setPrivacy(PrivacyStatus::PUBLIC);
                ctx->defineFunction(fn);
            }

            auto parentHasConstructor =
                    allowConstructor && parentType != nullptr && !parentType->isStruct() && parentType->hasConstructor;
            if (!parentHasConstructor && !transformedType->hasConstructor && !transformedType->isStruct()) {
                E<SYNTAX_ERROR>(ty,
                                "This class does not have a constructor!",
                                {.info = "This class does not have a constructor!",
                                 .note = "No constructor has been defined or can be inherited.",
                                 .help = "You have to define a constructor for this class.\n"
                                         "For example:\n"
                                         "1 |   class Test {\n"
                                         "2 |       Test() {\n"
                                         "3 |           // ...\n"
                                         "4 |       }\n"
                                         "5 |   }\n"
                                         "6 |"});
            }

            ctx->setCurrentClass(backupClass);
        });
    });
    return transformedType;
}

} // namespace Syntax
} // namespace snowball