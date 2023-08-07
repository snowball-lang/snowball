
#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

bool Transformer::shouldUseGeneratedFunction(std::shared_ptr<ir::Func> fn, std::vector<types::Type*> arguments) {
    assert(fn->getArgs().size() <= arguments.size());
    auto i = 0;
    for (auto arg : fn->getArgs()) {
        auto argType = arg.second->getType();
        auto argValue = arguments.at(i);
        i++;
        if (argType->is(argValue)) {
            continue;
        }
        if (argType->canCast(argValue)) {
            continue;
        }
        return false;
    }
    return true;    
}

} // namespace Syntax
} // namespace snowball