

#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Expression;

namespace snowball::parser {

std::vector<TypeRef *> Parser::parseGenericExpr() {
    assert(is<TokenType::OP_LT>());
    assert(is<TokenType::SYM_QUESTION>(peek()));

    next(); // Current token: OP_LT
    std::vector<TypeRef *> types;

    while (true) {
        next();

        if (is<TokenType::_EOF>()) {
            createError<UNEXPECTED_EOF>(
                "Found an unexpected EOF while parsing generic expression");
        } else if (is<TokenType::IDENTIFIER>()) {
            // Generate a new parameter instance
            auto ty = parseType();
            types.push_back(ty);

            if (is<TokenType::OP_GT>()) {
                next();
                break;
            } else if (is<TokenType::SYM_COMMA>() &&
                       is<TokenType::IDENTIFIER>(peek(0, true))) {
                continue;
            }

            assert_tok<TokenType::OP_GT>("a comma or a >");
        } else if (is<TokenType::OP_GT>()) {
            next();
            break;
        } else {
            createError<SYNTAX_ERROR>(
                "Expected a vaid generic exoression but got '%s'",
                m_current.to_string().c_str());
        }
    }

    return types;
}

} // namespace snowball::parser
