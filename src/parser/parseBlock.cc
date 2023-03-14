
#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

ptr<Syntax::Block> Parser::parseBlock(std::vector<TokenType> termination) {
    assert(!is<TokenType::_EOF>());
    std::vector<ptr<Syntax::Node>> stmts;

    while (true) {
        auto pk = peek();

        switch (pk.type) {
            case TokenType::_EOF: {
                next(); // eat EOF
                createError<UNEXPECTED_EOF>(
                    "Found an unexpected EOF while parsing a block");
            }

            case TokenType::BRACKET_LCURLY: {
                next();
                stmts.push_back(parseBlock());
                break;
            }

            case TokenType::SYM_SEMI_COLLON: {
                next();
                break;
            }

            case TokenType::KWORD_VAR: {
                next();
                stmts.push_back(parseVariable());
                break;
            }

            case TokenType::KWORD_RETURN: {
                next();
                stmts.push_back(parseReturn());
                break;
            }

            default: {
                for (auto t : termination) {
                    if (pk.type == t) {
                        next();
                        return new Syntax::Block(stmts);
                    }
                }

                auto expr = parseExpr();
                stmts.push_back(expr);
            }
        }
    }

    return nullptr; // to remove warnings
}

} // namespace snowball::parser