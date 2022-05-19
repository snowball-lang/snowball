
#include "nodes.h"
#include "lexer.h"

#include <memory>

#ifndef __SNOWBALL_PARSER_H_
#define __SNOWBALL_PARSER_H_

namespace snowball {

    class Parser {

        public:
            Parser(Lexer* p_lexer, SourceInfo* p_source_info) : _lexer(p_lexer) {
                _tokens = _lexer->tokens;
                _source_info = p_source_info;
                _current_token = _tokens[__token_possition];
            };

            void parse();

            ~Parser() {};

        private:
            void next_token(int p_offset = 0);
            Token peek(int p_offset = 0, bool p_safe = false);
            void _parser_error(Error type, std::string msg);

            // Parser methods
            std::unique_ptr<FunctionNode> _parse_function();
            std::unique_ptr<VarNode> _parse_variable();

            // Variables
            Lexer* _lexer;
            Token _current_token;

            SourceInfo* _source_info;
            int __token_possition = 0;

            std::vector<Token> _tokens;

            std::vector<std::unique_ptr<FunctionNode>> _functions;
    };

}

#endif // __SNOWBALL_PARSER_H_
