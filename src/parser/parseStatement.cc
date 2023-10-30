
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

Syntax::Node* Parser::parseStatement(Token pk) {
  switch (pk.type) {
    case TokenType::_EOF: {
      next(); // eat EOF
      createError<UNEXPECTED_EOF>("Found an unexpected EOF while parsing a block");
    }

    case TokenType::KWORD_UNSAFE: {
      next(1);
      assert_tok<TokenType::BRACKET_LCURLY>("'{' expected after 'unsafe' keyword");
      auto b = parseBlock();
      b->addAttribute(Attributes::UNSAFE);
      return b;
    } break;

    case TokenType::BRACKET_LCURLY: {
      next();
      return parseBlock();
      break;
    }

    case TokenType::SYM_SEMI_COLLON: {
      next();
      break;
    }

    case TokenType::KWORD_BREAK:
    case TokenType::KWORD_CONTINUE: {
      next();
      return parseLoopControl();
      break;
    }

    case TokenType::KWORD_THROW: {
      next();
      return parseThrow();
      break;
    }

    case TokenType::KWORD_VAR: {
      next();
      return parseVariable();
      break;
    }

      // TODO: can const be declared at block level in rust?

    case TokenType::KWORD_FOR: {
      next();
      return parseForLoop();
      break;
    }

    case TokenType::KWORD_WHILE:
    case TokenType::KWORD_DO: {
      next();
      return parseWhile();
      break;
    }

    case TokenType::KWORD_TYPEDEF: {
      next();
      return parseTypeAlias();
      break;
    }

    case TokenType::KWORD_IF: {
      next();
      return parseConditional();
      break;
    }

    case TokenType::KWORD_TRY: {
      next();
      return parseTryCatch();
      break;
    }

    case TokenType::KWORD_RETURN: {
      next();
      return parseReturn();
      break;
    }

    default: {
      auto expr = parseExpr();
      if (auto x = utils::cast<Syntax::Expression::PseudoVariable>(expr)) { x->asStatement = true; }
      return expr;
    }
  }

  assert(false);
  return nullptr; // to remove warnings
}

} // namespace snowball::parser
