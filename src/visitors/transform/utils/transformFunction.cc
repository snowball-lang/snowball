#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::shared_ptr<ir::Func> Transformer::transformFunction(Cache::FunctionStore fnStore,
        const std::vector<types::Type*>& deducedTypes,
        bool isEntryPoint,
        std::deque<std::shared_ptr<ir::Func>>
                overloads) {
  auto node = fnStore.function;
  bool dontAddToModule = false;

  // get the function name and store it for readability
  auto name = node->getName();

  // Cast the function into a bodied one, if it's not bodied,
  // we will get nullptr as a result.
  auto bodiedFn = cast<Statement::BodiedFunction>(node);

  std::shared_ptr<ir::Func> fn = nullptr;
  ctx->withState(fnStore.state, [&]() {
    // Parent scope for things such as: generics
    ctx->withScope([&]() {
      // Transform generics
      // TODO: variadic generics?
      assert(deducedTypes.size() == node->getGenerics().size());
      std::vector<std::pair<std::string, types::Type*>> fnGenerics;
      for (int genericCount = 0; genericCount < deducedTypes.size(); genericCount++) {
        auto nodeGeneric = node->getGenerics().at(genericCount);
        auto name = nodeGeneric->getName();
        auto generic = deducedTypes.at(genericCount);

        auto item = std::make_shared<transform::Item>(generic);
        // TODO:
        // item->setDBGInfo(generic->getDBGInfo());
        ctx->addItem(name, item);
        executeGenericTests(nodeGeneric->getWhereClause(), generic, name);

        fnGenerics.push_back({name, generic});
      }

      // Get the respective return type for this function
      auto returnType = transformType(node->getRetType());
      // Create a new function value and store it's return type.
      fn = getBuilder().createFunction(node->getDBGInfo(), name,
              (bodiedFn == nullptr && !node->hasAttribute(Attributes::LLVM_FUNC)), node->isVariadic());
      fn->setParent(ctx->getCurrentClass());
      fn->setRetTy(returnType);
      fn->setPrivacy(node->getPrivacy());
      fn->setStatic(node->isStatic());
      if (node->isGeneric())
        fn->setGenerics(fnGenerics);
      fn->setModule(ctx->module);
      fn->setAttributes(node);
      auto isExtern = node->isExtern();
      if (((fn->hasParent() || !fn->isStatic()) || fn->isPrivate()) && !isEntryPoint && !isExtern &&
              !fn->hasAttribute(Attributes::EXTERNAL_LINKAGE) && !fn->hasAttribute(Attributes::EXPORT))
        fn->addAttribute(Attributes::INTERNAL_LINKAGE);

      ir::Func::FunctionArgs newArgs = {};
      if (fn->isConstructor()) {
        auto a = getBuilder().createArgument(node->getDBGInfo(), "self", 0, (Syntax::Expression::Base*)nullptr);
        auto ty = ctx->getCurrentClass(true)->getReferenceTo();
        ty->setMutable(node->isMutable());
        a->setType(ty);
        newArgs.emplace(newArgs.begin(), std::make_pair("self", a));
      }

      for (int i = 0; i < node->getArgs().size(); i++) {
        auto arg = node->getArgs().at(i);

        auto a = getBuilder().createArgument(node->getDBGInfo(), arg->getName(), fn->isConstructor() + i,
                arg->hasDefaultValue() ? arg->getDefaultValue() : nullptr);
        a->setType(transformType(arg->getType()));
        if (arg->getName() != "self") a->getType()->setMutable(arg->isMutable());
        a->setMutability(a->getType()->isMutable());
        newArgs.push_back({arg->getName(), a});
      }

      fn->setArgs(newArgs);
      auto fnType = types::FunctionType::from(fn.get(), node);
      fn->setType(fnType);
      if (auto x = shouldReturnOverload(fn, overloads)) {
        fn = x;
        dontAddToModule = true;
        return;
      }

      if (auto c = ctx->getCurrentClass(true)) {
        auto pClass = utils::cast<types::DefinedType>(c);
        if (pClass != nullptr)
          if (node->isVirtual()) { 
            auto index = pClass->getModule()->typeInformation.at(pClass->getId())->addVtableItem(fn);
            //pClass->addVtableItem(fn); // just in case
            fn->setVirtualIndex(index); 
          }
      }

      ctx->defineFunction(fn);

      // Generate a bodied for functions that have
      // them defined.
      if (bodiedFn != nullptr) {
        auto backupFunction = ctx->getCurrentFunction();
        ctx->setCurrentFunction(fn);

        ctx->withScope([&]() {
          int argIndex = 0;
          for (auto arg : newArgs) {
            auto ref = getBuilder().createVariable(node->getDBGInfo(), arg.first, true, arg.second->isMutable());
            getBuilder().setType(ref, arg.second->getType());
            ref->getType()->setMutable(arg.second->isMutable());
            auto refItem = std::make_shared<transform::Item>(transform::Item::Type::VALUE, ref);
            ref->setId(arg.second->getId());
            ctx->addItem(arg.first, refItem);
            argIndex++;
          }

          auto body = bodiedFn->getBody();
          if (!bodyReturns(body->getStmts()) &&
                  !((utils::cast<types::NumericType>(returnType)) || (utils::cast<types::VoidType>(returnType))) &&
                  !fn->isConstructor() && !node->hasAttribute(Attributes::NOT_IMPLEMENTED) &&
                  !node->hasAttribute(Attributes::BUILTIN)) {
            E<TYPE_ERROR>(node,
                    "Function lacks ending return statement!",
                    {.info = "Function does not return on all "
                             "paths!"});
          }

          std::vector<std::shared_ptr<ir::Value>> prependedInsts;
          if (fn->isConstructor()) {
            auto constructor = utils::cast<Statement::ConstructorDef>(node);
            assert(constructor != nullptr);
            fn->getType()->setMutable(true);
            auto [insts, superCall] = transformConstructor(constructor);
            prependedInsts = insts;
            fn->superCall = superCall;
          }

          auto block = trans(body);
          auto functionBody = utils::dyn_cast<ir::Block>(block);
          functionBody->prepend(prependedInsts);
          fn->setBody(functionBody);
        });

        ctx->setCurrentFunction(backupFunction);
      } else if (auto e = utils::cast<Statement::ExternFnDef>(node)) {
        assert(node->isExtern());
        fn->setExternalName(e->getExternalName());
      } else if (auto e = utils::cast<Statement::LLVMFunction>(node)) {
        fn->setLLVMBody(getLLVMBody(e->getBody(), e->getTypesUsed()));
      }
    });

    if (dontAddToModule) return;
    ctx->module->addFunction(fn);
  });

  if (!dontAddToModule) ctx->cache->setFunctionState(fn->getId(), fnStore.state);
  return fn;
}

} // namespace Syntax
} // namespace snowball