
#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>
#define TOKEN(comp) is<TokenType::comp>()

namespace snowball::parser {

ptr<Syntax::Expression::Base> Parser::parseExpr(bool allowAssign) {
    std::vector<ptr<Syntax::Expression::Base>> exprs;

    auto parseIdentifier =
        [&](ptr<DBGSourceInfo> dbg) -> ptr<Syntax::Expression::Identifier> {
        if (is<TokenType::OP_LT>(peek()) &&
            is<TokenType::SYM_QUESTION>(peek(1, true))) {
            auto name = m_current.to_string();
            next();
            auto generics = parseGenericExpr();
            auto width    = m_current.get_pos().second - dbg->pos.second;

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
        ptr<Syntax::Expression::Base> expr = nullptr;

        auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
        if (TOKEN(VALUE_NUMBER) || TOKEN(VALUE_NULL) || TOKEN(VALUE_FLOAT) ||
            TOKEN(VALUE_STRING) || TOKEN(VALUE_CHAR)) {

            auto ty =
                Syntax::Expression::ConstantValue::deduceType(m_current.type);

            expr = Syntax::N<Syntax::Expression::ConstantValue>(
                ty, m_current.to_string());
        } else if (TOKEN(IDENTIFIER)) {
            expr = parseIdentifier(dbg);
        }  else if (TOKEN(KWORD_NEW)) {
            next();
            auto ty = parseType();
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

        exprs.emplace_back(expr);
        bool valid = true;

        tk = peek();
        switch (tk.type) {
            default:
                valid = false;
        }

        if (valid) {
            // TODO:
            assert(false && "TODO: not valid expr");
        } else {
            break;
        }
    }

    auto expr = buildOperatorTree(exprs);

#if 0 // TODO:
    if (false/* TODO: check if it's an operator node */) {
        if (!allowAssign && BinaryOperator::is_assignment(expr)) {
            allowAssign(Error::SYNTAX_ERROR, "assignment is not allowed inside expression.");
        }
    }
#endif

    return expr; // to remove warnings
}

} // namespace snowball::parser

#undef IF_TOKEN
