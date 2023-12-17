
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "../services/OperatorService.h"
#include "../utils/utils.h"
#include "./Parser.h"

#include <assert.h>
#define TOKEN(comp) is<TokenType::comp>()

#define RIGHT_NEXT_TO(atPos, iPos) (atPos.first == iPos.first) && (atPos.second == (iPos.second - 1))

using Operators = snowball::services::OperatorService;

namespace snowball::parser {

Syntax::Expression::Base* Parser::parseExpr(bool allowAssign) {
  std::vector<Syntax::Expression::Base*> exprs;

  while (true) {
    auto tk = next();
    Syntax::Expression::Base* expr = nullptr;

    bool parseNormal = false;
    auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);

    if (TOKEN(SYM_HASH)) {
      if (TOKEN(SYM_HASH) && is<TokenType::IDENTIFIER>(peek())) {
        auto atPos = m_current.get_pos();
        next();
        auto iPos = m_current.get_pos();
        if (RIGHT_NEXT_TO(atPos, iPos)) {
          auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);

          dbg->pos.second++;
          dbg->width++;

          auto var = Syntax::N<Syntax::Expression::PseudoVariable>(m_current.to_string());
          var->setDBGInfo(dbg);
          expr = var;
        } else {
          prev();
          parseNormal = true;
        }
      } else
        parseNormal = true;
    } else if (TOKEN(IDENTIFIER), is<TokenType::OP_NOT>(peek())) {
      auto atPos = m_current.get_pos();
      atPos.second = atPos.second + m_current.to_string().size() - 1;
      auto name = m_current.to_string();
      next();
      auto iPos = m_current.get_pos();
      if (RIGHT_NEXT_TO(atPos, iPos)) {
        auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
        next();

        assert_tok<TokenType::BRACKET_LPARENT>("'('");
        dbg->width--;
        std::vector<Syntax::Node*> args;
        next();
        if (!is<TokenType::BRACKET_RPARENT>()) {
          prev(1);
          while (true) {
            next();
            auto pk = peek();
            if (is<TokenType::SYM_COLLON>(pk)) {
              next(1);
              args.push_back(parseType());
              prev();
            } else {
              args.push_back(parseStatement(pk));
            }
            if (is<TokenType::SYM_COMMA>(peek())) {
            } else {
              next();
              break;
            }
          }

          assert_tok<TokenType::BRACKET_RPARENT>("')'");
          auto var = Syntax::N<Syntax::Expression::PseudoVariable>(name);
          var->setDBGInfo(dbg);
          var->setArgs(args);
          expr = var;
        } else {
          auto var = Syntax::N<Syntax::Expression::PseudoVariable>(name);
          var->setDBGInfo(dbg);
          var->setArgs(args);
          expr = var;
        }
      } else {
        prev();
        parseNormal = true;
      }
    } else
      parseNormal = true;

