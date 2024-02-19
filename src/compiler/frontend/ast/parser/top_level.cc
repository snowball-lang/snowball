
#include <fmt/format.h>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"

namespace snowball {
namespace frontend {

ast::TopLevelAst Parser::parse_top_level(Token::Type terminator) {
  ast::TopLevelAst top_level;
  while (!is(terminator)) {
    switch (current.type) {
      case Token::Type::KwordFunc:
        top_level.push_back(parse_fn_decl());
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

}
}
