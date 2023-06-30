#include "../../Transformer.h"

#include <optional>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::LambdaFunction) {
    E<TODO>("Not implementing lambdas until next year!");

    auto node = p_node->getFunc();

    auto parent = ctx->getCurrentFunction();
    assert(parent != nullptr);

    // Get the respective return type for this function
    auto returnType = transformType(node->getRetType());

    // Create a new function value and store it's return type.
    char l[] = _SNOWBALL_LAMBDA_FUNCTIONS;
    auto name = parent->getName() + "::" + l + '\00';
    std::shared_ptr<ir::Func> fn = ctx->module->N<ir::Func>(
            node->getDBGInfo(), name, false, node->isVariadic(), ctx->getCurrentClass());
    fn->setRetTy(returnType);
    fn->setPrivacy(Statement::Privacy::PUBLIC);
    fn->setStatic(false);

    fn->setAttributes(node);
    ir::Func::FunctionArgs newArgs = {};

    for (int i = 0; i < node->getArgs().size(); i++) {
        auto arg = node->getArgs().at(i);

        auto a = ctx->module->N<ir::Argument>(node->getDBGInfo(),
                                              arg->getName(),
                                              fn->isConstructor() + i,
                                              arg->hasDefaultValue() ? arg->getDefaultValue()
                                                                     : nullptr);
        a->setType(transformType(arg->getType()));
        newArgs.insert(newArgs.end(), {arg->getName(), a});
    }

    fn->setArgs(newArgs);

    auto fnType = types::FunctionType::from(fn.get());
    fn->setType(std::shared_ptr<types::FunctionType>(fnType));

    // Generate a bodied for functions that have
    // them defined.
    if (auto bodiedFn = utils::cast<Statement::BodiedFunction>(node)) {
        auto backupFunction = ctx->getCurrentFunction();
        ctx->setCurrentFunction(fn);

        ctx->withScope([&]() {
            int argIndex = 0;
            for (auto arg : newArgs) {
                auto ref = ctx->module->N<ir::Variable>(
                        node->getDBGInfo(), arg.first, true /* TODO: is mutable */);

                ref->setType(arg.second->getType());
                auto refItem = std::make_shared<transform::Item>(transform::Item::Type::VALUE, ref);

                ref->setId(arg.second->getId());
                ctx->addItem(arg.first, refItem);
                argIndex++;
            }

            auto body = bodiedFn->getBody();

            if (!fn->isConstructor() && !bodyReturns(body->getStmts()) &&
                !((utils::dyn_cast<types::NumericType>(returnType)) ||
                  (utils::dyn_cast<types::VoidType>(returnType)))) {
                E<TYPE_ERROR>(node,
                              "Function lacks ending return statement!",
                              {.info = "Function does not return on all paths!"});
            }

            body->accept(this);
            auto functionBody = std::dynamic_pointer_cast<ir::Block>(this->value);
            fn->setBody(functionBody);
        });

        ctx->setCurrentFunction(backupFunction);
    } else if (auto e = utils::cast<Statement::LLVMFunction>(node)) {
        fn->setLLVMBody(e->getBody());
    }

    ctx->module->addFunction(fn);
    this->value = fn;
}

} // namespace Syntax
} // namespace snowball