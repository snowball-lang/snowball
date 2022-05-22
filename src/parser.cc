
#include "snowball/nodes.h"
#include "snowball/colors.h"
#include "snowball/errors.h"
#include "snowball/parser.h"
#include "snowball/logger.h"

#include "snowball/snowball.h"

#include <string>
#include <memory>

#include <assert.h>

#define ASSERT(x) assert(x);

#define PARSER_ERROR(err, msg) _parser_error(err, msg);
#define UNEXPECTED_TOK(expectation) PARSER_ERROR(Error::SYNTAX_ERROR, Logger::format("Expected %s, got %s%s%s", expectation, RED, _current_token.to_string().c_str(), RESET));
#define ASSERT_TOKEN(tk, ty, idnt) if (tk.type != ty) UNEXPECTED_TOK(idnt);
#define ASSERT_TOKEN_EOF(tk, ty, idnt, method) \
    if (tk.type == TokenType::_EOF) PARSER_ERROR(Error::UNEXPECTED_EOF, Logger::format("Found an unexpected EOF while parsing %s", method)); \
    ASSERT_TOKEN(tk, ty, idnt)

namespace snowball {

    void Parser::parse() {
        while (true) {
            switch (_current_token.type)
            {
                case TokenType::_EOF:
                    return;

                case TokenType::KWORD_FUNC: {
                    std::unique_ptr<FunctionNode> function = _parse_function();
                    _functions.emplace_back(std::move(function));
                    break;
                }

                case TokenType::KWORD_VAR: {
                    std::unique_ptr<VarNode> var = _parse_variable();
                    break;
                }

                case TokenType::VALUE_UNDEFINED:
                case TokenType::SYM_SEMI_COLLON:
			    case TokenType::VALUE_STRING:
                case TokenType::VALUE_NUMBER:
                case TokenType::VALUE_FLOAT:
                case TokenType::VALUE_BOOL:
                    break;

                default:
                    PARSER_ERROR(Error::SYNTAX_ERROR, Logger::format("Unexpected token found: %s%s%s", BLU, _current_token.to_string().c_str(), RESET))
                    break;
            }

            next_token();
        }
    }

    // Parse methods

    std::unique_ptr<VarNode> Parser::_parse_variable() {
        ASSERT(_current_token.type == TokenType::KWORD_VAR)
        next_token();

        auto var = std::make_unique<VarNode>();
        ASSERT_TOKEN_EOF(_current_token, TokenType::IDENTIFIER, "an identifier", "variable")

        var->name = _current_token.to_string();
        next_token();

        ASSERT_TOKEN_EOF(_current_token, TokenType::OP_EQ, "=", "variable")
        next_token();

        if (_current_token.type == TokenType::_EOF) {
            PARSER_ERROR(Error::UNEXPECTED_EOF, "Found an unexpected EOF while parsing variable's statement");
        }

        // TODO: get return value
        _parse_expression();

        return var;
    }

