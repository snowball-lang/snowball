
#include <cassert>
#include <fmt/format.h>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"

#include "compiler/utils/utils.h"

namespace snowball {
namespace frontend {

ast::VarDecl* Parser::parse_var_decl() {
  assert(is(Token::Type::KwordVar));
  next();
  ast::AttributedNode attribs;
  attribs.set_mut(is(Token::Type::KwordMutable));
  if (attribs.get_mut()) next();
  auto name = expect(Token::Type::Identifier, "an identifier for the variable name", Token::Type::SymColon)
    .to_string();
  auto pos = loc();
  next();
  std::optional<ast::TypeRef> type = std::nullopt;
  if (is(Token::Type::SymColon)) {
    next();
    type = parse_type_ref();
  }
  std::optional<ast::Expr*> expr = std::nullopt;
  if (is(Token::Type::OpEq)) {
    expr = parse_expr(false);
  }
  return pnode<ast::VarDecl>(pos, name, type, expr, attribs);
}

}
}

