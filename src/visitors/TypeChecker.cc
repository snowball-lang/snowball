
#include "TypeChecker.h"

#include "../ast/errors/error.h"
#include "../ast/syntax/nodes.h"
#include "../ast/types/FunctionType.h"
#include "../ast/types/PrimitiveTypes.h"
#include "../ir/values/Call.h"
#include "../ir/values/Cast.h"
#include "../ir/values/Conditional.h"
#include "../ir/values/Func.h"
#include "../ir/values/IndexExtract.h"
#include "../ir/values/Return.h"
#include "../ir/values/Value.h"
#include "../ir/values/VariableDeclaration.h"
#include "../ir/values/WhileLoop.h"

#include <assert.h>
#include <optional>
#include <string>
#include <vector>

#define VISIT(Val) void TypeChecker::visit(ir::Val *p_node)

namespace snowball {
namespace codegen {

TypeChecker::TypeChecker(std::shared_ptr<ir::Module> mod)
    : AcceptorExtend<TypeChecker, ValueVisitor>(), module(mod) {}

VISIT(Func) {
    auto backup = ctx->getCurrentFunction();
    ctx->setCurrentFunction(p_node);
    auto body = p_node->getBody();
    if (body) body->visit(this);

    ctx->setCurrentFunction(backup);
}

VISIT(StringValue) { /* noop */
}
VISIT(NumberValue) { /* noop */
}
VISIT(BooleanValue) { /* noop */
}
VISIT(FloatValue) { /* noop */
}
VISIT(CharValue) { /* noop */
}

VISIT(Call) {
    auto args = p_node->getArguments();
    for (auto a : args) {
        a->visit(this);
    }

    // TODO: check for operator sides being equal

    // TODO: add support for "callable" type, not just function type
    if (std::dynamic_pointer_cast<types::FunctionType>(
            p_node->getCallee()->getType()) == nullptr) {
        Syntax::E<TYPE_ERROR>(
            p_node, FMT("Value trying to be called is not callable!"));
    }

    if (auto fn = utils::dyn_cast<ir::Func>(p_node->getCallee())) {
        if (services::OperatorService::isOperator(fn->getName(true)) &&
            args.size() == 2) {

            if (services::OperatorService::opEquals<
                    services::OperatorService::EQ>(fn->getName(true))) {
                if (auto x = isMutable(args.at(0));
                    (x.has_value() && (!x.value()))) {
                    if (!p_node->isInitialization) {
                        Syntax::E<VARIABLE_ERROR>(
                            p_node,
                            "You can't assign a new value to a unmutable "
                            "variable",
                            {.info = "This variable is not mutable!"});
                    }
                }
            }
            // TODO: check for operator sides being equal.
        }
    }
}

VISIT(VariableDeclaration) {
    auto val = p_node->getValue();
    val->visit(this);

    cantBeVoid(p_node, val->getType(),
               FMT("Value used for variable '%s' has a value with 'void' type!",
                   p_node->getIdentifier().c_str()));
}

VISIT(IndexExtract) {
    cantBeVoid(p_node, p_node->getType(),
               "Value used for index extraction has a value with 'void' type!");
}

VISIT(Variable) {
    cantBeVoid(p_node, p_node->getType(),
               FMT("Value used for variable '%s' has a value with 'void' type!",
                   p_node->getIdentifier().c_str()));
}

VISIT(Argument) {
    assert(ctx->getCurrentFunction() != nullptr);
    /* noop */
}

VISIT(ValueExtract) { /* noop */
}

VISIT(WhileLoop) {
    p_node->getCondition()->visit(this);
    p_node->getBlock()->visit(this);
}

VISIT(Conditional) {

    p_node->getCondition()->visit(this);
    p_node->getBlock()->visit(this);

    if (auto x = p_node->getElse()) {
        x->visit(this);
    }
}

VISIT(Cast) {
    auto v = p_node->getExpr();
    auto t = p_node->getCastType();
    assert(t->is(p_node->getType()));

    if ((utils::dyn_cast<types::NumericType>(v->getType()) == nullptr) &&
        (utils::dyn_cast<types::NumericType>(t) != nullptr)) {
        Syntax::E<TYPE_ERROR>(p_node,
                              FMT("Can't create a casting operator from a "
                                  "non-numerical type ('%s') "
                                  "to a numerical ('%s')!",
                                  t->getPrettyName().c_str(),
                                  v->getType()->getPrettyName().c_str()));
    } else if ((utils::dyn_cast<types::NumericType>(v->getType()) != nullptr) &&
               (utils::dyn_cast<types::NumericType>(t) == nullptr)) {
        Syntax::E<TYPE_ERROR>(
            p_node,
            FMT("Can't create a casting operator from a numerical type ('%s') "
                "to a non-numerical type ('%s')!",
                t->getPrettyName().c_str(),
                v->getType()->getPrettyName().c_str()));
    } else if (!v->getType()->canCast(t)) {
        Syntax::E<TYPE_ERROR>(
            p_node, FMT("Can't create a casting operator from value ('%s') "
                        "to type '%s'!",
                        t->getPrettyName().c_str(),
                        v->getType()->getPrettyName().c_str()));
    }
}

VISIT(Return) {
    auto fn = ctx->getCurrentFunction();
    assert(fn != nullptr);

    if (p_node->getExpr() != nullptr) {
        p_node->getExpr()->visit(this);
    }

    if ((std::dynamic_pointer_cast<types::VoidType>(fn->getRetTy()) !=
         nullptr) &&
        (p_node->getExpr() != nullptr)) {
        Syntax::E<TYPE_ERROR>(p_node,
                              FMT("Nonvalue returning function cant have a "
                                  "return containing an expression (%s)!",
                                  p_node->getType()->getPrettyName().c_str()));
    }

    if ((std::dynamic_pointer_cast<types::VoidType>(fn->getRetTy()) ==
         nullptr) &&
        (p_node->getExpr() == nullptr)) {
        Syntax::E<TYPE_ERROR>(p_node,
                              FMT("Can't return \"nothing\" in a function with "
                                  "non-void return type (%s)!",
                                  fn->getRetTy()->getPrettyName().c_str()));
    }

    if (!fn->getRetTy()->is(p_node->getType())) {
        Syntax::E<TYPE_ERROR>(p_node,
                              FMT("Return type (%s) does not match parent "
                                  "function's return type (%s)!",
                                  p_node->getType()->getPrettyName().c_str(),
                                  fn->getRetTy()->getPrettyName().c_str()));
    }
}

VISIT(Block) {
    for (auto i : p_node->getBlock()) {
        i->visit(this);
    }
}

void TypeChecker::codegen() {
    // Visit variables
    for (auto v : module->getVariables()) {
        visit(v.get());
    }

    // Generate the functions from the end to the front.
    auto functions = module->getFunctions();

    // Iterate every function with a reversed iterator.
    for (auto fn = functions.rbegin(); fn != functions.rend(); ++fn) {
        visit(fn->get());
    }
}

void TypeChecker::cantBeVoid(DBGObject *dbg, std::shared_ptr<types::Type> ty,
                             const std::string& message) {
    if (std::dynamic_pointer_cast<types::VoidType>(ty)) {
        Syntax::E<TYPE_ERROR>(dbg, message);
    }
}

std::optional<bool> TypeChecker::isMutable(std::shared_ptr<ir::Value> value) {
    if (auto x = utils::dyn_cast<ir::Variable>(value)) {
        return x->isMutable();
    } else if (auto x = utils::dyn_cast<ir::VariableDeclaration>(value)) {
        assert(false);
    } else if (auto x = utils::dyn_cast<ir::IndexExtract>(value)) {
        return x->getField()->isMutable;
    }

    return std::nullopt;
}

} // namespace codegen
} // namespace snowball

#undef VISIT