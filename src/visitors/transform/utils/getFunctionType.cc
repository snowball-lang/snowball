#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

types::FunctionType* Transformer::getFunctionType(types::Type* valueType) {
    if (auto x = cast<types::FunctionType>(valueType)) {
        return x;
    } 

    if (auto x = cast<types::DefinedType>(valueType)) {
        if (utils::startsWith(x->getUUID(), services::ImportService::CORE_UUID + "Core.Function")) {
            return utils::cast<types::FunctionType>(x->getGenerics()[0]);
        }
    }

    return nullptr;
}

} // namespace Syntax
} // namespace snowball