
#include "nodes.h"
#include "lexer.h"

#include <memory>

#ifndef __SNOWBALL_PARSER_H_
#define __SNOWBALL_PARSER_H_

namespace snowball {

    class Parser {

        public:

            struct ParserContext {
                bool is_test = false; // parsing in test declaration
                FunctionNode* current_function = nullptr;
                ClassNode* current_class = nullptr;
            };

            Parser(Lexer* p_lexer, SourceInfo* p_source_info) : _lexer(p_lexer) {
                _tokens = _lexer->tokens;
                _source_info = p_source_info;
                _current_token = _tokens[__token_possition];
            };

            void parse();

            std::vector<Node*> nodes() { return _nodes; }

            ~Parser() {};

        private:
            void next_token(int p_offset = 0);
            void previous_token(int p_offset = 0);
            Token peek(int p_offset = 0, bool p_safe = false);
            void _parser_error(Error type, std::string msg);

            // Parser methods
            Node* _parse_expression(bool p_allow_assign = false);
            ClassNode* _parse_class();
            VarNode* _parse_variable();
            ImportNode* _parse_import();
            ReturnNode* _parse_return();
            TestingNode* _parse_unittest();
            FunctionNode* _parse_function();
            IfStatementNode* _parse_ifstmt();
            CallNode* _parse_function_call();
            BlockNode* _parse_block(std::vector<TokenType> p_termination = { TokenType::BRACKET_RCURLY });
            Node* _build_op_tree(std::vector<Node*> &expressions);

            std::vector<std::string> _parse_generic_expr();

            // Variables
            Lexer* _lexer;
            Token _current_token;

            SourceInfo* _source_info;
            int __token_possition = 0;

            std::vector<Node*> _nodes;
            std::vector<Token> _tokens;

            ParserContext _context;
    };

}

#endif // __SNOWBALL_PARSER_H_
