
#include "../common.h"
#include "../services/OperatorService.h"
#include "../token.h"
#include "../utils/utils.h"
#include "./Parser.h"

#include <assert.h>
#define TOKEN(comp) is<TokenType::comp>()

namespace snowball::parser {

Syntax::Expression::Base* Parser::parseExpr(bool allowAssign) {
    std::vector<Syntax::Expression::Base*> exprs;

    auto parseIdentifier =
        [&](DBGSourceInfo* dbg) -> Syntax::Expression::Identifier* {
        if (is<TokenType::OP_LT>(peek()) &&
            is<TokenType::SYM_QUESTION>(peek(1, true))) {
            auto name = m_current.to_string();
            next();
            auto generics = parseGenericExpr();
            auto width = m_current.get_pos().second - dbg->pos.second;

            dbg->width = width;
            prev();

            auto i = Syntax::N<Syntax::Expression::GenericIdentifier>(name,
                                                                      generics);
            i->setDBGInfo(dbg);
            return i;
        } else {
            auto i = Syntax::N<Syntax::Expression::Identifier>(
                m_current.to_string());
            i->setDBGInfo(dbg);
            return i;
        }
    };

    while (true) {
        auto tk                            = next();
        Syntax::Expression::Base* expr = nullptr;

        auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
        if (TOKEN(VALUE_NUMBER) || TOKEN(VALUE_NULL) || TOKEN(VALUE_FLOAT) ||
            TOKEN(VALUE_STRING) || TOKEN(VALUE_CHAR)) {

            auto ty =
                Syntax::Expression::ConstantValue::deduceType(m_current.type);

            expr = Syntax::N<Syntax::Expression::ConstantValue>(
                ty, m_current.to_string());
        } else if (TOKEN(IDENTIFIER)) {
            expr = parseIdentifier(dbg);
        } else if (TOKEN(KWORD_NEW)) {
            next();
            auto ty   = parseType();
            auto call = parseFunctionCall(ty);

            expr = Syntax::N<Syntax::Expression::NewInstance>(call, ty);
            expr->setDBGInfo(call->getDBGInfo());
        } else {
            createError<SYNTAX_ERROR>(
                "Expected a valid expression but got '%s'",
                m_current.to_string().c_str());
        }

        if (expr->getDBGInfo() == nullptr) expr->setDBGInfo(dbg);

        while (true) {
            tk = peek(0, true);
            if (is<TokenType::BRACKET_LPARENT>(tk)) {
                next();
                // auto callee = expr;
                expr = parseFunctionCall(expr);
            } else if (is<TokenType::SYM_COLCOL>(tk) ||
                       is<TokenType::SYM_DOT>(tk)) {
                auto isStatic = is<TokenType::SYM_COLCOL>(tk);
                next(1);

                assert_tok<TokenType::IDENTIFIER>("an identifier");
                auto index = parseIdentifier(dbg);

                auto dbgInfo = new DBGSourceInfo(
                    m_source_info, expr->getDBGInfo()->pos,
                    expr->getDBGInfo()->width + index->getDBGInfo()->width +
                        (isStatic + 1));
                expr =
                    Syntax::N<Syntax::Expression::Index>(expr, index, isStatic);
                expr->setDBGInfo(dbgInfo);
            } else if (is<TokenType::KWORD_AS>(tk)) {
                next(1);
                assert_tok<TokenType::IDENTIFIER>("a type reference");
                auto ty = parseType();
                prev();

                auto dbgInfo = new DBGSourceInfo(
                    m_source_info, expr->getDBGInfo()->pos,
                    expr->getDBGInfo()->width + expr->getDBGInfo()->width + 2 +
                        ty->getDBGInfo()->width);

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
#define OP_CASE(m_tk, m_op)                                                    \
    case TokenType::m_tk: {                                                    \
        op_type = services::OperatorService::OperatorType::m_op;               \
        break;                                                                 \
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
            default:
                valid = false;
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
                expr->getDBGInfo()->pos,
                "assignment is not allowed inside expression.", "",
                x->to_string().size());
        }
    }

    return expr; // to remove warnings
}

} // namespace snowball::parser

#undef IF_TOKEN
