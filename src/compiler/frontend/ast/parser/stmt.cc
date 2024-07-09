
#include <cassert>
#include <optional>
#include <vector>
#include <fmt/format.h>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"

#include "compiler/utils/utils.h"

namespace snowball {
namespace frontend {

ast::Node* Parser::parse_stmt(const Token& peek) {
  auto expect_semi_ending = [&](ast::Node* node) {
    expect(Token::Type::SymSemiColon, "a semicolon to end the statement");
    return node;
  };
  switch (peek.type) {
    case Token::Type::Eof:
      err("Unexpected end of file while parsing statement!", Error::Info {
        .highlight = "The file has ended unexpectedly",
        .help = "Check if all the blocks are closed properly",
        .note = has_errors() ? "The previous error might have caused this" : ""
      });
      assert(false);
    case Token::Type::KwordVar:
      next();
      return expect_semi_ending(parse_var_decl(ast::AttributedNode::empty()));
    case Token::Type::KwordReturn:
      next();
      return expect_semi_ending(parse_return());
    case Token::Type::BracketLcurly: {
      next();
      return parse_block();
    }
    default: {
      auto expr = parse_expr();
      if (!is(Token::Type::SymSemiColon)) {
        return ast::Return::create(expr->get_location(), expr, /* implicit = */true);
      }
      return expr;
    }
  }
}

}
}

