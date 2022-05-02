

#ifndef __SNOWBALL_PARSER_H_
#define __SNOWBALL_PARSER_H_

namespace snowball {


    class Parser {

        public:
            Parser(Lexer* p_lexer) : _lexer(p_lexer) {};
            void parse();

            ~Parser() {};

        private:
            Lexer* _lexer;
    }

}

#endif // __SNOWBALL_PARSER_H_
