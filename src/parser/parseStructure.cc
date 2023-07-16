
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "../services/OperatorService.h"
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
    auto cls = Syntax::N<Syntax::Statement::DefinedTypeDef>(name, nullptr,
                                                            Syntax::Statement::Privacy::fromInt(isPublic), true);
    cls->setGenerics(generics);
    cls->setDBGInfo(dbg);

    bool keepParsing = true;
    while (keepParsing) {
        switch (m_current.type) {
            case TokenType::KWORD_PUBLIC:
            case TokenType::KWORD_PRIVATE: {
                next();
                assert_tok<TokenType::KWORD_VAR>("a valid member declaration");
                break;
            }

            case TokenType::KWORD_VAR: {
                auto member = parseVariable();
                consume<TokenType::SYM_SEMI_COLLON>("';'");
                cls->addVariable(member);
                break;
            }

            case TokenType::BRACKET_RCURLY: {
                keepParsing = false;
                break;
            }

            default: {
                createError<SYNTAX_ERROR>(
                        FMT("Expected a valid member declaration but found '%s'", m_current.to_string().c_str()));
                break;
            }
        }
    }

    assert_tok<TokenType::BRACKET_RCURLY>("'}'");
    return cls;
}

} // namespace snowball::parser
