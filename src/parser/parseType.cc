

#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Expression;

namespace snowball::parser {

TypeRef* Parser::parseType() {
  throwIfNotType();
  assert(is<TokenType::OP_BIT_AND>() || is<TokenType::IDENTIFIER>() || is<TokenType::KWORD_DECLTYPE>() ||
         is<TokenType::KWORD_FUNC>() || is<TokenType::OP_AND>() || is<TokenType::OP_MUL>() ||
         is<TokenType::BRACKET_LPARENT>());
  auto pos = m_current.get_pos();
  auto dbg = new DBGSourceInfo(m_source_info, pos, m_current.get_pos().second - pos.second);
  if (is<TokenType::KWORD_DECLTYPE>()) {
    next();
    assert_tok<TokenType::BRACKET_LPARENT>("'('");
    auto expr = parseExpr(false);
    next();
    consume<TokenType::BRACKET_RPARENT>("')'");
    return Syntax::N<DeclType>(expr, dbg);
  } else if (is<TokenType::KWORD_FUNC>()) {
    std::vector<TypeRef*> fnArgs;
    next();
    assert_tok<TokenType::BRACKET_LPARENT>("'('");
    while (!is<TokenType::BRACKET_RPARENT>()) {
      next();
      if (is<TokenType::BRACKET_RPARENT>()) break;
      auto arg = parseType();
      fnArgs.push_back(arg);
      if (is<TokenType::SYM_COMMA>()) {
      } else if (is<TokenType::BRACKET_RPARENT>()) {
      } else {
        createError<SYNTAX_ERROR>("Expected ')' or ','");
      }
    }
    consume<TokenType::BRACKET_RPARENT>("')'");
    consume<TokenType::OP_ARROW>("'=>'");
    auto retType = parseType();
    return Syntax::N<FuncType>(fnArgs, retType, dbg);
  } else if (is<TokenType::BRACKET_LPARENT>()) {
    std::vector<TypeRef*> generics;
    while (true) {
      next();
      if (is<TokenType::BRACKET_RPARENT>()) break;
      auto arg = parseType();
      generics.push_back(arg);
      if (is<TokenType::SYM_COMMA>()) {
      } else if (is<TokenType::BRACKET_RPARENT>()) {
        break;
      } else {
        createError<SYNTAX_ERROR>("Expected ')' or ','");
      }
    }
    next();
    auto ty = Syntax::N<TupleType>(generics, dbg);
    return ty;
  }
  if (is<TokenType::OP_MUL>()) {
    next();
    if (is<TokenType::KWORD_CONST>()) {
      next();
      return Syntax::N<PointerType>(parseType(), false, dbg);
    } else if (is<TokenType::KWORD_MUTABLE>()) {
      next();
      return Syntax::N<PointerType>(parseType(), true, dbg);
    } else {
      createError<SYNTAX_ERROR>(
      "Expected 'const' or 'mut' after '*' (pointer type specifier)", {
        .note = "If you want to use '*' as a multiplication operator, use parentheses around the "
        "expression",
        .help = "check the documentation for more information "
        "(https://snowball-lang.gitbook.io/docs/language-reference/types/pointer-types)",
      }
      );
    }
  } else if (is<TokenType::OP_AND>()) { // we treat op and as 2 bit ands
    next();
    auto isMutable = is<TokenType::KWORD_MUTABLE>();
    if (isMutable) next();
    auto ref = Syntax::N<ReferenceType>(parseType(), dbg);
    ref->setMutable(isMutable);
    return ref;
  } else if (is<TokenType::OP_BIT_AND>()) {
    next();
    auto isMutable = is<TokenType::KWORD_MUTABLE>();
    if (isMutable) next();
    auto ref = Syntax::N<ReferenceType>(parseType(), dbg);
    ref->setMutable(isMutable);
    return ref;
  }
  bool isMutable = false;
  auto ident = parseIdentifier(true);
  Base* ast = ident;
  auto name = ident->getIdentifier();
  auto id = ident->getIdentifier();
  auto g = utils::cast<GenericIdentifier>(ast);
  auto generics = (g != nullptr) ? g->getGenerics() : std::vector<TypeRef*> {};
  next();
  while (is<TokenType::SYM_COLCOL>()) {
    next();
    auto i = parseIdentifier(true);
    name += "::" + i->getIdentifier();
    id += "." + i->getIdentifier();
    ast = Syntax::N<Index>(ast, i, true);
    ast->setDBGInfo(i->getDBGInfo());
    auto g = utils::cast<GenericIdentifier>(i);
    generics = (g != nullptr) ? g->getGenerics() : std::vector<TypeRef*> {};
    next();
  }
  auto t = Syntax::TR(ast, name, dbg, id);
  t->setGenerics(generics);
  t->setMutable(isMutable);
  return t;
}

} // namespace snowball::parser