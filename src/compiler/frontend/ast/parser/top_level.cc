
#include <cassert>
#include <fmt/format.h>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"

namespace snowball {
namespace frontend {

ast::TopLevelAst Parser::parse_top_level(Token::Type terminator) {
  ast::TopLevelAst top_level;
  ast::AttributedNode global_attrs;
  while (!is(terminator)) {
    switch (current.type) {
      case Token::Type::KwordPublic:
      case Token::Type::KwordPrivate: {
        global_attrs.set_privacy(current.type == Token::Type::KwordPublic);
        next();
        switch (current.type) {
          case Token::Type::KwordFunc:
          case Token::Type::KwordStruct:
          case Token::Type::KwordEnum:
          case Token::Type::KwordStatic:
          case Token::Type::KwordConst:
          case Token::Type::KwordClass:
          case Token::Type::KwordInter:
          case Token::Type::KwordInline:
          case Token::Type::KwordAbstract:
          case Token::Type::KwordFinal:
          case Token::Type::KwordExtern:
          case Token::Type::KwordTypedef:
          case Token::Type::KwordUnsafe:
            break;
          default:
            err("Expected a top-level item after privacy modifier", Error::Info {
              .highlight = fmt::format("Token '{}' is not expected here", current),
              .help = "At the top-level, only top-level items are allowed",
              .see = "https://snowball-lang.gitbook.io/docs/language-reference/global-scope"
            });
        }
        break;
      }
      case Token::Type::KwordInline:
        global_attrs.set_inline(true);
        next();
        switch (current.type) {
          case Token::Type::KwordFunc:
          case Token::Type::KwordExtern:
          case Token::Type::KwordStatic:
          case Token::Type::KwordUnsafe:
            break;
          default:
            err("Expected a function declaration after 'inline' keyword", Error::Info {
              .highlight = fmt::format("Token '{}' is not expected here", current),
              .help = "At the top-level, only top-level items are allowed",
              .see = "https://snowball-lang.gitbook.io/docs/language-reference/global-scope"
            });
        }
        break;
      case Token::Type::KwordAbstract:
      case Token::Type::KwordFinal:
        if (is(Token::Type::KwordAbstract)) global_attrs.set_abstract(true);
        else global_attrs.set_final(true);
        next();
        switch (current.type) {
          case Token::Type::KwordClass:
            break;
          default:
            err("Expected a class or interface declaration after 'abstract' or 'final' keyword", Error::Info {
              .highlight = fmt::format("Token '{}' is not expected here", current),
              .help = "At the top-level, only top-level items are allowed",
              .see = "https://snowball-lang.gitbook.io/docs/language-reference/global-scope"
            });
        }
        break;
      case Token::Type::KwordStatic: 
        global_attrs.set_static(true);
        next();
        switch (current.type) {
          case Token::Type::KwordFunc:
          case Token::Type::KwordConst:
          case Token::Type::KwordExtern:
          case Token::Type::KwordUnsafe:
            break;
          default:
            err("Expected a top-level item after 'static' keyword", Error::Info {
              .highlight = fmt::format("Token '{}' is not expected here", current),
              .help = "At the top-level, only top-level items are allowed",
              .see = "https://snowball-lang.gitbook.io/docs/language-reference/global-scope"
            });
        }
        break;
      case Token::Type::KwordExtern:
        parse_extern_decl(global_attrs);
        break;
      case Token::Type::KwordFunc:
        top_level.push_back(parse_fn_decl(global_attrs));
        global_attrs = ast::AttributedNode();
        break;
      case Token::Type::KwordClass:
        top_level.push_back(parse_class_decl(global_attrs));
        global_attrs = ast::AttributedNode();
        break;
      case Token::Type::KwordUnsafe:
        global_attrs.set_unsafe(true);
        next();
        switch (current.type) {
          case Token::Type::KwordFunc:
          case Token::Type::KwordExtern:
          case Token::Type::KwordStatic:
          case Token::Type::KwordInline:
            break;
          default:
            err("Expected a top-level item after 'unsafe' keyword", Error::Info {
              .highlight = fmt::format("Token '{}' is not expected here", current),
              .help = "At the top-level, only top-level items are allowed",
              .see = "https://snowball-lang.gitbook.io/docs/language-reference/global-scope"
            });
        }
        break;
      default:
        err("Unexpected token found while parsing top-level", Error::Info {
          .highlight = fmt::format("Token '{}' is not expected here", current),
          .help = "At the top-level, only top-level items are allowed",
          .see = "https://snowball-lang.gitbook.io/docs/language-reference/global-scope"
        });
    }
  }
  return top_level;
}

void Parser::parse_extern_decl(ast::AttributedNode& node) {
  assert(is(Token::Type::KwordExtern));

  next();
  auto name = expect(Token::Type::ValueString, "a string literal for the external linkage name", {Token::Type::KwordVar, Token::Type::KwordFunc}).to_string();
  if (is(Token::Type::ValueString)) {
    if (name == "\"C\"") {
      node.set_external(ast::AttributedNode::C);
    } else if (name == "\"Snowball\"") {
      node.set_external(ast::AttributedNode::Snowball);
    } else if (name == "\"System\"") {
      node.set_external(ast::AttributedNode::System);
    } else {
      err(fmt::format("Invalid external linkage name '{}' found!", name), 
        Error::Info {
        .highlight = fmt::format("External linkage name '{}' is not expected here", name),
        .help = "Expected an external linkage name to be 'C', 'Snowball' or 'System'",
        .see = "https://snowball-lang.gitbook.io/docs/language-reference/functions/external-functions"
      }, Error::Type::Err, false);
    }
    next();
  }
  switch (current.type) {
    case Token::Type::KwordVar:
    case Token::Type::KwordFunc:
      break;
    default:
      err("Expected a top-level item after external linkage name", Error::Info {
        .highlight = fmt::format("Token '{}' is not expected here", current),
        .help = "At the top-level, only top-level items are allowed",
        .see = "https://snowball-lang.gitbook.io/docs/language-reference/global-scope"
      });
  }
}

}
}
