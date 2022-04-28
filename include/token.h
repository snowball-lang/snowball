
#include <string>

#ifndef __SNOWBALL_TOKEN_H_
#define __SNOWBALL_TOKEN_H_

namespace snowball {
    enum Token {
        TOK_EOF = -1,

        TOK_IDNT, TOK_NUMBER,
        KEY_DEF, KEY_EXTRN
    };
}

#endif // __SNOWBALL_TOKEN_H_
