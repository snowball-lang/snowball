
#include <cassert>
#include <fmt/format.h>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"

#include "compiler/utils/utils.h"

namespace snowball {
namespace frontend {

ast::Use* Parser::parse_use(const ast::AttributedNode& attrs) {
  assert(is(Token::Type::KwordUse));
  auto location = loc();
  next();
  std::vector<ast::Use::Section> sections;
  while (is(Token::Type::Identifier) || is(Token::Type::BracketLparent)) {
    auto section = parse_use_section();
    sections.push_back(section);
    if (is(Token::Type::SymColcol)) {
      next();
    } else {
      break;
    }
  }
  for (size_t i = 0; i < sections.size(); i++) {
    auto& section = sections[i];
    for (auto& item : section.items) {
      if (item.alias.has_value() && i != sections.size() - 1) {
        err("Alias '{}' cant be defined in the middle of a use statement", Error::Info {
          .highlight = "Invalid alias definition",
          .help = "Move the alias definition to the end of the use statement"
        }, Error::Type::Err, false);
      } else if (i == sections.size() - 1 && !item.alias.has_value()) {
        // Add a default alias based on the last namespace path
        item.alias = item.path.get_last();
      }
    }
  }
  consume(Token::Type::SymSemiColon, "a semicolon after a use statement");
  return pnode<ast::Use>(location, sections, attrs);
}

ast::Use::Section Parser::parse_use_section() {
  assert(is(Token::Type::Identifier) || is(Token::Type::BracketLparent));
  std::vector<ast::Use::Item> items;
  if (is(Token::Type::BracketLparent)) {
    next();
    while (true) {
      NamespacePath path = NamespacePath::dummy();
      while (is(Token::Type::Identifier)) {
        path.push(current.to_string());
        next();
        if (is(Token::Type::SymColcol)) {
          next();
        } else {
          break;
        }
      }
      std::optional<std::string> alias;
      if (is(Token::Type::KwordAs)) {
        next();
        alias = current.to_string();
        next();
      }
      items.push_back(ast::Use::Item { path, alias });
      if (is(Token::Type::SymComma)) {
        next();
      } else {
        break;
      }
    }
    consume(Token::Type::BracketRparent, "a closing parenthesis after a namespace path");
  } else {
    auto path = NamespacePath { current.to_string() };
    next();
    std::optional<std::string> alias;
    if (is(Token::Type::KwordAs)) {
      next();
      alias = current.to_string();
      next();
    }
    items.push_back(ast::Use::Item { path, alias });
  }
  return ast::Use::Section { items };
}

}
}
