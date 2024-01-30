
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "../services/OperatorService.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

Syntax::Statement::EnumTypeDef* Parser::parseEnum() {
  assert(is<TokenType::KWORD_ENUM>());
  auto comment = parseDocstring(m_current.getComment());
  next(); // East "enum"
  bool isPublic = false;
  if (is<TokenType::KWORD_PUBLIC, TokenType::KWORD_PRIVATE>(peek(-3, true))) {
    isPublic = is<TokenType::KWORD_PUBLIC>(peek(-3, true));
  }
  auto attributes = verifyAttributes([&](std::string attr) {
                                     return Attributes::INVALID;
                                     });
  auto name = assert_tok<TokenType::IDENTIFIER>("enum identifier").to_string();
  auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
  Syntax::Statement::GenericContainer<>::GenericList generics;
  bool hasGenerics = false;
  if (is<TokenType::OP_LT>(peek())) {
    next();
    hasGenerics = true;
    generics = parseGenericParams();
    prev();
  }
  next();
  assert_tok<TokenType::BRACKET_LCURLY>("'{'");
  next();
  auto cls = Syntax::N<Syntax::Statement::EnumTypeDef>(
             name, Syntax::Statement::Privacy::fromInt(isPublic)
             );
  if (hasGenerics)
    cls->setGenerics(generics);
  cls->setDBGInfo(dbg);
  bool keepParsing = true;
  while (keepParsing) {
    switch (m_current.type) {
      case TokenType::IDENTIFIER: {
        auto name = m_current.to_string();
        if (is<TokenType::BRACKET_LPARENT>(peek())) {
          next();
          std::vector<Syntax::Expression::TypeRef*> fields;
          while (true) {
            next();
            fields.push_back(parseType());
            if (!is<TokenType::SYM_COMMA>()) {
              break;
            }
          }
          assert_tok<TokenType::BRACKET_RPARENT>("')'");
          cls->addField({name, fields});
        } else {
          cls->addField({name, {}});
        }
        next();
        if (!is<TokenType::BRACKET_RCURLY>()) {
          assert_tok<TokenType::SYM_COMMA>("',' or '}'");
          next();
        }
        break;
      }
      case TokenType::BRACKET_RCURLY: {
        keepParsing = false;
        break;
      }
      default: {
        createError<SYNTAX_ERROR>(
        FMT("Expected a valid member declaration but found '%s'", m_current.to_string().c_str())
        );
        break;
      }
    }
  }
  assert_tok<TokenType::BRACKET_RCURLY>("'}'");
  cls->setComment(comment);
  for (auto attr : attributes) cls->addAttribute(attr.first, attr.second);
  return cls;
}

} // namespace snowball::parser
