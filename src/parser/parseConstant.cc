
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

Syntax::Statement::VariableDecl* Parser::parseConstant() {
  assert(is<TokenType::KWORD_CONST>());
  auto comment = parseDocstring(m_current.getComment());
  auto attributes = verifyAttributes([&](std::string attr) {
                                       return Attributes::INVALID;
                                     });
  next();
  bool isPublic = false;
  bool isExternal = false;
  bool isStatic = false;
  if (is<TokenType::KWORD_PUBLIC, TokenType::KWORD_PRIVATE>(peek(-3, true))) {
    isPublic = is<TokenType::KWORD_PUBLIC>(peek(-3, true));
  } else if (is<TokenType::KWORD_EXTERN>(peek(-3, true))) {
    isExternal = true;
    isPublic = is<TokenType::KWORD_PUBLIC>(peek(-4, true));
  } else if (is<TokenType::KWORD_STATIC>(peek(-3, true))) {
    isStatic = true;
    isPublic = is<TokenType::KWORD_PUBLIC>(peek(-4, true));
  }
  if (!isStatic && m_current_class != nullptr) {
    createError<SYNTAX_ERROR>("Cannot declare a non-static constant inside a class", {
      .info = "Not static constant",
      .note = "This is because constants are not tied to a specific instance of a class,\n"
      "and therefore cannot be accessed from an instance of a class",
      .help = "Make the constant static by adding the 'static' keyword\nbefore the 'const' keyword",
    });
  }
  auto token = assert_tok<TokenType::IDENTIFIER>("an identifier");
  next(); // consume identifier
  auto name = token.to_string();
  // TODO: actually find type definition
  Syntax::Expression::TypeRef* typeDef = nullptr;
  consume<TokenType::SYM_COLLON>("':' for a type declaration");
  typeDef = parseType();
  Syntax::Expression::Base* value = nullptr;
  if (!isExternal) {
    assert_tok<TokenType::OP_EQ>("'=' for a variable declaration");
    value = parseExpr(false);
  }
  if (is<TokenType::SYM_SEMI_COLLON>(peek(0, true))) next();
  auto v = Syntax::N<Syntax::Statement::VariableDecl>(name, value, false, true);
  v->setDefinedType(typeDef);
  v->setPrivacy(Syntax::Statement::Privacy::fromInt(isPublic));
  auto info = new DBGSourceInfo(m_source_info, token.get_pos(), token.get_width());
  v->setDBGInfo(info);
  v->setComment(comment);
  v->setExternDecl(isExternal);
  for (auto[n, a] : attributes) { v->addAttribute(n, a); }
  return v; // to remove warnings
}

} // namespace snowball::parser
