

#include <cassert>
#include <optional>
#include <vector>
#include <fmt/format.h>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"

#include "compiler/utils/utils.h"

#define NEXT_TO(i, f) \
  (i.location.first == f.location.first && \
   i.location.second == f.location.second-1)

namespace snowball {
namespace frontend {

ast::Expr* Parser::parse_expr(bool allow_assign) {
  ast::Expr* expr = nullptr;
  while (true) {
    next();
    switch (current.type) {
      case Token::Type::Identifier: {
        if (NEXT_TO(current, peek()) && is(Token::Type::ValueString, peek())) {
          auto prefix = current.to_string()[0];
          next();
          expr = node<ast::String>(current.to_string(), prefix);
          break;
        }
        expr = parse_ident();
        break;
      }
      case Token::Type::ValueNumber:
        expr = node<ast::Number>(current.to_string());
        break;
      case Token::Type::ValueString:
        expr = node<ast::String>(current.to_string());
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
      case Token::Type::SymDot:
      case Token::Type::SymColcol: {
        auto op = current.type == Token::Type::SymDot 
          ? ast::MemberAccess::AccessType::Default 
          : ast::MemberAccess::AccessType::Static;
        next();
        auto name = parse_ident();
        expr = node<ast::MemberAccess>(expr, name, op);
        next();
      } break;
      default: goto continue_parse;
    }
  }
continue_parse:
  assert(expr);
  return expr;
}

ast::Ident* Parser::parse_ident() {
  auto l = loc();
  auto name = expect(Token::Type::Identifier, "an identifier");
  std::optional<ast::GenericNode<ast::TypeRef>> generics;
  if (is(Token::Type::SymColcol) && is(Token::Type::OpLt, peek())) {
    next();
    generics = parse_generics_expr();
    next();
    consume(Token::Type::OpGt, "a greater than symbol '>' after the generics");
  }
  return pnode<ast::Ident>(l, name.to_string());
}

}
}
