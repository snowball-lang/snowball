
#include "TypeChecker.h"

#include "../ast/errors/error.h"
#include "../ast/syntax/nodes.h"
#include "../ast/types/FunctionType.h"
#include "../ast/types/PointerType.h"
#include "../ast/types/PrimitiveTypes.h"
#include "../ast/types/ReferenceType.h"
#include "../ir/values/Argument.h"
#include "../ir/values/Call.h"
#include "../ir/values/Cast.h"
#include "../ir/values/Conditional.h"
#include "../ir/values/Dereference.h"
#include "../ir/values/Func.h"
#include "../ir/values/IndexExtract.h"
#include "../ir/values/ReferenceTo.h"
#include "../ir/values/Return.h"
#include "../ir/values/Throw.h"
#include "../ir/values/TryCatch.h"
#include "../ir/values/Value.h"
#include "../ir/values/ValueExtract.h"
#include "../ir/values/VariableDeclaration.h"
#include "../ir/values/WhileLoop.h"

#include <assert.h>
#include <optional>
#include <string>
#include <vector>

#define VISIT(Val) void TypeChecker::visit(ir::Val* p_node)

namespace snowball {
namespace codegen {

using namespace Syntax;
using Operators = services::OperatorService;

TypeChecker::TypeChecker(std::shared_ptr<ir::Module> mod) : AcceptorExtend<TypeChecker, ValueVisitor>(), module(mod) { }

VISIT(Func) {
  if (p_node->hasAttribute(Attributes::TYPECHECKED)) return;
  p_node->addAttribute(Attributes::TYPECHECKED);
  checkFunctionDeclaration(p_node);
  auto backup = ctx->getCurrentFunction();
  ctx->setCurrentFunction(p_node);
  auto unsafeBk = ctx->unsafeContext;
  auto body = p_node->getBody();
  ctx->unsafeContext = p_node->hasAttribute(Attributes::UNSAFE) && !p_node->hasAttribute(Attributes::UNSAFE_FUNC_NOT_BODY);
  if (body) body->visit(this);
  ctx->unsafeContext = unsafeBk;
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

VISIT(DereferenceTo) {
  auto val = p_node->getValue();
  val->visit(this);

  cantBeVoid(
          p_node,
          val->getType(),
          FMT("Value used for reference '%s' has a value with 'void' "
              "type!",
              p_node->getType()->getPrettyName().c_str())
  );
  if (utils::cast<types::PointerType>(val->getType())) {
    if (!ctx->unsafeContext) {
      E<SYNTAX_ERROR>(
              p_node,
              FMT("Pointer dereference is unsafe!"),
              {.info = "This pointer dereference is unsafe!",
               .note = "This error is caused by the pointer dereference being unsafe.",
               .help = "Try wrapping the pointer dereference in an `unsafe { ... }` block\nor adding the "
                       "'unsafe' attribute to the function.\n\nsee more: "
                       "https://snowball-lang.gitbook.io/docs/language-reference/unsafe-snowball",
               .tail = EI<>(val->getDBGInfo(), "", {.info = "This is the pointer declaration."})}
      );
    }
  } else if (!utils::cast<types::ReferenceType>(val->getType())) {
    E<TYPE_ERROR>(
            p_node,
            FMT("Value used for dereference '%s' is not a "
                "reference!",
                p_node->getType()->getPrettyName().c_str())
    );
  }
}

VISIT(ReferenceTo) {
  auto val = p_node->getValue();
  val->visit(this);

  cantBeVoid(
          p_node,
          val->getType(),
          FMT("Value used for reference '%s' has a value with 'void' "
              "type!",
              p_node->getType()->getPrettyName().c_str())
  );
}

VISIT(Call) {
  auto fn = utils::dyn_cast<ir::Func>(p_node->getCallee());
  bool validMethod = fn != nullptr && fn->hasParent() && !fn->isStatic();
  if (utils::is<ir::ZeroInitialized>(p_node)) return;
  if (p_node->getCallee() == nullptr) {
    E<BUG>(p_node, "Call has no callee!");
  } else if (utils::cast<types::FunctionType>(p_node->getCallee()->getType()) == nullptr) {
    E<TYPE_ERROR>(p_node, FMT("Value trying to be called is not callable!"));
  }

  // TODO: check for operator sides being equal

  int i = 0;
  if (fn) {
    if (fn->hasAttribute(Attributes::NOT_IMPLEMENTED)) {
      E<SYNTAX_ERROR>(
              p_node,
              FMT("Function '%s' is not implemented!", fn->getNiceName().c_str()),
              {.info = "This function is not implemented!",
               .note = "This error is caused by the function having the \n"
                       "'not implemented' attribute.",
               .help = "Try implementing the function or removing the \n"
                       "'= 0' attribute from it or override it from a \n"
                       "child class.",
               .tail = EI<>(fn->getDBGInfo(), "", {.info = "This is the function declaration."})}
      );
    } else if (fn->hasAttribute(Attributes::UNSAFE) && !ctx->unsafeContext) {
      E<SYNTAX_ERROR>(
              p_node,
              FMT("Function '%s' is unsafe!", fn->getNiceName().c_str()),
              {.info = "This function is unsafe!",
               .note = "This error is caused by the function being marked\n"
                       "as 'unsafe'.",
               .help = "Try wrapping the call in an 'unsafe { ... }' block\nor removing the 'unsafe' "
                       "attribute from the function.\n\nsee more: "
                       "https://snowball-lang.gitbook.io/docs/language-reference/unsafe-snowball",
               .tail = EI<>(fn->getDBGInfo(), "", {.info = "This is the function declaration."})}
      );
    }
    fn->visit(this);
  }
  for (auto a : p_node->getArguments()) {
    // TODO: maybe check even if it's not a function value?
    if (i == 0 && fn) checkMutability(p_node, fn, a);

    a->visit(this);
    i++;
  }
}

VISIT(VariableDeclaration) {
  auto val = p_node->getValue();
  val->visit(this);

  cantBeVoid(
          p_node,
          val->getType(),
          FMT("Value used for variable '%s' has a value with 'void' "
              "type!",
              p_node->getIdentifier().c_str())
  );
}

VISIT(Throw) {
  auto val = p_node->getExpr();
  val->visit(this);

  // TODO: check if the value is throwable
}

VISIT(TryCatch) {
  auto tryBlock = p_node->getBlock();
  auto catchBlock = p_node->getCatchBlocks();

  tryBlock->visit(this);
  for (auto c : catchBlock) { c->visit(this); }
}

VISIT(IndexExtract) {
  cantBeVoid(
          p_node,
          p_node->getType(),
          "Value used for index extraction has a value with 'void' "
          "type!"
  );
}

VISIT(Variable) {
  cantBeVoid(
          p_node,
          p_node->getType(),
          FMT("Value used for variable '%s' has a value with 'void' "
              "type!",
              p_node->getIdentifier().c_str())
  );
}

VISIT(Argument) {
  assert(ctx->getCurrentFunction() != nullptr);
  /* noop */
}

VISIT(ValueExtract) {
  if (auto func = ctx->getCurrentFunction()) {
    if (!func->isAnon()) return;

    auto variable = utils::dyn_cast<ir::Variable>(p_node->getValue());
    if (!variable) return;

    // mark as variable if it's a variable outside the function
    auto varScope = variable->getScopeIndex();
    auto funcScope = func->getScopeIndex();

    if (varScope <= funcScope) {
      // Ignore global variables
      if (varScope <= 2) return;

      variable->setUsedInLambda();
      variable->setParentFunc(func->getParentScope().get());
    }
  }
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

VISIT(LoopFlow) { /* noop */ }

VISIT(Cast) {
  auto v = p_node->getExpr();
  auto t = p_node->getCastType();
  assert(t->is(p_node->getType()));

  if (utils::cast<types::VoidType>(v->getType())) {
    E<TYPE_ERROR>(p_node, FMT("Cant cast from void type ('%s')!", v->getType()->getPrettyName().c_str()));
  }

  if (v->getType()->is(t)) return;

  // we allow casting from void pointers to any other pointer type
  if (utils::cast<types::PointerType>(v->getType()) && utils::cast<types::PointerType>(t)) {
    if (utils::cast<types::VoidType>(utils::cast<types::PointerType>(v->getType())->getBaseType()) ||
        utils::cast<types::VoidType>(utils::cast<types::PointerType>(t)->getBaseType())) {
      return;
    }
  }

  // we also allow "&x to *x"
  if (utils::cast<types::ReferenceType>(v->getType()) && utils::cast<types::PointerType>(t)) {
    if (utils::cast<types::ReferenceType>(v->getType())
                ->getPointedType()
                ->is(utils::cast<types::PointerType>(t)->getBaseType())) {
      return;
    }
  }

  if ((!v->getType()->isMutable()) && t->isMutable()) {
    E<TYPE_ERROR>(
      p_node,
      FMT("Cant cast from nonmutable type ('%s') to mutable type ('%s')!",
          v->getType()->getPrettyName().c_str(),
          t->getPrettyName().c_str())
    );
  }

  if (!v->getType()->canCast(t)) {
    E<TYPE_ERROR>(
            p_node,
            FMT("Cant create a casting operator from type '%s' "
                "to type '%s'!",
                v->getType()->getPrettyName().c_str(),
                t->getPrettyName().c_str()),
            {.note = "This error is caused by the types not being "
                     "castable.",
             .help = "Casting operators allow for type conversions between "
                     "different data types.\n"
                     "However, in this case, it is not possible to create a "
                     "casting operator from \n"
                     "the specified source type to the desired target type.\n\n"
                     "Please ensure that the types involved in the casting "
                     "operation are compatible \n"
                     "and that there is a valid casting mechanism defined "
                     "between them. Check the \n"
                     "documentation or language specifications to verify the "
                     "supported casting operations \n"
                     "and rules for the involved types.\n\n"
                     "If the desired type conversion is not directly supported, "
                     "you may need to consider \n"
                     "alternative approaches such as using explicit conversion "
                     "functions or implementing \n"
                     "custom conversion logic to achieve the desired result."}
    );
  }
}

VISIT(Return) {
  auto fn = ctx->getCurrentFunction();
  assert(fn != nullptr);

  if (p_node->getExpr() != nullptr) p_node->getExpr()->visit(this);
  if ((utils::cast<types::VoidType>(fn->getRetTy()) != nullptr) && (p_node->getExpr() != nullptr)) {
    E<TYPE_ERROR>(
            p_node,
            FMT("Nonvalue returning function cant have a "
                "return containing an expression ('%s')!",
                p_node->getType()->getPrettyName().c_str())
    );
  }

  if ((utils::cast<types::VoidType>(fn->getRetTy()) == nullptr) && (p_node->getExpr() == nullptr)) {
    E<TYPE_ERROR>(
            p_node,
            FMT("Cant return \"nothing\" in a function with "
                "non-void return type (%s)!",
                fn->getRetTy()->getPrettyName().c_str())
    );
  }

  if (!p_node->getType()->is(fn->getRetTy())) {
    E<TYPE_ERROR>(
            p_node,
            FMT("Return type ('%s') does not match parent "
                "function return type ('%s')!",
                p_node->getType()->getPrettyName().c_str(),
                fn->getRetTy()->getPrettyName().c_str())
    );
  }
}

VISIT(Block) {
  auto bk = ctx->unsafeContext;
  if (p_node->hasAttribute(Attributes::UNSAFE)) ctx->unsafeContext = true;
  for (auto i : p_node->getBlock()) i->visit(this);
  if (p_node->hasAttribute(Attributes::UNSAFE)) ctx->unsafeContext = bk;
}

void TypeChecker::codegen() {
  for (auto [idx, ty] : module->typeInformation) { fixTypes(ty); }

  // Visit variables
  for (auto v : module->getVariables()) { visit(v.get()); }

  // Generate the functions from the end to the front.
  auto functions = module->getFunctions();

  // Iterate every function with a reversed iterator.
  for (auto fn = functions.rbegin(); fn != functions.rend(); ++fn) visit(fn->get());
}

void TypeChecker::cantBeVoid(DBGObject* dbg, types::Type* ty, const std::string& message) {
  if (utils::cast<types::VoidType>(ty)) { E<TYPE_ERROR>(dbg, message); }
}

void TypeChecker::checkMutability(ir::Call* p_node, std::shared_ptr<ir::Func> fn, std::shared_ptr<ir::Value> value) {
  auto fnName = fn->getName(true);
  auto isMutable = this->isMutable(value);
  bool accessingSelf = this->accessingSelf(value);
  if (Operators::isOperator(fnName) && !Operators::opEquals<Operators::CONSTRUCTOR>(fnName)) {
    auto opType = Operators::operatorID(fnName);
    auto binOp = utils::cast<ir::BinaryOp>(p_node);
    auto isAssignment = Expression::BinaryOp::is_assignment(opType);
    assert(binOp);
    if (isAssignment && accessingSelf && !ctx->getCurrentFunction()->getType()->isMutable()) {
      E<VARIABLE_ERROR>(
              p_node,
              "You cant call a mutating method on an immutable instance!",
              {.info = "This function is mutable!",
               .note = "This error is caused by the function being "
                       "mutable, but the value being nonmutable.",
               .help = "Try to make the value mutable by adding the 'mut' "
                       "keyword or make the function\nnonmutable by "
                       "removing the 'mut' keyword from its declaration.",
               .tail =
                       EI<>(value->getDBGInfo(),
                            "",
                            {
                                    .info = "This value is nonmutable!",
                            })}
      );
    }

    if (isAssignment && !binOp->ignoreMutability && !isMutable) {
      if (!p_node->isInitialization) {
        E<VARIABLE_ERROR>(
                p_node,
                "You cant assign a new value to a "
                "unmutable "
                "variable",
                {.note = "This error is caused by the 'mut' keyword "
                         "not being present in \nthe variable "
                         "declaration.\n\nvalue type: " +
                         (std::string) BOLD + fn->getRetTy()->getPrettyName() + RESET,
                 .help = "Try to make the variable mutable by adding "
                         "the 'mut' keyword.",
                 .tail = EI<>(value->getDBGInfo(), "", {.info = "This variable is not mutable!"})}
        );
      }
    } else if (isAssignment) {
      if ((utils::dyn_cast<ir::Variable>(value) == nullptr &&
           utils::dyn_cast<ir::VariableDeclaration>(value) == nullptr &&
           utils::dyn_cast<ir::ValueExtract>(value) == nullptr && utils::dyn_cast<ir::IndexExtract>(value) == nullptr &&
           utils::dyn_cast<ir::Argument>(value) == nullptr && utils::dyn_cast<ir::DereferenceTo>(value) == nullptr &&
           utils::dyn_cast<ir::ReferenceTo>(value) == nullptr && utils::dyn_cast<ir::Call>(value) == nullptr) &&
          utils::cast<types::PrimitiveType>(value->getType())) {
        E<VARIABLE_ERROR>(
                p_node,
                "Expression is not assignable!",
                {.note = "This error is caused by the expression not "
                         "being assignable.",
                 .help = "Try to make the expression assignable by "
                         "adding the 'mut' keyword to the variable "
                         "declaration.",
                 .tail = EI<>(value->getDBGInfo(), "", {.info = "This expression is not assignable!"})}
        );
      }
      return;
    }

    // TODO: check for operator sides being equal.
  }

  if (!fn->isConstructor() && (fn->getType()->isMutable() && !isMutable)) {
    E<VARIABLE_ERROR>(
            p_node,
            "You cant call a mutating method on an immutable instance!",
            {.info = "This function is mutable!",
             .note = "This error is caused by the function being "
                     "mutable, but the value being nonmutable.",
             .help = "Try to make the value mutable by adding the 'mut' "
                     "keyword or make the function\nnonmutable by "
                     "removing the 'mut' keyword from its declaration.",
             .tail =
                     EI<>(value->getDBGInfo(),
                          "",
                          {
                                  .info = "This value is nonmutable!",
                          })}
    );
  }
}

bool TypeChecker::isMutable(std::shared_ptr<ir::Value> value) {
  if (auto x = utils::dyn_cast<ir::Variable>(value)) return x->isMutable();
  if (auto x = utils::dyn_cast<ir::IndexExtract>(value)) return x->getField()->isMutable;
  if (auto x = utils::dyn_cast<ir::VariableDeclaration>(value)) return x->getVariable()->isMutable();
  if (auto x = utils::dyn_cast<ir::ValueExtract>(value)) return isMutable(x->getValue());
  if (auto x = utils::dyn_cast<ir::Argument>(value)) return x->isMutable();
  if (auto x = utils::dyn_cast<ir::DereferenceTo>(value)) return isMutable(x->getValue());
  if (auto x = utils::dyn_cast<ir::ReferenceTo>(value)) return isMutable(x->getValue());

  return value->getType()->isMutable();
}

bool TypeChecker::accessingSelf(std::shared_ptr<ir::Value> value) {
  auto index = utils::dyn_cast<ir::IndexExtract>(value);

  while (index) {
    if (auto x = utils::dyn_cast<ir::Variable>(index->getValue())) return x->getIdentifier() == "self";
    index = utils::dyn_cast<ir::IndexExtract>(index->getValue());
  }

  return false;
}

void TypeChecker::checkFunctionDeclaration(ir::Func* p_node) {
  if (p_node->hasAttribute(Attributes::UNSAFE)) {
    // TODO:
    if (p_node->getAttributeArgs(Attributes::UNSAFE_FUNC_NOT_BODY).size() != 0) {
      E<SYNTAX_ERROR>(
              p_node->getDBGInfo(),
              "This attribute can't have arguments!",
              {.info = "This function is an unsafe function!",
               .note = "This error is caused giving arguments to this attribute.",
               .help = "Try removing the arguments from the attribute."}
      );
    }
  } else if (p_node->hasAttribute(Attributes::UNSAFE_FUNC_NOT_BODY)) {
    E<SYNTAX_ERROR>(
            p_node->getDBGInfo(),
            "This attribute may only be used on unsafe functions!",
            {.info = "This function is not an unsafe function!",
             .note = "This error is caused by the function having the 'unsafe_func_not_body' attribute.",
             .help = "Try removing the 'unsafe_func_not_body' attribute from the function or by making the "
                     "function 'unsafe'."}
    );
  } else if (p_node->hasAttribute(Attributes::TEST)) {
    if (p_node->isDeclaration())
      E<SYNTAX_ERROR>(
              p_node->getDBGInfo(),
              "Test functions must have a body!",
              {.info = "This function is a test function!",
               .note = "This error is caused by the function not having a body.",
               .help = "Try adding a body to the function."}
      );
    else if (!types::isInt32Type(p_node->getRetTy()))
      E<SYNTAX_ERROR>(
              p_node->getDBGInfo(),
              "Test functions must return an integer!",
              {.info = "This function is a test function!",
               .note = "This error is caused by the function not returning an integer.",
               .help = "Try changing the return type to an integer."}
      );
    else if (p_node->getArgs().size() > 0)
      E<SYNTAX_ERROR>(
              p_node->getDBGInfo(),
              "Test functions cant have arguments!",
              {.info = "This function is a test function!",
               .note = "This error is caused by the function having arguments.",
               .help = "Try removing the arguments from the function."}
      );
    else if (p_node->hasAttribute(Attributes::INLINE))
      E<SYNTAX_ERROR>(
              p_node->getDBGInfo(),
              "Test functions cant be inline!",
              {.info = "This function is a test function!",
               .note = "This error is caused by the function having the 'inline' attribute.",
               .help = "Try removing the 'inline' attribute from the function."}
      );

    auto args = p_node->getAttributeArgs(Attributes::TEST);
    for (auto [name, value] : args) {
      if (name == "expect") {
        if (value == "") {
          E<SYNTAX_ERROR>(
                  p_node->getDBGInfo(),
                  "Test functions must have an 'expect' value!",
                  {.info = "This function is a test function!",
                   .note = "This error is caused by the function not having an 'expect' value.",
                   .help = "Try adding an 'expect' value to the function."}
          );
        } else if (!utils::isNumber(value)) {
          E<SYNTAX_ERROR>(
                  p_node->getDBGInfo(),
                  "Test functions 'expect' value must be a number!",
                  {.info = "This function is a test function!",
                   .note = "This error is caused by the function having an 'expect' value that is "
                           "not a number.",
                   .help = "Try changing the 'expect' value to a number."}
          );
        }
      } else if (name == "skip") {
        if (value != "") {
          E<SYNTAX_ERROR>(
                  p_node->getDBGInfo(),
                  "Test functions 'skip' value must be empty!",
                  {.info = "This function is a test function!",
                   .note = "This error is caused by the function having a 'skip' value that is not "
                           "empty.",
                   .help = "Try removing the 'skip' value from the function."}
          );
        }
      } else {
        E<SYNTAX_ERROR>(
                p_node->getDBGInfo(),
                "Test functions cant have the '" + name + "' attribute!",
                {.info = "This function is a test function!",
                 .note = "This error is caused by the function having the '" + name + "' attribute.",
                 .help = "Try removing the '" + name + "' attribute from the function."}
        );
      }
    }
  } else if (p_node->hasAttribute(Attributes::BENCH)) {
    if (p_node->isDeclaration())
      E<SYNTAX_ERROR>(
              p_node->getDBGInfo(),
              "Benchmark functions must have a body!",
              {.info = "This function is a benchmark function!",
               .note = "This error is caused by the function not having a body.",
               .help = "Try adding a body to the function."}
      );
    else if (p_node->getArgs().size() > 0)
      E<SYNTAX_ERROR>(
              p_node->getDBGInfo(),
              "Benchmark functions can't have arguments!",
              {.info = "This function is a benchmark function!",
               .note = "This error is caused by the function having arguments.",
               .help = "Try removing the arguments from the function."}
      );
    else if (p_node->hasAttribute(Attributes::INLINE))
      E<SYNTAX_ERROR>(
              p_node->getDBGInfo(),
              "Benchmark functions cant be inline!",
              {.info = "This function is a benchmark function!",
               .note = "This error is caused by the function having the 'inline' attribute.",
               .help = "Try removing the 'inline' attribute from the function."}
      );
  } else if (p_node->hasAttribute(Attributes::INLINE)) {
    if (p_node->isDeclaration())
      E<SYNTAX_ERROR>(
              p_node->getDBGInfo(),
              "Inline functions must have a body!",
              {.info = "This function is an inline function!",
               .note = "This error is caused by the function not having a body.",
               .help = "Try adding a body to the function."}
      );
    else if (p_node->hasAttribute(Attributes::NO_INLINE))
      E<SYNTAX_ERROR>(
              p_node->getDBGInfo(),
              "Inline functions can't have the 'no_inline' attribute!",
              {.info = "This function is an inlined function!",
               .note = "This error is caused by the function having the 'no_inline' "
                       "attribute.",
               .help = "Try removing the 'no_inline' attribute from the function."}
      );
  } else if (p_node->hasAttribute(Attributes::LLVM_FUNC)) {
    auto args = p_node->getAttributeArgs(Attributes::LLVM_FUNC);
    for (auto [name, value] : args) {
      if (name == "sanitise_void_return") {
        if (value != "") {
          E<SYNTAX_ERROR>(
                  p_node->getDBGInfo(),
                  "LLVM functions 'sanitise_void_return' value must be empty!",
                  {.info = "This function is an LLVM function!",
                   .note = "This error is caused by the function having a 'sanitise_void_return' "
                           "value that is not empty.",
                   .help = "Try removing the 'sanitise_void_return' value from the function."}
          );
        }
      } else {
        E<SYNTAX_ERROR>(
                p_node->getDBGInfo(),
                "LLVM functions can't have the '" + name + "' attribute!",
                {.info = "This function is an LLVM function!",
                 .note = "This error is caused by the function having the '" + name + "' attribute.",
                 .help = "Try removing the '" + name + "' attribute from the function."}
        );
      }
    }
  }
}

void TypeChecker::fixTypes(std::shared_ptr<types::BaseType> ty) {
  // fix it's virtual table, for example:
  // [parent's vtable] -> [child's vtable]
  // parentFn(i32)[vtable index is 0] "overriden by" childFn(i32)[vtable index is 1]
  // we need to fix the vtable index of the childFn to 0 instead of 1 and
  // remove the parentFn from the vtable and remove one from the index of the
  // other functions
  auto type = utils::dyn_cast<types::DefinedType>(ty);
  if (type && type->hasVtable) {
    std::vector<types::DefinedType*> parents;
    std::vector<std::shared_ptr<ir::Func>> finalVtable;
    parents.push_back(type.get());

    // add parents from lowest to highest
    auto parent = type->getParent();
    while (parent) {
      parents.push_back(parent);
      parent = parent->getParent();
    }

    // reverse iterate over the parents
    for (auto parent = parents.rbegin(); parent != parents.rend(); ++parent) {
      int vtableIndex = 0;
      auto parentVtable = (*parent)->getVTable();
      for (auto fn : parentVtable) {
        // add it if it's not already in the vtable
        // we first check by name and then if the types exist
        // in the vtable
        auto it = std::find_if(finalVtable.begin(), finalVtable.end(), [&](auto& f) {
          return f->getName() == fn->getName() && utils::cast<types::FunctionType>(f->getType())->isIgnoringSelf(utils::cast<types::FunctionType>(fn->getType()));
        });

        if (it == finalVtable.end()) {
          // TODO: only when "overriding"!!!
          fn->setVirtualIndex(vtableIndex++);
          finalVtable.push_back(fn);
        } else {
          // if it's already in the vtable, we need to replace it
          // with the new function
          fn->setVirtualIndex(it - finalVtable.begin());
          finalVtable.at(it - finalVtable.begin()) = fn;
          vtableIndex = it - finalVtable.begin() + 1;
        }
      }
    }

    type->unsafeOverrideVtable(finalVtable);
  }
}

} // namespace codegen
} // namespace snowball

#undef VISIT