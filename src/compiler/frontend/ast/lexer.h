
#ifndef __SNOWBALL_FRONTEND_AST_LEXER_H__
#define __SNOWBALL_FRONTEND_AST_LEXER_H__

#include <vector>

#include "compiler/ctx.h"
#include "compiler/frontend/ast/token.h"
#include "compiler/reports/reporter.h"

namespace snowball {
namespace frontend {

/**
 * @brief The Lexer class is responsible for lexing the source code into tokens.
 * 
 * The lexer takes care of absolutely everything that is needed to lex the 
 *  source code providing a simple interface to the user.
*/
class Lexer : public Reporter {
  const Ctx ctx;
  std::vector<Token> tokens;
  unsigned int line = 1;
  unsigned int column = 1;

  std::string buffer;
  unsigned int tok_index = 0;
public:
  Lexer(const Ctx& ctx);
  ~Lexer() = default;

  std::vector<Token> lex();
private:
  void add_token(const Token& token);
  void consume(Token::Type type, unsigned int length = 1U);

  void shoot_error(const std::string& message, const Error::Info& info = Error::Info(), Error::Type type = Error::Type::Err);
};

}
}

#endif // __SNOWBALL_FRONTEND_AST_LEXER_H_