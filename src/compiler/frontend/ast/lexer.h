
#ifndef __SNOWBALL_FRONTEND_AST_LEXER_H__
#define __SNOWBALL_FRONTEND_AST_LEXER_H__

#include "compiler/ctx.h"
#include "compiler/frontend/ast/token.h"

namespace snowball {
namespace frontend {

/**
 * @brief The Lexer class is responsible for lexing the source code into tokens.
 * 
 * The lexer takes care of absolutely everything that is needed to lex the 
 *  source code providing a simple interface to the user.
*/
class Lexer {
  const Ctx ctx;
  std::vector<Token> tokens;
public:
  Lexer(const Ctx& ctx);
  ~Lexer() = default;

  std::vector<Token> lex();
};

}
}

#endif // __SNOWBALL_FRONTEND_AST_LEXER_H_