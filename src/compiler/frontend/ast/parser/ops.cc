
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
  switch (current.type) {
#include "compiler/frontend/ast/operators.def"
    default: valid = false;
  }
  if (valid) {
    auto bop = node<ast::BinaryOp>(type);
    bop->is_operator = true;
    exprs.push_back(bop);
  } 
  return !valid;
}

#undef DEFINE_OP

ast::Expr* Parser::fix_precedence(std::vector<ast::Expr*>& exprs) {
  if (exprs.size() == 1) {
    return exprs[0];
  }
  assert(exprs.size() > 0);
  while (exprs.size() > 1) {
    int next = -1;
    unsigned min_prec = 0xFFFFF;
    bool unary = false;
    for (size_t i = 0; i < exprs.size(); i++) {
      auto bop = exprs[i]->as<ast::BinaryOp>();
      if (!bop || !bop->is_operator) continue;
      auto prec = get_precedence(bop->get_op());
      if (prec < min_prec) {
        min_prec = prec;
        next = i;
        unary = false; // TODO: Unary operators
      }
    }
    assert(next != -1);
    if (unary) {
      sn_assert(false, "Unary operators not implemented");
      continue;
    }
    assert(next >= 1 && next < (int)exprs.size() - 1);
    assert(!(exprs[next - 1]->as<ast::BinaryOp>() && exprs[next - 1]->as<ast::BinaryOp>()->is_operator) ||
           !(exprs[next + 1]->as<ast::BinaryOp>() && exprs[next + 1]->as<ast::BinaryOp>()->is_operator));
    auto bop = exprs[next]->as<ast::BinaryOp>();
    auto lhs = exprs[next - 1];
    auto rhs = exprs[next + 1];
    bop->mutate_lhs(lhs);
    bop->mutate_rhs(rhs);
    bop->is_operator = false;
    exprs.erase(exprs.begin() + next + 1);
    exprs.erase(exprs.begin() + next - 1);
  }
  assert(exprs.size() == 1);
  return exprs[0];
}

unsigned int get_precedence(Operator op) {
  switch (op) {
    // TODO: Unary operators
    case Operator::New:
    case Operator::Delete:
    case Operator::Not:
    case Operator::BitNot:
      return 0;
    case Operator::Mul:
    case Operator::Div:
    case Operator::Mod:
      return 1;
    case Operator::Plus:
    case Operator::Minus:
      return 2;
    case Operator::BitRshift:
    case Operator::BitLshift:
      return 3;
    case Operator::Lt:
    case Operator::Lteq:
    case Operator::Gt:
    case Operator::Gteq:
      return 4;
    case Operator::Eqeq:
    case Operator::Noteq:
      return 5;
    case Operator::BitAnd:
      return 6;
    case Operator::BitXor:
      return 7;
    case Operator::BitOr:
      return 8;
    case Operator::And:
      return 9;
    case Operator::Or:
      return 10;
    case Operator::Eq:
    case Operator::Pluseq:
    case Operator::Minuseq:
    case Operator::Muleq:
    case Operator::Diveq:
    case Operator::ModEq:
    case Operator::BitLshiftEq:
    case Operator::BitRshiftEq:
    case Operator::BitAndEq:
    case Operator::BitXorEq:
    case Operator::BitOrEq:
      return 11;
    case Operator::Arrow: 
      // [[fallthrough]];
  }
  sn_unreachable();
}

}
}

#undef OP_CASE
