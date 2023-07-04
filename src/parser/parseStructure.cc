
#include "../common.h"
#include "../services/OperatorService.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>
#define IS_CONSTRUCTOR(tk) is<TokenType::IDENTIFIER>(tk) && tk.value == name

namespace snowball::parser {

Syntax::Statement::DefinedTypeDef* Parser::parseClass() {
    assert(is<TokenType::KWORD_CLASS>());
    next(); // East "class"

    bool isPublic = false;
    if (is<TokenType::KWORD_PUBLIC, TokenType::KWORD_PRIVATE>(peek(-4, true))) {
        isPublic = is<TokenType::KWORD_PUBLIC>(peek(-4, true));
    }

    auto name = assert_tok<TokenType::IDENTIFIER>("class identifier").to_string();
    auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);

    Syntax::Expression::TypeRef* parentClass = nullptr;
    Syntax::Statement::GenericContainer<>::GenericList generics;

    if (is<TokenType::OP_LT>(peek())) {
        next();
        generics = parseGenericParams();
        prev();
    }

    next();
    if (is<TokenType::SYM_COLLON>()) {
        next();
        throwIfNotType();
        parentClass = parseType();
    }

    assert_tok<TokenType::BRACKET_LCURLY>("'{'");
    auto cls = Syntax::N<Syntax::Statement::DefinedTypeDef>(
            name, parentClass, Syntax::Statement::Privacy::fromInt(isPublic));
    cls->setGenerics(generics);
    cls->setDBGInfo(dbg);
    return cls;
}

} // namespace snowball::parser
