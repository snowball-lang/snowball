#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

void Transformer::assertSizedType(types::Type* ty, const std::string message, DBGObject* dbgInfo) {
  bool isSized = utils::is<types::PointerType>(ty) || utils::is<types::ReferenceType>(ty) || utils::is<types::FunctionType>(ty);
  for (const auto& impl : ty->getImpls()) {
    if (impl->is(ctx->getBuiltinTypeImpl("Sized"))) {
      isSized = true;
      break;
    }
  }
  if (!isSized) {
    E<TYPE_ERROR>(
            dbgInfo,
            FMT(message.c_str(), ty->getPrettyName().c_str()),
            {.info = FMT("Type '%s' is not sized.", ty->getPrettyName().c_str()),
             .help = FMT("You can use the 'Sized' interface to make sure a type is sized or\nwrap in a "
                         "container or pointer type.")}
    );
  }
}

types::Type* Transformer::transformSizedType(Expression::TypeRef* ty, bool ignoreVoid, const std::string message) {
  auto type = transformType(ty);
  if (ignoreVoid && utils::is<types::VoidType>(type)) { return type; }

  assertSizedType(type, message, ty);
  return type;
}

} // namespace Syntax
} // namespace snowball