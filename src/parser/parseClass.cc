
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "../services/OperatorService.h"
#include "./Parser.h"

#include <assert.h>
#define IS_CONSTRUCTOR(tk) is<TokenType::IDENTIFIER>(tk) && tk.value == name

namespace snowball::parser {

Syntax::Statement::DefinedTypeDef* Parser::parseClass() {
  bool isInterface = is<TokenType::KWORD_INTER>();
  assert(is<TokenType::KWORD_CLASS>() || isInterface);

  next(); // East "class" or "interface"

  bool isPublic = false;
  bool extends = false;
  if (is<TokenType::KWORD_PUBLIC, TokenType::KWORD_PRIVATE>(peek(-3, true))) {
    isPublic = is<TokenType::KWORD_PUBLIC>(peek(-3, true));
  }

  std::unordered_map<Attributes, std::unordered_map<std::string, std::string>> attributes;
  if (is<TokenType::BRACKET_LSQUARED>() && is<TokenType::BRACKET_LSQUARED>(peek())) {
    attributes = parseAttributes([&](std::string attr) {
      if (attr == "extends") {
        extends = true;
        return Attributes::CLASS_EXTENDS;
      } else if (attr == "__internal__") {
        return Attributes::BUILTIN;
      }
      return Attributes::INVALID;
    });
  }

  std::string name;
  // TODO: check this is only for std lib builds!!!
  if (is<TokenType::OP_MUL>()) {
    next();
    if (is<TokenType::KWORD_MUTABLE>()) {
      name = _SNOWBALL_MUT_PTR;
    } else {
      assert_tok<TokenType::KWORD_CONST>("'const' or 'mut'");
      name = _SNOWBALL_CONST_PTR;
    }
  } else {
    name = assert_tok<TokenType::IDENTIFIER>("class identifier").to_string();
  }

  auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);

  Syntax::Expression::TypeRef* parentClass = nullptr;
  Syntax::Statement::GenericContainer<>::GenericList generics;
  std::vector<Syntax::Expression::TypeRef*> impls;

  if (is<TokenType::OP_LT>(peek())) {
    next();
    generics = parseGenericParams();
    prev();
  }

  next();
  if (is<TokenType::KWORD_EXTENDS>()) {
    next();
    throwIfNotType();
    parentClass = parseType();
  }

  if (is<TokenType::KWORD_IMPLEMENTS>()) {
    next();
    while (true) {
      impls.push_back(parseType());
      if (is<TokenType::SYM_COMMA>()) {
        next();
        continue;
      }

      break;
    }
  }

  assert_tok<TokenType::BRACKET_LCURLY>("'{'");
  bool inPrivateScope = true;
  bool hasConstructor = false;

  auto cls = Syntax::N<Syntax::Statement::DefinedTypeDef>(
          name,
          parentClass,
          Syntax::Statement::Privacy::fromInt(isPublic),
          isInterface ? Syntax::Statement::DefinedTypeDef::Type::INTERFACE :
                        Syntax::Statement::DefinedTypeDef::Type::CLASS
  );
  cls->setImpls(impls);
  cls->setGenerics(generics);
  cls->setDBGInfo(dbg);
  for (auto attr : attributes) cls->addAttribute(attr.first, attr.second);
  if (cls->hasAttribute(Attributes::BUILTIN) && name == "IntegerImpl") { cls->unsafeSetName(_SNOWBALL_INT_IMPL); }

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
        if (pk.type == TokenType::KWORD_MUTABLE) {
          next();
          createError<ARGUMENT_ERROR>(
                  "Static members can't be mutable!",
                  {.note = "To fix this error, you can remove the 'static' or 'mut' keyword.",
                   .help = "If you want to have a static mutable member, you can use a \nstatic pointer to a "
                           "mutable member."}
          );
        }

