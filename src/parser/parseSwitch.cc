
#include "../ast/types/PrimitiveTypes.h"
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Statement;
using namespace snowball::Syntax::Expression;

namespace snowball::parser {

Syntax::Statement::Switch* Parser::parseSwitch() {
  assert(is<TokenType::KWORD_CASE>() || is<TokenType::KWORD_SWITCH>());
  auto cStyleSwitch = is<TokenType::KWORD_SWITCH>();
  auto info = DBGSourceInfo::fromToken(m_source_info, m_current);
  
  Syntax::Expression::Base* expr = parseExpr();
  assert(expr);
  next();
  consume<TokenType::BRACKET_LCURLY>("'{' expected after 'case' expression");
  std::vector<Syntax::Statement::Switch::CaseBlock> cases;
  while (!is<TokenType::BRACKET_RCURLY>()) {
    auto pk = m_current;
    switch (pk.type) {
      case TokenType::IDENTIFIER: {
        if (!cStyleSwitch) {
          auto id = m_current.to_string();
          next();
          bool variadic = false;
          std::vector<std::string> args;
          if (is<TokenType::BRACKET_LPARENT>()) {
            next();
            while (!is<TokenType::BRACKET_RPARENT>()) {
              if (is<TokenType::SYM_DOT>() && is<TokenType::SYM_DOT>(peek()) && is<TokenType::SYM_DOT>(peek(1, true))) {
                variadic = true;
                next(2);
                break;
              } else {
                assert_tok<TokenType::IDENTIFIER>("identifier expected as case argument");
                args.push_back(m_current.to_string());
                next();
              }

              if (is<TokenType::SYM_COMMA>()) {
                next();
              } else if (!is<TokenType::BRACKET_RPARENT>()) {
                createError<SYNTAX_ERROR>("expected ',' or ')' after case argument");
              } else break;
            }
            assert_tok<TokenType::BRACKET_RPARENT>("')' expected after case arguments");
            next();
          }
          assert_tok<TokenType::OP_ARROW>("'=>' expected after case name");
          auto body = parseBlockOrStmt();
          cases.push_back(Syntax::Statement::Switch::CaseBlock{
            .expression = {nullptr, id}, 
            .args = args, 
            .isDefault = false,
            .isVariadic = variadic,
            .block = body,
          });
          pk = peek();
          if (!is<TokenType::BRACKET_RCURLY>(pk)) {
            next();
            consume<TokenType::SYM_COMMA>("',' expected after case block");
          }
          break;
        }
        __attribute__ ((fallthrough));
      }

      case TokenType::KWORD_DEFAULT: {
        next();
        assert_tok<TokenType::OP_ARROW>("'=>' expected after 'default' keyword");
        auto body = parseBlockOrStmt();
        cases.push_back(Syntax::Statement::Switch::CaseBlock{
          .expression = {nullptr, ""}, 
          .args = {}, 
          .isDefault = true,
          .isVariadic = false,
          .block = body,
        });
        next();
        if (is<TokenType::SYM_COMMA>()) {
          next();
        } else if (!is<TokenType::BRACKET_RCURLY>()) {
          createError<SYNTAX_ERROR>("expected ',' or '}' after case block");
        }
      } break;

      default: {
        if (cStyleSwitch) {
          prev();
          auto stmt = parseExpr(false);
          next();
          auto body = parseBlockOrStmt();
          cases.push_back(Syntax::Statement::Switch::CaseBlock{
            .expression = {stmt, ""},
            .args = {}, 
            .isDefault = false,
            .isVariadic = false,
            .block = body,
          });
          next();
          if (is<TokenType::SYM_COMMA>()) {
            next();
          } else if (!is<TokenType::BRACKET_RCURLY>()) {
            createError<SYNTAX_ERROR>("expected ',' or '}' after case block");
          }
          break;
        }
        createError<SYNTAX_ERROR>("expected 'case name' or 'default' keyword");
      } break;
    }
  }
  auto node = Syntax::N<Switch>(expr, cases, cStyleSwitch);
  node->setDBGInfo(info);

  return node;
}
} // namespace snowball::parser
