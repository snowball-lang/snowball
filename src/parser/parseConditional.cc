
#include "../ast/types/PrimitiveTypes.h"
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Statement;
using namespace snowball::Syntax;
namespace snowball::parser {

Statement::Base* Parser::parseConditional() {
  assert(is<TokenType::KWORD_IF>());
  auto info = DBGSourceInfo::fromToken(m_source_info, m_current);
  // If the next token is a constexpr, then this is a compile-time conditional.
  if (is<TokenType::KWORD_CONSTEXPR>(peek())) {
    createError<TODO>("Compile-time conditionals are not yet supported");
    next();
    auto attrs = parseAttributes(true);
    next();
    auto block = parseBlock();
    //auto node = Syntax::N<ConditionalConstExpr>(block);
    //for (auto [n, a] : verifyAttributes([](auto _) { return Attributes::INVALID; }, attrs)) { node->addAttribute(n, a); }
    //node->setDBGInfo(info);
    //return node;
  }
  // Otherwise, parse a runtime conditional.
  auto expr = parseExpr(false);
  next();
  auto block = parseBlock();
  Block* elseBlock = nullptr;
  if (is<TokenType::KWORD_ELSE>(peek())) {
    next();
    elseBlock = parseBlockOrStmt();
  }
  auto node = Syntax::N<Conditional>(expr, block, elseBlock);
  node->setDBGInfo(info);
  return node;
}
} // namespace snowball::parser
