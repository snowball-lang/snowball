
#include <cassert>
#include <fmt/format.h>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"

#include "compiler/utils/utils.h"

namespace snowball {
namespace frontend {

ast::ClassDecl* Parser::parse_class_decl(const ast::AttributedNode& attrs) {
  assert(is(Token::Type::KwordClass));
  attrs.assert_is_type();
  next();
  auto name = expect(Token::Type::Identifier, "an identifier for the class name", {Token::Type::OpLt, Token::Type::BracketLcurly})
    .to_string();
  auto pos = loc();
  next();
  auto generics = parse_generics();
  auto block = parse_class_body();
  next(); // skip the closing curly brace
  return pnode<ast::ClassDecl>(pos, name, block.vars, block.funcs, generics, attrs);
}

Parser::ParsingClassResult Parser::parse_class_body() { 
  ParsingClassResult result;
  ast::AttributedNode attrs;
  expect(Token::Type::BracketLcurly, "an opening curly brace after the return type");
  if (is(Token::Type::BracketRcurly, peek())) {
    next();
    return result;
  }
  while (!is(Token::Type::BracketRcurly)) {
    switch (current.type) {
      case Token::Type::KwordPublic:
      case Token::Type::KwordPrivate: {
        attrs.set_privacy(current.type == Token::Type::KwordPublic);
        next();
        switch (current.type) {
          case Token::Type::KwordFunc:
          case Token::Type::KwordStatic:
          case Token::Type::KwordConst:
          case Token::Type::KwordVar:
            break;
          default:
            err("Expected a class member after privacy modifier", Error::Info {
              .highlight = fmt::format("Token '{}' is not expected here", current),
              .help = "At the class level, only class members are allowed",
              .see = "https://snowball-lang.gitbook.io/docs/language-reference/classes"
            });
        }
        break;
      }
      case Token::Type::KwordStatic: {
        attrs.set_static(true);
        next();
        switch (current.type) {
          case Token::Type::KwordFunc:
          case Token::Type::KwordConst:
            break;
          default:
            err("Expected a class member after 'static' keyword", Error::Info {
              .highlight = fmt::format("Token '{}' is not expected here", current),
              .help = "At the class level, only class members are allowed",
              .see = "https://snowball-lang.gitbook.io/docs/language-reference/classes"
            });
        }
        break;
      }
      case Token::Type::KwordFunc: {
        auto fn = parse_fn_decl(attrs);
        result.funcs.push_back(fn);
        break;
      }
      case Token::Type::KwordConst: {
        sn_assert(false, "Const member not implemented yet");
      }
      case Token::Type::KwordVar: {
        auto var = parse_var_decl(attrs);
        result.vars.push_back(var);
        break;
      }
      default:
        err("Expected a class member", Error::Info {
          .highlight = fmt::format("Token '{}' is not expected here", current),
          .help = "At the class level, only class members are allowed",
          .see = "https://snowball-lang.gitbook.io/docs/language-reference/classes"
        });
    }
  }
  return result;
}

}
}
