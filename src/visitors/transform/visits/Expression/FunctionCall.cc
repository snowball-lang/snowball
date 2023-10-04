#include "../../../../ir/values/Cast.h"
#include "../../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::FunctionCall) {
  auto callBackUp = ctx->latestCall;
  ctx->latestCall = p_node;
  auto [argValues, argTypes] =
          utils::vectors_iterate<Syntax::Expression::Base*, std::shared_ptr<ir::Value>, types::Type*>(
                  p_node->getArguments(),
                  [&](Syntax::Expression::Base* a) -> std::pair<std::shared_ptr<ir::Value>, types::Type*> {
                    auto val = trans(a);
                    return {val, val->getType()};
                  });
  auto callee = p_node->getCallee();
  std::shared_ptr<ir::Value> fn = nullptr;
  if (auto x = utils::cast<Expression::Identifier>(callee)) {
    auto g = utils::cast<Expression::GenericIdentifier>(callee);
    auto generics = (g != nullptr) ? g->getGenerics() : std::vector<Expression::TypeRef*>{};
    auto r = getFromIdentifier(x->getDBGInfo(), x->getIdentifier(), generics);
    auto rTuple = std::tuple_cat(r, std::make_tuple(true));
    fn = getFunction(p_node, rTuple, x->getNiceName(), argTypes, generics);
    assert(fn);
  } else if (auto x = utils::cast<Expression::Index>(callee)) {
    bool inModule = false;
    std::string baseName;
    auto indexBase = x->getBase();
    auto [r, b] = getFromIndex(x->getDBGInfo(), x, x->isStatic);
    if (auto b = utils::cast<Expression::Identifier>(indexBase)) {
      auto r = getFromIdentifier(b);
      auto m = std::get<4>(r);
      utils::assert_value_type<std::shared_ptr<ir::Module>&, decltype(*m)>();

      inModule = m.has_value();
      auto ir = std::tuple_cat(r, std::make_tuple(false));

      baseName = getNiceBaseName(ir) + "::";
    } else if (auto b = utils::cast<Expression::Index>(indexBase)) {
      auto [r, _] = getFromIndex(b->getDBGInfo(), b, b->isStatic);
      auto m = std::get<4>(r);
      utils::assert_value_type<std::shared_ptr<ir::Module>&, decltype(*m)>();

      inModule = m.has_value();
      baseName = getNiceBaseName(r) + "::";
    } else if (auto b = utils::cast<Expression::TypeRef>(indexBase)) {
      baseName = transformType(b)->getPrettyName() + "::";
    }
    auto g = utils::cast<Expression::GenericIdentifier>(x->getIdentifier());
    auto generics = (g != nullptr) ? g->getGenerics() : std::vector<Expression::TypeRef*>{};
    auto name = baseName + x->getIdentifier()->getNiceName();
    if (b.has_value()) {
      if (utils::cast<types::PrimitiveType>((*b)->getType()) || utils::cast<types::ReferenceType>((*b)->getType()) ||
              utils::cast<types::PointerType>((*b)->getType())) {
        argTypes.insert(argTypes.begin(), b.value()->getType());
      } else {
        argTypes.insert(argTypes.begin(), b.value()->getType()->getReferenceTo());
      }
    }
    auto c = getFunction(p_node, r, name, argTypes, generics, false, b.has_value());
    if (b.has_value()) argTypes.erase(argTypes.begin());
    // TODO: actually check if base is a module with:
    // "getFromIdentifier" of the module
    if ((x->isStatic && (!c->isStatic())) && (!inModule)) {
      E<TYPE_ERROR>(p_node,
              FMT("Can't access class method '%s' "
                  "that's not static as if it was one!",
                      c->getNiceName().c_str()));
    } else if ((!x->isStatic) && c->isStatic()) {
      E<TYPE_ERROR>(p_node,
              FMT("Can't access static class method '%s' "
                  "as with a non-static index expression!",
                      c->getNiceName().c_str()));
    }
    if (b.has_value()) {
      // if (auto t = utils::cast<types::ReferenceType>(b.value()->getType())) {
      //   if (utils::cast<types::ReferenceType>(t->getPointedType()) && !c->hasAttribute(Attributes::BUILTIN)) {
      //     E<TYPE_ERROR>(p_node,
      //                   FMT("Can't access class method '%s' "
      //                       "from a reference to a reference!",
      //                       c->getNiceName().c_str()),
      //                   {
      //                           .tail = callBackUp == nullptr ? nullptr
      //                                                         : EI<>(callBackUp, "this is the call causing the
      //                                                         error"),
      //                   });
      //   }
      // }
      
      auto baseType = (*b)->getType();
      if ((utils::cast<types::PrimitiveType>(baseType)) || utils::cast<types::ReferenceType>(baseType) ||
              utils::cast<types::PointerType>(baseType)) {
        argValues.insert(argValues.begin(), *b);
        argTypes.insert(argTypes.begin(), baseType);
      } else {
        auto reference = builder.createReferenceTo(p_node->getDBGInfo(), *b);
        argValues.insert(argValues.begin(), reference);
        argTypes.insert(argTypes.begin(), reference->getType());
      }
    }
    fn = c;
  } else {
    fn = trans(callee);
  }
  assert(fn);
  // clang-format off
    auto call = builder.createCall(p_node->getDBGInfo(), fn, argValues);
    if (auto t = utils::cast<types::FunctionType>(fn->getType())) {
      auto isContructor = utils::dyn_cast<ir::Func>(fn) && utils::dyn_cast<ir::Func>(fn)->isConstructor();
      if (t->getArgs().size() <= argTypes.size() || /**sorry**/
        ((t->getArgs().size()-1 <= argTypes.size()) && isContructor)) {
        for (int i = 0; i < t->getArgs().size()-isContructor; i++) {
          auto arg = argTypes.at(i);
          auto deduced = t->getArgs().at(i+isContructor);
          if (arg->is(deduced)) { /* ok */
          } else if (auto x = tryCast(argValues.at(i), deduced); x != nullptr) {
            argValues.at(i) = x;
            argTypes.at(i) = deduced;
          } else {
              E<TYPE_ERROR>(p_node,
                FMT("Can't assign value with type '%s' "
                  "to a parameter with type '%s'!",
                  arg->getPrettyName().c_str(),
                  deduced->getPrettyName().c_str()),
                ErrorInfo{.info = "This is the call causing the error! (argument index: " + std::to_string(i+1) + ")",
                  .note = utils::dyn_cast<ir::Func>(fn) == nullptr
                  ? FMT("Errored trying to cal function with type `%s`",
                    t->getPrettyName().c_str())
                  : FMT("Errored trying to call function `%s`!\n With type `%s`",
                    utils::dyn_cast<ir::Func>(fn)->getNiceName().c_str(),
                    t->getPrettyName().c_str()),
                  .tail = EI<>(argValues.at(i), "",
                    {.info = "this is the value that's causing the error",
                    .help = "Maybe try to convert a cast to the correct type?"})});
            }
          }
        }

        builder.setType(call, t->getRetType());
    } else {
        assert(false && "TODO: other function values?!?!?");
    }

    if (auto func = utils::dyn_cast<ir::Func>(fn)) {
        // Check for default arguments
        auto args = func->getArgs();
        if (argTypes.size() < (args.size() - func->hasParent())) {
            int default_arg_count = 0;
            for (auto arg : args) {
                if (arg.second->hasDefaultValue()) { ++default_arg_count; }
            }

            if (((args.size() - default_arg_count) - func->hasParent()) <= (argTypes.size() - func->hasParent())) {
                ctx->withState(ctx->cache->getFunctionState(func->getId()),
                [&argTypes = argTypes, this, call, args, &argValues = argValues, p_node]() {
                // add default arguments
                for (auto arg = std::next(args.begin(), argTypes.size()); arg != args.end(); ++arg) {
                    if (arg->second->hasDefaultValue()) {
                        auto val = trans(arg->second->getDefaultValue());
                        auto ty = val->getType();
                        if (!arg->second->getType()->is(ty)) {
                            if (!tryCast(val, arg->second->getType()))
                                E<TYPE_ERROR>(arg->second,
                                    FMT("Function's default value does not match argument ('%s') type!",
                                        arg->first.c_str()),
                                    {.info = "This is the default value that's causing the error",
                                    .help = "Maybe try to convert a cast to the correct type?"});
                            assert(false && "TODO: cast default argument");
                        } else {
                            argTypes.push_back(ty);
                            argValues.push_back(val);

                            call->setArguments(argValues);
                        }
                    } else {
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
                }
                });
            } else {
                E<TYPE_ERROR>(p_node, "Function call missing arguments!");
            }
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