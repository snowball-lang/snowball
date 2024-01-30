#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

#include "generate_equilizers.h"

namespace snowball {
namespace Syntax {

types::BaseType* Transformer::transformClass(
  const std::string& uuid, cacheComponents::Types::TypeStore& classStore, Expression::TypeRef* typeRef
) {
  auto ty = utils::cast<Statement::DefinedTypeDef>(classStore.type);
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
  types::BaseType* transformedType;
  ctx->withState(classStore.state, [&]() {
                   ctx->withScope([&] {
                                    std::vector<types::Type*> defaultGenerics;
                                    int defaultGenericStart = 0;
                                    auto tyFunctions = ty->getFunctions();
                                    auto backupClass = ctx->getCurrentClass();
                                    // TODO: maybe not reset completly, add nested classes in
                                    // the future
                                    ctx->setCurrentClass(nullptr);
                                    auto baseUuid = ctx->createIdentifierName(ty->getName());
                                    auto existantTypes = ctx->cache->getTransformedType(uuid);
                                    auto _uuid = baseUuid + ":" + utils::itos(existantTypes.has_value() ? existantTypes->size() : 0);
                                    auto basedName = ty->getName();
                                    transformedType = ty->isInterface() ? (types::BaseType*) new types::InterfaceType(
                                      basedName,
                                      _uuid,
                                      ctx->module,
                                      std::vector<types::InterfaceType::Member*>{},
  std::vector<types::Type*>{}
                                    ) :
  (types::BaseType*) new types::DefinedType(
    basedName,
    _uuid,
    ctx->module,
    ty,
  {},
  {},
  nullptr,
  std::vector<types::Type*>{},
  ty->isStruct()
  );
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
  types::DefinedType* parentType = nullptr;
  if (auto x = ty->getParent()) {
  auto parent = transformSizedType(x, false, "Parent types must be sized but found '%s' (which is not sized)");
    parentType = utils::cast<types::DefinedType>(parent);
    if (!parentType) {
      E<TYPE_ERROR>(
        x,
      FMT("Cant inherit from '%s'", parent->getPrettyName().c_str()), {
        .info = "This is not a class nor a struct type!",
        .note = "Classes can only inherit from other "
        "classes or "
        "structs meaning\n that you can't "
        "inherit from `i32` "
        "(for example) because it's\n a "
        "primitive type.",
        .help = "If trying to implement from an interface, "
        "use the `implements`\nkeyword "
        "instead.\n"
      }
      );
    }
  }
  auto backupGenerateFunction = ctx->generateFunction;
                                ctx->setCurrentClass(transformedType);
                                // Transform types first thing
                                ctx->generateFunction = false;
  for (auto ty : ty->getChildTypes()) { trans(ty); }
  ctx->generateFunction = true;
  for (auto ty : ty->getChildTypes()) { trans(ty); }
  int fieldCount = 0;
  if (!ty->isInterface()) {
  for (auto& v : ty->getVariables()) {
      if (v->isContantDecl()) {
        auto var = trans(v);
        assert(utils::dyn_cast<ir::VariableDeclaration>(var));
        ((types::DefinedType*) transformedType)->addStaticField(utils::dyn_cast<ir::VariableDeclaration>(var));
      } else {
        auto definedType = v->getDefinedType();
        if (!definedType)
          E<SYNTAX_ERROR>(
            v->getDBGInfo(),
          "Cant infer type!", {
          .info = "The type of this variable cant be inferred!",
          .note = "This rule only applies to variables inside classes.",
          .help = "You cant infer the type of a variable "
          "without specifying its type.\n"
          "For example, you can't do this:\n   let a = 10\n"
          "You have to do this:\n   let a: i32 = 10\n"
          "Or this:\n   let a = 10: i32"
        }
        );
        auto varTy = transformSizedType(
                       definedType, false, "Class fields must be sized but found '%s' (which is not sized)"
                     );
        varTy->setMutable(v->isMutable());
        auto field = new types::DefinedType::ClassField(
          v->getName(), varTy, v->getPrivacy(), v->getValue(), v->isMutable()
        );
        field->setDBGInfo(v->getDBGInfo());
        ((types::DefinedType*) transformedType)->addField(field);
        fieldCount++;
      }
    }
    ((types::DefinedType*) transformedType)->setParent(parentType);
  } else {
    for (auto v : ty->getVariables()) {
      auto definedType = v->getDefinedType();
      if (!definedType)
        E<SYNTAX_ERROR>(
          v->getDBGInfo(),
        "Cant infer type!", {
        .info = "The type of this variable cant be inferred!",
        .note = "This rule only applies to variables inside interfaces.",
        .help = "You cant infer the type of a variable "
        "without specifying its type.\n"
        "For example, you can't do this:\n   let a = 10\n"
        "You have to do this:\n   let a: i32 = 10\n"
        "Or this:\n   let a = 10: i32"
      }
      );
      auto varTy = transformSizedType(
                     definedType, false, "Interface fields must be sized but found '%s' (which is not sized)"
                   );
      varTy->setMutable(v->isMutable());
      auto field = new types::InterfaceType::Member(
        v->getName(), varTy, types::InterfaceType::Member::Kind::FIELD, v, v->getPrivacy(), v->isMutable()
      );
      field->setDBGInfo(v->getDBGInfo());
      ((types::InterfaceType*) transformedType)->addField(field);
      fieldCount++;
    }
  }
  bool allowConstructor = (!ty->hasConstructor) && fieldCount == 0;
                          if (parentType != nullptr && !ty->isInterface())
                          ctx->cache->performInheritance((types::DefinedType*) transformedType, parentType, allowConstructor);
                          if (!ty->isInterface()) implementTypes((types::DefinedType*) transformedType, ty->getImpls(), tyFunctions);
                            assert(!ty->isStruct() || (ty->isStruct() && ty->getFunctions().size() == 0));
                            // if (!ty->isInterface()) {
                            // Create function definitions
                            ctx->generateFunction = false;
                            ctx->module->typeInformation.emplace(transformedType->getId(), std::shared_ptr<types::BaseType>(transformedType));
                            GENERATE_EQUALIZERS
    for (auto fn : tyFunctions) {
      if (services::OperatorService::opEquals<OperatorType::CONSTRUCTOR>(fn->getName()))
          if (auto x = utils::cast<types::DefinedType>(transformedType)) x->hasConstructor = true;
        if (fn->isVirtual()) transformedType->hasVtable = true;
        trans(fn);
      }
  if (auto x = utils::cast<types::DefinedType>(transformedType); x && !transformedType->hasVtable) {
  auto p = x;
  while (p->hasParent()) {
      p = p->getParent();
      p = utils::cast<types::DefinedType>(p->getModule()->typeInformation.find(p->getId())->second.get());
      if (!p) break;
      if (p->hasVtable) {
        transformedType->hasVtable = true;
        break;
      }
    }
  }
  // Generate the function bodies
  ctx->generateFunction = true;
                          GENERATE_EQUALIZERS
  for (auto fn : tyFunctions) { trans(fn); }
  ctx->generateFunction = backupGenerateFunction;
                          auto parentHasConstructor =
                            allowConstructor && parentType != nullptr && !parentType->isStruct() && parentType->hasConstructor;
                          auto type = utils::cast<types::DefinedType>(transformedType);
                          if (!parentHasConstructor && type && !type->hasConstructor && !type->isStruct() &&
  !ty->hasAttribute(Attributes::BUILTIN) && !ty->hasAttribute(Attributes::NO_CONSTRUCTOR)) {
  E<SYNTAX_ERROR>(
    ty,
  "This class does not have a constructor!", {
    .info = "This class does not have a constructor!",
    .note = "No constructor has been defined or can be inherited.",
    .help =
    FMT("You have to define a constructor for this class.\n"
        "For example:\n"
        "  |\n"
        "1 | class %s {\n"
        "  |\n"
        "2 |   %s() { ... }\n"
        "3 | }\n"
        "  |",
        ty->getName().c_str(),
        ty->getName().c_str())
    }
    );
  }
  //}
  ctx->setCurrentClass(backupClass);
                                  });
                 });
  return transformedType;
}

} // namespace Syntax
} // namespace snowball