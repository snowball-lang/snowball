
#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

Syntax::Statement::VariableDecl *Parser::parseVariable() {
    assert(is<TokenType::KWORD_VAR>());
    next();

    // TODO: dinamic mutability
    bool isMutable = false;

    auto token = assert_tok<TokenType::IDENTIFIER>("an identifier");
    next(); // consume identifier

    auto name = token.to_string();

    // TODO: actually find type definition
    Syntax::Expression::TypeRef *typeDef = nullptr;

    if (is<TokenType::SYM_COLLON>()) {
        next();
        typeDef = parseType();
    }

    Syntax::Expression::Base *value = nullptr;
    if (is<TokenType::OP_EQ>()) {
        value = parseExpr();
    } else if (!is<TokenType::SYM_SEMI_COLLON>()) {
        createError<SYNTAX_ERROR>("Invalid variable declaration syntax!",
                                  "Expected '=' for a variable declaration");
    } else if (typeDef == nullptr) {
        createError<SYNTAX_ERROR>(
            "Undeclared type for uninitialized variable declaration!",
            "Variable declarations must have type definition if it's not "
            "initialized");
    }

    auto v = Syntax::N<Syntax::Statement::VariableDecl>(name, value, isMutable);
    v->setDefinedType(typeDef);

    auto info =
        new DBGSourceInfo(m_source_info, token.get_pos(), token.get_width());
    v->setDBGInfo(info);

    return v; // to remove warnings
}

} // namespace snowball::parser
