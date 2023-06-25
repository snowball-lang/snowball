
#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Expression;

namespace snowball::parser {

WhereClause* Parser::parseWhereClause() {
    assert(is<TokenType::SYM_COLLON>());
    WhereClause::ChecksVectorType tests;

    do {
        next();
        tests.push_back(parseType());
    } while (is<TokenType::OP_PLUS>());
    return new WhereClause(tests);
}

} // namespace snowball::parser
