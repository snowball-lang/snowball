
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

Syntax::Block* Parser::parseBlock(std::vector<TokenType> termination) {
    assert(!is<TokenType::_EOF>());
    std::vector<Syntax::Node*> stmts;

    while (true) {
        auto pk = peek();

        for (auto t : termination) {
            if (pk.type == t) {
                next();
                return new Syntax::Block(stmts);
            }
        }

        if (is<TokenType::SYM_SEMI_COLLON>(pk)) {
            next();
            continue;
        }

        stmts.push_back(parseStatement(pk));
    }

    return nullptr; // to remove warnings
}

} // namespace snowball::parser
