
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

#include "compiler/frontend/ast/lexer.h"
#include "compiler/frontend/ast/token.h"
#include "compiler/utils/utils.h"
#include "compiler/globals.h"

#define GET_CHAR(offset) buffer[tok_index + offset] 

namespace snowball {
namespace frontend {

Lexer::Lexer(const Ctx& ctx) : ctx(ctx) {}

std::vector<Token> Lexer::lex() {
  std::vector<Token> tokens;
  buffer = globals::read_file(ctx.input_file);

  while (tok_index < buffer.size()) {
    switch (buffer[tok_index]) {
      case ' ':
      case '\t':
        column++;
        tok_index++;
        break;
      case '\n':
        line++;
        column = 1;
        tok_index++;
        break;
      case '/':
        switch (GET_CHAR(1)) {
          case '/':
            while (GET_CHAR(0) != '\n') {
              tok_index++;
            }
            break;
          case '*':
            while (GET_CHAR(0) != '*' && GET_CHAR(1) != '/') {
              if (GET_CHAR(0) == '\n') {
                line++;
                column = 1;
              }
              tok_index++;
            }
            tok_index++;
            if (GET_CHAR(0) == '\0') {
              shoot_error("Found an unexpected EOF while lexing a 'multiline comment'!", Error::Info {
                .highlight = "Unterminated comment here.",
                .help = "Make sure to close the comment with '*/'."
              });
            }
            tok_index++;
            break; 
        }
    }
  }

  return tokens;
}

void Lexer::shoot_error(const std::string& message, const Error::Info& info) {
  add_error(E(message, SourceLocation {
    .line = line,
    .column = column,
    .length = 1,
    .file = ctx.input_file,
  }, info, Error::Type::Err));
}

} // namespace frontend
} // namespace snowball

