#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::shared_ptr<ir::Func>
Transformer::getFunction(DBGObject* dbgInfo,
                         std::tuple<std::optional<std::shared_ptr<ir::Value>>,
                                    std::optional<types::Type*>,
                                    std::optional<std::deque<std::shared_ptr<ir::Func>>>,
                                    std::optional<std::deque<Cache::FunctionStore>>,
                                    std::optional<std::shared_ptr<ir::Module>>,
                                    bool /* Accept private members */>
                                 store,
                         const std::string& name,
                         std::vector<types::Type*> _arguments,
                         const std::vector<Expression::TypeRef*>& generics,
                         bool isIdentifier,
                         bool hasSelf) {
  auto arguments = _arguments;
  auto [val, ty, functions, overloads, mod, canBePrivate] = store;
  auto checkIfContextEqual = [&dbgInfo = dbgInfo, name = name, canBePrivate = canBePrivate](
                                     std::shared_ptr<ir::Func> fn) -> std::shared_ptr<ir::Func> {
    if ((!canBePrivate) && fn->isPrivate()) {
      E<TYPE_ERROR>(dbgInfo,
                    FMT("Function '%s' is a private method and "
                        "it cant be accessed from this context!",
                        name.c_str()));
    }

    return fn;
  };

  if (val) {
    auto v = *val;
    auto fnType = utils::cast<types::FunctionType>(v->getType());
    if (fnType == nullptr) {
      E<TYPE_ERROR>(dbgInfo,
                    FMT("Value with name '%s' (with type: '%s') "
                        "is not callable!",
                        name.c_str(),
                        v->getType()->getPrettyName().c_str()));
    }

    auto argsVector = fnType->getArgs();
    size_t numArgs = arguments.size();

    if (ir::Func::argumentSizesEqual(argsVector, arguments, fnType->isVariadic())) {
      bool equal = true;
      for (auto arg = argsVector.begin(); (arg != argsVector.end()) && (equal); ++arg) {
        auto i = std::distance(argsVector.begin(), arg);
        if (i < numArgs) {
          equal = (*arg)->is(arguments.at(i));
        } else {
          if (!fnType->isVariadic()) {
            equal = false;
            break;
          } else {
            equal = true;
          }
        }
      }

      // TODO: check for ambiguous functions
      if (equal) { return std::reinterpret_pointer_cast<ir::Func>(v); }
    }

    E<TYPE_ERROR>(dbgInfo,
                  FMT("Call parameters to '%s' does not match it's "
                      "function type ('%s')!",
                      name.c_str(),
                      v->getType()->getPrettyName().c_str()));
  } else if (ty) {
    // TODO: Call smth like Type::operator ()(..args)
    E<TYPE_ERROR>(dbgInfo, FMT("Value with name '%s' is a type that can't be called!", name.c_str()));
  } else if (mod) {
    E<TYPE_ERROR>(dbgInfo, FMT("Silly billy, you can't call modules! ('%s')", name.c_str()));
  }
  auto [fn, args, res] = getBestFittingFunction(overloads.has_value() ? overloads.value() : std::deque<Cache::FunctionStore>{}, arguments, generics, isIdentifier);
  switch (res) {
    case Ok: {
      return checkIfContextEqual(transformFunction(fn, args, false, functions.has_value() ? functions.value() : std::deque<std::shared_ptr<ir::Func>>{}));
    }

    case NoMatchesFound: {
      if (hasSelf)
        arguments.erase(arguments.begin());
      if ((!overloads.has_value()) && (!functions.has_value()))
        E<VARIABLE_ERROR>(dbgInfo, FMT("Function '%s' is not defined!", name.c_str()));
      CompilerError* tailErrors = nullptr;
#define ADD_FUNCTION_ERROR(id, idx)                                                                                    \
  for (auto overload : id.value()) {                                                                                   \
    if (idx->getDBGInfo() == nullptr) continue;                                                                        \
    auto err = EI<>(idx, "", {.info = "A possible function overload found here"});                                     \
    if (tailErrors == nullptr) {                                                                                       \
      tailErrors = err;                                                                                                \
      continue;                                                                                                        \
    }                                                                                                                  \
    tailErrors->info.tail = err;                                                                                       \
  }

      // TODO: check if this is necesary (just for functions)
      // ADD_FUNCTION_ERROR(overloads, overload.function)
      if (functions.has_value())
        ADD_FUNCTION_ERROR(functions, overload)
      else
        ADD_FUNCTION_ERROR(overloads, overload.function)
      // TODO: throw a note that sugest's it's correct types: only if
      // there's one
      //  overload
      E<VARIABLE_ERROR>(dbgInfo,
                        FMT("No matches found for `%s(%s)`",
                            name.c_str(),
                            Expression::FunctionCall::getArgumentsAsString(arguments).c_str()),
                        {.info = "No function overloads found for this function!",
                         .note = "The function does exist but it's arguments are "
                                 "not correctly "
                                 "defined.",
                         .help = "The provided function name and arguments do not "
                                 "match any of "
                                 "the \navailable function overloads. Please "
                                 "ensure that you "
                                 "have correctly spelled the \nfunction name and "
                                 "provided the "
                                 "appropriate arguments. Additionally, check the "
                                 "\ndocumentation or function signature to confirm "
                                 "the correct "
                                 "syntax and parameter \ntypes.",
                         .tail = tailErrors});
    }

    case AmbiguityConflict: {
      if (hasSelf)  
        arguments.erase(arguments.begin());
      CompilerError* tailErrors = nullptr;
      ADD_FUNCTION_ERROR(overloads, overload.function)
      E<TYPE_ERROR>(dbgInfo,
                    FMT("Ambiguous function call to '%s(%s)' found!",
                        name.c_str(),
                        Expression::FunctionCall::getArgumentsAsString(arguments).c_str()),
                    {.info = "Multiple functions match the provided arguments.",
                     .note = "The arguments provided match multiple function overloads that "
                             "could not be resolved.",
                     .help = "Please ensure that you have correctly spelled the function "
                             "name and provided the \nappropriate arguments. Additionally, "
                             "check the documentation or function signature\nto confirm the "
                             "correct syntax and parameter types.",
                     .tail = tailErrors});
    }

#undef ADD_FUNCTION_ERROR
    default: assert(false);
  }

  assert(false && "BUG: unhandled getFunction res case.");
}
} // namespace Syntax
} // namespace snowball