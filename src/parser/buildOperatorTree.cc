
#include "../common.h"
#include "../services/OperatorService.h"
#include "../token.h"
#include "../utils/utils.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

ptr<Syntax::Expression::Base>
Parser::buildOperatorTree(std::vector<ptr<Syntax::Expression::Base>>& exprs) {
    assert(exprs.size() > 0);

    while (exprs.size() > 1) {
        int next_op        = -1;
        int min_precedence = 0xFFFFF;
        bool unary         = false;

        for (int i = 0; i < (int)exprs.size(); i++) {
            auto expression =
                static_cast<ptr<Syntax::Expression::BinaryOp>>(exprs[i]);
            if (!expression->isOperator) {
                continue;
            }

            int precedence = -1;
            switch (expression->op_type) {
                case Syntax::Expression::BinaryOp::OpType::NOT:
                case Syntax::Expression::BinaryOp::OpType::BIT_NOT:
                case Syntax::Expression::BinaryOp::OpType::UPLUS:
                case Syntax::Expression::BinaryOp::OpType::UMINUS: {
                    precedence = 0;
                    break;
                }

                case Syntax::Expression::BinaryOp::OpType::MUL:
                case Syntax::Expression::BinaryOp::OpType::DIV:
                case Syntax::Expression::BinaryOp::OpType::MOD: {
                    precedence = 1;
                    break;
                }

                case Syntax::Expression::BinaryOp::OpType::PLUS:
                case Syntax::Expression::BinaryOp::OpType::MINUS: {
                    precedence = 2;
                    break;
                }

                case Syntax::Expression::BinaryOp::OpType::BIT_LSHIFT:
                case Syntax::Expression::BinaryOp::OpType::BIT_RSHIFT: {
                    precedence = 3;
                    break;
                }

                case Syntax::Expression::BinaryOp::OpType::LT:
                case Syntax::Expression::BinaryOp::OpType::LTEQ:
                case Syntax::Expression::BinaryOp::OpType::GT:
                case Syntax::Expression::BinaryOp::OpType::GTEQ: {
                    precedence = 4;
                    break;
                }

                case Syntax::Expression::BinaryOp::OpType::EQEQ:
                case Syntax::Expression::BinaryOp::OpType::NOTEQ: {
                    precedence = 5;
                    break;
                }

                case Syntax::Expression::BinaryOp::OpType::BIT_AND: {
                    precedence = 6;
                    break;
                }

                case Syntax::Expression::BinaryOp::OpType::BIT_XOR: {
                    precedence = 7;
                    break;
                }

                case Syntax::Expression::BinaryOp::OpType::BIT_OR: {
                    precedence = 8;
                    break;
                }

                case Syntax::Expression::BinaryOp::OpType::AND: {
                    precedence = 9;
                    break;
                }

                case Syntax::Expression::BinaryOp::OpType::OR: {
                    precedence = 10;
                    break;
                }

                case Syntax::Expression::BinaryOp::OpType::EQ:
                case Syntax::Expression::BinaryOp::OpType::PLUSEQ:
                case Syntax::Expression::BinaryOp::OpType::MINUSEQ:
                case Syntax::Expression::BinaryOp::OpType::MULEQ:
                case Syntax::Expression::BinaryOp::OpType::DIVEQ:
                case Syntax::Expression::BinaryOp::OpType::MOD_EQ:
                case Syntax::Expression::BinaryOp::OpType::BIT_LSHIFT_EQ:
                case Syntax::Expression::BinaryOp::OpType::BIT_RSHIFT_EQ:
                case Syntax::Expression::BinaryOp::OpType::BIT_AND_EQ:
                case Syntax::Expression::BinaryOp::OpType::BIT_XOR_EQ:
                case Syntax::Expression::BinaryOp::OpType::BIT_OR_EQ: {
                    precedence = 11;
                    break;
                }

                default: {
                    precedence = -1;
                    break;
                }
            }

            if (precedence < min_precedence) {
                min_precedence = precedence;
                next_op        = i;
                auto op        = expression->op_type;
                unary = (op == Syntax::Expression::BinaryOp::OpType::NOT ||
                         op == Syntax::Expression::BinaryOp::OpType::BIT_NOT ||
                         op == Syntax::Expression::BinaryOp::OpType::UPLUS ||
                         op == Syntax::Expression::BinaryOp::OpType::UMINUS);
                // break;
            }
        }

        ASSERT(next_op >= 0);

        if (unary) {

            int next_expr = next_op;
            while (exprs[next_expr]->isOperator) {
                if (++next_expr == exprs.size()) {
                    createError<SYNTAX_ERROR>(
                        exprs[next_expr]->getDBGInfo()->pos,
                        "expected an expression.", "", 1);
                }
            }

            for (int i = next_expr - 1; i >= next_op; i--) {
                auto e =
                    utils::cast<Syntax::Expression::BinaryOp>(exprs[(size_t)i]);
                auto op_node = new Syntax::Expression::BinaryOp(e->op_type);
                op_node->setDBGInfo(e->getDBGInfo());

                op_node->left = exprs[(size_t)i + 1];

                exprs.at(i) = op_node;
                exprs.erase(exprs.begin() + i + 1);
            }
        } else {

            ASSERT(next_op >= 1 && next_op < (int)exprs.size() - 1)
            ASSERT(!(exprs[(size_t)next_op + 1]->isOperator) &&
                   !(exprs[(size_t)next_op - 1]->isOperator));

            auto e = utils::cast<Syntax::Expression::BinaryOp>(
                exprs[(size_t)next_op]);
            auto op_node = new Syntax::Expression::BinaryOp(e->op_type);
            op_node->setDBGInfo(e->getDBGInfo());

            if (exprs[(size_t)next_op - 1]->isOperator) {
                if (Syntax::Expression::BinaryOp::is_assignment(
                        (Syntax::Expression::BinaryOp *)
                            exprs[(size_t)next_op - 1])) {
                    createError<SYNTAX_ERROR>(
                        exprs[(size_t)next_op - 1]->getDBGInfo()->pos,
                        "unexpected assignment.", "", 1);
                }
            }

            if (exprs[(size_t)next_op + 1]->isOperator) {
                if (Syntax::Expression::BinaryOp::is_assignment(
                        (Syntax::Expression::BinaryOp *)
                            exprs[(size_t)next_op + 1])) {
                    createError<SYNTAX_ERROR>(
                        exprs[(size_t)next_op + 1]->getDBGInfo()->pos,
                        "unexpected assignment.", "", 1);
                }
            }

            op_node->left  = exprs[(size_t)next_op - 1];
            op_node->right = exprs[(size_t)next_op + 1];

            exprs.at((size_t)next_op - 1) = op_node;

            exprs.erase(exprs.begin() + next_op);
            exprs.erase(exprs.begin() + next_op);
        }
    }

    return exprs[0];
}

} // namespace snowball::parser

#undef IF_TOKEN
