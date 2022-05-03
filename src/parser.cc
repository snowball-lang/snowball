
#include "nodes.h"
#include "errors.h"
#include "parser.h"

#include <string>
#include <memory>
#include <assert.h>

#define ASSERT(x) assert(x);
#define PARSER_ERROR(err, msg) _parser_error(err, msg);

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

                case TokenType::SYM_SEMI_COLLON:
			    case TokenType::VALUE_STRING:
                case TokenType::VALUE_BOOL:
                case TokenType::VALUE_NUMBER:
                case TokenType::VALUE_FLOAT:
                    break;

                default:
                    break;
            }

            next_token();
        }
    }

    // Parse methods
    std::unique_ptr<FunctionNode> Parser::_parse_function() {
        auto func = std::make_unique<FunctionNode>();

        // Assert if the token is the "func" keyword
        // and consume it.
        ASSERT(_current_token.type == TokenType::KWORD_FUNC)
        next_token();

        // Find function's name
        if (_current_token.type == TokenType::IDENTIFIER) {

            // TODO: check if any variable, class or function exists with same name in the parent
            func->name = _current_token.to_string();
        } else {
            // TODO: maybe, anonimus functions?
            PARSER_ERROR(Error::SYNTAX_ERROR, Logger::format("Expected an identifier, got \"%s\"", _current_token.to_string().c_str()))
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
