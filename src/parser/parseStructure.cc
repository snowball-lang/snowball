
#include "../common.h"
#include "../services/OperatorService.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

Syntax::Statement::DefinedTypeDef* Parser::parseStructure() {
    assert(is<TokenType::KWORD_STRUCT>());
    next(); // East "struct"

    bool isPublic = false;
    if (is<TokenType::KWORD_PUBLIC, TokenType::KWORD_PRIVATE>(peek(-3, true))) {
        isPublic = is<TokenType::KWORD_PUBLIC>(peek(-3, true));
    }
    
    auto name = assert_tok<TokenType::IDENTIFIER>("structure identifier").to_string();
    auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
    Syntax::Statement::GenericContainer<>::GenericList generics;

    if (is<TokenType::OP_LT>(peek())) {
        next();
        generics = parseGenericParams();
        prev();
    }

    next();
    assert_tok<TokenType::BRACKET_LCURLY>("'{'");
    next();
    auto cls = Syntax::N<Syntax::Statement::DefinedTypeDef>(
            name, nullptr, Syntax::Statement::Privacy::fromInt(isPublic), true);
    cls->setGenerics(generics);
    cls->setDBGInfo(dbg);

    while (is<TokenType::KWORD_VAR>()) {
        // TODO: maybe a custom syntax?
        auto member = parseVariable();
        consume<TokenType::SYM_SEMI_COLLON>("';'");
        cls->addVariable(member);
    }

    assert_tok<TokenType::BRACKET_RCURLY>("'}'");
    return cls;
}

} // namespace snowball::parser
