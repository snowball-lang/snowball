
#include "../../Transformer.h"

namespace snowball {
namespace Syntax {

void Transformer::transformTypeExtension(Statement::DefinedTypeDef* node, std::string uuid) {
  auto name = node->getName();
  assert(node->getVariables().size() == 0);
  if (!ctx->isGlobalScope()) {
    E<SYNTAX_ERROR>(
            node,
            "Class extensions can only be defined in the global scope!",
            {.info = FMT("Class '%s' is not defined in the global scope!", name.c_str()),
             .note = "Class extensions can only be defined in the global scope!",
             .help = "Move this class extension to the global scope."}
    );
  }

  auto [item, found] = ctx->getItem(name);
  if (found) {
    if (item->isType()) {
      if (utils::cast<types::TypeAlias>(item->getType())) {
        E<SYNTAX_ERROR>(
                node,
                "Cant extend a type alias!",
                {.info = FMT("'%s' is a type alias!", item->toString().c_str()),
                 .note = "Only types can be extended!",
                 .help = "Remove the 'extends' keyword from this class."}
        );
      }
      auto backup = ctx->getCurrentClass();
      ctx->setCurrentClass(item->getType());
      for (auto fn : node->getFunctions()) trans(fn);
      ctx->setCurrentClass(backup);
      return; // :D
    } else {
      E<SYNTAX_ERROR>(
              node,
              "Cant extend a non-type!",
              {.info = FMT("'%s' is not a type!", item->toString().c_str()),
               .note = "Only types can be extended!",
               .help = "Remove the 'extends' keyword from this class."}
      );
    }
  }
  int usedUUIDCount = -1;
refetchUUID:
  auto usedUUID = usedUUIDCount == -1 ? uuid : ctx->uuidStack.at(usedUUIDCount) + "." + name;
  if (auto x = ctx->cache->getType(usedUUID)) {
    auto type = x.value();
    if (auto alias = utils::cast<Statement::TypeAlias>(type.type)) {
      E<SYNTAX_ERROR>(
              node,
              "Cant extend a type alias!",
              {.info = FMT("'%s' is a type alias!", alias->getIdentifier().c_str()),
               .note = "Only types can be extended!",
               .help = "Remove the 'extends' keyword from this class."}
      );
    }

    auto definedType = utils::cast<Statement::DefinedTypeDef>(type.type);
    assert(definedType);

    if (definedType->isInterface()) {
      E<SYNTAX_ERROR>(
              node,
              "Cant extend an interface!",
              {.info = FMT("'%s' is an interface!", definedType->getName().c_str()),
               .note = "Only types can be extended!",
               .help = "Remove the 'extends' keyword from this class."}
      );
    }

    auto state = ctx->saveState();

    for (auto fn : node->getFunctions()) {
      fn->setContextState(state);
      definedType->addFunction(fn);
    }

    auto backup = ctx->getCurrentClass();

    // extend the already generated types
    // TODO: I don't think we should "override" the type state here
    auto types = ctx->cache->getTransformedType(usedUUID);
    if (types.has_value()) {
      for (auto item : types.value()) {
        ctx->withScope([&]() {
          assert(item->isType());
          auto definedType = utils::cast<types::DefinedType>(item->getType());
          ctx->setCurrentClass(definedType);
          assert(definedType);

          auto ast = definedType->getAST();
          assert(ast->getGenerics().size() == definedType->getGenerics().size());
          for (size_t i = 0; i < ast->getGenerics().size(); i++) {
            auto generic = ast->getGenerics().at(i);
            auto genericType = definedType->getGenerics().at(i);
            ctx->addItem(generic->getName(), std::make_shared<transform::Item>(genericType));
          }

          // TODO: should we override `ctx->generateFunction` here too?
          auto backupGenerateFn = ctx->generateFunction;
          ctx->generateFunction = false;
          for (auto fn : node->getFunctions()) { trans(fn); }
          ctx->generateFunction = true;
          for (auto fn : node->getFunctions()) { trans(fn); }
          ctx->generateFunction = backupGenerateFn;
        });
      }
    }

    ctx->setCurrentClass(backup);
    return;
  }

  if (usedUUIDCount < (int)ctx->uuidStack.size()-1) {
    usedUUIDCount++;
    goto refetchUUID;
  }

  E<VARIABLE_ERROR>(
          node,
          "Cant extend an undefined type!",
          {.info = FMT("'%s' is not defined in the currect context!", name.c_str()),
           .note = "Only types can be extended!",
           .help = "Define this type or remove the 'extends' keyword from this class."}
  );
}

} // namespace Syntax
} // namespace snowball
