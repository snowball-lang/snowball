#include "../../../Transformer.h"

#include <optional>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::BinaryOp) {
  auto opType = p_node->op_type;

  if (p_node->unary) {
    if (opType == Expression::BinaryOp::OpType::REFERENCE) {
      auto value = trans(p_node->left);
      auto ref = builder.createReferenceTo(p_node->getDBGInfo(), value);
      this->value = ref;
      return;
    } else if (opType == Expression::BinaryOp::OpType::DEREFERENCE) {
      auto value = trans(p_node->left);
      auto type = value->getType();
      if (auto x = utils::cast<types::ReferenceType>(type)) {
        type = x->getPointedType();
      } else if (auto x = utils::cast<types::PointerType>(type)) {
        type = x->getPointedType(); // this will error if it's not in unsafe context at the type checker.
      } else {
        E<DEREFERENCE_ERROR>(p_node, "Can't dereference a non-pointer type!");
      }

      auto ref = builder.createDereferenceTo(p_node->getDBGInfo(), value, type);
      this->value = ref;
      return;
    }
  }

  auto left = p_node->left;
  auto right = p_node->right;

  if (opType == Expression::BinaryOp::OpType::RANGE) {
    // TODO: maybe look for the actual core range instead of just "Range"
    auto rangeIdent = Syntax::N<Expression::Identifier>("Range");
    auto rangeType = Syntax::N<Expression::TypeRef>(rangeIdent, "Range", p_node->getDBGInfo(), "Range");
    auto call = Syntax::N<Expression::FunctionCall>(rangeIdent, std::vector<Expression::Base*>{left, right});
    auto init = Syntax::N<Expression::NewInstance>(call, rangeType);
    init->setDBGInfo(p_node->getDBGInfo());
    call->setDBGInfo(p_node->getDBGInfo());
    rangeIdent->setDBGInfo(p_node->getDBGInfo());
    trans(init);
  } else {
    auto ident = Syntax::N<Expression::Identifier>(services::OperatorService::getOperatorMangle(opType));
    auto index = Syntax::N<Expression::Index>(left, ident);
    std::vector<Expression::Base*> args =
            p_node->unary ? std::vector<Expression::Base*>{} : std::vector<Expression::Base*>{right};
    auto call = Syntax::N<Expression::FunctionCall>(index, args);

    call->isInitialization = p_node->isInitialization;

    ident->setDBGInfo(p_node->getDBGInfo());
    call->setDBGInfo(p_node->getDBGInfo());
    index->setDBGInfo(p_node->getDBGInfo());

    auto val = trans(call);
    auto assigmentAsCall = utils::dyn_cast<ir::Call>(val);
    auto assigmentValue = builder.createBinaryOp(assigmentAsCall);
    this->value = assigmentValue;
  }
}

} // namespace Syntax
} // namespace snowball