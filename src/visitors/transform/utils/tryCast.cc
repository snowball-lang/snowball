
#include "../../Transformer.h"

namespace snowball {
namespace Syntax {

std::shared_ptr<ir::Value> Transformer::tryCast(std::shared_ptr<ir::Value> value, types::Type* type) {
  auto castType = canCast(value->getType(), type);
  switch (castType) {
    case CastType::Valid: return builder.createCast(value->getDBGInfo(), value, type);
    case CastType::AutoDeref: return builder.createDereferenceTo(value->getDBGInfo(), value, type);
    case CastType::AutoRef: return builder.createReferenceTo(value->getDBGInfo(), value);
    case CastType::ToPointer: {
      auto pointerType = builder.createReferenceTo(value->getDBGInfo(), value);
      // we change the type of the pointer to the type we want. shhh...
      pointerType->setType(value->getType()->getPointerTo(type->isMutable()));
      return pointerType;
    }
    case CastType::NoCast: break;
  }
  return nullptr;
}

} // namespace Syntax
} // namespace snowball
