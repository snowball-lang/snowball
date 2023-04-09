
#include "../../ast/types/DefinedType.h"
#include "../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::string Transformer::getNiceBaseName(std::tuple<
        std::optional<std::shared_ptr<ir::Value>>,
        std::optional<std::shared_ptr<types::Type>>,
        std::optional<std::vector<std::shared_ptr<ir::Func>>>,
        std::optional<std::vector<cacheComponents::Functions::FunctionStore>>,
        std::optional<std::shared_ptr<ir::Module>>,
        bool /* (Ignore) Accept private members */> base) {

    if (auto x = std::get<0>(base)) {
        return x.value()->getType()->getPrettyName();
    } else if (auto x = std::get<1>(base)) {
        return x.value()->getPrettyName();
    } else if (std::get<2>(base) || std::get<3>(base)) {
        return "<BUG>";
    } else if (auto x = std::get<4>(base)) {
        return x.value()->getName();
    }

    assert(false);
}

} // namespace Syntax
} // namespace snowball
