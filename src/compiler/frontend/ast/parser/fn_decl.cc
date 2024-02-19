
#include <cassert>
#include <fmt/format.h>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"

#include "compiler/utils/utils.h"

namespace snowball {
namespace frontend {

ast::FnDecl* Parser::parse_fn_decl() {
  assert(is(Token::Type::KwordFunc));
  next();

  auto name = expect(Token::Type::Identifier, "an identifier for the function name", Token::Type::BracketLparent)
    .to_string();
  next();
  //auto params = parse_params();
  consume(Token::Type::BracketLparent, "an open parenthesis after the function name", Token::Type::BracketLcurly);

  sn_assert(false, "Functions Not Implemented Yet");
}

}
}
