#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

void Transformer::transformMainFunction(Statement::FunctionDef* p_node) {
  assert(ctx->module->isMain());
  assert(p_node->getName() == "main");
  assert(p_node->getPrivacy() == Statement::Privacy::PUBLIC);
  if (std::find(ctx->exported.begin(), ctx->exported.end(), "main") != ctx->exported.end()) {
    E<SYNTAX_ERROR>(p_node, "Multiple main functions have been defined!");
  }
  // Checking for errors
  if (p_node->getArgs().size() > 0) {
    E<SYNTAX_ERROR>(p_node, "Program entry point can't have parameters!");
  } else if (p_node->isExtern()) {
    E<SYNTAX_ERROR>(p_node, "Program entry point can't have and external flag!");
  } else if (p_node->getGenerics().size() > 0) {
    E<SYNTAX_ERROR>(p_node, "Program entry point can't have generics!");
  } else if (cast<Statement::BodiedFunction>(p_node) == nullptr) {
    E<SYNTAX_ERROR>(p_node, "Program entry cant be a declaration!");
  } // TODO: main function cant be variadic!
  auto rawRetTy = p_node->getRetType();
  auto returnType = transformType(rawRetTy); // we asume it's sized
  if (!types::isInt32Type(returnType)) {
    E<SYNTAX_ERROR>(rawRetTy, "Program entry must have 'i32' as return type!");
  }
  if (p_node->getAttributes() > 0) {
    E<SYNTAX_ERROR>(p_node, "Program entry point cant have attributes!");
  }
  // Create a new function value.
  // notes: The name will always be "main" and the function shall not
  // have any arguments.
  auto fn = transformFunction({p_node, ctx->saveState()}, {}, true);
  fn->setExternalName("main");
  ctx->exported.push_back("main");
}

} // namespace Syntax
} // namespace snowball
