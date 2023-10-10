#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::pair<std::vector<std::shared_ptr<ir::Value>>, std::shared_ptr<ir::Call>> Transformer::transformConstructor(Statement::ConstructorDef* p_node) {
  auto instrList = std::vector<std::shared_ptr<ir::Value>>();
  auto currentClass = utils::cast<types::DefinedType>(ctx->getCurrentClass());
  std::shared_ptr<ir::Call> superCall = nullptr;
  assert(currentClass && "Current class is not a defined type!");
  if (p_node->hasSuperArgs()) {
    auto [selfArg, foundSelfArg] = ctx->getInCurrentScope("self");
    assert(foundSelfArg);
    auto superArgs = p_node->getSuperArgs();
    auto parentClass = currentClass->getParent();
    auto parentClassRef = parentClass->toRef();
    auto newInstance = Syntax::N<Expression::NewInstance>(p_node->getDBGInfo(), superArgs, parentClassRef);
    newInstance->setDBGInfo(p_node->getDBGInfo());
    superCall = utils::dyn_cast<ir::Call>(trans(newInstance));
    assert(superCall);
    if (auto ptr = utils::dyn_cast<ir::ReferenceTo>(superCall)) {
      utils::dyn_cast<ir::ObjectInitialization>(ptr->getValue())->createdObject = selfArg->getValue();
    } else {
      utils::dyn_cast<ir::ObjectInitialization>(superCall)->createdObject = selfArg->getValue();
    }
  }
  for (auto field : currentClass->getFields()) {
    auto name = field->name;
    auto initializedValue = field->initializedValue;
    if (initializedValue) {
      // TODO: build a cast here to deduced type
      auto selfRef = Syntax::N<Expression::Identifier>("self");
      auto nameIdent = Syntax::N<Expression::Identifier>(name);
      auto indexExpr = Syntax::N<Expression::Index>(selfRef, nameIdent);
      auto assign = Syntax::N<Syntax::Expression::BinaryOp>(OperatorType::EQ);
      assign->left = indexExpr;
      assign->right = initializedValue;
      assign->setDBGInfo(field->getDBGInfo());
      nameIdent->setDBGInfo(field->getDBGInfo());
      selfRef->setDBGInfo(field->getDBGInfo());
      indexExpr->setDBGInfo(field->getDBGInfo());
      auto val = trans(assign);
      auto assigmentAsCall = utils::dyn_cast<ir::Call>(val);
      auto assigmentValue = getBuilder().createBinaryOp(assigmentAsCall);
      assigmentValue->ignoreMutability = true;
      instrList.emplace_back(assigmentValue);
    }
  }
  for (auto [name, arg] : p_node->getInitArgs()) {
    auto selfRef = Syntax::N<Expression::Identifier>("self");
    auto indexExpr = Syntax::N<Expression::Index>(selfRef, name);
    auto assign = Syntax::N<Syntax::Expression::BinaryOp>(OperatorType::EQ);
    assign->left = indexExpr;
    assign->right = arg;
    assign->setDBGInfo(name->getDBGInfo());
    selfRef->setDBGInfo(name->getDBGInfo());
    indexExpr->setDBGInfo(name->getDBGInfo());
    auto val = trans(assign);
    auto assigmentAsCall = utils::dyn_cast<ir::Call>(val);
    auto assigmentValue = getBuilder().createBinaryOp(assigmentAsCall);
    assigmentValue->ignoreMutability = true;
    instrList.emplace_back(assigmentValue);
  }

  return {instrList, superCall};
}

} // namespace Syntax
} // namespace snowball