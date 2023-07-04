
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
#include "../ir/values/ReferenceTo.h"
#include "../ir/values/Return.h"
#include "../ir/values/Value.h"
#include "../ir/values/VariableDeclaration.h"
#include "../ir/values/WhileLoop.h"
#include "../ir/values/Argument.h"

#include <assert.h>
#include <optional>
#include <string>
#include <vector>

#define VISIT(Val) void TypeChecker::visit(ir::Val* p_node)

namespace snowball {
namespace codegen {

using Operators = services::OperatorService;

TypeChecker::TypeChecker(std::shared_ptr<ir::Module> mod)
    : AcceptorExtend<TypeChecker, ValueVisitor>(), module(mod) { }

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

VISIT(ReferenceTo) {
    auto val = p_node->getValue();
    val->visit(this);

    cantBeVoid(p_node,
               val->getType(),
               FMT("Value used for reference '%s' has a value with 'void' "
                   "type!",
                   p_node->getType()->getPrettyName().c_str()));
    if (!utils::dyn_cast<ir::Variable>(val) && !utils::dyn_cast<ir::IndexExtract>(val)) {
        Syntax::E<TYPE_ERROR>(p_node,
                              FMT("Value used for reference '%s' is not a "
                                  "variable!",
                                  p_node->getType()->getPrettyName().c_str()));
    }
}

VISIT(Call) {
    auto fn = utils::dyn_cast<ir::Func>(p_node->getCallee());
    bool validMethod = fn != nullptr && fn->hasParent() && !fn->isStatic();
    if (utils::dyn_cast<types::FunctionType>(p_node->getCallee()->getType()) == nullptr) {
        Syntax::E<TYPE_ERROR>(p_node, FMT("Value trying to be called is not callable!"));
    }

    // TODO: check for operator sides being equal

    int i = 0;
    for (auto a : p_node->getArguments()) {
        if (i == 0) checkMutability(p_node, fn, a);

        i++;
        a->visit(this); 
    }
}

VISIT(VariableDeclaration) {
    auto val = p_node->getValue();
    val->visit(this);

    cantBeVoid(p_node,
               val->getType(),
               FMT("Value used for variable '%s' has a value with 'void' "
                   "type!",
                   p_node->getIdentifier().c_str()));
}

VISIT(IndexExtract) {
    cantBeVoid(p_node,
               p_node->getType(),
               "Value used for index extraction has a value with 'void' "
               "type!");
}

VISIT(Variable) {
    cantBeVoid(p_node,
               p_node->getType(),
               FMT("Value used for variable '%s' has a value with 'void' "
                   "type!",
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

    if (auto x = p_node->getElse()) { x->visit(this); }
}

VISIT(Cast) {
    auto v = p_node->getExpr();
    auto t = p_node->getCastType();
    assert(t->is(p_node->getType()));

    if (utils::dyn_cast<types::VoidType>(t)) {
        Syntax::E<TYPE_ERROR>(p_node,
                              FMT("Can't cast to void type ('%s')!", t->getPrettyName().c_str()));
    } else if (utils::dyn_cast<types::VoidType>(v->getType())) {
        Syntax::E<TYPE_ERROR>(
                p_node,
                FMT("Can't cast from void type ('%s')!", v->getType()->getPrettyName().c_str()));
    }

    if (v->getType()->is(t)) return;
    if (!v->getType()->canCast(t)) {
        Syntax::E<TYPE_ERROR>(p_node,
                              FMT("Can't create a casting operator from value ('%s') "
                                  "to type '%s'!",
                                  t->getPrettyName().c_str(),
                                  v->getType()->getPrettyName().c_str()));
    }
}

VISIT(Return) {
    auto fn = ctx->getCurrentFunction();
    assert(fn != nullptr);

    if (p_node->getExpr() != nullptr) { p_node->getExpr()->visit(this); }

    if ((std::dynamic_pointer_cast<types::VoidType>(fn->getRetTy()) != nullptr) &&
        (p_node->getExpr() != nullptr)) {
        Syntax::E<TYPE_ERROR>(p_node,
                              FMT("Nonvalue returning function cant have a "
                                  "return containing an expression (%s)!",
                                  p_node->getType()->getPrettyName().c_str()));
    }

    if ((std::dynamic_pointer_cast<types::VoidType>(fn->getRetTy()) == nullptr) &&
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
    for (auto i : p_node->getBlock()) { i->visit(this); }
}

void TypeChecker::codegen() {
    // Visit variables
    for (auto v : module->getVariables()) { visit(v.get()); }

    // Generate the functions from the end to the front.
    auto functions = module->getFunctions();

    // Iterate every function with a reversed iterator.
    for (auto fn = functions.rbegin(); fn != functions.rend(); ++fn) { visit(fn->get()); }
}

void TypeChecker::cantBeVoid(
        DBGObject* dbg, std::shared_ptr<types::Type> ty, const std::string& message) {
    if (utils::dyn_cast<types::VoidType>(ty)) { Syntax::E<TYPE_ERROR>(dbg, message); }
}

void TypeChecker::checkMutability(ir::Call* p_node, std::shared_ptr<ir::Func> fn, std::shared_ptr<ir::Value> value) {
    if (auto x = utils::dyn_cast<ir::Variable>(value)) {
        DUMP_S(x->getIdentifier().c_str())
    }
    auto fnName = fn->getName(true);
    auto isMutable = this->isMutable(value);
    bool accessingSelf = this->accessingSelf(value);
    if (Operators::isOperator(fnName)) {
        auto opType = Operators::operatorID(fnName);
        auto binOp = utils::cast<ir::BinaryOp>(p_node);
        auto isAssignment = Syntax::Expression::BinaryOp::is_assignment(opType);
        if (isAssignment && accessingSelf && !ctx->getCurrentFunction()->getType()->isMutable()) {
            Syntax::E<VARIABLE_ERROR>(p_node,
                "You can't call a mutating method on an immutable instance!",
                {.info = "This function is mutable!",
                .note = "This error is caused by the function being "
                        "mutable, but the value being nonmutable.",
                .help = "Try to make the value mutable by adding the 'mut' "
                        "keyword or make the function\nnonmutable by "
                        "removing the 'mut' keyword from it's declaration.",
                .tail = Syntax::EI<>(value->getDBGInfo(), "", {
                    .info = "This value is nonmutable!",
                }) });
        } 
        
        if (isAssignment && (!binOp->ignoreMutability && !isMutable) && !accessingSelf) {
            if (!p_node->isInitialization) {
                Syntax::E<VARIABLE_ERROR>(p_node,
                    "You can't assign a new value to a "
                    "unmutable "
                    "variable",
                    {
                    .note = "This error is caused by the 'mut' keyword "
                            "not being present in \nthe variable"
                            "declaration.",
                    .help = "Try to make the variable mutable by adding "
                        "the 'mut' keyword.",
                    .tail = Syntax::EI<>(value->getDBGInfo(), "", {
                        .info = "This variable is not mutable!"
                    })});
            }
        } else if (isAssignment) return;
        // TODO: check for operator sides being equal.
    }

    if (fn->getType()->isMutable() && !isMutable) {
        Syntax::E<VARIABLE_ERROR>(p_node,
            "You can't call a mutating method on an immutable instance!",
            {.info = "This function is mutable!",
            .note = "This error is caused by the function being "
                    "mutable, but the value being nonmutable.",
            .help = "Try to make the value mutable by adding the 'mut' "
                    "keyword or make the function\nnonmutable by "
                    "removing the 'mut' keyword from it's declaration.",
            .tail = Syntax::EI<>(value->getDBGInfo(), "", {
              .info = "This value is nonmutable!",
            }) });
    }
}

bool TypeChecker::isMutable(std::shared_ptr<ir::Value> value) {
    return value->getType()->isMutable();
}

bool TypeChecker::accessingSelf(std::shared_ptr<ir::Value> value) {
    auto index = utils::dyn_cast<ir::IndexExtract>(value);

    while (index) {
        if (auto x = utils::dyn_cast<ir::Variable>(index->getValue())) 
            return x->getIdentifier() == "self";
        index = utils::dyn_cast<ir::IndexExtract>(index->getValue());
    }

    return false;
}

} // namespace codegen
} // namespace snowball

#undef VISIT