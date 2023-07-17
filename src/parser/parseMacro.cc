
#include "Parser.h"

#include <assert.h>

namespace snowball {
namespace parser {

Syntax::Macro* Parser::parseMacro() {
    assert(is<TokenType::KWORD_MACRO>());
    next();
    // TODO: expression macro: 'macro foo() = 1 + 1'
    auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
    auto name = assert_tok<TokenType::IDENTIFIER>("an identifier for macro name").to_string();
    next();
    consume<TokenType::BRACKET_LPARENT>("'('");
    std::vector<std::string> args;
    while (is<TokenType::IDENTIFIER>()) {
        args.push_back(m_current.to_string());
        next();
        consume<TokenType::SYM_COLLON>("':'");
        auto type = assert_tok<TokenType::IDENTIFIER>("an identifier for type").to_string();
        next();
        if (is<TokenType::SYM_COMMA>()) {
            next();
        } else {
            break;
        }
    }
    consume<TokenType::BRACKET_RPARENT>("')'");
    assert_tok<TokenType::BRACKET_LCURLY>("'{'");
    auto body = parseBlock();
    auto macro = Syntax::N<Syntax::Macro>(name, args, body);
    auto width = m_current.get_pos().second - dbg->pos.second;
    dbg->width = width;
    macro->setDBGInfo(dbg);
    return macro;
}

} // namespace parser
} // namespace snowball
