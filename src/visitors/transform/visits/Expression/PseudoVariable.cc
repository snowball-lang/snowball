#include "../../../../ir/values/Cast.h"
#include "../../../Transformer.h"

#include <filesystem>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;
namespace fs = std::filesystem;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::PseudoVariable) {
  std::string stringValue;
  int intValue = -1;
  std::string pseudo = p_node->getIdentifier();

  if (pseudo == "FUNCTION") {
    if (auto x = ctx->getCurrentFunction()) {
      stringValue = x->getNiceName();
    } else {
      E<PSEUDO_ERROR>(p_node, "Cant use @FN pseudo variable outside a function!");
    }
  } else if (pseudo == "MANGLED_FN") {
    if (auto x = ctx->getCurrentFunction()) {
      stringValue = x->getMangle();
    } else {
      E<PSEUDO_ERROR>(
              p_node,
              "Cant use @MANGLED_FN pseudo variable outside "
              "a function!"
      );
    }
  } else if (pseudo == "MODULE") {
    stringValue = ctx->module->getName();
  } else if (pseudo == "CLASS") {
    if (auto x = ctx->getCurrentClass()) {
      stringValue = x->getPrettyName();
    } else {
      E<PSEUDO_ERROR>(p_node, "Cant use @CLASS pseudo variable outside a class!");
    }
  } else if (pseudo == "FILE") {
    stringValue = getSourceInfo()->getPath();
  } else if (pseudo == "LINE_STR") {
    stringValue = std::to_string(p_node->getDBGInfo()->pos.first + 1);
  } else if (pseudo == "LINE") {
    intValue = p_node->getDBGInfo()->pos.first + 1;
  } else if (pseudo == "FILE_LINE") {
    stringValue = getSourceInfo()->getPath() + ":" + std::to_string(p_node->getDBGInfo()->pos.first);
  } else if (pseudo == "COLUMN_STR") {
    stringValue = std::to_string(p_node->getDBGInfo()->pos.second);
  } else if (pseudo == "COLUMN") {
    intValue = p_node->getDBGInfo()->pos.second;
  } else if (pseudo == "SN_VERSION") {
    stringValue = _SNOWBALL_VERSION;
  } else if (pseudo == "DATE") {
    auto date = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(date);
    char buffer[12]; // __DATE__ format requires 12 characters (including null terminator)
    std::strftime(buffer, sizeof(buffer), "%b %d %Y", std::localtime(&time));
    stringValue = buffer;
  } else if (pseudo == "SN_FOLDER") {
    stringValue = fs::path(get_exe_folder()).remove_filename();
  } else {
    if (auto parent = ctx->getCurrentMacro()) {
      auto arg = parent->stack.find(pseudo);
      if (arg != parent->stack.end()) {
        auto backup = parent;
        auto [node, type] = (*arg).second;
        if (node->parentMacro != nullptr) ctx->macroBacktrace.push_back({p_node->getDBGInfo(), node->parentMacro});
        if (!p_node->asStatement && type == Macro::ArguementType::STATEMENT) {
          E<PSEUDO_ERROR>(
                  p_node,
                  FMT("Macro arguement '%s' is not an expression!", pseudo.c_str()),
                  {.info = "Trying to use a statement macro as an expression macro.",
                   .note = "You can't use a statement macro as an expression macro.\n"
                           "You can use the macro as a statement instead.",
                   .help = "Try using the macro as a statement instead or declare the\n"
                           "macro as an expression macro.",
                   .tail =
                           EI<>(node->getDBGInfo(),
                                "",
                                {
                                        .info = "Macro arguement declaration here.",
                                })}
          );
        }
        if (utils::is<Expression::TypeRef>(node)) {
          E<SYNTAX_ERROR>(
                  p_node,
                  FMT("Macro arguement '%s' is a type!", pseudo.c_str()),
                  {.info = "Trying to use a type as an expression macro.",
                   .note = "You can't use a type as an expression macro.\n"
                           "You can use the type as a type instead.",
                   .help = "Try using the type as a type instead or declare the\n"
                           "macro as an expression macro.",
                   .tail =
                           EI<>(node->getDBGInfo(),
                                "",
                                {
                                        .info = "Macro arguement declaration here.",
                                })}
          );
        }
        trans(node);
        if (node->parentMacro != nullptr) ctx->macroBacktrace.pop_back();
        return;
      }
    }

    if (auto [item, found] = ctx->getItem(pseudo); found) {
      auto macroInstance = item->getMacro();
      auto macro = macroInstance->macro;
      if (!p_node->asStatement && macro->isMacroStatement()) {
        E<PSEUDO_ERROR>(
                p_node,
                FMT("Macro '%s' is not an expression!", pseudo.c_str()),
                {.info = "Trying to use a statement macro as an expression macro.",
                 .note = "You can't use a statement macro as an expression macro.\n"
                         "You can use the macro as a statement instead.",
                 .help = "Try using the macro as a statement instead or declare the\n"
                         "macro as an expression macro.",
                 .tail =
                         EI<>(macro->getDBGInfo(),
                              "",
                              {
                                      .info = "Macro declaration here.",
                              })}
        );
      }
      transformMacro(p_node, macroInstance);
      return;
    }

    E<PSEUDO_ERROR>(p_node, FMT("Pseudo variable with name '%s' hasn't been found!", pseudo.c_str()));
  }

  if (stringValue.empty()) {
    assert(intValue != -1);
    auto val = new Syntax::Expression::ConstantValue(
            Expression::ConstantValue::ConstantType::Number, std::to_string(intValue)
    );
    val->setDBGInfo(p_node->getDBGInfo());
    trans(val);
  } else {
    // We add " to both sides because the generator removes them and we
    // prevent the values
    //  from being lost.
    auto val = new Syntax::Expression::ConstantValue(
            Expression::ConstantValue::ConstantType::String, "\"" + stringValue + "\""
    );
    val->setDBGInfo(p_node->getDBGInfo());
    trans(val);
  }
}

} // namespace Syntax
} // namespace snowball