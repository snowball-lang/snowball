
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
  switch (peek.type) {
    case Token::Type::Eof:
      err("Unexpected end of file", Error::Info {
        .highlight = "The file has ended unexpectedly",
        .help = "Check if all the blocks are closed properly"
      });
      assert(false);
    default:
      return parse_expr();
  }
}

}
}

