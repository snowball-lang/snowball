
#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::shared_ptr<ir::Value> Transformer::createObjectConstructor(
  DBGSourceInfo* dbgInfo,
  types::Type* ty,
  std::vector<types::Type*> args
) {
  assert(ty != nullptr && "BUG: Type cant be null!");
  auto structType = utils::cast<types::DefinedType>(ty);
  assert(structType != nullptr && "BUG: Type must be a struct!");
  assert(structType->isStruct() && "BUG: Type must be a struct!");
  auto typeInfo = structType->getModule()->typeInformation.at(structType->getId());
  assert(typeInfo && "BUG: Type must have type info!");
  assert(utils::dyn_cast<types::DefinedType>(typeInfo) && "BUG: Type info must be a defined type!");
  auto& fields = utils::dyn_cast<types::DefinedType>(typeInfo)->getFields();
  std::function<std::string(std::vector<types::DefinedType::ClassField*>::const_iterator)> fieldFormatter = [](auto x) {
      return (*x)->name + ": " + BWHT + (*x)->type->getPrettyName() + RESET + ";";
    };
  int i = 0;
  for (auto& field : fields) {
    auto name = field->name;
    auto type = field->type;
    if (args.size() <= (size_t)i) {
      E<TYPE_ERROR>(
        dbgInfo,
        FMT("Missing argument '%s' of type '%s' in struct initializer!", name.c_str(), type->getName().c_str()),
      ErrorInfo {
        .info = FMT("Struct '%s' has %d fields!", structType->getName().c_str(), fields.size()),
        .note = FMT("Did you forget to pass the argument '%s'?", name.c_str()),
        .help = FMT("Struct '%s' has the following fields:\nRequired fields:\n + %s", structType->getName().c_str(), utils::join(fields.begin(), fields.end(), "\n + ", fieldFormatter).c_str())
      }
      );
    }
    auto arg = args.at(i);
    if (!type->is(arg)) {
      E<TYPE_ERROR>(
        dbgInfo,
        FMT("Argument '%s' of type '%s' does not match struct fields type '%s'!", name.c_str(), arg->getPrettyName().c_str(),
            type->getPrettyName().c_str()),
      ErrorInfo {
        .info = FMT("Struct '%s' has %d fields!", structType->getName().c_str(), fields.size()),
        .note = FMT("Did you forget to pass the argument '%s'?", name.c_str()),
        .help = FMT("Struct '%s' has the following fields:\nRequired fields:\n + %s", structType->getName().c_str(), utils::join(fields.begin(), fields.end(), "\n + ", fieldFormatter).c_str())
      }
      );
    }
    i++;
  }
  return getBuilder().createObjectInitialization(dbgInfo, ty, nullptr, {}, true);
}

} // namespace Syntax
} // namespace snowball