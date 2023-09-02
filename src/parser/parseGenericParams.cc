

#include "../common.h"
#include "../lexer/tokens/token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Expression;

namespace snowball::parser {

std::vector<Syntax::Expression::Param*> Parser::parseGenericParams() {
  assert(is<TokenType::OP_LT>());
  std::vector<Syntax::Expression::Param*> params;
  while (true) {
    next();
    if (is<TokenType::_EOF>()) {
      createError<UNEXPECTED_EOF>("Found an unexpected EOF while "
                                  "parsing generic declaration");
    } else if (is<TokenType::IDENTIFIER>()) {
      // Get the current name for the parameter
      auto name = m_current.to_string();
      // Define the default type. The default
      // value is a null pointer, meaning that
      // there are no default parameters defined.
      TypeRef* default_ty = nullptr;
      // Statements to be executed in order to perform
      // checks for the selected generics.
      WhereClause* whereClause = nullptr;
      // Consume identifier
      next();
      // Parse [where_clause]
      if (is<TokenType::SYM_COLLON>()) whereClause = parseWhereClause();
      // "=" [default_type]
      if (is<TokenType::OP_EQ>()) {
        next();
        default_ty = parseType();
      }
      // Generate a new parameter instance
      auto param = new Param(name, default_ty, Param::Generic);
      param->setWhereClause(whereClause);
      params.push_back(param);
      if (is<TokenType::OP_GT>()) {
        next();
        break;
      } else if (is<TokenType::SYM_COMMA>() && is<TokenType::IDENTIFIER>(peek(0, true))) {
        continue;
      }
      assert_tok<TokenType::OP_GT>("a ',', ':' or a '>'");
    } else if (is<TokenType::OP_GT>()) {
      next();
      break;
    } else {
      createError<SYNTAX_ERROR>(FMT("Expected a vaid generic declaration but got '%s'", m_current.to_string().c_str()),
              {.info = "Unexpected token here"});
    }
  }
  return params;
}

} // namespace snowball::parser
