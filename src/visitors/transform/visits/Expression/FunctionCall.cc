#include "../../../../ir/values/Cast.h"
#include "../../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::FunctionCall) {
  auto callBackUp = ctx->latestCall;
  ctx->latestCall = p_node;
  auto[argValues, argTypes] =
  utils::vectors_iterate<Syntax::Expression::Base*, std::shared_ptr<ir::Value>, types::Type*>(
  p_node->getArguments(),
  [&](Syntax::Expression::Base * a) -> std::pair<std::shared_ptr<ir::Value>, types::Type*> {
  auto val = trans(a);
  return {val, val->getType()};
  }
  );
  auto callee = p_node->getCallee();
  std::shared_ptr<ir::Value> fn = nullptr;
  if (auto x = utils::cast<Expression::Identifier>(callee)) {
    auto g = utils::cast<Expression::GenericIdentifier>(callee);
    auto generics = (g != nullptr) ? g->getGenerics() : std::vector<Expression::TypeRef*> {};
    auto r = getFromIdentifier(x->getDBGInfo(), x->getIdentifier(), generics);
    auto rTuple = std::tuple_cat(r, std::make_tuple(true));
    fn = getFunction(p_node, rTuple, x->getNiceName(), argTypes, generics);
  } else if (auto x = utils::cast<Expression::Index>(callee)) {
    bool inModule = false;
    std::string baseName;
    auto indexBase = x->getBase();
    auto[r, b] = getFromIndex(x->getDBGInfo(), x, x->isStatic);
    if (auto b = utils::cast<Expression::Identifier>(indexBase)) {
      auto r = getFromIdentifier(b);
      auto m = std::get<4>(r);
      utils::assert_value_type<std::shared_ptr<ir::Module>&, decltype(*m)>();
      inModule = m.has_value();
      auto ir = std::tuple_cat(r, std::make_tuple(false));
      baseName = getNiceBaseName(ir) + "::";
    } else if (auto b = utils::cast<Expression::Index>(indexBase)) {
      auto[r, _] = getFromIndex(b->getDBGInfo(), b, b->isStatic);
      auto m = std::get<4>(r);
      utils::assert_value_type<std::shared_ptr<ir::Module>&, decltype(*m)>();
      inModule = m.has_value();
      baseName = getNiceBaseName(r) + "::";
    } else if (auto b = utils::cast<Expression::TypeRef>(indexBase)) {
      baseName = transformType(b)->getPrettyName() + "::";
    }
    auto g = utils::cast<Expression::GenericIdentifier>(x->getIdentifier());
    auto generics = (g != nullptr) ? g->getGenerics() : std::vector<Expression::TypeRef*> {};
    auto name = baseName + x->getIdentifier()->getNiceName();
    if (b.has_value()) {
      if (utils::cast<types::PrimitiveType>((*b)->getType()) || utils::cast<types::ReferenceType>((*b)->getType()) ||
          utils::cast<types::PointerType>((*b)->getType())) {
        argTypes.insert(argTypes.begin(), b.value()->getType());
      } else {
        argTypes.insert(argTypes.begin(), b.value()->getType()->getReferenceTo());
      }
    }
    // We asume it's a function
    fn = getFunction(p_node, r, name, argTypes, generics, false, b.has_value());
    if (auto c = utils::dyn_cast<ir::Func>(fn)) {
      if (b.has_value()) argTypes.erase(argTypes.begin());
      // TODO: actually check if base is a module with:
      // "getFromIdentifier" of the module
      if ((x->isStatic && (!c->isStatic())) && (!inModule)) {
        E<TYPE_ERROR>(
        p_node,
        FMT("Cant access class method '%s' "
            "that's not static as if it was one!",
            c->getNiceName().c_str())
        );
      } else if ((!x->isStatic) && c->isStatic()) {
        E<TYPE_ERROR>(
        p_node,
        FMT("Cant access static class method '%s' "
            "as with a non-static index expression!",
            c->getNiceName().c_str())
        );
      }
      if (b.has_value()) {
        // if (auto t = utils::cast<types::ReferenceType>(b.value()->getType())) {
        // if (utils::cast<types::ReferenceType>(t->getPointedType()) && !c->hasAttribute(Attributes::BUILTIN)) {
        // E<TYPE_ERROR>(p_node,
        // FMT("Cant access class method '%s' "
        // "from a reference to a reference!",
        // c->getNiceName().c_str()),
        // {
        // .tail = callBackUp == nullptr ? nullptr
        // : EI<>(callBackUp, "this is the call causing the
        // error"),
        // });
        // }
        // }
        auto baseType = (*b)->getType();
        if ((utils::cast<types::PrimitiveType>(baseType)) || utils::cast<types::ReferenceType>(baseType) ||
            utils::cast<types::PointerType>(baseType)) {
          argValues.insert(argValues.begin(), *b);
          argTypes.insert(argTypes.begin(), baseType);
        } else {
          auto reference = getBuilder().createReferenceTo(p_node->getDBGInfo(), *b);
          argValues.insert(argValues.begin(), reference);
          argTypes.insert(argTypes.begin(), reference->getType());
        }
      }
    }
  } else {
    fn = trans(callee);
  }
  assert(fn);
  if (auto x = utils::dyn_cast<ir::ObjectInitialization>(fn)) {
    x->setArguments(argValues);
    this->value = x;
    return;
  }
  // clang-format off
  auto call = getBuilder().createCall(p_node->getDBGInfo(), fn, {});
  if (auto t = getFunctionType(fn->getType())) {
    auto isContructor = utils::dyn_cast<ir::Func>(fn) && utils::dyn_cast<ir::Func>(fn)->isConstructor();
    for (size_t i = isContructor; i < argTypes.size() + isContructor; i++) {
      if (i >= t->getArgs().size()) break; // Ignore variadic arguments
      auto arg = argTypes.at(i - isContructor);
      auto deduced = t->getArgs().at(i);
      if (arg->is(deduced)) { /* ok */
      } else if (auto x = tryCast(argValues.at(i - isContructor), deduced)) {
        argValues.at(i - isContructor) = x;
        argTypes.at(i - isContructor) = deduced;
      } else {
        E<TYPE_ERROR>(p_node,
                      FMT("Cant assign value with type '%s' "
                          "to a parameter with type '%s'!",
                          arg->getPrettyName().c_str(),
                          deduced->getPrettyName().c_str()),
                      ErrorInfo{.info = "Argument at index " + std::to_string(i + 1) + " caused an error in the function call",
                                .note = utils::dyn_cast<ir::Func>(fn) == nullptr
                                        ? FMT("Errored trying to cal function with type `%s`",
                                              t->getPrettyName().c_str())
                                        : FMT("Errored trying to call function %s`%s`%s!\n\nWith type %s%s`%s`%s",
                                              BOLD,
                                              utils::dyn_cast<ir::Func>(fn)->getNiceName().c_str(),
                                              RESET,
                                              BOLD,
                                              UNDERLINE,
                                              t->getPrettyName().c_str(),
                                              RESET),
                                .tail = EI<>(argValues.at(i - isContructor), "",
        {
          .info = "this is the value that's causing the error",
          .help = "Maybe try to convert a cast to the correct type?"
        })});
      }
    }
    getBuilder().setType(call, t->getRetType());
  } else if (!utils::is<ir::EnumInit>(fn.get())) {
    assert(false && "TODO: other function values?!?!?");
  } else {
    getBuilder().setType(call, fn->getType());
  }
  if (auto func = utils::dyn_cast<ir::Func>(fn)) {
    // Check for default arguments
    auto args = utils::list2vec(func->getArgs());
    if (((int)argTypes.size() - func->hasParent()) < (int)(args.size() - func->hasParent())) {
      ctx->withState(ctx->cache->getFunctionState(func->getId()),
                     [&argTypes = argTypes, this, call, args, &argValues = argValues, p_node, func]() {
                     // add default arguments
                     auto shouldAdd = func->isConstructor();
                     for (size_t i = argTypes.size() == 0 ? 0 : (argTypes.size() + shouldAdd); i < args.size(); i++) {
                     auto arg = &args.at(i);
                     if (arg->second->hasDefaultValue()) {
                       auto defaultVal = arg->second->getDefaultValue();
                       auto backSrcInfo = defaultVal->getDBGInfo();
                       defaultVal->setDBGInfo(p_node->getDBGInfo());
                       auto val = trans(defaultVal);
                       defaultVal->setDBGInfo(backSrcInfo);
                       auto ty = val->getType();
                       argTypes.push_back(arg->second->getType());
                       if (!arg->second->getType()->is(ty)) {
                         if (auto cast = tryCast(val, arg->second->getType())) {
                           argValues.push_back(cast);
                           continue;
                           }
                           E<TYPE_ERROR>(arg->second,
                                         FMT("Function's default value does not match argument ('%s') type!",
            arg->first.c_str()), {
            .info = "This is the default value that's causing the error",
            .help = "Maybe try to convert a cast to the correct type?"
          });
    assert(false && "TODO: cast default argument");
                   }
    argValues.push_back(val);
             continue;
                   }
    if (arg->first == "self") {
      // We skip the "self" argument
      // inside a method (or constructor)
      // since it's a weird situation
      // where you pass an argument
      // implicitly.
      continue;
    }
    E<TYPE_ERROR>(p_node,
                  FMT("Could not get value for argument '%s'!",
                      arg->first.c_str()));
                   }
                   });
    }
    // clang-format on
  }
  // Set an updated version of the call arguments
  call->setArguments(argValues);
  call->isInitialization = p_node->isInitialization;
  this->value = call;
  ctx->latestCall = callBackUp;
}

} // namespace Syntax
} // namespace snowball