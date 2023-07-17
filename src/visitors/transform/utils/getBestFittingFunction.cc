#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::tuple<Cache::FunctionStore, std::vector<std::shared_ptr<types::Type>>, Transformer::FunctionFetchResponse>
Transformer::getBestFittingFunction(const std::vector<Cache::FunctionStore>& overloads,
                                    const std::vector<std::shared_ptr<types::Type>>& arguments,
                                    const std::vector<Expression::TypeRef*>& generics,
                                    bool isIdentifier) {
    std::vector<std::pair<Cache::FunctionStore, std::vector<std::shared_ptr<types::Type>>>> functions;
    for (auto n : overloads) {
        auto fn = n.function;
        if (ir::Func::argumentSizesEqual(getActualFunctionArgs(n), arguments, fn->isVariadic()) || isIdentifier) {
            auto genericArguments = utils::vector_iterate<Expression::TypeRef*, std::shared_ptr<types::Type>>(
                    generics, [&](auto g) { return transformType(g); });
            auto [deducedArgs, errors] = deduceFunction(n, arguments, genericArguments);
            if (errors.empty()) {
                functions.push_back({n, deducedArgs});
            } else {
                E<TYPE_ERROR>(fn, errors);
            }
        }
    }
    bool exactFunctionExists = false;
    std::pair<Cache::FunctionStore, std::vector<std::shared_ptr<types::Type>>> bestFunction = {{nullptr},{}};
    std::vector<std::pair<Cache::FunctionStore, std::vector<std::shared_ptr<types::Type>>>> matchedFunctions;
    int genericIndex = -1;
    int genericCount = 0;
    int genericIterator = 0;
    // Check for the best function overload
    for (auto foundFunction : functions) {
        if (foundFunction.second.size() > 0) {
            // Automatically accept generic functions
            matchedFunctions.push_back(foundFunction);
            genericCount++;
            genericIndex = genericIterator;
        } else {
            ctx->withState(foundFunction.first.state, [&] {
                auto fnArgs = getActualFunctionArgs(foundFunction.first);
                bool argsEqual = (fnArgs.size() == 0) && (arguments.size() == 0);
                bool argsNeedCasting = false;
                for (auto i = 0; (i < fnArgs.size()) && !argsEqual; i++) {
                    auto type = transformType(fnArgs.at(i)->getType());
                    if ((fnArgs.at(i)->hasDefaultValue() || isIdentifier) && arguments.size() < fnArgs.size()) {
                        argsEqual = true;
                        continue;
                    }
                    argsEqual = type->is(arguments.at(i));
                    if (!argsEqual) {
                        if (arguments.at(i)->canCast(type)) {
                            argsEqual = true;
                            argsNeedCasting = true;
                        }
                    }
                }
                if (argsEqual) {
                    if (!argsNeedCasting) {
                        exactFunctionExists = true;
                        bestFunction = foundFunction;
                    } else {
                        matchedFunctions.push_back(foundFunction);
                    }
                }
            });
        }
        genericIterator++;
    }
    if (((matchedFunctions.size() > 1) && (!exactFunctionExists) && (genericIndex == -1)) || (genericCount > 1))
        return {{nullptr}, {}, FunctionFetchResponse::AmbiguityConflict};
    else if (matchedFunctions.size() == 1) {
        auto matched = matchedFunctions.at(0);
        return {matched.first, matched.second, FunctionFetchResponse::Ok};
    } else if (exactFunctionExists)
        return {bestFunction.first, bestFunction.second, FunctionFetchResponse::Ok};
    else if (genericIndex != -1)
        return {matchedFunctions.at(genericIndex).first, matchedFunctions.at(genericIndex).second,
                FunctionFetchResponse::Ok};
    return {{nullptr}, {}, FunctionFetchResponse::NoMatchesFound};
}

} // namespace Syntax
} // namespace snowball