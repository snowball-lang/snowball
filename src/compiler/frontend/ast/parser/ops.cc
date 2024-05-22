
#include <cassert>
#include <optional>
#include <vector>
#include <fmt/format.h>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/ast/operators.h"

#include "compiler/utils/utils.h"

namespace snowball {
namespace frontend {

#define OP_CASE(tk, op) \
  case Token::Type::tk: { \
    type = Operator::op; \
    break; \
  }

#define DEFINE_OP(tk, name, _) \
  OP_CASE(tk, name)

bool Parser::parse_operator(std::vector<ast::Expr*>& exprs) {
  bool valid = true;
  Operator type;
  switch (peek().type) {
#include "compiler/frontend/ast/operators.def"
    default: valid = false;
  }
  if (valid) {
    next(); // Eat peeked token.
    auto bop = node<ast::BinaryOp>(type);
    exprs.push_back(bop);
  } 
  return valid;
}

}
}

#undef OP_CASE
