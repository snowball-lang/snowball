
#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::string TransformContext::createIdentifierName(const std::string name, bool includeBase) {
  std::string result;
  // bool alreadyGenerated = name.find('.') != std::string::npos;

  if (name == _SNOWBALL_CONST_PTR) return _SNOWBALL_CONST_PTR;

  if (includeBase) {
    // alreadyGenerated = true;
    if (currentClass != nullptr) {
      if (auto x = utils::cast<types::DefinedType>(currentClass)) {
        result = x->getUUID() + "." + name;
      } else if (utils::cast<types::PrimitiveType>(currentClass)) {
        result = currentClass->getName() + "." + name;
      } else if (utils::cast<types::PointerType>(currentClass)) {
        result = currentClass->getName();
      } else {
        assert(false && "Unknown type!");
      }
    } else {
      auto currentModule = module->getUniqueName();

      // TODO: include class name if exists.
      result = currentModule + "." + name;
    }
  }

  if (!includeBase) {
    auto currentModule = module->getUniqueName();
    result = currentModule + "." + name;
  }

  return result;
}

} // namespace Syntax
} // namespace snowball