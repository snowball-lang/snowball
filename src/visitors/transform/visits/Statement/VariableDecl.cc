#include "../../../../ir/values/Cast.h"
#include "../../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::VariableDecl) {
  auto definedType = p_node->getDefinedType() == nullptr ?
                     nullptr :
                     transformSizedType(p_node->getDefinedType(), false, "Cannot declare variable with unsized type '%s'");
  auto variableName = p_node->getName();
  auto variableValue = p_node->getValue();
  auto isMutable = p_node->isMutable();
  assert(p_node->isInitialized() || definedType != nullptr);
  if (definedType) {
    // definedType = utils::copy_shared(definedType);
    definedType->setMutable(isMutable);
  }
  if (p_node->isExternDecl()) {
    if (std::find(ctx->exported.begin(), ctx->exported.end(), p_node->getName()) != ctx->exported.end()) {
      E<VARIABLE_ERROR>(
      p_node->getDBGInfo(),
      "External symbol already exists!", {
        .info = "This function name is already exported as unmangled.",
        .note = "This symbols is exported on another location with the "
        "'external' attribute.",
        .help = "Try renaming the variable or removing the 'external' "
        "attribute."
      }
      );
    } else {
      ctx->exported.push_back(p_node->getName());
    }
  }
  if (ctx->getInScope(variableName, ctx->currentScope()).second) {
    E<VARIABLE_ERROR>(
    p_node,
    FMT("Variable with name '%s' is already "
        "defined in the current scope!",
        variableName.c_str())
    );
  }
  auto var = getBuilder().createVariable(p_node->getDBGInfo(), variableName, false, isMutable, ctx->getScopeIndex());
  auto item = std::make_shared<transform::Item>(transform::Item::Type::VALUE, var);
  // TODO: it should always be declared
  if (p_node->isInitialized()) {
    auto val = trans(variableValue);
    auto varDecl = getBuilder().createVariableDeclaration(p_node->getDBGInfo(), var, val, p_node->isExternDecl());
    varDecl->setId(var->getId());
    getBuilder().setType(varDecl, val->getType());
    if (auto f = ctx->getCurrentFunction().get()) {
      f->addSymbol(varDecl);
    } else if (!ctx->getCurrentClass()) {
      ctx->module->addVariable(varDecl);
    }
    if (definedType) {
      if (!definedType->is(val->getType())) {
        if (auto v = tryCast(val, definedType); v != nullptr) {
          this->value = v;
        } else {
          E<VARIABLE_ERROR>(
          p_node,
          FMT("Cant assign value with type '%s' to "
              "the variable with type '%s'!",
              val->getType()->getPrettyName().c_str(),
              definedType->getPrettyName().c_str())
          );
        }
      }
    }
    auto ty = val->getType()->copy();
    ty->setMutable(isMutable);
    var->setType(ty);
    this->value = varDecl;
  } else {
    auto varDecl = getBuilder().createVariableDeclaration(p_node->getDBGInfo(), var, nullptr, p_node->isExternDecl());
    varDecl->setId(var->getId());
    getBuilder().setType(varDecl, definedType);
    if (auto f = ctx->getCurrentFunction().get()) {
      f->addSymbol(varDecl);
    } else if (!ctx->getCurrentClass()) {
      ctx->module->addVariable(varDecl);
    }
    getBuilder().setType(var, definedType);
    this->value = var;
  }
  ctx->addItem(variableName, item);
}

} // namespace Syntax
} // namespace snowball