    if (parseNormal) {
      if (TOKEN(BRACKET_LPARENT)) {
        expr = parseExpr(allowAssign);
        next();
        assert_tok<TokenType::BRACKET_RPARENT>("')'");
      } else if (TOKEN(VALUE_NUMBER) || TOKEN(VALUE_FLOAT) || TOKEN(VALUE_STRING) || TOKEN(VALUE_CHAR) || TOKEN(VALUE_BOOL)) {
        auto ty = Syntax::Expression::ConstantValue::deduceType(m_current.type);

        expr = Syntax::N<Syntax::Expression::ConstantValue>(ty, m_current.to_string());
      } else if (TOKEN(IDENTIFIER)) {
        if (is<TokenType::VALUE_STRING>(peek())) {
          auto identifier = m_current.to_string();
          auto atPos = m_current.get_pos();
          next();
          auto iPos = m_current.get_pos();
          if (RIGHT_NEXT_TO(atPos, iPos)) {
            auto ty = Syntax::Expression::ConstantValue::deduceType(m_current.type);
            expr = Syntax::N<Syntax::Expression::ConstantValue>(ty, m_current.to_string(), identifier);
          } else {
            prev();
          }
        }
        if (expr == nullptr)
          expr = parseIdentifier();
      } else if (TOKEN(KWORD_NEW)) {
        next();

        auto ty = parseType();
        assert_tok<TokenType::BRACKET_LPARENT>("'('");

        auto call = parseFunctionCall(ty);

        expr = Syntax::N<Syntax::Expression::NewInstance>(call, ty);
        expr->setDBGInfo(call->getDBGInfo());
      } else if (TOKEN(OP_NOT) || TOKEN(OP_PLUS) || TOKEN(OP_MINUS) || TOKEN(OP_BIT_NOT) || TOKEN(OP_BIT_AND) || TOKEN(OP_MUL)) {
        if (tk.type == TokenType::OP_NOT)
          exprs.push_back(Syntax::N<Syntax::Expression::BinaryOp>(Operators::OperatorType::NOT));
        else if (tk.type == TokenType::OP_PLUS)
          exprs.push_back(Syntax::N<Syntax::Expression::BinaryOp>(Operators::OperatorType::UPLUS));
        else if (tk.type == TokenType::OP_MINUS)
          exprs.push_back(Syntax::N<Syntax::Expression::BinaryOp>(Operators::OperatorType::UMINUS));
        else if (tk.type == TokenType::OP_BIT_NOT)
          exprs.push_back(Syntax::N<Syntax::Expression::BinaryOp>(Operators::OperatorType::BIT_NOT));
        else if (tk.type == TokenType::OP_BIT_AND) {
          exprs.push_back(Syntax::N<Syntax::Expression::BinaryOp>(Operators::OperatorType::REFERENCE));
          if (is<TokenType::KWORD_MUTABLE>(peek())) {
            next();
            ((Syntax::Expression::BinaryOp*)exprs.back())->isMutableReference = true;
          }          
        }
        else if (tk.type == TokenType::OP_MUL)
          exprs.push_back(Syntax::N<Syntax::Expression::BinaryOp>(Operators::OperatorType::DEREFERENCE));

        exprs.back()->isOperator = true;
        exprs.back()->setDBGInfo(dbg);
        continue;
      } else if (TOKEN(KWORD_FUNC)) {
        auto f = parseFunction(false, false, true);
        expr = Syntax::N<Syntax::Expression::LambdaFunction>(utils::cast<Syntax::Statement::BodiedFunction>(f));
        expr->setDBGInfo(f->getDBGInfo());
      } else {
        createError<SYNTAX_ERROR>(FMT("Expected a valid expression but got '%s'", m_current.to_string().c_str()));
      }
    }

    if (expr->getDBGInfo() == nullptr) expr->setDBGInfo(dbg);

    while (true) {
      tk = peek(0, true);
      if (is<TokenType::BRACKET_LPARENT>(tk)) {
        next();
        // auto callee = expr;
        expr = parseFunctionCall(expr);
      } else if (is<TokenType::BRACKET_LSQUARED>(tk)) {
        next();
        auto indexExpr = parseExpr(false);
        auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
        auto bop = Syntax::N<Syntax::Expression::BinaryOp>(Syntax::Expression::BinaryOp::OpType::INDEX);
        bop->isOperator = false;
        bop->setDBGInfo(dbg);
        next();
        assert_tok<TokenType::BRACKET_RSQUARED>("']'");

        bop->left = expr;
        bop->right = indexExpr;
        expr = bop;
      } else if (is<TokenType::SYM_COLCOL>(tk) || is<TokenType::SYM_DOT>(tk)) {
        auto isStatic = is<TokenType::SYM_COLCOL>(tk);
        auto x = peek(1, true);
        if (!isStatic && is<TokenType::SYM_DOT>(peek(1, true))) { // Range expr (1..5)
          auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
          auto bop = Syntax::N<Syntax::Expression::BinaryOp>(Syntax::Expression::BinaryOp::OpType::RANGE);
          bop->isOperator = false;
          bop->setDBGInfo(dbg);
          bop->left = expr;
          next(1);
          bop->right = parseExpr(false);
          expr = bop;
        } else {
          next(1);
          assert_tok<TokenType::IDENTIFIER>("an identifier");
          auto index = parseIdentifier();

          auto dbgInfo = new DBGSourceInfo(
                  m_source_info,
                  expr->getDBGInfo()->pos,
                  expr->getDBGInfo()->width + index->getDBGInfo()->width + 2
          );
          expr = Syntax::N<Syntax::Expression::Index>(expr, index, isStatic);
          expr->setDBGInfo(dbgInfo);
        }
      } else if (is<TokenType::KWORD_AS>(tk)) {
        next(1);
        throwIfNotType();

        auto ty = parseType();
        prev();

        auto dbgInfo = new DBGSourceInfo(
                m_source_info,
                expr->getDBGInfo()->pos,
                ty->getDBGInfo()->pos.second - expr->getDBGInfo()->pos.second + ty->getDBGInfo()->width
        );

        expr = Syntax::N<Syntax::Expression::Cast>(expr, ty);
        expr->setDBGInfo(dbgInfo);
      } else {
        break;
      }
    }

