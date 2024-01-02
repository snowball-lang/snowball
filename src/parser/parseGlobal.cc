
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Expression;

namespace snowball::parser {

Parser::NodeVec Parser::parseGlobal(TokenType terminator) {
  bool keep_parsing = true;
  std::vector<Syntax::Node*> global;

  while (keep_parsing) {
    if (terminator == m_current.type) {
      keep_parsing = false;
    } else {
      switch (m_current.type) {
        case TokenType::_EOF:
          // Unexpected because it shoud've been caught by the conditional above
          createError<SYNTAX_ERROR>("unexpected end of file");
        case TokenType::SYM_SEMI_COLLON: break;

        case TokenType::KWORD_MACRO: {
          global.push_back(parseMacro());
          break;
        }

        case TokenType::KWORD_PUBLIC:
        case TokenType::KWORD_PRIVATE: {
          auto pk = peek();
          if (!is<TokenType::KWORD_FUNC>(pk) && !is<TokenType::KWORD_VAR>(pk) && !is<TokenType::KWORD_TYPEDEF>(pk) && !is<TokenType::KWORD_STRUCT>(pk) &&
              !is<TokenType::KWORD_STATIC>(pk) && !is<TokenType::KWORD_UNSAFE>(pk) && !is<TokenType::KWORD_CLASS>(pk) &&
              !is<TokenType::KWORD_EXTERN>(pk) && !is<TokenType::KWORD_CONST>(pk) && !is<TokenType::KWORD_INTER>(pk)) {
            createError<SYNTAX_ERROR>("expected keyword \"func\", \"static\", \"unsafe\", \"class\", "
                                      "\"let\", \"const\" "
                                      "or "
                                      "\"extern\" after public/private declaration");
          }

          break;
        }

        case TokenType::SYM_AT: {
          parseAttributes();
          break;
        }

        case TokenType::KWORD_EXTERN: {
          auto pk = peek();
          if (!is<TokenType::KWORD_FUNC>(pk) && !is<TokenType::KWORD_CONST>(pk) && !is<TokenType::KWORD_UNSAFE>(pk)) {
            createError<SYNTAX_ERROR>("expected 'func' or 'const' keyword after an "
                                      "external symbol declaration");
          }

          break;
        }

        case TokenType::KWORD_STATIC: {
          auto pk = peek();
          if (!is<TokenType::KWORD_FUNC>(pk) && !is<TokenType::KWORD_UNSAFE>(pk)) {
            next();
            createError<SYNTAX_ERROR>("expected 'func' or 'unsafe' keyword after a "
                                      "static function declaration");
          }

          break;
        }

        case TokenType::KWORD_UNSAFE: {
          auto pk = peek();
          if (!is<TokenType::KWORD_FUNC>(pk)) {
            createError<SYNTAX_ERROR>("expected 'func' keyword after an "
                                      "unsafe function declaration");
          }

          break;
        }

        case TokenType::KWORD_NAMESPACE: {
          global.push_back(parseNamespace());
          break;
        }

        case TokenType::KWORD_ENUM: {
          global.push_back(parseEnum());
          break;
        }

        case TokenType::KWORD_STRUCT: {
          global.push_back(parseStructure());
          break;
        }

        case TokenType::KWORD_VAR: {
          global.push_back(parseVariable());
          break;
        }

        case TokenType::KWORD_CONST: {
          global.push_back(parseConstant());
          break;
        }

        case TokenType::KWORD_FUNC: {
          global.push_back(parseFunction());
          break;
        }

        case TokenType::KWORD_CLASS:
        case TokenType::KWORD_INTER: {
          global.push_back(parseClass());
          break;
        }

        case TokenType::KWORD_IMPORT: {
          global.push_back(parseImportStatement());
          break;
        }

        case TokenType::KWORD_TYPEDEF: {
          assertNoAttributes("type alias");
          global.push_back(parseTypeAlias());
          break;
        }

        default:
          createError<SYNTAX_ERROR>(FMT("Unexpected token ('%s') found", m_current.to_string().c_str()));
      }
    }

    if (keep_parsing && !is<TokenType::_EOF>(m_current)) next();
  }

  assertNoAttributes("after global or namespace declaration");
  return global;
}

} // namespace snowball::parser