        if (pk.type != TokenType::KWORD_FUNC && pk.type != TokenType::KWORD_VAR &&
            pk.type != TokenType::KWORD_OPERATOR && pk.type != TokenType::KWORD_UNSAFE && (!IS_CONSTRUCTOR(pk))) {
          next();
          createError<SYNTAX_ERROR>("expected keyword \"fn\", \"let\", \"operator\", \"unsafe\" or a "
                                    "constructor "
                                    "declaration after static member");
        }
      } break;

      case TokenType::KWORD_UNSAFE: {
        auto pk = peek();
        if (pk.type != TokenType::KWORD_FUNC && pk.type != TokenType::KWORD_OPERATOR) {
          next();
          createError<SYNTAX_ERROR>("expected keyword \"fn\" or \"operator\" after unsafe declaration!");
        }
      } break;

      case TokenType::KWORD_FUNC: {
        auto func = parseFunction(false, false, false, isInterface);
        func->setPrivacy(Syntax::Statement::Privacy::fromInt(!inPrivateScope));
        cls->addFunction(func);
      } break;

      case TokenType::KWORD_OPERATOR: {
        auto func = parseFunction(false, true);
        func->setPrivacy(Syntax::Statement::Privacy::fromInt(!inPrivateScope));
        cls->addFunction(func);
      } break;

      case TokenType::KWORD_MUTABLE: {
        auto pk = peek();
        if (pk.type != TokenType::KWORD_FUNC && pk.type != TokenType::KWORD_OPERATOR &&
            pk.type != TokenType::KWORD_UNSAFE) {
          next();
          createError<SYNTAX_ERROR>("expected keyword \"fn\", \"unsafe\" or \"operator\" after mutable declaration!");
        }
      } break;

      case TokenType::KWORD_VIRTUAL: {
        auto pk = peek();
        if (pk.type == TokenType::KWORD_STATIC) {
          next();
          createError<ARGUMENT_ERROR>("Virtual methods can't be static!");
        } else if (extends) {
          next();
          createError<SYNTAX_ERROR>("Classes that extend other types can't have *new* virtual methods!");
        } else if (pk.type != TokenType::KWORD_FUNC && pk.type != TokenType::KWORD_MUTABLE) {
          next();
          createError<SYNTAX_ERROR>("Expected keyword \"fn\" or \"mut\" after virtual declaration!");
        }
      } break;

      case TokenType::KWORD_VAR: {
        auto var = parseVariable();
        var->setPrivacy(Syntax::Statement::Privacy::fromInt(!inPrivateScope));
        cls->addVariable(var);

        assert_tok<TokenType::SYM_SEMI_COLLON>("a ';'");
        if (extends) { createError<SYNTAX_ERROR>("Classes that extend other types can't have *new* variables!"); }
      } break;

      case TokenType::BRACKET_RCURLY: {
        cls->hasConstructor = hasConstructor;
        m_current_class = classBackup;
        return cls;
      }

      case TokenType::KWORD_TYPEDEF: {
        if (extends) {
          createError<SYNTAX_ERROR>("Classes that extend other types can't have *new* type aliases!");
        } else if (isInterface) {
          createError<SYNTAX_ERROR>("Interfaces can't have type aliases!");
        }

        auto typeDef = parseTypeAlias();
        typeDef->setPrivacy(Syntax::Statement::Privacy::fromInt(!inPrivateScope));
        cls->addTypeAlias(typeDef);

        assert_tok<TokenType::SYM_SEMI_COLLON>("a ';'");
        if (extends) { createError<SYNTAX_ERROR>("Classes that extend other types can't have *new* type aliases!"); }
      } break;

      // note: This case should be always at the bottom!
      case TokenType::IDENTIFIER: {
        if (IS_CONSTRUCTOR(m_current)) {
          if (isInterface) {
            createError<SYNTAX_ERROR>("Interfaces can't have constructors!");
          } else if (extends) {
            createError<SYNTAX_ERROR>("Classes that extend other types can't have *new* constructors!");
          }
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
                FMT("Unexpected token ('%s') found while parsing class body", m_current.to_string().c_str())
        );
      }
    }
  }
}

} // namespace snowball::parser
