
#include <cassert>
#include <fmt/format.h>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"

#include "compiler/utils/utils.h"

namespace snowball {
namespace frontend {

ast::TypeRef Parser::parse_type_ref() {
  switch (current.type) {
    case Token::Type::Identifier: {
      auto name = node<ast::Ident>(current.to_string());
      next();
      if (is(Token::Type::OpLt)) 
        name->mutate_generics(parse_generics_expr());
      ast::Expr* expr = name;
      while (is(Token::Type::SymColcol)) {
        next();
        auto name = node<ast::Ident>(current.to_string());
        next();
        if (is(Token::Type::OpLt)) 
          name->mutate_generics(parse_generics_expr());
        expr = node<ast::MemberAccess>(expr, name, ast::MemberAccess::AccessType::Static);
      }
      return ast::TypeRef::create(name->get_location(), expr);
    }
    default: {
      next();
      err("Unexpected token found while parsing type reference", Error::Info {
        .highlight = fmt::format("Token '{}' is not expected here", current),
        .help = "At the top-level, only top-level items are allowed",
        .see = "https://snowball-lang.gitbook.io/docs/language-reference/types"
      });
    }
  }
  assert(false);
}

ast::GenericNode<ast::TypeRef> Parser::parse_generics_expr() {
  sn_assert(is(Token::Type::OpLt), "Expected '<' to start a generic expression");
  next();
  std::vector<ast::TypeRef> generics;
  while (!is(Token::Type::OpGt)) {
    auto type = parse_type_ref();
    generics.push_back(type);
    if (is(Token::Type::OpGt)) break;
    consume(Token::Type::SymComma, "a comma after the generic type", Token::Type::OpGt);
  }
  if (generics.empty()) {
    err("Empty generic expression!", Error::Info { 
      .highlight = "No generic declarations found!",  
      .help = "Remove the '<>' or add a type inside it",
      .see = "https://snowball-lang.gitbook.io/docs/language-reference/generics"
    }, Error::Type::Warn);
  }
  next();
  return ast::GenericNode<ast::TypeRef> { generics };
}

}
}

