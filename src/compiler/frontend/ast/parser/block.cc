
#include <cassert>
#include <fmt/format.h>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"

#include "compiler/utils/utils.h"

namespace snowball {
namespace frontend {

ast::Block* Parser::parse_block(Token::Type terminator) {
  std::vector<ast::Node*> stmts;
  while (true) {
    auto pk = peek();
    if (is(terminator, pk)) {
      next();
      return node<ast::Block>(stmts);
    }
    if (is(Token::Type::SymSemiColon, pk)) {
      err("Excesive semicolons found!", Error::Info {
        .highlight = "Extra ';' found here",
        .help = "Remove the semicolon(s)",
        .note = "Semicolons are used to separate statements.\nThis semicolon is not needed here"
      }, Error::Type::Warn);
      while (is(Token::Type::SymSemiColon, peek())) next();
      continue;
    }
    stmts.push_back(parse_stmt(pk));
    if (is(terminator)) {
      prev();
      continue;
    }
  }
  assert(false);
}

}
}
