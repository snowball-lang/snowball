
#include "Parser.h"

#include <assert.h>

namespace snowball {
namespace parser {

Syntax::Macro* Parser::parseMacro() {
  assert(is<TokenType::KWORD_MACRO>());
  auto comment = parseDocstring(m_current.getComment());
  next();
  // TODO: expression macro: 'macro foo() = 1 + 1'
  auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
  bool isStatementMacro = true;
  auto attributes = verifyAttributes([&](std::string attr) {
                                     if (attr == "export") { return Attributes::EXPORT; }
                                     return Attributes::INVALID;
                                     });
  auto name = assert_tok<TokenType::IDENTIFIER>("an identifier for macro name").to_string();
  next();
  consume<TokenType::BRACKET_LPARENT>("'('");
  std::vector<std::tuple<std::string, Syntax::Macro::ArguementType, Syntax::Node*>> args;
  while (is<TokenType::IDENTIFIER>()) {
    auto name = m_current.to_string();
    next();
    consume<TokenType::SYM_COLLON>("':'");
    auto type = m_current.to_string();
    Syntax::Macro::ArguementType argType;
    if (type == "expr") {
      argType = Syntax::Macro::ArguementType::EXPRESSION;
    } else if (type == "type") {
      argType = Syntax::Macro::ArguementType::TYPE;
    } else if (type == "const") {
      argType = Syntax::Macro::ArguementType::CONSTANT;
      next();
      if (is<TokenType::BRACKET_LSQUARED>()) {
        next();
        auto val = assert_tok<TokenType::IDENTIFIER>("an identifier for constant value").to_string();
        next();
        assert_tok<TokenType::BRACKET_RSQUARED>("']'");
        if (val == "str") {
          argType = Syntax::Macro::ArguementType::CONSTANT_STRING;
        } else if (val == "num") {
          argType = Syntax::Macro::ArguementType::CONSTANT_NUMBER;
        } else if (val == "chr") {
          argType = Syntax::Macro::ArguementType::CONSTANT_CHAR;
        } else {
          createError<SYNTAX_ERROR>("Expected 'str', 'num', or 'chr' for constant type");
        }
      }
    } else if (type == "stmt") {
      argType = Syntax::Macro::ArguementType::STATEMENT;
    } else {
      createError<SYNTAX_ERROR>("Expected 'expr' or 'stmt' for macro arguement type");
    }
    Syntax::Node* defaultArg = nullptr;
    if (is<TokenType::OP_EQ>(peek())) {
      next();
      defaultArg = parseStatement(peek());
    }
    // TODO: check for existant args
    args.push_back(std::make_tuple(name, argType, defaultArg));
    next();
    if (is<TokenType::SYM_COMMA>()) {
      next();
    } else {
      break;
    }
  }
  consume<TokenType::BRACKET_RPARENT>("')'");
  if (is<TokenType::OP_EQ>()) {
    isStatementMacro = false;
    auto expr = parseExpr(false);
    auto macro = Syntax::N<Syntax::Macro>(
                 name, args, Syntax::N<Syntax::Block>(std::vector<Syntax::Node*> {expr}), isStatementMacro
                 );
    macro->setDBGInfo(dbg);
    for (auto[n, a] : attributes) { macro->addAttribute(n, a); }
    macro->setComment(comment);
    return macro;
  }
  assert_tok<TokenType::BRACKET_LCURLY>("'{'");
  auto body = parseBlock();
  auto macro = Syntax::N<Syntax::Macro>(name, args, body, isStatementMacro);
  macro->setDBGInfo(dbg);
  for (auto[n, a] : attributes) { macro->addAttribute(n, a); }
  macro->setComment(comment);
  return macro;
}

} // namespace parser
} // namespace snowball
