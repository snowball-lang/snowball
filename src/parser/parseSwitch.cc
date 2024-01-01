
#include "../ast/types/PrimitiveTypes.h"
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Statement;
namespace snowball::parser {

Syntax::Statement::Switch* Parser::parseSwitch() {
  assert(is<TokenType::KWORD_SWITCH>());

  auto info = DBGSourceInfo::fromToken(m_source_info, m_current);
  next();
  
  Syntax::Expression::Base* expr = parseExpr();
  assert(expr);

  assert_tok<TokenType::BRACKET_LCURLY>("'{' expected after 'case' keyword");
  std::vector<Syntax::Statement::Switch::CaseBlock> cases;
  while (!is<TokenType::BRACKET_RCURLY>()) {
    auto pk = peek();
    switch (pk.type) {
      case TokenType::IDENTIFIER: {
        auto id = m_current.to_string();
        next();
        bool variadic = false;
        std::vector<std::string> args;
        if (is<TokenType::BRACKET_LPARENT>()) {
          next();
          while (!is<TokenType::BRACKET_LPARENT>()) {
            args.push_back(m_current.to_string());
            next();
            if (is<TokenType::SYM_COMMA>()) {
              next();
            }
            if (is<TokenType::SYM_DOT>() && is<TokenType::SYM_DOT>(peek(1)) && is<TokenType::SYM_DOT>(peek(2, true))) {
              variadic = true;
              next(3);
              break;
            }
          }
          assert_tok<TokenType::BRACKET_RPARENT>("')' expected after case arguments");
          next();
        }
        assert_tok<TokenType::OP_ARROW>("'->' expected after case name");
        auto body = parseBlockOrStmt();
        cases.push_back(Syntax::Statement::Switch::CaseBlock{
          .expression = id, 
          .args = args, 
          .isDefault = false,
          .isVariadic = variadic,
          .block = body,
        });
      } break;

      case TokenType::KWORD_DEFAULT: {
        next();
        assert_tok<TokenType::OP_ARROW>("'->' expected after 'default' keyword");
        auto body = parseBlockOrStmt();
        cases.push_back(Syntax::Statement::Switch::CaseBlock{
          .expression = "", 
          .args = {}, 
          .isDefault = true,
          .isVariadic = false,
          .block = body,
        });
      } break;

      default: {
        next();
        createError<SYNTAX_ERROR>("case name or 'default' keyword");
      } break;
    }
  }
  next();
  auto node = Syntax::N<Switch>(expr, cases);
  node->setDBGInfo(info);

  return node;
}
} // namespace snowball::parser
