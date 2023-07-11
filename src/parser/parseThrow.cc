
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "../services/OperatorService.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

Syntax::Statement::Raise* Parser::parseThrow() {
    assert(is<TokenType::KWORD_THROW>());
    auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
    auto expr = parseExpr(false);
    next();
    auto raise = Syntax::N<Syntax::Statement::Raise>(expr);
    raise->setDBGInfo(dbg);
    return raise;
}

} // namespace snowball::parser
