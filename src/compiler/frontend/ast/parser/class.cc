
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
  std::vector<ast::TypeRef> implemented_interfaces;
  switch (current.type) {
    case Token::Type::KwordImplements: {
      next();
      while (!is(Token::Type::BracketLcurly)) {
        auto interface = parse_type_ref();
        implemented_interfaces.push_back(interface);
        if (is(Token::Type::BracketLcurly)) break;
        consume(Token::Type::SymComma, "a comma after the implemented interface", Token::Type::BracketLcurly);
      }
      break;
    }
    default: break;
  }
  auto block = parse_class_body();
  next(); // skip the closing curly brace
  auto cls = pnode<ast::ClassDecl>(pos, name, block.vars, block.funcs, ast::ClassDecl::ClassType::Class, generics, attrs);
  cls->set_implemented_interfaces(implemented_interfaces);
  return cls;
}

Parser::ParsingClassResult Parser::parse_class_body() { 
  ParsingClassResult result;
  ast::AttributedNode attrs;
  expect(Token::Type::BracketLcurly, "an opening curly brace after the return type");
  next();
  size_t vtable_index = 0;
  uint64_t member_count = 0;
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
          case Token::Type::KwordOperator:
          case Token::Type::KwordVirtual:
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
      case Token::Type::KwordOperator: {
        attrs.set_operator(true);
        next();
        switch (current.type) {
          case Token::Type::KwordFunc:
            break;
          default:
            err("Expected a class member after 'operator' keyword", Error::Info {
              .highlight = fmt::format("Token '{}' is not expected here", current),
              .help = "At the class level, only class members are allowed",
              .see = "https://snowball-lang.gitbook.io/docs/language-reference/classes"
            });
        }
        break;
      }
      case Token::Type::KwordFunc: {
        auto fn = parse_fn_decl(attrs);
        if (fn->get_virtual()) {
          fn->set_vtable_index({0, vtable_index++});
        }
        result.funcs.push_back(fn);
        attrs = ast::AttributedNode::empty();
        break;
      }
      case Token::Type::KwordConst: {
        sn_assert(false, "Const member not implemented yet");
      }
      case Token::Type::KwordVar: {
        auto var = parse_var_decl(attrs);
        var->set_member_index(member_count++);
        result.vars.push_back(var);
        attrs = ast::AttributedNode::empty();
        consume(Token::Type::SymSemiColon, "a semicolon after the variable declaration");
        break;
      }
      case Token::Type::KwordVirtual: {
        attrs.set_virtual(true);
        next();
        switch (current.type) {
          case Token::Type::KwordFunc:
          case Token::Type::KwordOperator:
            break;
          default:
            err("Expected a class member after 'virtual' keyword", Error::Info {
              .highlight = fmt::format("Token '{}' is not expected here", current),
              .help = "At the class level, only class members are allowed",
              .see = "https://snowball-lang.gitbook.io/docs/language-reference/classes"
            });
        }
        break;
      }
      case Token::Type::Identifier: // This must be the last case always!
        if (current.to_string() == "init") {
          attrs.set_operator(true);
          attrs.set_static(true);
          auto fn = parse_fn_decl(attrs, true);
          result.funcs.push_back(fn);
          attrs = ast::AttributedNode::empty();
          break;
        }
        [[fallthrough]];
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
