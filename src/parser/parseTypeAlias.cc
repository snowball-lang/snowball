
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "../services/OperatorService.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

Syntax::Statement::TypeAlias* Parser::parseTypeAlias() {
  assert(is<TokenType::KWORD_TYPEDEF>());
  auto comment = parseDocstring(m_current.getComment());
  next(); // East "type"
  bool isPublic = false;
  bool isGeneric = false;
  if (is<TokenType::KWORD_PUBLIC, TokenType::KWORD_PRIVATE>(peek(-3, true))) {
    isPublic = is<TokenType::KWORD_PUBLIC>(peek(-3, true));
  }
  auto name = assert_tok<TokenType::IDENTIFIER>("type identifier").to_string();
  auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
  Syntax::Statement::GenericContainer<>::GenericList generics;
  next();
  if (is<TokenType::OP_LT>()) {
    isGeneric = true;
    generics = parseGenericParams();
  }
  consume<TokenType::OP_EQ>("'='");
  auto type = parseType();
  auto privacy = Syntax::Statement::Privacy::fromInt(isPublic);
  auto node = Syntax::N<Syntax::Statement::TypeAlias>(name, type);
  node->setPrivacy(privacy);
  node->setDBGInfo(dbg);
  node->setComment(comment);
  if (isGeneric) node->setGenerics(generics);
  return node;
}

} // namespace snowball::parser
