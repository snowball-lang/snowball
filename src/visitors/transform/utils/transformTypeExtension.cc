
#include "../../Transformer.h"

namespace snowball {
namespace Syntax {

void Transformer::transformTypeExtension(Statement::DefinedTypeDef* node, std::string uuid) {
  auto name = node->getName();
  if (!ctx->isGlobalScope()) {
    E<SYNTAX_ERROR>(node, "Class extensions can only be defined in the global scope!",
    {
      .info = FMT("Class '%s' is not defined in the global scope!", name.c_str()),
      .note = "Class extensions can only be defined in the global scope!",
      .help = "Move this class extension to the global scope."
    });
  }

  auto [item, found] = ctx->getItem(name);
  if (found) {
    if (item->isType()) {
      if (utils::cast<types::TypeAlias>(item->getType())) {
        E<SYNTAX_ERROR>(node, "Can't extend a type alias!",
        {
          .info = FMT("'%s' is a type alias!", item->toString().c_str()),
          .note = "Only types can be extended!",
          .help = "Remove the 'extends' keyword from this class."
        });
      }
      auto backup = ctx->getCurrentClass();
      ctx->setCurrentClass(item->getType());
      for (auto fn : node->getFunctions()) {
        trans(fn);
      }
      ctx->setCurrentClass(backup);
      return; // :D
    } else {
      E<SYNTAX_ERROR>(node, "Can't extend a non-type!",
      {
        .info = FMT("'%s' is not a type!", item->toString().c_str()),
        .note = "Only types can be extended!",
        .help = "Remove the 'extends' keyword from this class."
      });
    }
  }

  assert(false && "TODO: transformTypeExtension");
}

} // namespace Syntax
} // namespace snowball
