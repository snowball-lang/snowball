
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

Syntax::Statement::VariableDecl* Parser::parseConstant() {
  assert(is<TokenType::KWORD_CONST>());
  auto comment = parseDocstring(m_current.getComment());
  next();
  bool isPublic = false;
  if (is<TokenType::KWORD_PUBLIC, TokenType::KWORD_PRIVATE>(peek(-3, true))) {
    isPublic = is<TokenType::KWORD_PUBLIC>(peek(-3, true));
  }
  auto token = assert_tok<TokenType::IDENTIFIER>("an identifier");
  next(); // consume identifier
  auto name = token.to_string();
  // TODO: actually find type definition
  Syntax::Expression::TypeRef* typeDef = nullptr;
  consume<TokenType::SYM_COLLON>("':' for a type declaration");
  typeDef = parseType();
  Syntax::Expression::Base* value = nullptr;
  assert_tok<TokenType::OP_EQ>("'=' for a variable declaration");
  value = parseExpr(false);
  if (is<TokenType::SYM_SEMI_COLLON>(peek(0, true))) next();
  auto v = Syntax::N<Syntax::Statement::VariableDecl>(name, value, false, true);
  v->setDefinedType(typeDef);
  v->setPrivacy(Syntax::Statement::Privacy::fromInt(isPublic));

  auto info = new DBGSourceInfo(m_source_info, token.get_pos(), token.get_width());
  v->setDBGInfo(info);
  v->setComment(comment);

  return v; // to remove warnings
}

} // namespace snowball::parser
