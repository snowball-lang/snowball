#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Macro) {
  // TODO: test this better out
  if (!ctx->generateFunction) return; // noop
  auto macroName = p_node->getName();
  if (ctx->getItem(macroName).second)
    Syntax::E<VARIABLE_ERROR>(p_node, FMT("Macro with name '%s' is already defined!", macroName.c_str()));
  if (!p_node->isMacroStatement()) {
    for (const auto& arg : p_node->getArgs()) {
      if (std::get<1>(arg) == Macro::ArguementType::STATEMENT)
        Syntax::E<SYNTAX_ERROR>(p_node, "Expression macro cannot have statement arguements!");
    }
  }
  auto instance = new MacroInstance(p_node, ctx->module);
  auto item = std::make_shared<Item>(instance);
  // TODO: export to module
  if (p_node->hasAttribute(Attributes::EXPORT)) {
    auto args = p_node->getAttributeArgs(Attributes::EXPORT);
    std::string exportName = macroName;
    if (args.find("as") != args.end()) { exportName = args["as"]; }
    auto& moduleExports = ctx->module->getExportedMacros();
    if (moduleExports.find(macroName) != moduleExports.end())
      Syntax::E<VARIABLE_ERROR>(p_node, FMT("Macro with name '%s' is already exported!", macroName.c_str()));
    ctx->module->addExportedMacro(macroName, instance);
  }
  ctx->addItem(macroName, item);
}

} // namespace Syntax
} // namespace snowball