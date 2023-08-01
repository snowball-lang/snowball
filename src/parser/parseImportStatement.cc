
#include "Parser.h"

#include <assert.h>

namespace snowball {
namespace parser {

Syntax::Statement::ImportStmt* Parser::parseImportStatement() {
  assert(is<TokenType::KWORD_IMPORT>());
  auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
  next();

  std::map<Attributes, std::map<std::string, std::string>> attributes;
  if (is<TokenType::BRACKET_LSQUARED>() && is<TokenType::BRACKET_LSQUARED>(peek())) {
    attributes = parseAttributes([&](std::string attr) {
      if (attr == "use_macro" || attr == "use_macros") { return Attributes::MACROS; }
      return Attributes::INVALID;
    });
  }

  std::string package = assert_tok<TokenType::IDENTIFIER>("an identifier for package reference").to_string();
  next();

  consume<TokenType::SYM_COLCOL>("'::'");
  std::vector<std::string> paths;
  paths.push_back(assert_tok<TokenType::IDENTIFIER>("an identifier").to_string());
  next();

  std::vector<std::pair<std::string, std::string>> vars;
  while (is<TokenType::SYM_COLCOL>()) {
    next();
    if (is<TokenType::IDENTIFIER>()) {
      paths.push_back(m_current.to_string());
    } else if (is<TokenType::SYM_DOT>() && is<TokenType::SYM_DOT>(peek())) {
      paths.push_back("..");
    } else if (is<TokenType::BRACKET_LCURLY>() && is<TokenType::BRACKET_LCURLY>(peek())) {
      // var imports
      next(1);
      while (!is<TokenType::BRACKET_RCURLY>()) {
        if (is<TokenType::IDENTIFIER>()) {
          std::string name = m_current.to_string();
          std::string alias = name;
          next();
          if (is<TokenType::KWORD_AS>()) {
            next();
            alias = assert_tok<TokenType::IDENTIFIER>("an identifier for variable alias").to_string();
            next();
          }
          vars.push_back({name, alias});
          if (is<TokenType::SYM_COMMA>()) {
            next();
          } else {
            break;
          }
        } else {
          createError<SYNTAX_ERROR>("an identifier for variable import");
        }
      }

      consume<TokenType::BRACKET_RCURLY>("'}'");
      consume<TokenType::BRACKET_RCURLY>("'}'");
      createError<TODO>("variable imports");
      break;
    } else {
      prev();
      break;
    }

    next();
  }

  // TODO: handle all import types
  prev();
  auto import = Syntax::N<Syntax::Statement::ImportStmt>(paths, package);

  auto width = m_current.get_pos().second - dbg->pos.second;
  dbg->width = width;
  import->setDBGInfo(dbg);
  for (auto [n, a] : attributes) { import->addAttribute(n, a); }
  return import;
}

} // namespace parser
} // namespace snowball
