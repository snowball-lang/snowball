
#include "../ast/types/PrimitiveTypes.h"
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Statement;
namespace snowball::parser {

Syntax::Statement::Return* Parser::parseReturn() {
  assert(is<TokenType::KWORD_RETURN>());
  auto info = DBGSourceInfo::fromToken(m_source_info, m_current);
  Syntax::Expression::Base* expr = nullptr;
  if (!is<TokenType::SYM_SEMI_COLLON>(peek())) expr = parseExpr(false);
  auto node = Syntax::N<Return>(expr);
  node->setDBGInfo(info);
  return node;
}
} // namespace snowball::parser
