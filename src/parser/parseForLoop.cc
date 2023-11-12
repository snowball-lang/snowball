
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "../services/OperatorService.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

Syntax::Node* Parser::parseForLoop() {
  assert(is<TokenType::KWORD_FOR>());
  auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
  next(); // Eat "for"

  if (is<TokenType::IDENTIFIER>()) {
    auto var = m_current.to_string();
    next();
    if (is<TokenType::IDENTIFIER>() && m_current.to_string() == "in") {
      auto expr = parseExpr();
      next();
      bool backupLoop = m_inside_loop;
      m_inside_loop = true;
      assert_tok<TokenType::BRACKET_LCURLY>("'{'");
      auto body = parseBlock();
      m_inside_loop = backupLoop;
      auto loop = Syntax::N<Syntax::Statement::ForLoop>(var, expr, body);
      loop->setDBGInfo(dbg);
      return loop;
    }

    prev();
  }
  prev();
  std::vector<Syntax::Node*>(block);

  Syntax::Expression::Base* condExpr = nullptr;
  Syntax::Node* step = nullptr;

  // C-style for loop
  if (!is<TokenType::SYM_SEMI_COLLON>(peek())) {
    auto init = parseStatement(peek());
    assert_tok<TokenType::SYM_SEMI_COLLON>("';'");
    block.push_back(init);
  } else next();

  if (!is<TokenType::SYM_SEMI_COLLON>(peek())) {
    condExpr = parseExpr(false);
    next();
    assert_tok<TokenType::SYM_SEMI_COLLON>("';'");
  } else next();
  
  if (!is<TokenType::BRACKET_LCURLY>(peek())) {
    step = parseExpr();
  }

  next();
  bool backupLoop = m_inside_loop;
  m_inside_loop = true;
  assert_tok<TokenType::BRACKET_LCURLY>("'{'");
  auto body = parseBlock();
  m_inside_loop = backupLoop;

  // Convert it into a simple while loop with a parent block
  if (!condExpr)
    condExpr = Syntax::N<Syntax::Expression::ConstantValue>(Syntax::Expression::ConstantValue::Bool, "true");
  auto whileLoop = Syntax::N<Syntax::Statement::WhileLoop>(condExpr, body, step);
  block.push_back(whileLoop);
  auto loopBlock = Syntax::N<Syntax::Block>(block);
  loopBlock->setDBGInfo(dbg);

  return loopBlock;
}

} // namespace snowball::parser
