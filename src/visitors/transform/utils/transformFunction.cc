#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::shared_ptr<ir::Func>
Transformer::transformFunction(Cache::FunctionStore fnStore,
                               const std::vector<std::shared_ptr<types::Type>>& deducedTypes,
                               bool isEntryPoint) {
    auto node = fnStore.function;

    // get the function name and store it for readability
    auto name = node->getName();

    // Cast the function into a bodied one, if it's not bodied,
    // we will get nullptr as a result.
    auto bodiedFn = cast<Statement::BodiedFunction>(node);
    bool isGeneric = node->getGenerics().size() > 0;

    std::shared_ptr<ir::Func> fn = nullptr;
    for (auto s : fnStore.state->stack) { continue; }
    ctx->withState(fnStore.state, [&]() {
        // Parent scope for things such as: generics
        ctx->withScope([&]() {
            // Transform generics
            // TODO: variadic generics?
            assert(deducedTypes.size() == node->getGenerics().size());
            std::vector<std::pair<std::string, std::shared_ptr<types::Type>>> fnGenerics;
            for (int genericCount = 0; genericCount < deducedTypes.size(); genericCount++) {
                auto nodeGeneric = node->getGenerics().at(genericCount);
                auto name = nodeGeneric->getName();
                auto generic = deducedTypes.at(genericCount);

                auto item = std::make_shared<transform::Item>(generic);
                // TODO:
                // item->setDBGInfo(generic->getDBGInfo());
                ctx->addItem(name, item);
                executeGenericTests(nodeGeneric->getWhereClause(), generic);

                fnGenerics.push_back({name, generic});
            }

            // Get the respective return type for this function
            auto returnType = transformType(node->getRetType());

            // Create a new function value and store it's return type.
            fn = builder.createFunction(
                    node->getDBGInfo(),
                    name,
                    (bodiedFn == nullptr && !node->hasAttribute(Attributes::LLVM_FUNC)),
                    node->isVariadic());
            fn->setParent(ctx->getCurrentClass());
            fn->setRetTy(returnType);
            fn->setPrivacy(node->getPrivacy());
            fn->setStatic(node->isStatic());
            fn->setGenerics(fnGenerics);
            fn->setModule(ctx->module);
            fn->setAttributes(node);
            auto isExtern = node->isExtern();
            if (((ctx->getCurrentClass() || !fn->isStatic()) || fn->isPrivate()) && !isEntryPoint &&
                !isExtern && !fn->hasAttribute(Attributes::EXTERNAL_LINKAGE) &&
                !fn->hasAttribute(Attributes::EXPORT))
                fn->addAttribute(Attributes::INTERNAL_LINKAGE);
            if (auto c = ctx->getCurrentClass(true)) {
                if (node->isVirtual()) { fn->setVirtualIndex(c->addVtableItem(fn)); }
            }

            ir::Func::FunctionArgs newArgs = {};
            if (fn->isConstructor()) {
                auto a = builder.createArgument(node->getDBGInfo(), "self", 0, nullptr);
                a->setType(ctx->getCurrentClass(true)->getPointerTo());
                newArgs.emplace(newArgs.begin(), std::make_pair("self", a));
            }

            for (int i = 0; i < node->getArgs().size(); i++) {
                auto arg = node->getArgs().at(i);

                auto a = builder.createArgument(node->getDBGInfo(),
                                                arg->getName(),
                                                fn->isConstructor() + i,
                                                arg->hasDefaultValue() ? arg->getDefaultValue()
                                                                       : nullptr);
                a->setType(transformType(arg->getType()));
                newArgs.insert(newArgs.end(), {arg->getName(), a});
            }

            fn->setArgs(newArgs);

            auto fnType = types::FunctionType::from(fn.get(), node);
            fn->setType(std::shared_ptr<types::FunctionType>(fnType));

            ctx->defineFunction(fn);

            // Generate a bodied for functions that have
            // them defined.
            if (bodiedFn != nullptr) {
                auto backupFunction = ctx->getCurrentFunction();
                ctx->setCurrentFunction(fn);

                ctx->withScope([&]() {
                    int argIndex = 0;
                    for (auto arg : newArgs) {
                        auto ref = builder.createVariable(node->getDBGInfo(), arg.first, true);

                        ref->setType(arg.second->getType());
                        auto refItem = std::make_shared<transform::Item>(
                                transform::Item::Type::VALUE, ref);

                        ref->setId(arg.second->getId());
                        ctx->addItem(arg.first, refItem);
                        argIndex++;
                    }

                    auto body = bodiedFn->getBody();

                    if (!bodyReturns(body->getStmts()) &&
                        !((utils::dyn_cast<types::NumericType>(returnType)) ||
                          (utils::dyn_cast<types::VoidType>(returnType))) &&
                        !fn->isConstructor()) {
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
                        prependedInsts = transformConstructor(constructor);
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
                fn->setLLVMBody(e->getBody());
            }
        });

        ctx->module->addFunction(fn);
    });

    ctx->cache->setFunctionState(fn->getId(), fnStore.state);
    return fn;
}

} // namespace Syntax
} // namespace snowball