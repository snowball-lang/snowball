
#include "Parser.h"

#include <assert.h>

namespace snowball {
namespace parser {

Syntax::Statement::ImportStmt* Parser::parseImportStatement() {
  assert(is<TokenType::KWORD_IMPORT>());
  auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
  next();
  auto attributes = verifyAttributes([&](std::string attr) {
                                     if (attr == "use_macro" || attr == "use_macros") { return Attributes::MACROS; }
                                     return Attributes::INVALID;
                                     });
  std::string package = assert_tok<TokenType::IDENTIFIER>("an identifier for package reference").to_string();
  next();
  std::vector<std::string> paths;
  std::string exportName;
  std::vector<std::pair<std::string, std::string>> vars;
  if (is<TokenType::SYM_COLCOL>()) {
    next();
    paths.push_back(assert_tok<TokenType::IDENTIFIER>("an identifier").to_string());
    next();
    if (is<TokenType::SYM_COLCOL>()) while (is<TokenType::SYM_COLCOL>()) {
        next();
        if (is<TokenType::IDENTIFIER>()) {
          paths.push_back(m_current.to_string());
        } else if (is<TokenType::SYM_DOT>() && is<TokenType::SYM_DOT>(peek())) {
          paths.push_back("..");
        } else if (is<TokenType::BRACKET_LCURLY>()) {
          // var imports
          next();
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
          break;
        } else {
          prev();
          break;
        }
        next();
      }
  }
  if (is<TokenType::KWORD_AS>()) {
    next();
    exportName = assert_tok<TokenType::IDENTIFIER>("an identifier for export name").to_string();
    next();
  }
  // TODO: handle all import types
  auto width = m_current.get_pos().second - dbg->pos.second;
  dbg->width = width;
  prev();
  auto import = Syntax::N<Syntax::Statement::ImportStmt>(paths, package, vars, exportName);
  import->setDBGInfo(dbg);
  for (auto[n, a] : attributes) { import->addAttribute(n, a); }
  return import;
}

} // namespace parser
} // namespace snowball
