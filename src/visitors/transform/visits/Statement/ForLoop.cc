#include "../../../../ir/values/WhileLoop.h"
#include "../../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::ForLoop) {
  // How we transform a for loop:
  // example:
  // for i : 0..10 {
  //     x(i)
  // }
  //
  // Would be translated to:
  // {
  //   let mut $iter = 0..10
  //   let mut $iter_value = $iter.next()
  //   while $iter_value.is_valid() {
  //       let i = $iter_value.value();
  //       x(i);
  //       $iter_value = $iter.next();
  //   }
  //   $iter.reset();
  // }

  auto var = p_node->getVar();
  auto expr = p_node->getExpr();
  auto block = p_node->getBlock();
  std::string iterName = "$iter";
  std::string iterValName = "$iter_value";

  auto iteratorValue = Syntax::N<Syntax::Statement::VariableDecl>(iterName, expr, true);
  Syntax::Expression::FunctionCall* nextCall = nullptr;
  {
    auto ident = Syntax::N<Syntax::Expression::Identifier>(iterName);    // base
    auto nextIdent = Syntax::N<Syntax::Expression::Identifier>("next");  // next
    auto index = Syntax::N<Syntax::Expression::Index>(ident, nextIdent); // base.next
    auto call =
            Syntax::N<Syntax::Expression::FunctionCall>(index, std::vector<Syntax::Expression::Base*>()); // base.next()
    ident->setDBGInfo(expr->getDBGInfo());
    index->setDBGInfo(expr->getDBGInfo());
    nextIdent->setDBGInfo(expr->getDBGInfo());
    call->setDBGInfo(expr->getDBGInfo());
    nextCall = call;
  };

  // Append the incrementation of the iterator
  // i = $iter.next()
  auto iterIdent = Syntax::N<Syntax::Expression::Identifier>(iterValName);
  auto eq = Syntax::N<Syntax::Expression::BinaryOp>(Syntax::Expression::BinaryOp::OpType::EQ);
  eq->left = iterIdent;
  eq->right = nextCall;

  // Append the iterator variable
  // let mut i = $iter.next()
  auto iterVar = Syntax::N<Syntax::Statement::VariableDecl>(iterValName, nextCall, true);
  auto validIdent = Syntax::N<Syntax::Expression::Identifier>("is_valid");
  auto validIndex = Syntax::N<Syntax::Expression::Index>(iterIdent, validIdent);
  auto validCall = Syntax::N<Syntax::Expression::FunctionCall>(validIndex, std::vector<Syntax::Expression::Base*>());
  // while $i->valid() { ... }
  auto valIdent = Syntax::N<Syntax::Expression::Identifier>("value");
  auto iterValueIdx = Syntax::N<Syntax::Expression::Index>(iterIdent, valIdent);
  auto iterValueCall =
          Syntax::N<Syntax::Expression::FunctionCall>(iterValueIdx, std::vector<Syntax::Expression::Base*>());
  auto iterValue = Syntax::N<Syntax::Statement::VariableDecl>(var, iterValueCall);
  auto stmts = block->getStmts();
  stmts.insert(stmts.begin(), iterValue);
  stmts.push_back(eq);
  auto whileLoop = Syntax::N<Syntax::Statement::WhileLoop>(validCall, Syntax::N<Syntax::Block>(stmts));
  auto resetIdent = Syntax::N<Syntax::Expression::Identifier>("reset");
  auto resetIndex =
          Syntax::N<Syntax::Expression::Index>(Syntax::N<Syntax::Expression::Identifier>(iterName), resetIdent);
  auto resetCall = Syntax::N<Syntax::Expression::FunctionCall>(resetIndex, std::vector<Syntax::Expression::Base*>());

  // wrap everything in a block
  auto blockStmt = Syntax::N<Syntax::Block>(std::vector<Node*>{iteratorValue, iterVar, whileLoop, resetCall});
  // Mutate dbg info incase there's an error
  // ik... it's ugly :[ but it works
  blockStmt->setDBGInfo(expr->getDBGInfo());
  resetIdent->setDBGInfo(expr->getDBGInfo());
  resetIndex->setDBGInfo(expr->getDBGInfo());
  resetCall->setDBGInfo(expr->getDBGInfo());
  validCall->setDBGInfo(expr->getDBGInfo());
  whileLoop->setDBGInfo(expr->getDBGInfo());
  iterVar->setDBGInfo(expr->getDBGInfo());
  eq->setDBGInfo(expr->getDBGInfo());
  iterIdent->setDBGInfo(expr->getDBGInfo());
  iteratorValue->setDBGInfo(expr->getDBGInfo());
  nextCall->setDBGInfo(expr->getDBGInfo());
  iterValue->setDBGInfo(expr->getDBGInfo());
  iterValueCall->setDBGInfo(expr->getDBGInfo());
  iterValueIdx->setDBGInfo(expr->getDBGInfo());
  valIdent->setDBGInfo(expr->getDBGInfo());

  // transform the block
  trans(blockStmt);
}

} // namespace Syntax
} // namespace snowball