
#include "lexer.h"

#ifndef __SNOWBALL_PARSER_H_
#define __SNOWBALL_PARSER_H_

namespace snowball {

    class Parser {

        public:
            Parser(Lexer* p_lexer) : _lexer(p_lexer) { _current_token = _lexer->get_tokens().begin(); };
            void parse();

            ~Parser() {};

        private:
            Lexer* _lexer;
            std::vector<Token>::iterator _current_token;
    };

}

#endif // __SNOWBALL_PARSER_H_
