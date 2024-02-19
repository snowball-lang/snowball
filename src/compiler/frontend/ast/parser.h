
#ifndef __SNOWBALL_FRONTEND_AST_PARSER_H__
#define __SNOWBALL_FRONTEND_AST_PARSER_H__

#include <vector>
#include <memory>
#include <string>

#include "compiler/ctx.h"
#include "compiler/frontend/ast/token.h"
#include "compiler/reports/reporter.h"
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/location.h"
#include "compiler/frontend/ast/lexer.h"
#include "compiler/frontend/ast/module.h"

namespace snowball {
namespace frontend {

/**
 * @brief The Parser class is responsible for parsing a list of tokens into an AST.
 * The Parser class is responsible for parsing a list of tokens into an AST.
*/
class Parser : public Reporter {
  const Ctx ctx;
  std::vector<Token> tokens;
  unsigned int tok_index = 0;
  std::shared_ptr<SourceFile> file;
public:
  Parser(const Ctx& ctx, std::shared_ptr<SourceFile> file, const Lexer& lexer);
  ~Parser() = default;

  Module parse();

private:
  Token peek();
  void next();
  
  bool is(Token::Type type);
  bool is(Token::Type type, const Token& tok);

  const Token& expect(Token::Type type);
};

}
}

#endif // __SNOWBALL_FRONTEND_AST_PARSER_H_
