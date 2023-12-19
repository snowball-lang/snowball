
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

Syntax::Statement::VariableDecl* Parser::parseVariable() {
  assert(is<TokenType::KWORD_VAR>());
  auto comment = parseDocstring(m_current.getComment());
  next();

  auto attributes = verifyAttributes([&](std::string attr) {
    return Attributes::INVALID;
  });

  bool isPublic = false;
  if (is<TokenType::KWORD_PUBLIC, TokenType::KWORD_PRIVATE>(peek(-3, true))) {
    isPublic = is<TokenType::KWORD_PUBLIC>(peek(-3, true));
  }
  bool isMutable = false;
  if (is<TokenType::KWORD_MUTABLE>()) {
    isMutable = true;
    next();
  }
  auto token = assert_tok<TokenType::IDENTIFIER>("an identifier");
  next(); // consume identifier
  auto name = token.to_string();
  // TODO: actually find type definition
  Syntax::Expression::TypeRef* typeDef = nullptr;
  if (is<TokenType::SYM_COLLON>()) {
    next();
    typeDef = parseType();
  }
  Syntax::Expression::Base* value = nullptr;
  if (is<TokenType::OP_EQ>()) {
    value = parseExpr(false);
    if (is<TokenType::SYM_SEMI_COLLON>(peek(0, true))) next();
  } else if (!is<TokenType::SYM_SEMI_COLLON>()) {
    createError<SYNTAX_ERROR>(
            "Invalid variable declaration syntax!", {.info = "Expected '=' for a variable declaration"}
    );
  } else if (typeDef == nullptr) {
    createError<SYNTAX_ERROR>(
            "Undeclared type for uninitialized variable declaration!",
            {.info = "Variable declarations must have type definition if "
                     "it's not "
                     "initialized"}
    );
  }

  auto v = Syntax::N<Syntax::Statement::VariableDecl>(name, value, isMutable);
  v->setDefinedType(typeDef);
  v->setPrivacy(Syntax::Statement::Privacy::fromInt(isPublic));
  v->setComment(comment);

  auto info = new DBGSourceInfo(m_source_info, token.get_pos(), token.get_width());
  v->setDBGInfo(info);

  for (auto [n, a] : attributes) { v->addAttribute(n, a); }

  return v; // to remove warnings
}

} // namespace snowball::parser
