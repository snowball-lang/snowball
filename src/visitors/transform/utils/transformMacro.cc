#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

void Transformer::transformMacro(Expression::PseudoVariable* p_node, MacroInstance* macroIns) {
  auto args = p_node->getArgs();
  auto macroName = p_node->getIdentifier();
  auto macroInstance = macroIns;
  auto macro = macroIns->macro;
  auto numRequiredArgs = macro->getArgs().size();
  for (auto arg : macro->getArgs()) numRequiredArgs -= std::get<2>(arg) == nullptr ? 0 : 1;
  if (args.size() < numRequiredArgs) {
    E<PSEUDO_ERROR>(p_node,
                    FMT("Macro '%s' expects at least %d arguments, but %d were given!", macroName.c_str(),
                        numRequiredArgs, args.size()));
  }
  // Typecheck macros:
  for (int i = 0; i < macro->getArgs().size(); i++) {
    Node* arg = nullptr;
    auto macroArg = macro->getArgs()[i];
    auto name = std::get<0>(macroArg);
    auto argType = std::get<1>(macroArg);
    auto defaultArg = std::get<2>(macroArg);
    if ((i + 1) > args.size() && args.size() < macro->getArgs().size()) {
      assert(defaultArg);
      arg = defaultArg;
    } else {
      arg = args.at(i);
    }
    Macro::ArguementType deducedArgType;
    if (utils::cast<Expression::Base>(arg)) {
      if (auto x = utils::cast<Expression::ConstantValue>(arg)) {
        deducedArgType = Macro::ArguementType::CONSTANT;
        auto ty = x->getType();
        if (argType != Macro::ArguementType::CONSTANT) { // A more specific version of it
          if (ty == Expression::ConstantValue::ConstantType::String) {
            deducedArgType = Macro::ArguementType::CONSTANT_STRING;
          } else if (ty == Expression::ConstantValue::ConstantType::Number ||
                     ty == Expression::ConstantValue::ConstantType::Float ||
                     ty == Expression::ConstantValue::ConstantType::Bool) {
            deducedArgType = Macro::ArguementType::CONSTANT_NUMBER;
          } else if (ty == Expression::ConstantValue::ConstantType::Char) {
            deducedArgType = Macro::ArguementType::CONSTANT_CHAR;
          }
        }
      } else {
        deducedArgType = Macro::ArguementType::EXPRESSION;
      }
    } else if (utils::cast<Statement::Base>(arg)) {
      deducedArgType = Macro::ArguementType::STATEMENT;
    } else if (auto x = utils::cast<Macro>(arg)) {
      deducedArgType = x->isMacroStatement() ? Macro::ArguementType::STATEMENT : Macro::ArguementType::EXPRESSION;
    } else {
      E<PSEUDO_ERROR>(p_node, FMT("Unknown arguement type for macro '%s'!", macroName.c_str()));
    }
    if (argType != deducedArgType) {
      E<PSEUDO_ERROR>(p_node,
                      FMT("Macro '%s' expects arguement '%s' to be of type '%s', but '%s' was given!",
                          macroName.c_str(), name.c_str(), Macro::arguementTypeToString(argType).c_str(),
                          Macro::arguementTypeToString(deducedArgType).c_str()));
    }
    if (macroInstance->stack.find(name) != macroInstance->stack.end()) {
      E<PSEUDO_ERROR>(p_node,
                      FMT("Macro '%s' already has an arguement with name '%s'!", macroName.c_str(), name.c_str()));
    }
    arg->parentMacro = ctx->currentMacroInstance;
    macroInstance->stack.insert(std::make_pair(name, std::make_pair(arg, deducedArgType)));
  }
  if (macroName == "pkg") {
    if (ctx->currentMacroInstance == nullptr) {
      E<PSEUDO_ERROR>(p_node, "Can't use `@pkg` macro outside a parent macro!",
                      {.info = "This is the macro that was used",
                       .note = "This special macro is only available inside a parent macro.",
                       .help = "Try using the macro inside a parent macro."});
    }
    auto expr = args.at(0);
    auto backupModule = ctx->module;
    ctx->module = ctx->currentMacroInstance->module;
    trans(expr);
    ctx->module = backupModule;
  } else {
    auto backup = ctx->currentMacroInstance;
    ctx->currentMacroInstance = macroInstance;
    for (auto inst : macro->getBody()->getStmts()) { trans(inst); }
    ctx->currentMacroInstance = backup;
  }
  macroInstance->stack.clear();
}

} // namespace Syntax
} // namespace snowball
