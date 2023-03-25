
#include "../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::pair<
    std::tuple<
        std::optional<std::shared_ptr<ir::Value>>,
        std::optional<std::shared_ptr<types::Type>>,
        std::optional<std::vector<std::shared_ptr<ir::Func>>>,
        std::optional<std::vector<cacheComponents::Functions::FunctionStore>>,
        std::optional<std::shared_ptr<ir::Module>>,
        bool /* Accept private members */>,
    std::optional<std::shared_ptr<ir::Value>>>
Transformer::getFromIndex(ptr<DBGSourceInfo> dbgInfo,
                          ptr<Expression::Index> index, bool isStatic) {

    auto getFromType = [&](std::shared_ptr<types::Type> type)
        -> std::tuple<std::optional<std::shared_ptr<ir::Value>>,
                      std::optional<std::shared_ptr<types::Type>>,
                      std::optional<std::vector<std::shared_ptr<ir::Func>>>,
                      std::optional<std::vector<
                          cacheComponents::Functions::FunctionStore>>,
                      std::optional<std::shared_ptr<ir::Module>>,
                      bool /* Accept private members */> {
        if (auto x = std::dynamic_pointer_cast<types::DefinedType>(type)) {
            auto g = utils::cast<Expression::GenericIdentifier>(
                index->getIdentifier());
            auto generics = (g != nullptr)
                                ? g->getGenerics()
                                : std::vector<ptr<Expression::TypeRef>>{};

            auto fullUUID               = x->getUUID();
            auto [v, ty, fns, ovs, mod] = getFromIdentifier(
                dbgInfo, index->getIdentifier()->getIdentifier(), generics,
                fullUUID);

            if (!v.has_value() && !ty.has_value() && !fns.has_value() &&
                !ovs.has_value() && !mod.has_value()) {
                E<VARIABLE_ERROR>(
                    dbgInfo,
                    FMT("Coudn't find '%s' inside type '%s'!",
                        index->getIdentifier()->getIdentifier().c_str(),
                        x->getPrettyName().c_str()));
            }

            return {v, ty, fns, ovs, mod, isInClassContext(x)};
        } else {
            assert(false && "TODO: static non-defined type");
        }

        return {std::nullopt, std::nullopt, std::nullopt,
                std::nullopt, std::nullopt, false};
    };

    auto getFromModule = [&](std::shared_ptr<ir::Module> m)
        -> std::tuple<std::optional<std::shared_ptr<ir::Value>>,
                      std::optional<std::shared_ptr<types::Type>>,
                      std::optional<std::vector<std::shared_ptr<ir::Func>>>,
                      std::optional<std::vector<
                          cacheComponents::Functions::FunctionStore>>,
                      std::optional<std::shared_ptr<ir::Module>>,
                      bool /* Accept private members */> {
        auto g =
            utils::cast<Expression::GenericIdentifier>(index->getIdentifier());
        auto generics = (g != nullptr)
                            ? g->getGenerics()
                            : std::vector<ptr<Expression::TypeRef>>{};

        auto fullUUID = m->getUniqueName();
        auto [v, ty, fns, ovs, mod] =
            getFromIdentifier(dbgInfo, index->getIdentifier()->getIdentifier(),
                              generics, fullUUID);

        if (!v.has_value() && !ty.has_value() && !fns.has_value() &&
            !ovs.has_value() && !mod.has_value()) {
            E<VARIABLE_ERROR>(
                dbgInfo, FMT("Coudn't find '%s' inside module '%s'!",
                             index->getIdentifier()->getIdentifier().c_str(),
                             m->getName().c_str()));
        }

        return {v, ty, fns, ovs, mod, isInModuleContext(m)};
    };

    // Transform the base first
    auto base = index->getBase();
    if (auto baseIdentifier = utils::cast<Expression::Identifier>(base)) {
        auto [val, type, funcs, overloads, mod] =
            getFromIdentifier(dbgInfo, baseIdentifier->getIdentifier());

        if (val && (!isStatic)) {
            return {getFromType(val.value()->getType()), val.value()};
        } else if (val) {
            E<TYPE_ERROR>(dbgInfo, "Static method call / accesses can only be "
                                   "used with types, not values!");
        }

        else if (mod && (!isStatic)) {
            E<TYPE_ERROR>(
                dbgInfo,
                "Module members must be accessed by using static indexes!");
        } else if (mod) {
            return {getFromModule(*mod), std::nullopt};
        }

        else if (type && (!isStatic)) {
            E<TYPE_ERROR>(
                dbgInfo,
                "Can't use type references for method calls / accesses!");
        } else if (type) {
            return {getFromType(*type), std::nullopt};
        }

        else if (overloads || funcs) {
            E<TYPE_ERROR>(dbgInfo, "Can't use function pointer as index base!");
        } else {
            E<VARIABLE_ERROR>(dbgInfo,
                              FMT("Cannot find identifier `%s`!",
                                  baseIdentifier->getIdentifier().c_str()),
                              "this name is not defined");
        }

        assert(false && "BUG: unhandled index value");
    } else if (!isStatic) {
        assert(false && "TODO: non-static index");
    } else if (auto x = utils::cast<Expression::Index>(base)) {
        auto [r, b] = getFromIndex(base->getDBGInfo(), x, x->isStatic);
        auto [v, t, fs, ovs, mod, c] = r;

        if (v && (!isStatic)) {
            return {getFromType(v.value()->getType()), v.value()};
        } else if (v) {
            E<TYPE_ERROR>(dbgInfo, "Static method call / accesses can only be "
                                   "used with types, not values!");
        }

        else if (mod && (!isStatic)) {
            E<TYPE_ERROR>(
                dbgInfo,
                "Module members must be accessed by using static indexes!");
        } else if (mod) {
            return {getFromModule(*mod), std::nullopt};
        }

        else if (t && (!isStatic)) {
            E<TYPE_ERROR>(
                dbgInfo,
                "Can't use type references for method calls / accesses!");
        } else if (t) {
            return {getFromType(*t), std::nullopt};
        }

        else if (ovs || fs) {
            E<TYPE_ERROR>(dbgInfo, "Can't use function pointer as index base!");
        } else {
            // TODO: include base name
            E<VARIABLE_ERROR>(dbgInfo,
                              FMT("Identifier '%s' not found!",
                                  baseIdentifier->getIdentifier().c_str()));
        }

        assert(false && "TODO: index index");
    } else if (auto x = utils::cast<Expression::TypeRef>(base)) {
        auto ty = transformType(x);

        if (ty && (!isStatic)) {
            E<TYPE_ERROR>(
                dbgInfo,
                "Can't use type references for method calls / accesses!");
        } else if (ty) {
            return {getFromType(ty), std::nullopt};
        }
    } else {
        E<SYNTAX_ERROR>(dbgInfo,
                        "Static acces/method call can only be used with "
                        "(generic or not) indentifiers!");
    }

    return {{std::nullopt, std::nullopt, std::nullopt, std::nullopt,
             std::nullopt, false},
            std::nullopt};
}
} // namespace Syntax
} // namespace snowball