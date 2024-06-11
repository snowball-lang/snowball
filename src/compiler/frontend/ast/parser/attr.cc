
#include <cassert>
#include <fmt/format.h>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"

#include "compiler/utils/utils.h"

namespace snowball {
namespace frontend {

using namespace ast::attrs;

Attr Parser::parse_attr() {
  assert(is(Token::Type::SymHash));
  next();
  consume(Token::Type::BracketLsquared, "an opening square bracket after the hash symbol");
  bool is_global = is(Token::Type::OpNot);
  if (is_global) next();
  auto attr = parse_attr_value();
  consume(Token::Type::BracketRsquared, "a closing square bracket after the attribute");
  if (is_global) attr.set_global();
  return attr;
}

ast::attrs::Attr Parser::parse_attr_value() {
  auto loc = this->loc();
  auto key = expect(Token::Type::Identifier, "an identifier for the attribute key").to_string();
  next();
  Attr* attr;
  switch (current.type) {
    case Token::Type::OpEq: {
      next();
      auto value = expect(Token::Type::ValueString, "a string value for the attribute").to_string();
      next();
      attr = utils::get_temporary_address(Attr(key, value, loc));
      break;
    }
    case Token::Type::BracketLparent: {
      next();
      std::vector<Attr> attrs;
      while (!is(Token::Type::BracketRparent)) {
        attrs.push_back(parse_attr());
        if (is(Token::Type::BracketRparent)) break;
        consume(Token::Type::SymComma, "a comma after the attribute", Token::Type::BracketRparent);
      }
      attr = utils::get_temporary_address(Attr(key, attrs, loc));
      break;
    }
    default: {
      attr = utils::get_temporary_address(Attr(key, loc));
      break;
    }
  }
  return *attr;
}

}
}
