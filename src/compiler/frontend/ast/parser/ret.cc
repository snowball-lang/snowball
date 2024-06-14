
#include <cassert>
#include <fmt/format.h>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"

#include "compiler/utils/utils.h"

namespace snowball {
namespace frontend {

ast::Return* Parser::parse_return() {
  auto pos = loc();
  std::optional<ast::Expr*> value = std::nullopt;
  if (!is(Token::Type::SymSemiColon)) {
    value = parse_expr();
  }
  expect(Token::Type::SymSemiColon, "a semicolon to end the return statement");
  return pnode<ast::Return>(pos, value);
}

}
}

