
#include <cassert>
#include <fmt/format.h>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"

#include "compiler/utils/utils.h"

namespace snowball {
namespace frontend {

ast::FnDecl* Parser::parse_fn_decl(const ast::AttributedNode& attrs) {
  assert(is(Token::Type::KwordFunc));
  attrs.assert_is_func();
  next();

  auto name = expect(Token::Type::Identifier, "an identifier for the function name", Token::Type::BracketLparent)
    .to_string();
  next();
  auto generics = parse_generics();
  consume(Token::Type::BracketLparent, "an open parenthesis after the function name", Token::Type::BracketLcurly);

  std::vector<ast::FnDecl::Param> params;
  while (!is(Token::Type::BracketRparent)) {
    auto param_name = expect(Token::Type::Identifier, "an identifier for the parameter name", {Token::Type::SymColon, Token::Type::BracketRparent})
      .to_string();
    if (is(Token::Type::BracketRparent)) break;
    next(1 + !is(Token::Type::SymColon)); // skip the identifier and the colon
    auto param_type = parse_type_ref();
    params.push_back(ast::FnDecl::Param { param_name, param_type });
    if (is(Token::Type::BracketRparent)) break;
    consume(Token::Type::SymComma, "a comma after the parameter", Token::Type::BracketRparent);
  }
  consume(Token::Type::BracketRparent, "a closing parenthesis after the parameters"); // no recovery
  ast::TypeRef return_type = node<ast::TypeRef>(node<ast::Ident>("void"));
  if (!is(Token::Type::BracketLcurly)) {
    return_type = parse_type_ref();
  }
  expect(Token::Type::BracketLcurly, "an opening curly brace after the return type");
  auto block = parse_block();
  next(); // skip the closing curly brace
  return node<ast::FnDecl>(name, params, return_type, block, generics, attrs);
}

}
}
