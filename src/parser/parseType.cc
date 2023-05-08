

#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Expression;

namespace snowball::parser {

TypeRef *Parser::parseType() {
    throwIfNotType();
    assert(is<TokenType::IDENTIFIER>() || is<TokenType::KWORD_DECLTYPE>());
    auto pos = m_current.get_pos();

    if (is<TokenType::KWORD_DECLTYPE>()) {
        auto w = m_current.get_width();

        next();
        assert_tok<TokenType::BRACKET_LPARENT>("'('");

        auto expr = parseExpr();
        next();

        consume<TokenType::BRACKET_RPARENT>("')'");


        auto dbg = new DBGSourceInfo(m_source_info, pos, w);
        return Syntax::N<DeclType>(expr, dbg);
    }

    auto name = assert_tok<TokenType::IDENTIFIER>("a valid type").to_string();

    next();
    while (is<TokenType::SYM_COLCOL>()) {
        next();
        name += "::" + assert_tok<TokenType::IDENTIFIER>("a valid type").to_string();
        next();
    }

    std::vector<TypeRef *> tparams;

    // lookup for "<?"
    if (is<TokenType::SYM_QUESTION>(peek()) && is<TokenType::OP_LT>()) {
        tparams = parseGenericExpr();
    }

    auto dbg = new DBGSourceInfo(m_source_info, pos,
                                 m_current.get_pos().second - pos.second - 1);
    return Syntax::TR(name, dbg, tparams);
}

} // namespace snowball::parser