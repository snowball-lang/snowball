
#include "../../ir/values/IndexExtract.h"
#include "../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::pair<std::tuple<std::optional<std::shared_ptr<ir::Value>>,
                     std::optional<std::shared_ptr<types::Type>>,
                     std::optional<std::vector<std::shared_ptr<ir::Func>>>,
                     std::optional<std::vector<cacheComponents::Functions::FunctionStore>>,
                     std::optional<std::shared_ptr<ir::Module>>,
                     bool /* Accept private members */>,
          std::optional<std::shared_ptr<ir::Value>>>
Transformer::getFromIndex(DBGSourceInfo* dbgInfo, Expression::Index* index, bool isStatic) {
    auto getFromType = [&](std::shared_ptr<types::Type> type,
                           std::shared_ptr<ir::Value> value = nullptr)
            -> std::tuple<std::optional<std::shared_ptr<ir::Value>>,
                          std::optional<std::shared_ptr<types::Type>>,
                          std::optional<std::vector<std::shared_ptr<ir::Func>>>,
                          std::optional<std::vector<cacheComponents::Functions::FunctionStore>>,
                          std::optional<std::shared_ptr<ir::Module>>,
                          bool /* Accept private members */> {
        if (auto x = utils::dyn_cast<types::PointerType>(type)) { type = x->getBaseType(); }

        if (auto x = utils::dyn_cast<types::DefinedType>(type)) {
            auto g = utils::cast<Expression::GenericIdentifier>(index->getIdentifier());
            auto name = index->getIdentifier()->getIdentifier();
            auto generics = (g != nullptr) ? g->getGenerics() : std::vector<Expression::TypeRef*>{};

            auto fullUUID = x->getUUID();
            auto [v, ty, fns, ovs, mod] = getFromIdentifier(dbgInfo, name, generics, fullUUID);

            std::optional<std::shared_ptr<ir::Value>> indexValue;
            if (!isStatic) {
                auto fields = x->getFields();
                bool fieldFound = false;
                auto fieldValue = std::find_if(
                        fields.begin(), fields.end(), [&](types::DefinedType::ClassField* f) {
                            bool e = f->name == name;
                            fieldFound = e;
                            return fieldFound;
                        });

                if (fieldFound) {
                    // assert(v == std::nullopt);
                    assert(value != nullptr);

                    indexValue = ctx->module->N<ir::IndexExtract>(
                            dbgInfo, value, *fieldValue, std::distance(fields.begin(), fieldValue));
                    indexValue->get()->setType((*fieldValue)->type);
                }
            }

            if (indexValue == std::nullopt) { indexValue = v; }

            if (!indexValue.has_value() && !ty.has_value() && !fns.has_value() &&
                !ovs.has_value() && !mod.has_value()) {
                // TODO: operator
                E<VARIABLE_ERROR>(dbgInfo,
                                  FMT("Coudn't find '%s' inside type '%s'!",
                                      name.c_str(),
                                      x->getPrettyName().c_str()));
            }

            return {indexValue, ty, fns, ovs, mod, isInClassContext(x)};
        } else {
            // Case: index from a (for example) constant. You can access
            //  values from it so just check for functions
            auto name = index->getIdentifier()->getIdentifier();
            auto g = utils::cast<Expression::GenericIdentifier>(index->getIdentifier());
            auto generics = (g != nullptr) ? g->getGenerics() : std::vector<Expression::TypeRef*>{};

            auto [v, ty, fns, ovs, mod] =
                    getFromIdentifier(dbgInfo, name, generics, type->getName());

            if ((!fns.has_value()) && (!ovs.has_value())) {
                if (services::OperatorService::isOperator(name)) {
                    assert(false && "TODO: operator missing from builtin type!");
                }

                // TODO: operator
                E<VARIABLE_ERROR>(dbgInfo,
                                  FMT("Coudn't find '%s' inside type '%s'!",
                                      name.c_str(),
                                      type->getPrettyName().c_str()));
            }

            return {std::nullopt, std::nullopt, fns, ovs, std::nullopt, false};
        }

        return {std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, false};
    };

    auto getFromModule = [&](std::shared_ptr<ir::Module> m)
            -> std::tuple<std::optional<std::shared_ptr<ir::Value>>,
                          std::optional<std::shared_ptr<types::Type>>,
                          std::optional<std::vector<std::shared_ptr<ir::Func>>>,
                          std::optional<std::vector<cacheComponents::Functions::FunctionStore>>,
                          std::optional<std::shared_ptr<ir::Module>>,
                          bool /* Accept private members */> {
        // TODO: dont allow operators for modules

        auto g = utils::cast<Expression::GenericIdentifier>(index->getIdentifier());
        auto generics = (g != nullptr) ? g->getGenerics() : std::vector<Expression::TypeRef*>{};

        auto fullUUID = m->getUniqueName();
        auto [v, ty, fns, ovs, mod] = getFromIdentifier(
                dbgInfo, index->getIdentifier()->getIdentifier(), generics, fullUUID);

        if (!v.has_value() && !ty.has_value() && !fns.has_value() && !ovs.has_value() &&
            !mod.has_value()) {
            E<VARIABLE_ERROR>(dbgInfo,
                              FMT("Coudn't find '%s' inside module '%s'!",
                                  index->getIdentifier()->getIdentifier().c_str(),
                                  m->getName().c_str()));
        }

        return {v, ty, fns, ovs, mod, isInModuleContext(m)};
    };

    // Transform the base first
    auto base = index->getBase();
    if (auto baseIdentifier = utils::cast<Expression::Identifier>(base)) {
        auto g = utils::cast<Syntax::Expression::GenericIdentifier>(baseIdentifier);
        auto generics =
                (g != nullptr) ? g->getGenerics() : std::vector<Syntax::Expression::TypeRef*>{};

        auto [val, type, funcs, overloads, mod] =
                getFromIdentifier(dbgInfo, baseIdentifier->getIdentifier(), generics);

        if (val && (!isStatic)) {
            return {getFromType(val.value()->getType(), *val), val.value()};
        } else if (val) {
            E<TYPE_ERROR>(dbgInfo,
                          "Static method call / accesses can only be "
                          "used with types, not values!");
        }

        else if (mod && (!isStatic)) {
            E<TYPE_ERROR>(dbgInfo,
                          "Module members must be accessed by using "
                          "static indexes!");
        } else if (mod) {
            return {getFromModule(*mod), std::nullopt};
        }

        else if (type && (!isStatic)) {
            E<TYPE_ERROR>(dbgInfo,
                          "Can't use type references for method calls / "
                          "accesses!");
        } else if (type) {
            return {getFromType(*type), std::nullopt};
        }

        else if (overloads || funcs) {
            E<TYPE_ERROR>(dbgInfo, "Can't use function pointer as index base!");
        } else {
            E<VARIABLE_ERROR>(
                    baseIdentifier->getDBGInfo(),
                    FMT("Cannot find identifier `%s`!", baseIdentifier->getIdentifier().c_str()),
                    {.info = "this name is not defined"});
        }

        assert(false && "BUG: unhandled index value");
    } else if (auto x = utils::cast<Expression::Index>(base)) {
        auto [r, b] = getFromIndex(base->getDBGInfo(), x, x->isStatic);
        auto [v, t, fs, ovs, mod, c] = r;

        if (v && (!isStatic)) {
            return {getFromType(v.value()->getType(), *v), v.value()};
        } else if (v) {
            E<TYPE_ERROR>(dbgInfo,
                          "Static method index can only be "
                          "used with types, not values!");
        }

        else if (mod && (!isStatic)) {
            E<TYPE_ERROR>(dbgInfo,
                          "Module members must be accessed by using "
                          "static indexes!");
        } else if (mod) {
            return {getFromModule(*mod), std::nullopt};
        }

        else if (t && (!isStatic)) {
            E<TYPE_ERROR>(dbgInfo,
                          "Can't use type references for method calls / "
                          "accesses!");
        } else if (t) {
            return {getFromType(*t), std::nullopt};
        }

        else if (ovs || fs) {
            E<TYPE_ERROR>(dbgInfo, "Can't use function pointer as index base!");
        } else {
            // TODO: include base name
            E<VARIABLE_ERROR>(
                    dbgInfo,
                    FMT("Identifier '%s' not found!", baseIdentifier->getIdentifier().c_str()));
        }

        assert(false && "TODO: index index");
    } else if (auto x = utils::cast<Expression::TypeRef>(base)) {
        auto ty = transformType(x);

        if (ty && (!isStatic)) {
            E<TYPE_ERROR>(dbgInfo,
                          "Can't use type references for method calls / "
                          "accesses!");
        } else if (ty) {
            return {getFromType(ty), std::nullopt};
        }
    } else if (!isStatic) {
        // case: Integers, Strings, etc... index
        base->accept(this);
        auto v = this->value;
        return {getFromType(v->getType(), v), v};
    } else {
        E<SYNTAX_ERROR>(dbgInfo,
                        "Static acces/method call can only be used with "
                        "indentifiers!");
    }

    return {{std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, false},
            std::nullopt};
}
} // namespace Syntax
} // namespace snowball