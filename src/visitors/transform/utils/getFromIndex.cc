
#include "../../../ir/values/IndexExtract.h"
#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;
using namespace snowball::services;

namespace snowball {
namespace Syntax {

std::pair<
        std::tuple<
                std::optional<std::shared_ptr<ir::Value>>,
                std::optional<types::Type*>,
                std::optional<std::deque<std::shared_ptr<ir::Func>>>,
                std::optional<std::deque<Cache::FunctionStore>>,
                std::optional<std::shared_ptr<ir::Module>>,
                bool /* Accept private members */>,
        std::optional<std::shared_ptr<ir::Value>>>
Transformer::getFromIndex(DBGSourceInfo* dbgInfo, Expression::Index* index, bool isStatic) {
  auto getFromType = [&](types::Type* type, std::shared_ptr<ir::Value> value = nullptr)
          -> std::tuple<
                  std::optional<std::shared_ptr<ir::Value>>,
                  std::optional<types::Type*>,
                  std::optional<std::deque<std::shared_ptr<ir::Func>>>,
                  std::optional<std::deque<Cache::FunctionStore>>,
                  std::optional<std::shared_ptr<ir::Module>>,
                  bool /* Accept private members */> {
    if (auto x = utils::cast<types::ReferenceType>(type)) { type = x->getBaseType(); }
    if (auto x = utils::cast<types::TypeAlias>(type)) { type = x->getBaseType(); }

    if (auto x = utils::cast<types::BaseType>(type)) {
      auto g = utils::cast<Expression::GenericIdentifier>(index->getIdentifier());
      auto name = index->getIdentifier()->getIdentifier();
      auto generics = (g != nullptr) ? g->getGenerics() : std::vector<Expression::TypeRef*>{};

      auto fullUUID = x->getUUID();
      auto [v, ty, fns, ovs, mod] = getFromIdentifier(dbgInfo, name, generics, fullUUID);

      std::shared_ptr<ir::Value> indexValue = nullptr;
      if (!isStatic) {

#define FIND_FIELD(field_type)                                                                                         \
  auto fields = ty->getFields();                                                                                       \
  bool fieldFound = false;                                                                                             \
  auto fieldValue = std::find_if(fields.begin(), fields.end(), [&](field_type* f) {                                    \
    bool e = f->name == name;                                                                                          \
    fieldFound = e;                                                                                                    \
    return fieldFound;                                                                                                 \
  });                                                                                                                  \
  if (fieldFound) {                                                                                                    \
    assert(value != nullptr);                                                                                          \
    indexValue =                                                                                                       \
            getBuilder().createIndexExtract(dbgInfo, value, *fieldValue, std::distance(fields.begin(), fieldValue));   \
    getBuilder().setType(indexValue, (*fieldValue)->type);                                                             \
  }

        if (auto ty = utils::cast<types::DefinedType>(x)) {
          FIND_FIELD(types::DefinedType::ClassField)
        } else if (auto ty = utils::cast<types::InterfaceType>(x)) {
          FIND_FIELD(types::InterfaceType::Member)
        }
      } else {
        if (auto ty = utils::cast<types::DefinedType>(x)) {
          auto& fields = ty->getStaticFields();
          auto fieldValue = std::find_if(fields.begin(), fields.end(), [&](std::shared_ptr<ir::VariableDeclaration> f) {
            return f->getIdentifier() == name;
          });
          if (fieldValue != fields.end()) {
            indexValue = (*fieldValue)->getVariable();
          }
        } else if (auto e = utils::cast<types::EnumType>(x)) {
          auto& fields = e->getFields();
          auto fieldValue = std::find_if(fields.begin(), fields.end(), [&](types::EnumType::EnumField f) {
            return f.name == name;
          });
          if (fieldValue != fields.end()) {
            indexValue = getBuilder().createEnumInit(dbgInfo, e, (*fieldValue).name);
            getBuilder().setType(indexValue, e);
          }
        } else {
          E<TYPE_ERROR>(dbgInfo, "Only defined types can have static members!");
        }
      }

      if (indexValue == nullptr && v.has_value()) { indexValue = v.value(); }
      if (!indexValue && !ty.has_value() && !fns.has_value() && !ovs.has_value() && !mod.has_value()) {
        if (OperatorService::isOperator(name)) name = OperatorService::operatorName(OperatorService::operatorID(name));
        E<VARIABLE_ERROR>(dbgInfo, FMT("Coudnt find '%s' inside type '%s'!", name.c_str(), x->getPrettyName().c_str()));
      }
      return {indexValue ? std::make_optional(indexValue) : std::nullopt, ty, fns, ovs, mod, isInClassContext(x)};
    } else {
      // Case: index from a (for example) constant. You can access
      //  values from it so just check for functions
      auto name = index->getIdentifier()->getIdentifier();
      auto g = utils::cast<Expression::GenericIdentifier>(index->getIdentifier());
      auto generics = (g != nullptr) ? g->getGenerics() : std::vector<Expression::TypeRef*>{};

      auto uuid = type->getName();
      if (auto x = utils::cast<types::PointerType>(type)) {
        auto str = getBuiltinTypeUUID(x->getPointedType(), x->isMutable() ? _SNOWBALL_MUT_PTR : _SNOWBALL_CONST_PTR, x);
        if (!str.empty()) uuid = str;
      } else if (auto x = utils::cast<types::NumericType>(type)) {
        auto str = getBuiltinTypeUUID(x, _SNOWBALL_INT_IMPL);
        if (!str.empty()) uuid = str;
      } else if (auto x = utils::cast<types::FunctionType>(type)) {
        auto str = getBuiltinTypeUUID(x, _SNOWBALL_FUNC_IMPL, x);
        if (!str.empty()) uuid = str;
      }

      auto [v, ty, fns, ovs, mod] = getFromIdentifier(dbgInfo, name, generics, uuid);
      if ((!fns.has_value()) && (!ovs.has_value())) {
        if (OperatorService::isOperator(name)) name = OperatorService::operatorName(OperatorService::operatorID(name));
        E<VARIABLE_ERROR>(
                dbgInfo, FMT("Coudnt find member '%s' inside type '%s'!", name.c_str(), type->getPrettyName().c_str())
        );
      }

      return {std::nullopt, std::nullopt, fns, ovs, std::nullopt, false};
    }

    return {std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, false};
  };

  auto getFromModule = [&](std::shared_ptr<ir::Module> m) -> std::tuple<
                                                                  std::optional<std::shared_ptr<ir::Value>>,
                                                                  std::optional<types::Type*>,
                                                                  std::optional<std::deque<std::shared_ptr<ir::Func>>>,
                                                                  std::optional<std::deque<Cache::FunctionStore>>,
                                                                  std::optional<std::shared_ptr<ir::Module>>,
                                                                  bool /* Accept private members */> {
    // TODO: dont allow operators for modules

    auto g = utils::cast<Expression::GenericIdentifier>(index->getIdentifier());
    auto generics = (g != nullptr) ? g->getGenerics() : std::vector<Expression::TypeRef*>{};

    auto fullUUID = m->getUniqueName();
    auto [v, ty, fns, ovs, mod] =
            getFromIdentifier(dbgInfo, index->getIdentifier()->getIdentifier(), generics, fullUUID);

    if (!v.has_value()) {
      for (auto& variable : m->getVariables()) {
        if (variable->getIdentifier() == index->getIdentifier()->getIdentifier()) { // TODO: make this faster
          v = variable->getVariable();
          break;
        }
      } 
    }

    if (!v.has_value() && !ty.has_value() && !fns.has_value() && !ovs.has_value() && !mod.has_value()) {
      E<VARIABLE_ERROR>(
              dbgInfo,
              FMT("Coudnt find '%s' inside module '%s'!",
                  index->getIdentifier()->getIdentifier().c_str(),
                  m->getName().c_str())
      );
    }

    return {v, ty, fns, ovs, mod, isInModuleContext(m)};
  };

  // Transform the base first
  auto base = index->getBase();
  if (auto baseIdentifier = utils::cast<Expression::Identifier>(base)) {
    auto [val, type, funcs, overloads, mod] = getFromIdentifier(baseIdentifier);

    if (val && (!isStatic)) {
      return {getFromType(val.value()->getType(), *val), val.value()};
    } else if (val) {
      E<TYPE_ERROR>(
              dbgInfo,
              "Static method call / accesses can only be "
              "used with types, not values!"
      );
    }

    else if (mod && (!isStatic)) {
      E<TYPE_ERROR>(
              dbgInfo,
              "Module members must be accessed by using "
              "static indexes!"
      );
    } else if (mod) {
      return {getFromModule(*mod), std::nullopt};
    }

    else if (type && (!isStatic)) {
      E<TYPE_ERROR>(
              dbgInfo,
              "Cant use type references for method calls / "
              "accesses!"
      );
    } else if (type) {
      return {getFromType(*type), std::nullopt};
    }

    else if (overloads || funcs) {
      E<TYPE_ERROR>(dbgInfo, "Cant use function pointer as index base!");
    } else {

      E<VARIABLE_ERROR>(
              baseIdentifier->getDBGInfo(),
              FMT("Cannot find identifier '%s'!", baseIdentifier->getIdentifier().c_str()),
              {.info = "this name is not defined"}
      );
    }

    assert(false && "BUG: unhandled index value");
  } else if (auto x = utils::cast<Expression::Index>(base)) {
    auto [r, b] = getFromIndex(base->getDBGInfo(), x, x->isStatic);
    auto [v, t, fs, ovs, mod, c] = r;

    if (v && (!isStatic)) {
      return {getFromType(v.value()->getType(), *v), v.value()};
    } else if (v) {
      E<TYPE_ERROR>(
              dbgInfo,
              "Static method index can only be "
              "used with types, not values!"
      );
    }

    else if (mod && (!isStatic)) {
      E<TYPE_ERROR>(
              dbgInfo,
              "Module members must be accessed by using "
              "static indexes!"
      );
    } else if (mod) {
      return {getFromModule(*mod), std::nullopt};
    }

    else if (t && (!isStatic)) {
      E<TYPE_ERROR>(
              dbgInfo,
              "Cant use type references for method calls / "
              "accesses!"
      );
    } else if (t) {
      return {getFromType(*t), std::nullopt};
    }

    else if (ovs || fs) {
      E<TYPE_ERROR>(dbgInfo, "Cant use function pointer as index base!");
    } else {
      // TODO: include base name
      E<VARIABLE_ERROR>(dbgInfo, FMT("Identifier '%s' not found!", baseIdentifier->getIdentifier().c_str()));
    }

    assert(false && "TODO: index index");
  } else if (auto x = utils::cast<Expression::TypeRef>(base)) {
    auto ty = transformSizedType(x, false, "Cant access method calls from unsized types (%s)!");

    if (ty && (!isStatic)) {
      E<TYPE_ERROR>(
              dbgInfo,
              "Cant use type references for method calls / "
              "accesses!"
      );
    } else if (ty) {
      return {getFromType(ty), std::nullopt};
    }
  } else if (!isStatic) {
    // case: Integers, Strings, etc... index
    auto v = trans(base);
    return {getFromType(v->getType(), v), v};
  } else {
    E<SYNTAX_ERROR>(
            dbgInfo,
            "Static acces/method call can only be used with "
            "indentifiers!"
    );
  }

  return {{std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, false}, std::nullopt};
}
} // namespace Syntax
} // namespace snowball