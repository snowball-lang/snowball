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

std::string Transformer::getPointerTypeUUID(types::PointerType* ty) {
    if (ty->isMutable()) return ""; // TODO:
    auto pointers = ctx->cache->getTransformedType(_SNOWBALL_CONST_PTR).value();
    int uuid = 0;
    for (const auto& x : pointers) {
        auto ptr = utils::cast<types::DefinedType>(x->getType());
        assert(ptr);
        assert(ptr->getName() == _SNOWBALL_CONST_PTR);
        assert(ptr->getGenerics().size() == 1);

        auto pointedType = ptr->getGenerics().at(0);
        if (ty->getPointedType()->is(pointedType)) 
            return ty->getName() + ":" + std::to_string(uuid);
        uuid++;
    }
    assert(! "Pointer type not found");
}

} // namespace Syntax
} // namespace snowball