#include "../../../ast/syntax/nodes.h"
#include "../../Transformer.h"

#include "../../../lexer/lexer.h"
#include "../../../parser/Parser.h"
#include "../../../utils/utils.h"
#include "../../../visitors/Analyzer.h"
#include "../../../visitors/Transformer.h"
#include "../../../visitors/TypeChecker.h"
#include "../../../visitors/analyzers/DefinitveAssigment.h"
#include <fstream>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::string Transformer::getBuiltinTypeUUID(types::Type* ty, const std::string& name, types::Type* original) {
  if (original) // make sure pointer types are generated!
    transformType(original->toRef());
  auto pointers = ctx->cache->getTransformedType(name).value();
  int uuid = 0;
  for (const auto& x : pointers) {
    auto ptr = utils::cast<types::DefinedType>(x->getType());
    assert(ptr);
    assert(ptr->getName() == name);
    assert(ptr->getGenerics().size() == 1);

    auto pointedType = ptr->getGenerics().at(0);
    if (ty->is(pointedType)) return name + ":" + std::to_string(uuid);
    uuid++;
  }
  assert(!"Pointer type not found");
}

} // namespace Syntax
} // namespace snowball