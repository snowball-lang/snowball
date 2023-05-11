

#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Expression;

namespace snowball::parser {

Syntax::Expression::Identifier* Parser::parseIdentifier() {
    auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
    if (is<TokenType::OP_LT>(peek()) &&
        is<TokenType::SYM_QUESTION>(peek(1, true))) {
        auto name = m_current.to_string();
        next();
        auto generics = parseGenericExpr();
        auto width    = m_current.get_pos().second - dbg->pos.second;

        dbg->width = width;
        prev();

        auto i = Syntax::N<Syntax::Expression::GenericIdentifier>(name,
                                                                    generics);
        i->setDBGInfo(dbg);
        return i;
    } else {
        auto i = Syntax::N<Syntax::Expression::Identifier>(
            m_current.to_string());
        i->setDBGInfo(dbg);
        return i;
    }
}

} // namespace snowball::parser
