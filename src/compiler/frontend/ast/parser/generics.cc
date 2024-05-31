
#include <cassert>
#include <optional>
#include <vector>
#include <fmt/format.h>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"

#include "compiler/utils/utils.h"

namespace snowball {
namespace frontend {

std::optional<ast::GenericNode<>> Parser::parse_generics() {
  if (is(Token::Type::OpLt)) {
    next();
    std::vector<ast::GenericDecl> generics;
    while (!is(Token::Type::OpGt)) {
      std::vector<ast::TypeRef> constraints;
      auto name = expect(Token::Type::Identifier, "an identifier for the generic name", {Token::Type::OpGt, Token::Type::SymComma}).to_string();
      if (is(Token::Type::SymColon, peek())) {
        next();
        while (true) {
          next();
          constraints.push_back(parse_type_ref());
          if (is(Token::Type::OpPlus)) {
            next();
            continue;
          }
          break;
        }
      }
      generics.push_back(ast::GenericDecl::create(name, constraints));
      if (is(Token::Type::OpGt)) break; // we recover from this error
      else if (is(Token::Type::SymComma)) continue;
      next();
      // TODO: parse constraints and default values
      if (is(Token::Type::SymComma)) {
        next();
      } else break;
    }
    if (generics.empty()) {
      err("Empty generic expression", Error::Info { 
        .highlight = "No generic types found",  
        .help = "Remove the '<>' or add a type inside it",
        .see = "https://snowball-lang.gitbook.io/docs/language-reference/generics"
      }, Error::Type::Warn);
    }
    next();
    return generics;
  }
  return std::nullopt;  
}

}
}

