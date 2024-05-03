

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
      case Token::Type::Identifier: {
        auto name = current.to_string();
        std::optional<ast::GenericNode<ast::TypeRef>> generics;
        if (is(Token::Type::SymColcol, peek())) {
          next();
          if (is(Token::Type::OpLt, peek())) {
            next();
            generics = parse_generics_expr();
          }
          prev();
        }
        expr = node<ast::Ident>(name, generics);
        break;
      }
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
  while (true) {
    switch (current.type) {
      case Token::Type::BracketLparent: {
        std::vector<ast::Expr*> args;
        while (!is(Token::Type::BracketRparent, peek())) {
          args.push_back(parse_expr());
          prev();
          if (is(Token::Type::BracketRparent, peek())) break;
          consume(Token::Type::SymComma, "a comma after the argument", Token::Type::BracketRparent);
        }
        next();
        consume(Token::Type::BracketRparent, "a closing parenthesis after the arguments");
        expr = pnode<ast::Call>(expr->get_location(), expr, args);
      } break;
      default: goto continue_parse;
    }
  }
continue_parse:
  assert(expr);
  return expr;
}

}
}
