#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

Syntax::Block* Parser::parseBlockOrStmt() {
  if (is<TokenType::BRACKET_LCURLY>(peek())) {
    next();
    return parseBlock();
  } else {
    auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
    auto tk = peek();
    auto expr = parseStatement(tk);
    auto block = Syntax::N<Syntax::Block>(std::vector<Syntax::Node*> {expr});
    block->setDBGInfo(dbg);
    return block;
  }
}

} // namespace snowball::parser