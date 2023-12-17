#include "../../Transformer.h"
#include <fstream>

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
    E<PSEUDO_ERROR>(
            p_node,
            FMT("Macro '%s' expects at least %d arguments, but %d were given!",
                macroName.c_str(),
                numRequiredArgs,
                args.size())
    );
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
    if (utils::is<Expression::Base>(arg)) {
      if (auto x = utils::cast<Expression::ConstantValue>(arg)) {
        deducedArgType = Macro::ArguementType::CONSTANT;
        auto ty = x->getType();
        if (argType != Macro::ArguementType::CONSTANT) { // A more specific version of it
          if (ty == Expression::ConstantValue::ConstantType::String) {
            deducedArgType = Macro::ArguementType::CONSTANT_STRING;
          } else if (ty == Expression::ConstantValue::ConstantType::Number || ty == Expression::ConstantValue::ConstantType::Float || ty == Expression::ConstantValue::ConstantType::Bool) {
            deducedArgType = Macro::ArguementType::CONSTANT_NUMBER;
          } else if (ty == Expression::ConstantValue::ConstantType::Char) {
            deducedArgType = Macro::ArguementType::CONSTANT_CHAR;
          }
        }
        if (argType == Macro::ArguementType::EXPRESSION) {
          deducedArgType = Macro::ArguementType::EXPRESSION;
        }
      } else if (utils::is<Expression::TypeRef>(arg)) {
        deducedArgType = Macro::ArguementType::TYPE;
      } else {
        deducedArgType = Macro::ArguementType::EXPRESSION;
      }
    } else if (utils::is<Statement::Base>(arg)) {
      deducedArgType = Macro::ArguementType::STATEMENT;
    } else if (auto x = utils::cast<Macro>(arg)) {
      deducedArgType = x->isMacroStatement() ? Macro::ArguementType::STATEMENT : Macro::ArguementType::EXPRESSION;
    } else {
      E<PSEUDO_ERROR>(p_node, FMT("Unknown arguement type for macro '%s'!", macroName.c_str()));
    }
    if (argType != deducedArgType) {
      E<PSEUDO_ERROR>(
              p_node,
              FMT("Macro '%s' expects arguement '%s' to be of type '%s', but '%s' was given!",
                  macroName.c_str(),
                  name.c_str(),
                  Macro::arguementTypeToString(argType).c_str(),
                  Macro::arguementTypeToString(deducedArgType).c_str())
      );
    }
    if (macroInstance->stack.find(name) != macroInstance->stack.end()) {
      E<PSEUDO_ERROR>(
              p_node, FMT("Macro '%s' already has an arguement with name '%s'!", macroName.c_str(), name.c_str())
      );
    }
    arg->parentMacro = ctx->getCurrentMacro();
    macroInstance->stack.insert(std::make_pair(name, std::make_pair(arg, deducedArgType)));
  }
  ctx->macroDepth++;
  if (ctx->macroDepth > SN_MAX_MACRO_DEPTH) {
    E<PSEUDO_ERROR>(
            p_node,
            FMT("Macro '%s' has exceeded the maximum macro depth of '%i'!", macroName.c_str(), SN_MAX_MACRO_DEPTH)
    );
  }
  if (macroName == "pkg") {
    if (ctx->getCurrentMacro() == nullptr) {
      E<PSEUDO_ERROR>(
              p_node,
              "Cant use 'pkg' macro outside a parent macro!",
              {.info = "This is the macro that was used",
               .note = "This special macro is only available inside a parent macro.",
               .help = "Try using the macro inside a parent macro."}
      );
    }
    auto expr = args.at(0);
    auto backupModule = ctx->module;
    ctx->module = ctx->getCurrentMacro()->module;
    trans(expr);
    ctx->module = backupModule;
  } else if (macroName == "zero_initialized") {
    auto type = utils::cast<Expression::TypeRef>(args.at(0));
    auto tr = transformType(type);
    this->value = getBuilder().createZeroInitialized(p_node->getDBGInfo(), tr);
  } else if (macroName == "sizeof") {
    auto type = utils::cast<Expression::TypeRef>(args.at(0));
    auto tr = transformType(type);
    this->value = getBuilder().createNumberValue(p_node->getDBGInfo(), tr->sizeOf());
    this->value->setDBGInfo(p_node->getDBGInfo());
    this->value->setType(ctx->getInt32Type());
  } else if (macroName == "alignof") {
    auto type = utils::cast<Expression::TypeRef>(args.at(0));
    auto tr = transformType(type);
    this->value = getBuilder().createNumberValue(p_node->getDBGInfo(), tr->alignmentOf());
    this->value->setDBGInfo(p_node->getDBGInfo());
    this->value->setType(ctx->getInt32Type());
  } else if (macroName == "include_str") {
    auto str = utils::cast<Expression::ConstantValue>(args.at(0));
    auto filename = str->getValue();
    // remove the quotes from the string
    filename = filename.substr(1, filename.size() - 2);
    std::ifstream myfile; 
    myfile.open(filename);
    if (!myfile.is_open()) {
      E<PSEUDO_ERROR>(p_node, FMT("Could not find file '%s'!", filename.c_str()), {
        .info = "This is the file that was tried to be included",
        .note = "cwd: '" + std::filesystem::current_path().string() + "'",
      });
    }
    std::string strValue((std::istreambuf_iterator<char>(myfile)), std::istreambuf_iterator<char>());

    auto stringNode = N<Expression::ConstantValue>(Expression::ConstantValue::String, "\"" + strValue + "\"");
    stringNode->setDBGInfo(p_node->getDBGInfo());
    this->value = trans(stringNode);
  } else if (macroName == "env") {
    auto str = utils::cast<Expression::ConstantValue>(args.at(0));
    auto envName = str->getValue();
    // remove the quotes from the string
    envName = envName.substr(1, envName.size() - 2);
    auto envValue = std::getenv(envName.c_str());
    if (envValue == nullptr) {
      E<PSEUDO_ERROR>(p_node, FMT("Could not find environment variable '%s'!", envName.c_str()), {
        .info = "This is the environment variable that was tried to be accessed",
      });
    }
    auto stringNode = N<Expression::ConstantValue>(Expression::ConstantValue::String, "\"" + std::string(envValue) + "\"");
    stringNode->setDBGInfo(p_node->getDBGInfo());
    this->value = trans(stringNode);
  } else {
    ctx->macroBacktrace.push_back({p_node->getDBGInfo(), macroInstance});
    for (auto inst : macro->getBody()->getStmts()) { trans(inst); }
    ctx->macroBacktrace.pop_back();
  }
  ctx->macroDepth--;
  macroInstance->stack.clear();
}

} // namespace Syntax
} // namespace snowball
