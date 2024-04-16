
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
  auto comment = parseDocstring(m_current.getComment());
  next(); // East "class" or "interface"
  bool isPublic = false;
  bool extends = false;
  if (is<TokenType::KWORD_PUBLIC, TokenType::KWORD_PRIVATE>(peek(-3, true))) {
    isPublic = is<TokenType::KWORD_PUBLIC>(peek(-3, true));
  }
  auto attributes = verifyAttributes([&](std::string attr) {
                                       if (attr == "__internal__") {
                                         return Attributes::BUILTIN;
  } else if (attr == "no_constructor") {
    return Attributes::NO_CONSTRUCTOR;
  }
return Attributes::INVALID;
                                   });
  if (is<TokenType::KWORD_EXTENDS>()) {
    next();
    attributes[Attributes::CLASS_EXTENDS] = {};
    extends = true;
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
  bool hasGenerics = false;
  std::vector<Syntax::Expression::TypeRef*> impls;
  if (is<TokenType::OP_LT>(peek())) {
    next();
    hasGenerics = true;
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
  if (hasGenerics)
    cls->setGenerics(generics);
  cls->setDBGInfo(dbg);
  for (auto attr : attributes) cls->addAttribute(attr.first, attr.second);
  if (cls->hasAttribute(Attributes::BUILTIN)) {
    if (name == "IntegerImpl")
      cls->unsafeSetName(_SNOWBALL_INT_IMPL);
    else if (name == "FunctionImpl")
      cls->unsafeSetName(_SNOWBALL_FUNC_IMPL);
    else if (name != _SNOWBALL_CONST_PTR
             && name != _SNOWBALL_MUT_PTR) createError<ARGUMENT_ERROR>(FMT("Unknown builtin class '%s'", name.c_str()));
  }
  auto classBackup = m_current_class;
  m_current_class = cls;
  while (true) {
    next();
    switch (m_current.type) {
      case TokenType::KWORD_PRIVATE: {
        assertNoAttributes("before private keyword");
        inPrivateScope = true;
        next();
        assert_tok<TokenType::SYM_COLLON>("':'");
      } break;
      case TokenType::KWORD_PUBLIC: {
        assertNoAttributes("before public keyword");
        inPrivateScope = false;
        next();
        assert_tok<TokenType::SYM_COLLON>("':'");
      } break;
      case TokenType::KWORD_CONST: {
        assertNoAttributes("before const keyword");
        if (isInterface) {
          createError<SYNTAX_ERROR>("Interfaces can't have constants!");
        } else if (extends) {
          createError<SYNTAX_ERROR>("Classes that extend other types cant have *new* constants!");
        }
        auto var = parseConstant();
        var->setPrivacy(Syntax::Statement::Privacy::fromInt(!inPrivateScope));
        if (var->getValue() == nullptr) {
          createError<SYNTAX_ERROR>("expected a value for constant declaration!", {
            .note = "Static constants must have a value initialized because they don't "
                    "have a constructor to initialize them.",
            .help = "To fix this error, you can either remove the 'static' keyword or "
                    "initialize the constant with a value."
          });
        }
        cls->addVariable(var);
        assert_tok<TokenType::SYM_SEMI_COLLON>("a ';'");
      } break;
      case TokenType::KWORD_ENUM: {
        if (extends) {
          createError<SYNTAX_ERROR>("Classes that extend other types cant have *new* enums!");
        } else if (isInterface) {
          createError<SYNTAX_ERROR>("Interfaces can't have enums!");
        }
        auto enumDecl = parseEnum();
        enumDecl->setPrivacy(Syntax::Statement::Privacy::fromInt(!inPrivateScope));
        cls->addChildType(enumDecl);
      } break;
      case TokenType::SYM_AT: {
        parseAttributes();
      } break;
      case TokenType::KWORD_STATIC: {
        auto pk = peek();
        if (pk.type == TokenType::KWORD_MUTABLE) {
          next();
          createError<ARGUMENT_ERROR>(
          "Static members cant be mutable!", {
            .note = "To fix this error, you can remove the 'static' or 'mut' keyword.",
            .help = "If you want to have a static mutable member, you can use a \nstatic pointer to a "
            "mutable member."
          }
          );
        }
        if (pk.type != TokenType::KWORD_FUNC &&
            pk.type != TokenType::KWORD_OPERATOR && pk.type != TokenType::KWORD_UNSAFE && (!IS_CONSTRUCTOR(pk))
            && pk.type != TokenType::KWORD_OVERRIDE) {
          next();
          createError<SYNTAX_ERROR>("expected keyword \"func\", \"override\", \"let\", \"operator\", \"unsafe\" or a "
                                    "constructor "
                                    "declaration after static member");
        }
      } break;
      case TokenType::KWORD_OVERRIDE: {
        auto pk = peek();
        if (pk.type != TokenType::KWORD_FUNC && pk.type != TokenType::KWORD_OPERATOR && pk.type != TokenType::KWORD_UNSAFE
            && pk.type != TokenType::KWORD_MUTABLE && pk.type != TokenType::KWORD_VIRTUAL) {
          next();
          createError<SYNTAX_ERROR>("expected keyword \"func\" or \"operator\", \"unsafe\", \"mut\" or \"virtual\" "
                                    "after override declaration!");
        }
      } break;
      case TokenType::KWORD_UNSAFE: {
        auto pk = peek();
        if (pk.type != TokenType::KWORD_FUNC && pk.type != TokenType::KWORD_OPERATOR && pk.type != TokenType::KWORD_STATIC
            && pk.type != TokenType::KWORD_MUTABLE) {
          next();
          createError<SYNTAX_ERROR>("expected keyword \"func\" or \"operator\", \"static\" or \"mut\" after unsafe "
                                    "declaration!");
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
            pk.type != TokenType::KWORD_UNSAFE && pk.type != TokenType::KWORD_OVERRIDE) {
          next();
          createError<SYNTAX_ERROR>("expected keyword \"func\", \"unsafe\" or \"operator\" after mutable declaration!");
        }
      } break;
      case TokenType::KWORD_VIRTUAL: {
        auto pk = peek();
        if (pk.type == TokenType::KWORD_STATIC) {
          next();
          createError<ARGUMENT_ERROR>("Virtual methods cant be static!");
        } else if (extends) {
          next();
          createError<SYNTAX_ERROR>("Classes that extend other types cant have *new* virtual methods!");
        } else if (pk.type != TokenType::KWORD_FUNC && pk.type != TokenType::KWORD_MUTABLE) {
          next();
          createError<SYNTAX_ERROR>("Expected keyword \"func\" or \"mut\" after virtual declaration!");
        }
      } break;
      case TokenType::KWORD_VAR: {
        assertNoAttributes("a variable");
        auto var = parseVariable();
        var->setPrivacy(Syntax::Statement::Privacy::fromInt(!inPrivateScope));
        cls->addVariable(var);
        assert_tok<TokenType::SYM_SEMI_COLLON>("a ';'");
        if (extends) { createError<SYNTAX_ERROR>("Classes that extend other types cant have *new* variables!"); }
      } break;
      case TokenType::BRACKET_RCURLY: {
        assertNoAttributes("before '}'");
        cls->hasConstructor = hasConstructor;
        m_current_class = classBackup;
        cls->setComment(comment);
        return cls;
      }
      case TokenType::KWORD_TYPEDEF: {
        assertNoAttributes("a type alias");
        if (extends) {
          createError<SYNTAX_ERROR>("Classes that extend other types cant have *new* type aliases!");
        } else if (isInterface) {
          createError<SYNTAX_ERROR>("Interfaces can't have type aliases!");
        }
        auto typeDef = parseTypeAlias();
        typeDef->setPrivacy(Syntax::Statement::Privacy::fromInt(!inPrivateScope));
        cls->addChildType(typeDef);
        assert_tok<TokenType::SYM_SEMI_COLLON>("a ';'");
      } break;
      case TokenType::KWORD_CLASS:
      case TokenType::KWORD_INTER: {
        if (extends) {
          createError<SYNTAX_ERROR>("Classes that extend other types cant have *new* classes!");
        } else if (isInterface) {
          createError<SYNTAX_ERROR>("Interfaces can't have classes!");
        }
        auto innerClass = parseClass();
        innerClass->setPrivacy(Syntax::Statement::Privacy::fromInt(!inPrivateScope));
        cls->addChildType(innerClass);
      } break;
      case TokenType::KWORD_STRUCT: {
        if (extends) {
          createError<SYNTAX_ERROR>("Classes that extend other types cant have *new* structs!");
        } else if (isInterface) {
          createError<SYNTAX_ERROR>("Interfaces can't have structs!");
        }
        auto innerStruct = parseStructure();
        innerStruct->setPrivacy(Syntax::Statement::Privacy::fromInt(!inPrivateScope));
        cls->addChildType(innerStruct);
      } break;
      // note: This case should be always at the bottom!
      case TokenType::IDENTIFIER: {
        assertNoAttributes("before identifier");
        if (IS_CONSTRUCTOR(m_current)) {
          if (isInterface) {
            createError<SYNTAX_ERROR>("Interfaces can't have constructors!");
          } else if (extends) {
            // NOTE: If we end up allowing this, we need to make sure enums can't have constructors!
            createError<SYNTAX_ERROR>("Classes that extend other types cant have *new* constructors!");
          }
          hasConstructor = true;
          auto func = parseFunction(true);
          func->setPrivacy(Syntax::Statement::Privacy::fromInt(!inPrivateScope));
          func->setName(services::OperatorService::getOperatorMangle(services::OperatorService::CONSTRUCTOR));
          func->setStatic();
          cls->addFunction(func);
          break;
        }
        __attribute__((fallthrough));
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
