
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
  auto pos = loc();
  next();
  auto generics = parse_generics();
  consume(Token::Type::BracketLparent, "an open parenthesis after the function name", Token::Type::BracketLcurly);
  std::vector<ast::VarDecl*> params;
  while (!is(Token::Type::BracketRparent)) {
    auto pos = loc();
    auto param_name = expect(Token::Type::Identifier, "an identifier for the parameter name", {Token::Type::SymColon, Token::Type::BracketRparent})
      .to_string();
    if (is(Token::Type::BracketRparent)) break;
    next(1 + !is(Token::Type::SymColon)); // skip the identifier and the colon
    auto param_type = parse_type_ref();
    params.push_back(ast::VarDecl::create(pos, param_name, param_type, std::nullopt, nullptr));
    if (is(Token::Type::BracketRparent)) break;
    consume(Token::Type::SymComma, "a comma after the parameter", Token::Type::BracketRparent);
  }
  consume(Token::Type::BracketRparent, "a closing parenthesis after the parameters"); // no recovery
  ast::TypeRef return_type = node<ast::TypeRef>(node<ast::Ident>("void"));
  if (!is(Token::Type::BracketLcurly) && !is(Token::Type::SymSemiColon)) {
    return_type = parse_type_ref();
  }
  std::optional<ast::Block*> block = std::nullopt;
  if (is(Token::Type::SymSemiColon)) {
    next();
  } else {
    expect(Token::Type::BracketLcurly, "an opening curly brace after the return type");
    block = parse_block();
    next(); // skip the closing curly brace
  }
  if (attrs.get_external() == ast::AttributedNode::Extern::C && !attrs.get_unsafe()) {
    err("extern functions must be marked as unsafe", Error::Info {
      .highlight = fmt::format("This function is marked as extern"),
      .help = fmt::format("Mark this function as unsafe to allow extern functions"),
    }, Error::Type::Err);
  }
  return pnode<ast::FnDecl>(pos, name, params, return_type, block, generics, attrs);
}

}
}