    bool valid = true;
    exprs.emplace_back(expr);
    services::OperatorService::OperatorType op_type;

    tk = peek();
#define OP_CASE(m_tk, m_op)                                                                                            \
  case TokenType::m_tk: {                                                                                              \
    op_type = services::OperatorService::OperatorType::m_op;                                                           \
    break;                                                                                                             \
  }
    switch (tk.type) {
      OP_CASE(OP_EQ, EQ);
      OP_CASE(OP_EQEQ, EQEQ);
      OP_CASE(OP_PLUS, PLUS);
      OP_CASE(OP_PLUSEQ, PLUSEQ);
      OP_CASE(OP_MINUS, MINUS);
      OP_CASE(OP_MINUSEQ, MINUSEQ);
      OP_CASE(OP_MUL, MUL);
      OP_CASE(OP_MULEQ, MULEQ);
      OP_CASE(OP_DIV, DIV);
      OP_CASE(OP_DIVEQ, DIVEQ);
      OP_CASE(OP_MOD, MOD);
      OP_CASE(OP_MOD_EQ, MOD_EQ);
      OP_CASE(OP_LT, LT);
      OP_CASE(OP_LTEQ, LTEQ);
      OP_CASE(OP_GT, GT);
      OP_CASE(OP_GTEQ, GTEQ);
      OP_CASE(OP_AND, AND);
      OP_CASE(OP_OR, OR);
      OP_CASE(OP_NOT, NOT);
      OP_CASE(OP_NOTEQ, NOTEQ);
      OP_CASE(OP_BIT_NOT, BIT_NOT);
      OP_CASE(OP_BIT_LSHIFT, BIT_LSHIFT);
      OP_CASE(OP_BIT_LSHIFT_EQ, BIT_LSHIFT_EQ);
      OP_CASE(OP_BIT_RSHIFT, BIT_RSHIFT);
      OP_CASE(OP_BIT_RSHIFT_EQ, BIT_RSHIFT_EQ);
      OP_CASE(OP_BIT_OR, BIT_OR);
      OP_CASE(OP_BIT_OR_EQ, BIT_OR_EQ);
      OP_CASE(OP_BIT_AND, BIT_AND);
      OP_CASE(OP_BIT_AND_EQ, BIT_AND_EQ);
      OP_CASE(OP_BIT_XOR, BIT_XOR);
      OP_CASE(OP_BIT_XOR_EQ, BIT_XOR_EQ);
      default: valid = false;
#undef OP_CASE
    }

    if (valid) {
      next(); // Eat peeked token.
      auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
      auto bop = Syntax::N<Syntax::Expression::BinaryOp>(op_type);
      bop->isOperator = true;
      bop->setDBGInfo(dbg);

      exprs.push_back(bop);
    } else {
      break;
    }
  }

  auto expr = buildOperatorTree(exprs);
  if (auto x = utils::cast<Syntax::Expression::BinaryOp>(expr)) {
    if (!allowAssign && Syntax::Expression::BinaryOp::is_assignment(x)) {
      createError<SYNTAX_ERROR>(
              expr->getDBGInfo()->pos, "assignment is not allowed inside expression.", {}, x->to_string().size()
      );
    }
  }

  return expr; // to remove warnings
}

} // namespace snowball::parser

#undef IF_TOKEN
