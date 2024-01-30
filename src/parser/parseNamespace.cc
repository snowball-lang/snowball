
#include "Parser.h"
#include <assert.h>

namespace snowball {
namespace parser {

Syntax::Statement::Namespace* Parser::parseNamespace() {
  assert(is<TokenType::KWORD_NAMESPACE>());
  auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
  auto comment = parseDocstring(m_current.getComment());
  auto attributes = verifyAttributes([&](std::string attr) {
                                     return Attributes::INVALID;
                                     });
  next();
  auto name = assert_tok<TokenType::IDENTIFIER>("an identifier for namespace").to_string();
  next();
  consume<TokenType::BRACKET_LCURLY>("'{'");
  auto body = parseGlobal(TokenType::BRACKET_RCURLY);
  assert_tok<TokenType::BRACKET_RCURLY>("'}'");
  auto ns = Syntax::N<Syntax::Statement::Namespace>(name, body);
  ns->setDBGInfo(dbg);
  for (auto[n, a] : attributes) { ns->addAttribute(n, a); }
  ns->setComment(comment);
  return ns;
}

} // namespace parser
} // namespace snowball
