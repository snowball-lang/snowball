
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "../services/OperatorService.h"
#include "./Parser.h"

#include <assert.h>
#define IS_CONSTRUCTOR(tk) is<TokenType::IDENTIFIER>(tk) && tk.value == name

namespace snowball::parser {

Syntax::Statement::DefinedTypeDef* Parser::parseClass() {
  assert(is<TokenType::KWORD_CLASS>());
  next(); // East "class"

  bool isPublic = false;
  if (is<TokenType::KWORD_PUBLIC, TokenType::KWORD_PRIVATE>(peek(-3, true))) {
    isPublic = is<TokenType::KWORD_PUBLIC>(peek(-3, true));
  }

  auto name = assert_tok<TokenType::IDENTIFIER>("class identifier").to_string();
  auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);

  Syntax::Expression::TypeRef* parentClass = nullptr;
  Syntax::Statement::GenericContainer<>::GenericList generics;

  if (is<TokenType::OP_LT>(peek())) {
    next();
    generics = parseGenericParams();
    prev();
  }

  next();
  if (is<TokenType::SYM_COLLON>()) {
    next();
    throwIfNotType();
    parentClass = parseType();
  }

  assert_tok<TokenType::BRACKET_LCURLY>("'{'");
  bool inPrivateScope = true;
  bool hasConstructor = false;

  auto cls = Syntax::N<Syntax::Statement::DefinedTypeDef>(
          name, parentClass, Syntax::Statement::Privacy::fromInt(isPublic));
  cls->setGenerics(generics);
  cls->setDBGInfo(dbg);
  auto classBackup = m_current_class;
  m_current_class = cls;
  while (true) {
    next();
    switch (m_current.type) {
      case TokenType::KWORD_PRIVATE: {
        inPrivateScope = true;
        next();
        assert_tok<TokenType::SYM_COLLON>("':'");
      } break;

      case TokenType::KWORD_PUBLIC: {
        inPrivateScope = false;
        next();
        assert_tok<TokenType::SYM_COLLON>("':'");
      } break;

      case TokenType::KWORD_STATIC: {
        auto pk = peek();
        if (pk.type != TokenType::KWORD_FUNC && pk.type != TokenType::KWORD_VAR &&
            pk.type != TokenType::KWORD_OPERATOR && (!IS_CONSTRUCTOR(pk))) {
          next();
          createError<SYNTAX_ERROR>("expected keyword \"func\", \"let\", \"operator\" or a "
                                    "constructor "
                                    "declaration after static member");
        }
      } break;

      case TokenType::KWORD_FUNC: {
        auto func = parseFunction();
        func->setPrivacy(Syntax::Statement::Privacy::fromInt(!inPrivateScope));
        cls->addFunction(func);
      } break;

      case TokenType::KWORD_OPERATOR: {
        auto func = parseFunction(false, true);
        func->setPrivacy(Syntax::Statement::Privacy::fromInt(!inPrivateScope));
        cls->addFunction(func);
      } break;

      case TokenType::KWORD_VIRTUAL: {
        auto pk = peek();
        if (pk.type == TokenType::KWORD_STATIC) {
          next();
          createError<ARGUMENT_ERROR>("Virtual methods can't be static!");
        } else if (pk.type != TokenType::KWORD_FUNC) {
          next();
          createError<SYNTAX_ERROR>("Expected keyword \"func\" after virtual declaration!");
        }
      } break;

      case TokenType::KWORD_VAR: {
        auto var = parseVariable();
        var->setPrivacy(Syntax::Statement::Privacy::fromInt(!inPrivateScope));
        cls->addVariable(var);

        assert_tok<TokenType::SYM_SEMI_COLLON>("a ';'");
      } break;

      case TokenType::BRACKET_RCURLY: {
        cls->hasConstructor = hasConstructor;
        m_current_class = classBackup;
        return cls;
      }

      case TokenType::KWORD_TYPEDEF: {
        auto typeDef = parseTypeAlias();
        typeDef->setPrivacy(Syntax::Statement::Privacy::fromInt(!inPrivateScope));
        cls->addTypeAlias(typeDef);

        assert_tok<TokenType::SYM_SEMI_COLLON>("a ';'");
      } break;

      // note: This case should be always at the bottom!
      case TokenType::IDENTIFIER: {
        if (IS_CONSTRUCTOR(m_current)) {
          hasConstructor = true;
          auto func = parseFunction(true);
          func->setPrivacy(Syntax::Statement::Privacy::fromInt(!inPrivateScope));
          func->setName(services::OperatorService::getOperatorMangle(services::OperatorService::CONSTRUCTOR));
          func->setStatic();
          cls->addFunction(func);
          break;
        }
      }

      default: {
        createError<SYNTAX_ERROR>(
                FMT("Unexpected token ('%s') found while parsing class body", m_current.to_string().c_str()));
      }
    }
  }
}

} // namespace snowball::parser
