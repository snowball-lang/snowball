#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::tuple<Cache::FunctionStore, std::vector<types::Type*>, Transformer::FunctionFetchResponse>
Transformer::getBestFittingFunction(
        const std::deque<Cache::FunctionStore>& overloads,
        const std::vector<types::Type*>& arguments,
        const std::vector<Expression::TypeRef*>& generics,
        bool isIdentifier
) {
  std::vector<std::pair<Cache::FunctionStore, std::vector<types::Type*>>> functions;
  std::vector<int> importances;
  for (auto n : overloads) {
    auto fn = n.function;
    if (ir::Func::argumentSizesEqual(fn->getArgs(), arguments, fn->isVariadic()) || isIdentifier) {
      auto genericArguments = utils::vector_iterate<Expression::TypeRef*, types::Type*>(generics, [&](auto g) {
        return transformType(g);
      });
      auto [deducedArgs, errors, importance] = deduceFunction(n, arguments, genericArguments);
      if (errors.empty()) {
        functions.push_back({n, deducedArgs});
        importances.push_back(importance);
      } else {
        E<TYPE_ERROR>(fn, errors, {.tail = EI<>(ctx->latestCall->getDBGInfo(), "", {.info = "Called from here"})});
      }
    }
  }
  bool exactFunctionExists = false;
  std::pair<Cache::FunctionStore, std::vector<types::Type*>> bestFunction = {{nullptr}, {}};
  std::vector<std::pair<Cache::FunctionStore, std::vector<types::Type*>>> matchedFunctions;
  std::vector<int> matchedFunctionsPerception;
  int genericIndex = -1;
  int genericCount = -1;
  int i = 0;
  // Check for the best function overload
  for (auto foundFunction : functions) {
    auto fnArgs = foundFunction.first.function->getArgs();
    if (foundFunction.second.size() > 0) {
      // Automatically accept generic functions
      matchedFunctions.push_back(foundFunction);
      auto importance = importances.at(i);
      if (importance > genericCount) {
        genericIndex = i;
        genericCount = importance;
      }
      i++;
    } else {
      ctx->withState(foundFunction.first.state, [&] {
        bool argsEqual = true;
        bool argsNeedCasting = false;
        int succeededArgs = 0;
        for (size_t i = 0; (i < fnArgs.size()) && argsEqual; i++) {
          auto type = transformSizedType(
                  fnArgs.at(i)->getType(),
                  false,
                  "Function argument types but be sized but found '%s' (which is not sized)"
          );
          if ((fnArgs.at(i)->hasDefaultValue() || isIdentifier) && arguments.size() < fnArgs.size()) {
            argsEqual = true;
            continue;
          }
          argsEqual = arguments.at(i)->is(type);
          //if (type->isMutable() && !arguments.at(i)->isMutable()) argsEqual = false;
          if (!argsEqual) {
            if (auto castType = canCast(arguments.at(i), type); castType != CastType::NoCast) {
              argsEqual = true;
              argsNeedCasting = true;
              // we need to prioritize the casting type
              int castPriority = 0;
              switch (castType) {
                case CastType::NoCast: assert(false && "This should never happen");
                case CastType::AutoDeref:
                case CastType::ToPointer: castPriority = 2; break;
                case CastType::Valid: castPriority = 3; break;
                case CastType::AutoRef: castPriority = 4; break;
                default: assert(false && "Invalid cast type given at deducing function");
              }
              // Succeded arg should be higher depending on the cast priority
              succeededArgs = (succeededArgs + 1) * (castPriority + 1);
            }
          }
        }
        if (argsEqual) {
          if (!argsNeedCasting) {
            exactFunctionExists = true;
            bestFunction = foundFunction;
          } else {
            matchedFunctions.push_back(foundFunction);
            matchedFunctionsPerception.push_back(succeededArgs);
          }
        }
      });
    }
  }
  if ((matchedFunctions.size() > 1) && (!exactFunctionExists) && (genericIndex == -1)) {
    // we check if there's a function that succeeded more than the others
    // but if they all have the same amount of succeeded arguments, we throw an ambiguity error
    int max = 0;
    int maxIndex = -1;
    for (size_t i = 0; i < matchedFunctionsPerception.size(); i++) {
      if (matchedFunctionsPerception.at(i) > max) {
        max = matchedFunctionsPerception.at(i);
        maxIndex = i;
      }
    }
    // we dont return it if they all have the same amount of succeeded arguments
    if (maxIndex != -1 &&
        !std::all_of(matchedFunctionsPerception.begin(), matchedFunctionsPerception.end(), [&](auto i) {
          return i == max;
        })) {
      return {matchedFunctions.at(maxIndex).first, matchedFunctions.at(maxIndex).second, FunctionFetchResponse::Ok};
    }
    return {{nullptr}, {}, FunctionFetchResponse::AmbiguityConflict};
  } else if (exactFunctionExists)
    return {bestFunction.first, bestFunction.second, FunctionFetchResponse::Ok};
  else if (genericIndex != -1)
    return {matchedFunctions.at(genericIndex).first,
            matchedFunctions.at(genericIndex).second,
            FunctionFetchResponse::Ok};
  else if (matchedFunctions.size() == 1) {
    auto matched = matchedFunctions.at(0);
    return {matched.first, matched.second, FunctionFetchResponse::Ok};
  }

  return {{nullptr}, {}, FunctionFetchResponse::NoMatchesFound};
}

} // namespace Syntax
} // namespace snowball