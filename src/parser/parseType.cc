

#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Expression;

namespace snowball::parser {

TypeRef* Parser::parseType() {
  throwIfNotType();
  assert(is<TokenType::OP_BIT_AND>() || is<TokenType::IDENTIFIER>() || is<TokenType::KWORD_DECLTYPE>() || is<TokenType::KWORD_FUNC>());
  auto pos = m_current.get_pos();
  if (is<TokenType::KWORD_DECLTYPE>()) {
    auto w = m_current.get_width();
    next();
    assert_tok<TokenType::BRACKET_LPARENT>("'('");
    auto expr = parseExpr(false);
    next();
    consume<TokenType::BRACKET_RPARENT>("')'");
    auto dbg = new DBGSourceInfo(m_source_info, pos, w);
    return Syntax::N<DeclType>(expr, dbg);
  } else if (is<TokenType::KWORD_FUNC>()) {
    auto w = m_current.get_width();
    std::vector<TypeRef*> fnArgs;
    next();
    assert_tok<TokenType::BRACKET_LPARENT>("'('");
    while (!is<TokenType::BRACKET_RPARENT>()) {
      next();
      if (is<TokenType::BRACKET_RPARENT>()) break;
      auto arg = parseType();
      fnArgs.push_back(arg);
      if (is<TokenType::SYM_COMMA>()) {
        next();
      } else if (!is<TokenType::BRACKET_RPARENT>()) {
      } else {
        createError<SYNTAX_ERROR>("Expected ')' or ','");
      }
    }
    consume<TokenType::BRACKET_RPARENT>("')'");
    consume<TokenType::OP_ARROW>("'=>'");
    auto retType = parseType();
    auto dbg = new DBGSourceInfo(m_source_info, pos, w);
    auto ty = Syntax::N<FuncType>(fnArgs, retType, dbg);
    ty->setDBGInfo(dbg);
    return ty;
  }
  int referenceDepth = 0;
  while (is<TokenType::OP_BIT_AND>()) { // we treat op and as 2 bit ands
      referenceDepth++;
      next();
  }
  bool isMutable = false;
  if (is<TokenType::KWORD_MUTABLE>()) {
    isMutable = true;
    next();
  }
  auto ident = parseIdentifier(true);
  Base* ast = ident;
  auto name = ident->getIdentifier();
  auto id = ident->getIdentifier();
  auto g = utils::cast<GenericIdentifier>(ast);
  auto generics = (g != nullptr) ? g->getGenerics() : std::vector<TypeRef*>{};
  next();
  while (is<TokenType::SYM_COLCOL>()) {
    next();
    auto i = parseIdentifier(true);
    auto base = ast;
    name += "::" + i->getIdentifier();
    id += "." + i->getIdentifier();
    ast = Syntax::N<Index>(ast, i, true);
    ast->setDBGInfo(i->getDBGInfo());
    auto g = utils::cast<GenericIdentifier>(i);
    generics = (g != nullptr) ? g->getGenerics() : std::vector<TypeRef*>{};
    next();
  }
  auto dbg = new DBGSourceInfo(m_source_info, pos, m_current.get_pos().second - pos.second);
  auto t = Syntax::TR(ast, name, dbg, id);
  t->setGenerics(generics);
  t->setMutable(isMutable);
  for (int i = 0; i < referenceDepth; i++) {
    auto base = t;
    t = Syntax::N<ReferenceType>(base, dbg);
  }
  return t;
}

} // namespace snowball::parser