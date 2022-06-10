
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

            std::vector<Node> nodes() { return _nodes; }

            ~Parser() {};

        private:
            void next_token(int p_offset = 0);
            Token peek(int p_offset = 0, bool p_safe = false);
            void _parser_error(Error type, std::string msg);

            // Parser methods
            Node _parse_expression();
            VarNode _parse_variable();
            FunctionNode _parse_function();
            std::vector<Node> _parse_block(std::vector<TokenType> p_termination = { TokenType::BRACKET_RCURLY } );
            Node _build_op_tree(std::vector<Node> &expressions);

            // Variables
            Lexer* _lexer;
            Token _current_token;

            SourceInfo* _source_info;
            int __token_possition = 0;

            std::vector<Node> _nodes;
            std::vector<Token> _tokens;
    };

}

#endif // __SNOWBALL_PARSER_H_
