

#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Statement;

namespace snowball::parser {

WhileLoop* Parser::parseWhile() {
    assert(is<TokenType::KWORD_WHILE>() || is<TokenType::KWORD_DO>());
    auto token = m_current;

    bool isDoWhile = is<TokenType::KWORD_DO>(token);
    Syntax::Expression::Base* expr = nullptr;
    Syntax::Block* block = nullptr;

    if (!isDoWhile) {
        expr = parseExpr(false);
        next();
        block = parseBlock();
    } else {
        next();
        block = parseBlock();
        next();

        assert_tok<TokenType::KWORD_WHILE>("'while'");
        expr = parseExpr(false);
        next();

        assert_tok<TokenType::SYM_SEMI_COLLON>("';'");
    }

    auto v = Syntax::N<Syntax::Statement::WhileLoop>(expr, block, isDoWhile);
    auto info = DBGSourceInfo::fromToken(m_source_info, token);
    v->setDBGInfo(info);
    return v;
}

} // namespace snowball::parser