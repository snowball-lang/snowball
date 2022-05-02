
#include "token.h"
#include "errors.h"
#include "logger.h"
#include "source_info.h"

#include <vector>

#ifndef __SNOWBALL_LEXER_H_
#define __SNOWBALL_LEXER_H_

namespace snowball {

    class Lexer {

        public:
            Lexer(SourceInfo* p_source_info);

            void tokenize();

            ~Lexer() {};

        private:
            // methods
            void handle_eof();
            void tokenize_char();
            void consume(TokenType p_tk, int p_eat_size = 1);
            void lexer_error(Error m_error, std::string m_msg, int char_length = 1);

            // vars
            SourceInfo* _source_info;

            int cur_line = 1;
            int cur_col = 1;

            int char_ptr = 0;
            std::vector<Token> _tokens;
    };
}

#endif // __SNOWBALL_LEXER_H_
