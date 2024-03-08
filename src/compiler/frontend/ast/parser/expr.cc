

#include <cassert>
#include <optional>
#include <vector>
#include <fmt/format.h>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"

#include "compiler/utils/utils.h"

namespace snowball {
namespace frontend {

ast::Expr* Parser::parse_expr(bool allow_assign) {
  ast::Expr* expr = nullptr;
  while (true) {
    next();
    switch (current.type) {
      case Token::Type::Identifier:
        expr = node<ast::Ident>(current.to_string());
        break;
      case Token::Type::ValueNumber:
        expr = node<ast::Number>(current.to_string());
        break;
      default:
        err("Unexpected token found while parsing expression", Error::Info {
          .highlight = fmt::format("Token '{}' is not expected here", current),
          .help = "An expression is expected here",
          .see = "https://snowball-lang.gitbook.io/docs/language-reference/expressions"
        });
        assert(false);
    }
    break; // TODO: Remove this break statement, support binary expressions, etc.
  }
  next();
  assert(expr);
  return expr;
}

}
}
