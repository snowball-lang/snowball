
#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>
#define IS_CONSTRUCTOR(tk) is<TokenType::IDENTIFIER>(tk) && tk.value == name

namespace snowball::parser {

ptr<Syntax::Statement::ClassDef> Parser::parseClass() {
    assert(is<TokenType::KWORD_CLASS>());
    next(); // East "class"

    bool isPublic = false;
    if (is<TokenType::KWORD_PUBLIC, TokenType::KWORD_PRIVATE>(peek(-4, true))) {
        isPublic = is<TokenType::KWORD_PUBLIC>(peek(-4, true));
    }

    auto name =
        assert_tok<TokenType::IDENTIFIER>("class identifier").to_string();
    auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);

    ptr<Syntax::Expression::TypeRef> parentClass = nullptr;
    std::vector<ptr<Syntax::Expression::TypeRef>> generics;

    if (is<TokenType::OP_LT>(peek()) &&
        is<TokenType::SYM_QUESTION>(peek(1, true))) {
        auto name = m_current.to_string();
        next();
        auto generics = parseGenericExpr();
        auto width    = m_current.get_pos().second - dbg->pos.second;

        dbg->width = width;
        prev();
    }

    next();
    if (is<TokenType::SYM_COLLON>()) {
        next();
        parentClass = parseType();
    }

    assert_tok<TokenType::BRACKET_LCURLY>("'{'");
    bool inPrivateScope = true;

    auto cls = Syntax::N<Syntax::Statement::ClassDef>(
        name, parentClass, Syntax::Statement::Privacy::fromInt(isPublic));

    cls->setDBGInfo(dbg);

    while (true) {
        next();
        switch (m_current.type) {
            case TokenType::KWORD_PRIVATE: {
                inPrivateScope = true;
                next();
                assert_tok<TokenType::SYM_COLLON>("':'");
            } break;

            case TokenType::KWORD_PUBLIC: {
                inPrivateScope = false;
                next();
                assert_tok<TokenType::SYM_COLLON>("':'");
            } break;

            case TokenType::KWORD_STATIC: {
                if (peek().type != TokenType::KWORD_FUNC &&
                    peek().type != TokenType::KWORD_VAR &&
                    (!IS_CONSTRUCTOR(peek()))) {
                    next();
                    createError<SYNTAX_ERROR>(
                        "expected keyword \"func\", \"let\" or a constructor "
                        "declaration after static member");
                }
            } break;

            case TokenType::KWORD_FUNC: {
                auto func = parseFunction();
                func->setPrivacy(
                    Syntax::Statement::Privacy::fromInt(!inPrivateScope));
                cls->addFunction(func);
            } break;

            case TokenType::BRACKET_RCURLY: {
                return cls;
            }

            // note: This case should be always at the bottom!
            case TokenType::IDENTIFIER: {
                if (IS_CONSTRUCTOR(m_current)) {
                    auto func = parseFunction(true);
                    func->setPrivacy(
                        Syntax::Statement::Privacy::fromInt(!inPrivateScope));
                    func->setName();
                    cls->addFunction(func);
                    break;
                }
            }

            default: {
                createError<SYNTAX_ERROR>(FMT(
                    "Unexpected token ('%s') found while parsing class body",
                    m_current.to_string().c_str()));
            }
        }
    }
}

} // namespace snowball::parser
