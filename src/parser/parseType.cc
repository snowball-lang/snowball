

#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Expression;

namespace snowball::parser {

ptr<TypeRef> Parser::parseType() {
    assert(is<TokenType::IDENTIFIER>());
    auto pos = m_current.get_pos();

    auto name = assert_tok<TokenType::IDENTIFIER>("a valid type").to_string();

    next();
    std::vector<ptr<TypeRef>> tparams;

    // lookup for "<?"
    if (is<TokenType::SYM_QUESTION>(peek()) && is<TokenType::OP_LT>()) {
        tparams = parseGenericExpr();
    }

    auto dbg = new DBGSourceInfo(m_source_info, pos,
                                 m_current.get_pos().second - pos.second - 1);
    return Syntax::TR(name, dbg, tparams);
}

} // namespace snowball::parser