
#include "nodes.h"
#include "errors.h"
#include "parser.h"
#include <string>


namespace snowball {

    void Parser::parse() {
        while (true) {
            switch (_current_token.type)
            {
                case TokenType::_EOF:
                    return;

                case TokenType::KWORD_FUNC: {
                    FunctionNode function = _parse_function();
                    _functions.push_back(function);
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
    FunctionNode Parser::_parse_function() {
        FunctionNode func;

        func.name = "test";
        return func;
    }

    // Private
    void Parser::next_token(int p_offset) {
        try {
            __token_possition++;
            _current_token = _tokens.at(__token_possition);
        } catch (std::out_of_range& _) {
            DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, std::pair<int, int>(_current_token.line, _current_token.col), _current_token.to_string().size());
            throw ParserError(Error::BUG, "Index error", dbg_info);
        }
    }
}
