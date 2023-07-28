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
    //   let mut i = $iter.next()
    //   while $i->is_valid() {
    //       x(i)
    //       $i = $iter.next()
    //   }
    // }

    auto var = p_node->getVar();
    auto expr = p_node->getExpr();
    auto block = p_node->getBlock();
    std::string iterName = "$iter";

    auto iteratorValue = Syntax::N<Syntax::Statement::VariableDecl>(iterName, expr, true);
    Syntax::Expression::FunctionCall* nextCall = nullptr;
    {
        auto ident = Syntax::N<Syntax::Expression::Identifier>(iterName); // base
        auto nextIdent = Syntax::N<Syntax::Expression::Identifier>("next"); // next
        auto index = Syntax::N<Syntax::Expression::Index>(ident, nextIdent); // base.next
        auto call = Syntax::N<Syntax::Expression::FunctionCall>(index, std::vector<Syntax::Expression::Base*>()); // base.next()
        ident->setDBGInfo(expr->getDBGInfo());
        index->setDBGInfo(expr->getDBGInfo());
        nextIdent->setDBGInfo(expr->getDBGInfo());
        call->setDBGInfo(expr->getDBGInfo());
        nextCall = call;
    };

    // Append the incrementation of the iterator
    // i = $iter.next()
    auto iterIdent = Syntax::N<Syntax::Expression::Identifier>(var);
    auto eq = Syntax::N<Syntax::Expression::BinaryOp>(Syntax::Expression::BinaryOp::OpType::EQ);
    eq->left = iterIdent;
    eq->right = nextCall;

    // Append the iterator variable
    // let mut i = $iter.next()
    auto iterVar = Syntax::N<Syntax::Statement::VariableDecl>(var, nextCall, true);
    auto validIdent = Syntax::N<Syntax::Expression::Identifier>("is_valid");
    auto validIndex = Syntax::N<Syntax::Expression::Index>(iterIdent, validIdent);
    auto validCall = Syntax::N<Syntax::Expression::FunctionCall>(
        validIndex,
        std::vector<Syntax::Expression::Base*>()
    );
    // while $i->valid() { ... }
    auto stmts = block->getStmts();
    stmts.push_back(eq);
    auto whileLoop = Syntax::N<Syntax::Statement::WhileLoop>(
        validCall,
        Syntax::N<Syntax::Block>(stmts)
    );

    // wrap everything in a block
    auto blockStmt = Syntax::N<Syntax::Block>(std::vector<Node*>{
        iteratorValue,
        iterVar, 
        whileLoop
    });
    // Mutate dbg info incase there's an error
    blockStmt->setDBGInfo(expr->getDBGInfo());
    validCall->setDBGInfo(expr->getDBGInfo());
    whileLoop->setDBGInfo(expr->getDBGInfo());
    iterVar->setDBGInfo(expr->getDBGInfo());
    eq->setDBGInfo(expr->getDBGInfo());
    iterIdent->setDBGInfo(expr->getDBGInfo());
    iteratorValue->setDBGInfo(expr->getDBGInfo());

    // transform the block
    trans(blockStmt);
}

} // namespace Syntax
} // namespace snowball