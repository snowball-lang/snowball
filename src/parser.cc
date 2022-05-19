
#include "snowball/nodes.h"
#include "snowball/colors.h"
#include "snowball/errors.h"
#include "snowball/parser.h"

#include <string>
#include <memory>
#include <assert.h>

#define ASSERT(x) assert(x);

#define PARSER_ERROR(err, msg) _parser_error(err, msg);
#define UNEXPECTED_TOK(expectation) PARSER_ERROR(Error::SYNTAX_ERROR, Logger::format("Expected an %s, got %s%s%s", expectation, RED, _current_token.to_string().c_str(), RESET));

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

        if (_current_token.type == TokenType::IDENTIFIER) {
            var->name = _current_token.to_string();
        } else {
            UNEXPECTED_TOK("an identifier");
        }

        return var;
    }

    std::unique_ptr<FunctionNode> Parser::_parse_function() {
        PARSER_ERROR(Error::TODO, "Functions are not yet supported.")

        // Assert if the token is the "func" keyword
        // and consume it.
        ASSERT(_current_token.type == TokenType::KWORD_FUNC)

        auto func = std::make_unique<FunctionNode>();
        next_token();

        // Find function's name
        if (_current_token.type == TokenType::IDENTIFIER) {

            // TODO: check if any variable, class or function exists with same name in the parent
            func->name = _current_token.to_string();
        } else {
            // TODO: maybe, anonimus functions?
            UNEXPECTED_TOK("an identifier")
        }

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