    // TODO: return std::unique_ptr<Node>
    void Parser::_parse_expression() {
        std::vector<Node> expressions;

        while (true) {
            switch (_current_token.type)
            {
                case TokenType::IDENTIFIER:
                case TokenType::VALUE_BOOL:
                case TokenType::VALUE_NULL:
                case TokenType::VALUE_FLOAT:
                case TokenType::VALUE_NUMBER:
                case TokenType::VALUE_STRING:
                case TokenType::VALUE_UNDEFINED:
                    expressions.push_back(ConstantValue(_current_token.type, _current_token.to_string()));
                    break;

                case TokenType::OP_NOT:
                case TokenType::OP_PLUS:
                case TokenType::OP_MINUS:
                case TokenType::OP_BIT_NOT:

                    if (_current_token.type == TokenType::OP_NOT)     expressions.push_back(BinaryOp(BinaryOp::OpType::OP_NOT))     ;
                    if (_current_token.type == TokenType::OP_PLUS)    expressions.push_back(BinaryOp(BinaryOp::OpType::OP_PLUS))    ;
                    if (_current_token.type == TokenType::OP_MINUS)   expressions.push_back(BinaryOp(BinaryOp::OpType::OP_MINUS))   ;
                    if (_current_token.type == TokenType::OP_BIT_NOT) expressions.push_back(BinaryOp(BinaryOp::OpType::OP_BIT_NOT)) ;

                    break;

                case TokenType::_EOF:
                case TokenType::SYM_SEMI_COLLON:
                    break;

                default:
                    UNEXPECTED_TOK("a valid expression")
            }

            Token tk = peek(0, true);

            BinaryOp::OpType op;
            bool valid = true;

            switch (tk.type) {
            #define OP_CASE(m_op) case TokenType::m_op: op = BinaryOp::OpType::m_op; break;
                OP_CASE(OP_EQ);
                OP_CASE(OP_EQEQ);
                OP_CASE(OP_PLUS);
                OP_CASE(OP_PLUSEQ);
                OP_CASE(OP_MINUS);
                OP_CASE(OP_MINUSEQ);
                OP_CASE(OP_MUL);
                OP_CASE(OP_MULEQ);
                OP_CASE(OP_DIV);
                OP_CASE(OP_DIVEQ);
                OP_CASE(OP_MOD);
                OP_CASE(OP_MOD_EQ);
                OP_CASE(OP_LT);
                OP_CASE(OP_LTEQ);
                OP_CASE(OP_GT);
                OP_CASE(OP_GTEQ);
                OP_CASE(OP_AND);
                OP_CASE(OP_OR);
                OP_CASE(OP_NOT);
                OP_CASE(OP_NOTEQ);
                OP_CASE(OP_BIT_NOT);
                OP_CASE(OP_BIT_LSHIFT);
                OP_CASE(OP_BIT_LSHIFT_EQ);
                OP_CASE(OP_BIT_RSHIFT);
                OP_CASE(OP_BIT_RSHIFT_EQ);
                OP_CASE(OP_BIT_OR);
                OP_CASE(OP_BIT_OR_EQ);
                OP_CASE(OP_BIT_AND);
                OP_CASE(OP_BIT_AND_EQ);
                OP_CASE(OP_BIT_XOR);
                OP_CASE(OP_BIT_XOR_EQ);
            #undef OP_CASE

                default: valid = false;
            }

            if (valid) {
                next_token(); // Eat peeked token.
                expressions.push_back(BinaryOp(op));

                next_token();
            } else {
                break;
            }

        }

        for(int i = 0; i < expressions.size(); i++) {
            DUMP(expressions.at(i).type)
        }
    }

    std::unique_ptr<FunctionNode> Parser::_parse_function() {
        PARSER_ERROR(Error::TODO, "Functions are not yet supported.")

        // Assert if the token is the "func" keyword
        // and consume it.
        ASSERT(_current_token.type == TokenType::KWORD_FUNC)

        auto func = std::make_unique<FunctionNode>();
        next_token();

        // Find function's name
        ASSERT_TOKEN(_current_token, TokenType::IDENTIFIER, "an identifier")
        func->name = _current_token.to_string();

        next_token();
        switch (_current_token.type)
        {
            case TokenType::BRACKET_LPARENT:
                break;

            case TokenType::BRACKET_LCURLY:
                break;

            default:
                UNEXPECTED_TOK(Logger::format("a %sleft curly bracket%s or a %sleft parenthesis%s", BLU, RESET, BLU, RESET).c_str())
                break;
        }

        return func;
    }

    // Private
    void Parser::next_token(int p_offset) {
        try {
            __token_possition++;
            _current_token = _tokens.at(__token_possition);
        } catch (std::out_of_range& _) {
            PARSER_ERROR(Error::BUG, "Index error")
        }
    }

    Token Parser::peek(int p_offset, bool p_safe) {
        Token tmp = { TokenType::_EOF };
        if ((__token_possition + 1) + p_offset < 0 || (__token_possition + 1) + p_offset >= (int)_tokens.size()) {
            if (p_safe) return tmp;
            else PARSER_ERROR(Error::BUG, "Parser::peek() index out of bounds");
        }
        return _tokens.at((__token_possition + 1) + p_offset);
    }

    void Parser::_parser_error(Error type, std::string msg) {
        DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, std::pair<int, int>(_current_token.line, _current_token.col), _current_token.to_string().size());
        throw ParserError(type, msg, dbg_info);
    }
}
