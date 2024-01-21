#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

std::unordered_map<std::string, std::unordered_map<std::string, std::string>> Parser::parseAttributes(bool forConstexpr) {
  assert(is<TokenType::SYM_AT>() || forConstexpr);
  std::unordered_map<std::string, std::unordered_map<std::string, std::string>> attributes;
  while (is<TokenType::SYM_AT>() || forConstexpr) {
    if (!forConstexpr) next();
    std::unordered_map<std::string, std::string> attrArgs;
    auto attr = m_current.to_string();
    if (!(m_current.type > TokenType::KWORD__START__POINT && m_current.type < TokenType::KWORD__ENDING__POINT))
      assert_tok<TokenType::IDENTIFIER>("an identifier");
    if (is<TokenType::BRACKET_LPARENT>(peek())) {
      next();
      while (true) {
        next();
        if (is<TokenType::BRACKET_RPARENT>()) { break; }
        // TODO: check for already deifned ones
        auto name = assert_tok<TokenType::IDENTIFIER>("an identifier").to_string();
        next();
        if (is<TokenType::OP_EQ>()) {
          next();
          if (is<TokenType::VALUE_STRING>()) {
            auto val = m_current.to_string();
            if (is<TokenType::VALUE_STRING>()) val = val.substr(1, val.size() - 2); // remove "
            attrArgs[name] = val;
          } else if (is<TokenType::VALUE_NUMBER>()) {
            attrArgs[name] = m_current.to_string();
          } else {
            createError<SYNTAX_ERROR>(
                    FMT("Expected a string or a number value but found '%s' instead", peek().to_string().c_str())
            );
          }
        } else {
          attrArgs[name] = "";
          prev();
        }
        auto pk = peek();
        if (is<TokenType::SYM_COMMA>(pk) || is<TokenType::BRACKET_RPARENT>(pk)) {
          if (is<TokenType::SYM_COMMA>(pk)) next();
          continue;
        } else {
          next();
          createError<SYNTAX_ERROR>(FMT("Expected a ',' or a ')' but found '%s' instead", pk.to_string().c_str()));
        }
      }
    }
    if (attributes.find(attr) != attributes.end()) {
      createError<SYNTAX_ERROR>(FMT("Attribute '%s' is already defined!", attr.c_str()));
    }
    attributes.insert({attr, attrArgs});
    if (forConstexpr) break;
    next();
  }
  if (!forConstexpr) {
    prev();
    m_attributes = attributes;
  }
  return attributes;
}

std::unordered_map<Attributes, std::unordered_map<std::string, std::string>> Parser::verifyAttributes(
  std::function<Attributes(std::string)> parseFn
) {
  return verifyAttributes(parseFn, m_attributes);
}

std::unordered_map<Attributes, std::unordered_map<std::string, std::string>> Parser::verifyAttributes(
  std::function<Attributes(std::string)> parseFn,
  std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& attrs
) {
  std::unordered_map<Attributes, std::unordered_map<std::string, std::string>> attributes;
  for (auto& [attr, args] : attrs) {
    auto attrType = parseFn(attr);
    if (attr == "cfg") {
      attrType = Attributes::CFG;
    } else if (attr == "attr") {
      attrType = Attributes::ATTR;
    }
    if (attrType == Attributes::INVALID) {
      createError<SYNTAX_ERROR>(FMT("Invalid attribute '%s'", attr.c_str()));
    }
    attributes[attrType] = args;
  }
  attrs.clear();
  return attributes;
}

void Parser::assertNoAttributes(std::string context) {
  if (m_attributes.size() > 0) {
    createError<SYNTAX_ERROR>(FMT("Attributes are not allowed inside a %s", context.c_str()));
  }
}

} // namespace snowball::parser
