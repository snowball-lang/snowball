
#include "source_info.h"

#ifndef __SNOWBALL_LEXER_H_
#define __SNOWBALL_LEXER_H_

namespace snowball {

    class Lexer {

        public:
            Lexer(SourceInfo* p_source_info);

            void tokenize();

            ~Lexer() {};

    };
}

#endif // __SNOWBALL_LEXER_H_
