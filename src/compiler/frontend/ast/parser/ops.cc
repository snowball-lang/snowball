
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
    int min_prec = 0xFFFFF;
    bool unary = false;
    for (size_t i = 0; i < exprs.size(); i++) {
      auto bop = exprs[i]->as<ast::BinaryOp>();
      if (!bop) continue;
      int prec = -1;
      switch (bop->get_op()) {
        // TODO: Unary operators
        case Operator::New:
        case Operator::Delete:
        case Operator::Not:
        case Operator::BitNot:
          prec = 0;
          break;
        case Operator::Mul:
        case Operator::Div:
        case Operator::Mod:
          prec = 1;
          break;
        case Operator::Plus:
        case Operator::Minus:
          prec = 2;
          break;
        case Operator::BitRshift:
        case Operator::BitLshift:
          prec = 3;
          break;
        case Operator::Lt:
        case Operator::Lteq:
        case Operator::Gt:
        case Operator::Gteq:
          prec = 4;
          break;
        case Operator::Eqeq:
        case Operator::Noteq:
          prec = 5;
          break;
        case Operator::BitAnd:
          prec = 6;
          break;
        case Operator::BitXor:
          prec = 7;
          break;
        case Operator::BitOr:
          prec = 8;
          break;
        case Operator::And:
          prec = 9;
          break;
        case Operator::Or:
          prec = 10;
          break;
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
          prec = 11;
          break;
        case Operator::Arrow: 
          break;
      }
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
    auto bop = exprs[next]->as<ast::BinaryOp>();
    auto lhs = exprs[next - 1];
    auto rhs = exprs[next + 1];
    bop->mutate_lhs(lhs);
    bop->mutate_rhs(rhs);
    exprs.erase(exprs.begin() + next + 1);
    exprs.erase(exprs.begin() + next - 1);
  }
  assert(exprs.size() == 1);
  return exprs[0];
}

}
}

#undef OP_CASE
