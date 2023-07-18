#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

void Transformer::transformMacro(Expression::PseudoVariable* p_node, Macro* macro) {
    auto args = p_node->getArgs();
    auto macroName = p_node->getIdentifier();
    auto backup = ctx->currentMacroInstance;
    ctx->currentMacroInstance = new MacroInstance(macro, ctx->module);
    if (args.size() != macro->getArgs().size()) {
        E<PSEUDO_ERROR>(p_node, FMT("Macro '%s' expects %d arguments, but %d were given!",
                                    macroName.c_str(), macro->getArgs().size(), args.size()));
    }
    // Typecheck macros:
    int i = 0;
    for (auto arg : args) {
        auto name = macro->getArgs()[i].first;
        Macro::ArguementType argType = macro->getArgs()[i].second;
        Macro::ArguementType deducedArgType;
        if (utils::cast<Expression::Base>(arg)) {
            if (utils::cast<Expression::ConstantValue>(arg)) {
                deducedArgType = Macro::ArguementType::CONSTANT;
            } else {
                deducedArgType = Macro::ArguementType::EXPRESSION;
            }
        } else if (utils::cast<Statement::Base>(arg)) {
            deducedArgType = Macro::ArguementType::STATEMENT;
        } else {
            E<PSEUDO_ERROR>(p_node, FMT("Unknown arguement type for macro '%s'!", macroName.c_str()));
        }
        if (argType != deducedArgType) {
            E<PSEUDO_ERROR>(p_node, FMT("Macro '%s' expects arguement '%s' to be of type '%s', but '%s' was given!",
                                        macroName.c_str(), name.c_str(), Macro::arguementTypeToString(argType).c_str(),
                                        Macro::arguementTypeToString(deducedArgType).c_str()));
        }
        if (ctx->currentMacroInstance->stack.find(name) != ctx->currentMacroInstance->stack.end()) {
            E<PSEUDO_ERROR>(p_node, FMT("Macro '%s' already has an arguement with name '%s'!",
                                        macroName.c_str(), name.c_str()));
        }
        ctx->currentMacroInstance->stack.insert(std::make_pair(name, arg));
        i++;
    }

    for (auto inst : macro->getBody()->getStmts()) {
        trans(inst);
    }
    ctx->currentMacroInstance = backup;
}

} // namespace Syntax
} // namespace snowball
