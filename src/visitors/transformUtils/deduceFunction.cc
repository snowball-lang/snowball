#include "../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::optional<std::shared_ptr<types::Type>>
Transformer::deduceFunctionType(snowball::Syntax::Expression::Param* generic,
                                const std::vector<Expression::Param*>& fnArgs,
                                const std::vector<std::shared_ptr<types::Type>>& arguments,
                                const std::vector<std::shared_ptr<types::Type>>& generics,
                                const std::vector<std::shared_ptr<types::Type>>& deducedTypes) {
    // I'm pretty sure this function works, but I'm a programmer, not a
    // magician.

    // See if a generic parameter was given
    const auto genericsSize = generics.size();
    if (genericsSize > deducedTypes.size()) {
        const auto index = deducedTypes.size();
        return generics[index];
    }

    // Check if the generic is used inside the variables
    const auto it = std::find_if(fnArgs.begin(), fnArgs.end(), [&](const auto& arg) {
        return arg->getType()->getName() == generic->getName();
    });

    if (it != fnArgs.end()) {
        const auto argIdx = std::distance(fnArgs.begin(), it);
        const auto deducedType = arguments[argIdx];
        return deducedType;
    }

    // Check if the generic has a default type and non was found
    if (generic->type != nullptr) { return transformType(generic->type); }

    return std::nullopt;
}

std::pair<std::vector<std::shared_ptr<types::Type>>, std::string>
Transformer::deduceFunction(cacheComponents::Functions::FunctionStore s,
                            const std::vector<std::shared_ptr<types::Type>>& arguments,
                            const std::vector<std::shared_ptr<types::Type>>& generics) {
    auto function = s.function;
    auto fnArgs = getActualFunctionArgs(s);

    std::vector<std::shared_ptr<types::Type>> deducedTypes;

    for (const auto& generic : function->getGenerics()) {
        const auto deducedType =
                deduceFunctionType(generic, fnArgs, arguments, generics, deducedTypes);
        if (deducedType.has_value()) {
            deducedTypes.push_back(deducedType.value());
        } else {
            return {{},
                    FMT("Cannot deduce type '%s' in function call!", generic->getName().c_str())};
        }
    }

    return {deducedTypes, ""};
}

} // namespace Syntax
} // namespace snowball