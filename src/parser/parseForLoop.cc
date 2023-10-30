
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "../services/OperatorService.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

Syntax::Statement::ForLoop* Parser::parseForLoop() {
  assert(is<TokenType::KWORD_FOR>());
  auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
  next(); // Eat "for"

  auto var = assert_tok<TokenType::IDENTIFIER>("identifier").to_string();
  next();
  auto kword = assert_tok<TokenType::IDENTIFIER>("'in'").to_string();
  if (kword != "in") { createError<SYNTAX_ERROR>("Expected 'in' after for loop variable declaration!"); }
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

} // namespace snowball::parser
