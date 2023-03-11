
#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

ptr<Syntax::Statement::VariableDecl> Parser::parseVariable() {
    assert(is<TokenType::KWORD_VAR>());
    next();

    // TODO: dinamic mutability
    bool isMutable = false;

    auto token = assert_tok<TokenType::IDENTIFIER>("an identifier");
    next(); // consume identifier

    auto name = token.to_string();

    // TODO: actually find type definition
    ptr<Syntax::Expression::TypeRef> typeDef = nullptr;

    assert_tok<TokenType::OP_EQ>("'='");
    auto value = parseExpr();

    auto v = Syntax::N<Syntax::Statement::VariableDecl>(name, value, isMutable);
    v->setDefinedType(typeDef);

    auto info =
        new DBGSourceInfo(m_source_info, token.get_pos(), token.get_width());
    v->setDBGInfo(info);

    return v; // to remove warnings
}

} // namespace snowball::parser
