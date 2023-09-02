#include "../../../../services/OperatorService.h"
#include "../../../Transformer.h"

#include <cstring>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

#define IS_PUBLIC (p_node->getPrivacy() == Statement::Privacy::PUBLIC)
#define IS_MAIN   (name == "main" && ctx->module->isMain())

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::FunctionDef) {
  auto name = p_node->getName();
  if (p_node->hasAttribute(Attributes::TEST) && p_node->hasAttribute(Attributes::BENCH)) {
    E<SYNTAX_ERROR>(p_node, "Function cannot be both a test and a benchmark!");
  }

  if (p_node->hasAttribute(Attributes::TEST) && (!ctx->testMode || !ctx->isMainModule)) return;
  if (p_node->hasAttribute(Attributes::BENCH) && (!ctx->benchMode || !ctx->isMainModule))
    return;
  else if (p_node->hasAttribute(Attributes::TEST)) {
    p_node->addAttribute(Attributes::ALLOW_FOR_TEST);
  } else if (p_node->hasAttribute(Attributes::BENCH)) {
    p_node->addAttribute(Attributes::ALLOW_FOR_BENCH);
  }

  p_node = p_node->copy();
  if (auto c = ctx->getCurrentClass(true); c != nullptr && !p_node->hasAttribute(Attributes::FIRST_ARG_IS_SELF)) {
    auto args = p_node->getArgs();
    auto pointer = (p_node->hasAttribute(Attributes::NO_POINTER_SELF)) ? c->copy() : c->getReferenceTo();
    pointer->setMutable(p_node->isMutable() || p_node->isConstructor());
    if (!(args.size() > 0 && args.at(0)->getName() == "self") && !p_node->isStatic()) {
      auto self = new Expression::Param("self", pointer->toRef());
      args.insert(args.begin(), self);
      p_node->setArgs(args);
    } else if (!p_node->isStatic()) { /* "self" already set by another class */
      args.at(0)->setType(pointer->toRef());
    }
  } else if (p_node->hasAttribute(Attributes::FIRST_ARG_IS_SELF)) {
    const auto& args = p_node->getArgs();
    if (args.size() < 1) {
      E<SYNTAX_ERROR>(p_node, "Function with 'first_arg_is_self' attribute must have at least one argument!");
    } else if (args.at(0)->getName() != "self") {
      E<SYNTAX_ERROR>(p_node, "First argument of function with 'first_arg_is_self' attribute must be named 'self'!");
    }
  }

  if (!ctx->generateFunction && !(IS_MAIN)) {
    // assert(!services::OperatorService::isOperator(name));
    //  Check if the function requirements match the main function
    auto uuid = ctx->createIdentifierName(name);
    // TODO: check for already existing functions (for no mangled versions)
    if (p_node->hasAttribute(Attributes::NO_MANGLE) || p_node->hasAttribute(Attributes::EXPORT) || p_node->isExtern()) {
      auto hasExportName = p_node->hasAttribute(Attributes::EXPORT);
      auto exportName = p_node->getAttributeArgs(Attributes::EXPORT).find("name");
      if (exportName != p_node->getAttributeArgs(Attributes::EXPORT).end()) { name = exportName->second; }

      if (std::find(ctx->exported.begin(), ctx->exported.end(), name) != ctx->exported.end()) {
        E<VARIABLE_ERROR>(p_node->getDBGInfo(), "Unmangled export already exists!",
                {.info = "This function name is already exported as unmangled.",
                        .note = "This symbols is exported on another location with the "
                                "'no_mangle' or 'export' attribute.",
                        .help = "Try renaming the function or removing the 'no_mangle' "
                                "or the 'export' "
                                "attribute. If you want \n"
                                "to export the function as unmangled, remove the "
                                "mangled version of the function."});
      } else {
        ctx->exported.push_back(name);
      }
    }
    ctx->cache->setFunction(uuid, p_node, ctx->saveState());
    return;
  }

  if (ctx->generateFunction && IS_MAIN) {
    if (!IS_PUBLIC) E<SYNTAX_ERROR>(p_node, "Program entry point must be public!");
    transformMainFunction(p_node);
    return;
  }

  if (ctx->generateFunction && !p_node->isGeneric()) transformFunction({p_node, ctx->saveState()}, {});
}

} // namespace Syntax
} // namespace snowball
