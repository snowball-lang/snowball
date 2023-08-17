
#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

bool Transformer::isInClassContext(types::Type* ty) {
  auto cls = ctx->getCurrentClass();
  if (cls == nullptr) return false;

  if (auto x = utils::cast<types::DefinedType>(ty)) {
    auto clsType = utils::cast<types::DefinedType>(cls);
    if (clsType != nullptr) {
      auto clsUUID = clsType->getUUID();
      auto tyUUID = x->getUUID();

      auto colon = clsUUID.find(":");
      auto tyColon = tyUUID.find(":");
      if (colon != std::string::npos) { clsUUID = clsUUID.substr(0, colon); }
      if (tyColon != std::string::npos) { tyUUID = tyUUID.substr(0, tyColon); }

      return clsUUID == tyUUID;
    }
  }

  return cls->is(ty);
}

} // namespace Syntax
} // namespace snowball