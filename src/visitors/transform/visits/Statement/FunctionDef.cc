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

  p_node = p_node->copy(); // TODO: really?
  if (auto c = ctx->getCurrentClass(true); c != nullptr && !p_node->hasAttribute(Attributes::FIRST_ARG_IS_SELF)) {
    auto args = p_node->getArgs();
    auto pointer = (p_node->hasAttribute(Attributes::NO_POINTER_SELF)) ? c->copy() : c->getReferenceTo();
    pointer->setMutable(p_node->isMutable() || p_node->isConstructor());
    if (!(args.size() > 0 && args.at(0)->getName() == "self") && !p_node->isStatic()) {
      auto self = new Expression::Param("self", pointer->toRef());
      args.emplace(args.begin(), self);
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

  if (p_node->isVirtual() && p_node->isGeneric()) {
    E<SYNTAX_ERROR>(p_node, "Virtual functions cannot be generic!", {
      .info = "Virtual functions cannot be generic!",
      .note = "Virtual functions are not allowed to be generic because they\nare "
              "not allowed to be "
              "overloaded. This is because the virtual\nfunction table is "
              "generated at compile time "
              "and\ncannot be changed at runtime.\n\n"
              "read more:\n - 'https://stackoverflow.com/questions/2354210/can-a-class-member-function-template-be-virtual'",
      .help = "Try removing the 'virtual' or the 'generic' attribute."
    });
  }

  auto state = ctx->saveState();
  if (auto newState = p_node->getContextState()) {
    // we just replace module, uuidStack and stack
    // TODO: make sure it's up to date
    auto newStack = newState->stack;
    newStack.push_front(ctx->currentScope());
    state->module = newState->module;
    state->stack = newStack;
    state->uuidStack = newState->uuidStack;
  }

  if (!ctx->generateFunction && !(IS_MAIN)) {
    // assert(!services::OperatorService::isOperator(name));
    //  Check if the function requirements match the main function
    auto uuid = ctx->createIdentifierName(name);
    // TODO: check for already existing functions (for no mangled versions)
    if ((p_node->hasAttribute(Attributes::NO_MANGLE) || p_node->hasAttribute(Attributes::EXPORT) || p_node->isExtern()) && !p_node->hasAttribute(Attributes::INTRINSIC)) {
      if (p_node->isGeneric()) {
        E<SYNTAX_ERROR>(p_node, "Generic functions cannot be exported!", {
          .info = "Generic functions cannot be exported!",
          .note = "Generic functions are not allowed to be exported because they\nare "
                  "not allowed to be "
                  "overloaded. This is because the virtual\nfunction table is "
                  "generated at compile time "
                  "and\ncannot be changed at runtime.\n\n"
                  "read more:\n - 'https://stackoverflow.com/questions/2354210/can-a-class-member-function-template-be-virtual'",
          .help = "Try removing the 'export' or the 'generic' attribute."
        });
      }

      const auto attrArgs = p_node->getAttributeArgs(Attributes::EXPORT);
      auto exportedName = name;
      auto exportName = attrArgs.find("name");
      if (exportName != attrArgs.end()) { exportedName = exportName->second; }

      if (auto e = utils::cast<Statement::ExternFnDef>(p_node); e != nullptr) {
        exportedName = e->getExternalName();
      }

      if (std::find(ctx->exported.begin(), ctx->exported.end(), name) != ctx->exported.end()) {
        E<VARIABLE_ERROR>(
                p_node->getDBGInfo(),
                FMT("Function '%s' is already exported as unmangled!", exportedName.c_str()),
                {.info = "This function name is already exported as unmangled.",
                 .note = "This symbols is exported on another location with the "
                         "'no_mangle' or 'export' attribute.",
                 .help = "Try renaming the function or removing the 'no_mangle' "
                         "or the 'export' "
                         "attribute. If you want \n"
                         "to export the function as unmangled, remove the "
                         "mangled version of the function."}
        );
      } else {
        ctx->exported.push_back(name);
      }
    }
    ctx->cache->setFunction(uuid, p_node, state);
    return;
  }

  if (ctx->generateFunction && IS_MAIN) {
    if (!IS_PUBLIC) E<SYNTAX_ERROR>(p_node, "Program entry point must be public!");
    transformMainFunction(p_node);
    return;
  }

  if (ctx->generateFunction && !p_node->isGeneric()) transformFunction({p_node, state}, {});
}

} // namespace Syntax
} // namespace snowball
