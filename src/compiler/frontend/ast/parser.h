
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

class StopParsing : public std::exception {
public:
  StopParsing() = default;
  ~StopParsing() = default;
};

/**
 * @brief The Parser class is responsible for parsing a list of tokens into an AST.
 * The Parser class is responsible for parsing a list of tokens into an AST.
*/
class Parser : public Reporter {
  const Ctx ctx;
  Token current;
  std::vector<Token> tokens;

  unsigned int tok_index = 0;
  std::shared_ptr<SourceFile> file;
public:
  Parser(const Ctx& ctx, const std::shared_ptr<SourceFile>& file, const std::vector<Token>& tokens);
  ~Parser() = default;

  Module parse();

private:
  Token peek(int offset = 0, bool safe = false);
  void next(int offset = 1);
  
  bool is(Token::Type type);
  bool is(Token::Type type, const Token& tok);

  void err(const std::string& message, const Error::Info& info = Error::Info(), 
    Error::Type type = Error::Type::Err, bool fatal = true);
  void _recover(Token::Type ty);
  const Token& expect(Token::Type type, const std::string& expectation);
  const Token& expect(Token::Type type, const std::string& expectation, Token::Type recover);

  template <typename... Args>
  void recover(Token::Type ty, Args&&... args) {
    add_error(E(std::forward<Args>(args)...), false);
    _recover(ty);
  }

  template <typename... Args>
  void consume(Args&&... args) {
    expect(std::forward<Args>(args)...);
    next();
  }

  // --- Parsing functions ---

  ast::TopLevelAst parse_top_level(Token::Type terminator = Token::Type::Eof);
  ast::FnDecl* parse_fn_decl();
};

}
}

#endif // __SNOWBALL_FRONTEND_AST_PARSER_H_
