
#include "Parser.h"

#include <assert.h>

namespace snowball {
namespace parser {

Syntax::Macro* Parser::parseMacro() {
    assert(is<TokenType::KWORD_MACRO>());
    next();
    // TODO: expression macro: 'macro foo() = 1 + 1'
    auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
    bool isStatementMacro = true;
    auto name = assert_tok<TokenType::IDENTIFIER>("an identifier for macro name").to_string();
    next();
    consume<TokenType::BRACKET_LPARENT>("'('");
    std::map<std::string, Syntax::Macro::ArguementType> args;
    while (is<TokenType::IDENTIFIER>()) {
        auto name = m_current.to_string();
        next();
        consume<TokenType::SYM_COLLON>("':'");
        auto type = assert_tok<TokenType::IDENTIFIER>("an identifier for type").to_string();
        Syntax::Macro::ArguementType argType;
        if (type == "expr") {
            argType = Syntax::Macro::ArguementType::EXPRESSION;
        } else if (type == "const") {
            argType = Syntax::Macro::ArguementType::CONSTANT;
        } else if (type == "stmt") {
            argType = Syntax::Macro::ArguementType::STATEMENT;
        } else {
            createError<SYNTAX_ERROR>("expected 'expr' or 'stmt' for macro arguement type");
        }
        args[name] = argType;
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
    auto macro = Syntax::N<Syntax::Macro>(name, args, body, isStatementMacro);
    auto width = m_current.get_pos().second - dbg->pos.second;
    dbg->width = width;
    macro->setDBGInfo(dbg);
    return macro;
}

} // namespace parser
} // namespace snowball
