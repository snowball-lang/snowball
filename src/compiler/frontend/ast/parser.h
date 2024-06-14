
#ifndef __SNOWBALL_FRONTEND_AST_PARSER_H__
#define __SNOWBALL_FRONTEND_AST_PARSER_H__

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "compiler/ctx.h"
#include "compiler/frontend/ast/lexer.h"
#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/ast/token.h"
#include "compiler/frontend/location.h"
#include "compiler/reports/reporter.h"

#include "compiler/frontend/attrs/attr.h"
#include "compiler/frontend/attrs/interp.h"

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

  ast::attrs::AttrInterpreter& attr_interpreter;

public:
  Parser(const Ctx& ctx, const std::shared_ptr<SourceFile>& file,
         const std::vector<Token>& tokens, ast::attrs::AttrInterpreter& attr_interpreter);
  ~Parser() = default;

  Parser(const Parser&) = delete;
  Parser& operator=(const Parser&) = delete;

  Module parse();

private:
  Token peek(int offset = 0, bool safe = false);
  void next(int offset = 1);
  void prev();

  bool is(Token::Type type);
  bool is(Token::Type type, const Token& tok);
  SourceLocation loc() const;

  void
  err(const std::string& message, const Error::Info& info = Error::Info(),
      Error::Type type = Error::Type::Err, bool fatal = true);
  void _recover(std::vector<Token::Type> tys);

  const Token& expect(Token::Type type, const std::string& expectation);
  const Token&
  expect(Token::Type type, const std::string& expectation, Token::Type recover);
  const Token&
  expect(Token::Type type, const std::string& expectation,
         std::vector<Token::Type> recover);

  bool run_attr_interpreter(const std::vector<ast::attrs::Attr>& attrs,
                            ast::attrs::AttrInterpreter::Target target = std::nullopt);

  template <typename T, typename... Args>
  void recover(T ty, Args&&... args) {
    add_error(E(std::forward<Args>(args)...), false);
    _recover(ty);
  }

  template <typename... Args>
  void consume(Args&&... args) {
    expect(std::forward<Args>(args)...);
    next();
  }

  template <typename T, typename... Args>
  [[nodiscard]] auto node(Args&&... args) {
    return pnode<T>(loc(), std::forward<Args>(args)...);
  }

  template <typename T, typename... Args>
  [[nodiscard]] auto pnode(const SourceLocation& loc, Args&&... args) {
    // Create a new node with the given location and arguments
    return T::create(loc, std::forward<Args>(args)...);
  }

  // --- Parsing functions ---

  ast::TopLevelAst parse_top_level(Token::Type terminator = Token::Type::Eof);
  std::optional<ast::GenericNode<>> parse_generics(); // only if present
  ast::GenericNode<ast::TypeRef> parse_generics_expr();
  ast::FnDecl* parse_fn_decl(const ast::AttributedNode& attrs, bool is_constructor = false);
  ast::TypeRef parse_type_ref();
  ast::Node* parse_stmt(const Token& peek);
  ast::Expr* parse_expr(bool allow_assign = true);
  ast::VarDecl* parse_var_decl(ast::AttributedNode attrs);
  ast::Block* parse_block(Token::Type terminator = Token::Type::BracketRcurly);
  ast::ClassDecl* parse_class_decl(const ast::AttributedNode& attrs);
  ast::ClassDecl* parse_interface_decl(const ast::AttributedNode& attrs);
  ast::Return* parse_return();
  ast::attrs::Attr parse_attr();

#include "compiler/frontend/ast/parser_utils.def"
};

} // namespace frontend
} // namespace snowball

#endif // __SNOWBALL_FRONTEND_AST_PARSER_H_
