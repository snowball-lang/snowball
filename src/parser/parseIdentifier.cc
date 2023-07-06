#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Expression;

namespace snowball::parser {

Syntax::Expression::Identifier* Parser::parseIdentifier(bool isKnownType, bool allowGenerics) {
    assert(is<TokenType::IDENTIFIER>());
    auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
    auto genericContainsQuestion = is<TokenType::SYM_QUESTION>(peek(1, true));
    if (allowGenerics &&
        (is<TokenType::OP_LT>(peek()) && (isKnownType || genericContainsQuestion))) {
        if (genericContainsQuestion && isKnownType)
            createError<SYNTAX_ERROR>("Expected a valid generic expression but got '?'",
                                      {.info = "Not a valid generic expression"});

        auto name = m_current.to_string();
        next();
        auto generics = parseGenericExpr();
        auto width = m_current.get_pos().second - dbg->pos.second;

        dbg->width = width;
        prev();

        auto i = Syntax::N<Syntax::Expression::GenericIdentifier>(name, generics);
        i->setDBGInfo(dbg);
        return i;
    } else {
        auto i = Syntax::N<Syntax::Expression::Identifier>(m_current.to_string());
        i->setDBGInfo(dbg);
        return i;
    }
}

} // namespace snowball::parser