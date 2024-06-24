

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

ast::ExtensionDecl* Parser::parse_extension_decl(const ast::AttributedNode& attrs) {
  assert(is(Token::Type::KwordExtends));
  attrs.assert_is_type();
  auto pos = loc();
  next();
  auto base = parse_type_ref();
  std::vector<ast::FnDecl*> funcs;
  expect(Token::Type::BracketLcurly, "an opening curly brace after the return type");
  next();
  ast::AttributedNode fn_attrs;
  size_t virtual_index = 0;
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
    fn_attrs = ast::AttributedNode::empty();
  }
  next(); // skip the closing curly brace
  return pnode<ast::ExtensionDecl>(pos, base, funcs);
}

#undef SET_ATTR

}
}


