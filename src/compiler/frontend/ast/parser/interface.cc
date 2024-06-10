

#include <cassert>
#include <optional>
#include <vector>
#include <fmt/format.h>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"

#include "compiler/utils/utils.h"

namespace snowball {
namespace frontend {

#define SET_ATTR(n) \
  fn_attrs.set_##n(true); \
  next();

ast::ClassDecl* Parser::parse_interface_decl(const ast::AttributedNode& attrs) {
  assert(is(Token::Type::KwordInter));
  attrs.assert_is_type();
  next();
  auto name = expect(Token::Type::Identifier, "an identifier for the interface name", {Token::Type::OpLt, Token::Type::BracketLcurly})
    .to_string();
  auto pos = loc();
  next();
  auto generics = parse_generics();
  std::vector<ast::FnDecl*> funcs;
  expect(Token::Type::BracketLcurly, "an opening curly brace after the return type");
  next();
  ast::AttributedNode fn_attrs;
  while (!is(Token::Type::BracketRcurly)) {
    while (true) {
      switch (current.type) {
        case Token::Type::KwordFunc:
          goto parse_fn_decl;
        case Token::Type::KwordStatic:
          SET_ATTR(static);
          break;
        case Token::Type::KwordOperator:
          SET_ATTR(operator);
          break;
        case Token::Type::KwordDefault:
          SET_ATTR(default);
          break;
        case Token::Type::KwordPublic:
        case Token::Type::KwordPrivate:
          fn_attrs.set_privacy(current.type == Token::Type::KwordPublic 
            ? ast::AttributedNode::Privacy::Public 
            : ast::AttributedNode::Privacy::Private);
          next();
          break;
        default:
          err("Expected a class member after privacy modifier", Error::Info {
            .highlight = fmt::format("Token '{}' is not expected here", current),
            .help = "At the class level, only class members are allowed",
            .see = "https://snowball-lang.gitbook.io/docs/language-reference/classes"
          });
      }
    }
  parse_fn_decl:
    funcs.push_back(parse_fn_decl(fn_attrs));
    funcs.back()->set_virtual(true);
    fn_attrs = ast::AttributedNode::empty();
  }
  next(); // skip the closing curly brace
  return pnode<ast::ClassDecl>(pos, name, std::vector<ast::VarDecl*>{}, funcs, ast::ClassDecl::ClassType::Interface, generics, attrs);
}

#undef SET_ATTR

}
}


