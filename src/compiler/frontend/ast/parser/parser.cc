

#include <cassert>

#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/ast/nodes.h"
#include "compiler/utils/utils.h"

namespace snowball {
namespace frontend {

Parser::Parser(const Ctx& ctx, const std::shared_ptr<SourceFile>& file, const std::vector<Token>& tokens)
    : ctx(ctx), file(file), tokens(tokens) {
  assert(!tokens.empty());
  current = tokens[0]; // we know that there is at least one token
}

Module Parser::parse() {
  try {
    return Module(parse_top_level());
  } catch (const StopParsing&) {
    return Module(ast::TopLevelAst()); // we are gonna error out anyway
  }
}

Token Parser::peek(int offset, bool safe) {
  if (tok_index + offset >= tokens.size()) {
    if (safe) {
      return Token { 
        .type = Token::Type::Eof, 
        .location = std::make_pair(0, 0)
      };
    }
    sn_assert(false, "Unexpected end of file");
  }
  return tokens[tok_index + offset];
}

void Parser::next(int offset) {
  tok_index += offset;
  current = tokens[tok_index];
}

bool Parser::is(Token::Type type) {
  return current.type == type;
}

bool Parser::is(Token::Type type, const Token& tok) {
  return tok.type == type;
}

void Parser::err(const std::string& message, const Error::Info& info, Error::Type type, bool fatal) {
  SourceLocation loc(current.location.first, current.location.second, current.get_width(), file);
  add_error(E(message, loc, info, type));
  if (fatal) {
    throw StopParsing();
  }
}

const Token& Parser::expect(Token::Type type, const std::string& expectation) {
  return expect(type, expectation, Token::Type::Eof);
}

const Token& Parser::expect(Token::Type type, const std::string& expectation, Token::Type recover) {
  if (is(type)) {
    auto& tok = current;
    return tok;
  }
  err(fmt::format("Unexpected token '{}' found!", current), Error::Info {
    .highlight = fmt::format("Token '{}' is not expected here", current),
    .help = fmt::format("Expected a token to satisfy '{}'", expectation),
    .note = has_errors() ? "This error might be caused by error recovery activated by another\nerror before this one" : ""
  }, Error::Type::Err, recover == Token::Type::Eof);
  _recover(recover); // It already skips Eof if it is Eof
  return current;
}

void Parser::_recover(Token::Type ty) {
  while (!is(ty) && !is(Token::Type::Eof)) {
    next();
  }
  if (is(ty)) {
    next();
  } else {
    err("Unexpected end of file while trying to recover from a previous error", Error::Info {
      .highlight = "Unexpected end of file",
      .help = "Found an unexpected end of file while trying to recover from a previous error",
      .note = "This error might be caused by error recovery activated by another\nerror before this one"
    }, Error::Type::Err, true);
  }
}

}
}