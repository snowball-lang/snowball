

#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Statement;

namespace snowball::parser {

WhileLoop *Parser::parseWhile() {
    assert(is<TokenType::KWORD_WHILE>());
    auto token = m_current;

    auto expr = parseExpr(false);
    auto block = parseBlock(); prev();

    auto v = Syntax::N<Syntax::Statement::WhileLoop>(expr, block);
    auto info = DBGSourceInfo::fromToken(m_source_info, token);
    v->setDBGInfo(info);
    return v;
}

} // namespace snowball::parser