
#include "../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::vector<ptr<Expression::Param>> Transformer::getActualFunctionArgs(
    cacheComponents::Functions::FunctionStore node) {
    auto args = node.function->getArgs();
    if ((node.state.currentClass != nullptr) && (!node.function->isStatic()) &&
        (args.size() > 0) && (args.at(0)->getName() == "self")) {
        args.erase(args.begin());
    }

    return args;
}

} // namespace Syntax
} // namespace snowball
