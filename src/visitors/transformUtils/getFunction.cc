#include "../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::shared_ptr<ir::Func> Transformer::getFunction(
    DBGObject* dbgInfo,
    std::tuple<
        std::optional<std::shared_ptr<ir::Value>>,
        std::optional<std::shared_ptr<types::Type>>,
        std::optional<std::vector<std::shared_ptr<ir::Func>>>,
        std::optional<std::vector<cacheComponents::Functions::FunctionStore>>,
        std::optional<std::shared_ptr<ir::Module>>,
        bool /* Accept private members */>
        store,
    const std::string& name,
    const std::vector<std::shared_ptr<types::Type>>& arguments,
    const std::vector<Expression::TypeRef *>& generics) {

    auto [val, ty, functions, overloads, mod, canBePrivate] = store;
    auto checkIfContextEqual =
        [&dbgInfo = dbgInfo, name = name, canBePrivate = canBePrivate](
            std::shared_ptr<ir::Func> fn) -> std::shared_ptr<ir::Func> {
        if ((!canBePrivate) && fn->isPrivate()) {
            E<TYPE_ERROR>(dbgInfo, FMT("Function '%s' is a private method and "
                                       "it cant be accessed from this context!",
                                       name.c_str()));
        }

        return fn;
    };

    if (val) {
        auto v = *val;
        if (std::dynamic_pointer_cast<types::FunctionType>(v->getType()) ==
            nullptr) {
            E<TYPE_ERROR>(
                dbgInfo,
                FMT("Value with name '%s' (with type: '%s') is not callable!",
                    name.c_str(), v->getType()->getPrettyName().c_str()));
        }

        return std::reinterpret_pointer_cast<ir::Func>(v);
    } else if (ty) {
        // TODO: Call smth like Type::operator ()(..args)
        E<TYPE_ERROR>(
            dbgInfo, FMT("Value with name '%s' is a type that can't be called!",
                         name.c_str()));
    } else if (mod) {
        E<TYPE_ERROR>(
            dbgInfo,
            FMT("Silly billy, you can't call modules! ('%s')", name.c_str()));
    }

    if (functions) {
        for (auto f : *functions) {
            auto args       = f->getArgs(true);
            size_t numArgs  = arguments.size();
            auto argsVector = utils::list_to_vector(args);

            if (ir::Func::argumentSizesEqual(argsVector, arguments,
                                             f->isVariadic())) {
                bool equal = true;
                for (auto arg = args.begin(); ((arg != args.end()) && (equal));
                     ++arg) {
                    auto i = std::distance(args.begin(), arg);
                    if (i < numArgs) {
                        equal = arg->second->getType()->is(arguments.at(i));
                    } else {
                        auto defArg = arg->second->getDefaultValue();
                        if (!defArg && (!f->isVariadic())) {
                            equal = false;
                            break;
                        } else {
                            equal = true;
                        }
                    }
                }

                // TODO: check for ambiguous functions
                if (equal) {
                    return checkIfContextEqual(f);
                }
            }
        }
    }

    if (!overloads.has_value()) {
        E<VARIABLE_ERROR>(dbgInfo,
                          FMT("Function '%s' is not defined!", name.c_str()));
    }

    auto [fn, args, res] =
        getBestFittingFunction(overloads.value(), arguments, generics);
    switch (res) {
        case Ok: {
            return checkIfContextEqual(transformFunction(fn, args));
        }

        case NoMatchesFound: {
            E<VARIABLE_ERROR>(
                dbgInfo,
                FMT("No matches found for %s(%s)", name.c_str(),
                    Expression::FunctionCall::getArgumentsAsString(arguments)
                        .c_str()));
        }

        case AmbiguityConflict: {
            E<TYPE_ERROR>(
                dbgInfo,
                FMT("Function ambiguity for %s(%s)", name.c_str(),
                    Expression::FunctionCall::getArgumentsAsString(arguments)
                        .c_str()));
        }

            [[fallthrough]];
        case _Unknown: {
        }
    }

    assert(false && "BUG: unhandled getFunction res case.");
}
} // namespace Syntax
} // namespace snowball