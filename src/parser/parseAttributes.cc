#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

std::unordered_map<Attributes, std::unordered_map<std::string, std::string>> Parser::parseAttributes(
        std::function<Attributes(std::string)> parseFn) {
  assert(is<TokenType::BRACKET_LSQUARED>() && is<TokenType::BRACKET_LSQUARED>(peek()));
  next();
  std::unordered_map<Attributes, std::unordered_map<std::string, std::string>> attributes;
  while (true) {
    std::unordered_map<std::string, std::string> attrArgs;
    next();
    assert_tok<TokenType::IDENTIFIER>("an identifier");
    auto attr = m_current.to_string();
    Attributes parsed;
    if (attr == "cfg") {
      parsed = Attributes::CFG;
    } else {
      parsed = parseFn(attr);
      if (parsed == Attributes::INVALID) {
        createError<ATTRIBUTE_ERROR>(
                "Trying to use an undefined attribute!", {.info = FMT("Attribute '%s' is not defined!", attr.c_str())});
      }
    }
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
                    FMT("Expected a string or a number value but found '%s' instead", peek().to_string().c_str()));
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
    attributes[parsed] = attrArgs;
    next();
    if (is<TokenType::BRACKET_RSQUARED>()) {
      next();
      assert_tok<TokenType::BRACKET_RSQUARED>("']]'");
      next();
      break;
    } else if (is<TokenType::SYM_COMMA>()) {
    } else {
      assert_tok<TokenType::BRACKET_RSQUARED>("',' or ']]'");
    }
  }
  return attributes;
}

} // namespace snowball::parser
