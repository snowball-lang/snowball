
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

#include "compiler/frontend/ast/lexer.h"
#include "compiler/frontend/ast/token.h"
#include "compiler/utils/utils.h"
#include "compiler/globals.h"

#include "compiler/frontend/ast/kwords.def"

#define GET_CHAR(offset) buffer[tok_index + offset] 
#define EAT_CHAR(m_num) \
  { \
    tok_index += m_num; \
    column += m_num; \
  }

#define IS_NUM(c)      (('0' <= c && c <= '9'))
#define IS_HEX_CHAR(c) (IS_NUM(c) || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F'))
#define IS_TEXT(c)     ((c == '_') || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))

namespace snowball {
namespace frontend {

Lexer::Lexer(const Ctx& ctx, std::shared_ptr<SourceFile> file) 
  : ctx(ctx), file(file) {}

static bool is_newline(int c) {
  switch (c) {
    case 0x0A: // LF
    case 0x0B: // CR
      return true;
  }
  return false;
}

static Token::Type get_keyword_type(const std::string& keyword) {
  switch (keyword[0]) {
    case 'a': {
      if (keyword == SN_KEYWORD_AS) return Token::KwordAs;
      if (keyword == SN_KEYWORD_ABSTRACT) return Token::KwordAbstract;
      break;
    }
    case 'b': {
      if (keyword == SN_KEYWORD_BREAK) return Token::KwordBreak;
      break;
    }
    case 'c': {
      if (keyword == SN_KEYWORD_CASE) return Token::KwordCase;
      if (keyword == SN_KEYWORD_CLASS) return Token::KwordClass;
      if (keyword == SN_KEYWORD_CONSTANT) return Token::KwordConst;
      if (keyword == SN_KEYWORD_CONTINUE) return Token::KwordContinue;
      break;
    }
    case 'd': {
      if (keyword == SN_KEYWORD_DO) return Token::KwordDo;
      if (keyword == SN_KEYWORD_DEFAULT) return Token::KwordDefault;
      if (keyword == SN_KEYWORD_DELETE) return Token::KwordDelete;
      break;
    }
    case 'e': {
      if (keyword == SN_KEYWORD_ELSE) return Token::KwordElse;
      if (keyword == SN_KEYWORD_ENUM) return Token::KwordEnum;
      if (keyword == SN_KEYWORD_EXTERN) return Token::KwordExtern;
      if (keyword == SN_KEYWORD_EXTENDS) return Token::KwordExtends;
      break;
    }
    case 'f': {
      if (keyword == SN_KEYWORD_FOR) return Token::KwordFor;
      if (keyword == SN_KEYWORD_FUNCTION) return Token::KwordFunc;
      if (keyword == SN_KEYWORD_FALSE) return Token::ValueBool;
      if (keyword == SN_KEYWORD_FINAL) return Token::KwordFinal;
      break;
    }
    case 'i': {
      if (keyword == SN_KEYWORD_IF) return Token::KwordIf;
      if (keyword == SN_KEYWORD_IMPORT) return Token::KwordImport;
      if (keyword == SN_KEYWORD_INTER) return Token::KwordInter;
      if (keyword == SN_KEYWORD_IMPLS) return Token::KwordImplements;
      if (keyword == SN_KEYWORD_INLINE) return Token::KwordInline;
      break;
    }
    case 'l': {
      if (keyword == SN_KEYWORD_LET) return Token::KwordVar;
      break;
    }
    case 'm': {
      if (keyword == SN_KEYWORD_MACRO) return Token::KwordMacro;
      if (keyword == SN_KEYWORD_MUTABLE) return Token::KwordMutable;
      break;
    }
    case 'n': {
      if (keyword == SN_KEYWORD_NEW) return Token::KwordNew;
      break;
    }
    case 'o': {
      if (keyword == SN_KEYWORD_OPERATOR) return Token::KwordOperator;
      break;
    }
    case 'p': {
      if (keyword == SN_KEYWORD_PRIVATE) return Token::KwordPrivate;
      if (keyword == SN_KEYWORD_PUBLIC) return Token::KwordPublic;
      break;
    }
    case 'r': {
      if (keyword == SN_KEYWORD_RETURN) return Token::KwordReturn;
      break;
    }
    case 's': {
      if (keyword == SN_KEYWORD_SUPER) return Token::KwordSuper;
      if (keyword == SN_KEYWORD_STATIC) return Token::KwordStatic;
      if (keyword == SN_KEYWORD_SWITCH) return Token::KwordSwitch;
      break;
    }
    case 't': {
      if (keyword == SN_KEYWORD_TRUE) return Token::ValueBool;
      if (keyword == SN_KEYWORD_TRY) return Token::KwordTry;
      break;
    }
    case 'u': {
      if (keyword == SN_KEYWORD_UNSAFE) return Token::KwordUnsafe;
      break;
    }
    case 'v': {
      if (keyword == SN_KEYWORD_VIRTUAL) return Token::KwordVirtual;
      break;
    }
    case 'w': {
      if (keyword == SN_KEYWORD_WHILE) return Token::KwordWhile;
      break;
    }
    default: break;
  }
  return Token::Identifier;
}

std::vector<Token> Lexer::lex() {
  buffer = globals::read_file(file->get_path());
  while (tok_index < buffer.size()) {
    if (is_newline(buffer[tok_index])) {
      line++;
      column = 1;
      tok_index++;
      continue;
    }
    switch (buffer[tok_index]) {
      case ' ':
      case '\t':
      case '\v':
      case '\f':
        EAT_CHAR(1);
        break;
      case '\0': break;
      case '/':
        switch (GET_CHAR(1)) {
          case '/':
            while (!is_newline(GET_CHAR(0))) {
              tok_index++;
            }
            break;
          case '*':
            while (true) {
              if (GET_CHAR(0) == '*' && GET_CHAR(1) == '/') {
                EAT_CHAR(2);
                break;
              }
              if (GET_CHAR(0) == '\0') {
                shoot_error("Found an unexpected EOF while lexing a 'comment'!", Error::Info {
                  .highlight = "Unterminated comment here.",
                  .help = "Make sure to close the comment with '*/'.",
                  .note = "Comments that start with '/*' must end with '*/'.",
                });
                break;
              }
              if (is_newline(GET_CHAR(0))) {
                line++;
                column = 1;
                continue;
              }
              EAT_CHAR(1);
            }
            break; 
          default:
            consume(Token::Type::OpDiv);
            break;
        }
        break;
      // symbols
      case ':': {
        if (GET_CHAR(1) == ':')
          consume(Token::Type::SymColcol, 2);
        else
          consume(Token::Type::SymColon);
        break;
      }
      case ',': consume(Token::Type::SymComma); break;
      case ';': consume(Token::Type::SymSemiColon); break;
      case '#': consume(Token::Type::SymHash); break;
      case '$': consume(Token::Type::SymDollar); break;
      case '?': consume(Token::Type::SymQuestion); break;
      case '@': consume(Token::Type::SymAt); break;
      case '.': consume(Token::Type::SymDot); break;
      // brackets
      case '(': consume(Token::Type::BracketLparent); break;
      case ')': consume(Token::Type::BracketRparent); break;
      case '{': consume(Token::Type::BracketLcurly); break;
      case '}': consume(Token::Type::BracketRcurly); break;
      case '[': consume(Token::Type::BracketLsquared); break;
      case ']': consume(Token::Type::BracketRsquared); break;
      // op
      case '=': {
        if (GET_CHAR(1) == '=')
          consume(Token::Type::OpEqeq, 2);
        else if (GET_CHAR(1) == '>')
          consume(Token::Type::OpArrow, 2);
        else
          consume(Token::Type::OpEq);
        break;
      }
      case '+': {
        if (GET_CHAR(1) == '=')
          consume(Token::Type::OpPluseq, 2);
        else
          consume(Token::Type::OpPlus);
        break;
      }
      case '-': {
        if (GET_CHAR(1) == '=')
          consume(Token::Type::OpMinuseq, 2);
        else
          consume(Token::Type::OpMinus);
        break;
      }
      case '*': {
        if (GET_CHAR(1) == '=')
          consume(Token::Type::OpMuleq, 2);
        else
          consume(Token::Type::OpMul);
        break;
      }
      case '%': {
        if (GET_CHAR(1) == '=')
          consume(Token::Type::OpModEq, 2);
        else
          consume(Token::Type::OpMod);
        break;
      }
      case '<': {
        if (GET_CHAR(1) == '=')
          consume(Token::Type::OpLteq, 2);
        else if (GET_CHAR(1) == '<') {
          if (GET_CHAR(2) == '=')
            consume(Token::Type::OpBitLshiftEq, 3);
          else
            consume(Token::Type::OpBitLshift, 2);
        } else
          consume(Token::Type::OpLt);
        break;
      }
      case '>': {
        if (GET_CHAR(1) == '=')
          consume(Token::Type::OpGteq, 2);
        else if (GET_CHAR(1) == '>') {
          if (GET_CHAR(2) == '=')
            consume(Token::Type::OpBitRshiftEq, 3);
          else
            // TODO: (generics cant handle <type<hello<adios>>)
            // consume(Token::Type::OpBitRshift, 2);
            // ^^
            // actually parse ">>" at parser when we encounter an
            // operator
          {
            consume(Token::Type::OpGt);
            consume(Token::Type::OpGt);
          }
        } else
          consume(Token::Type::OpGt);
        break;
      }
      case '!': {
        if (GET_CHAR(1) == '=')
          consume(Token::Type::OpNoteq, 2);
        else
          consume(Token::Type::OpNot);
        break;
      }
      case '~': consume(Token::Type::OpBitNot); break;
      case '|': {
        if (GET_CHAR(1) == '=')
          consume(Token::Type::OpBitOrEq, 2);
        else if (GET_CHAR(1) == '|')
          consume(Token::Type::OpOr, 2);
        else if (GET_CHAR(1) == '>' && GET_CHAR(2) == '>')
          consume(Token::Type::OpBitRshift, 3);
        else
          consume(Token::Type::OpBitOr);
        break;
      }
      case '&': {
        if (GET_CHAR(1) == '=')
          consume(Token::Type::OpBitAndEq, 2);
        else if (GET_CHAR(1) == '&')
          consume(Token::Type::OpAnd, 2);
        else
          consume(Token::Type::OpBitAnd);
        break;
      }
      case '^': {
        if (GET_CHAR(1) == '=')
          consume(Token::Type::OpBitXorEq, 2);
        else
          consume(Token::Type::OpBitXor);
        break;
      }
      case '"': {
        std::string value;
        auto pos = std::make_pair(line, column);
        EAT_CHAR(1);
        while (GET_CHAR(0) != '"') {
          if (GET_CHAR(0) == '\\') {
            if (is_newline(GET_CHAR(1))) {
              line++;
              column = 1;
              tok_index++;
              continue;
            }
            switch (GET_CHAR(1)) {
              case 'n': value += '\n'; break;
              case 't': value += '\t'; break;
              case 'r': value += '\r'; break;
              case '0': value += '\0'; break;
              case '\\': value += '\\'; break;
              case '"': value += '"'; break;
              default: {
                column++;
                shoot_error("Invalid escape sequence!", Error::Info {
                  .highlight = "Invalid escape sequence here.",
                  .note = "Escape sequences are used to represent special characters in a string.\nUse '\\\\' to represent a backslash.",
                }, Error::Type::Warn);
                break;
              }
            }
            tok_index += 2;
          } else if (GET_CHAR(0) == '\0') {
            tok_index++;
            shoot_error("Found an unexpected EOF while lexing a 'string'!", Error::Info {
              .highlight = "Unterminated string here.",
              .help = "Make sure to close the string with '\"'.",
              .note = "Strings that start with '\"' must end with '\"'.",
            });
            break;
          } else if (is_newline(GET_CHAR(0))) {
            tok_index++;
            shoot_error("Found an unexpected newline while lexing a 'string'!", Error::Info {
              .highlight = "Unexpected newline here.",
              .help = "Make sure to close the string with '\"'.",
              .note = "Strings cannot contain newlines. Use '\\n' to represent a newline.",
            });
            break;
          } else {
            value += GET_CHAR(0);
            EAT_CHAR(1);
          }
        }
        tok_index++;
        add_token(Token {
          .value = value,
          .type = Token::Type::ValueString,
          .location = pos,
        });
        break;
      }
      case '\'': {
        std::string value = "";
        auto pos = std::make_pair(line, column);
        tok_index++;
        if (GET_CHAR(0) == '\\') {
          switch (GET_CHAR(1)) {
            case 'n': value += '\n'; break;
            case 't': value += '\t'; break;
            case 'r': value += '\r'; break;
            case '0': value += '\0'; break;
            case '\\': value += '\\'; break;
            case '\'': value += '\''; break;
            default: {
              column++;
              shoot_error("Invalid escape sequence!", Error::Info {
                .highlight = "Invalid escape sequence here.",
                .note = "Escape sequences are used to represent special characters in a string.\nUse '\\\\' to represent a backslash.",
              }, Error::Type::Warn);
              break;
            }
          }
          tok_index += 2;
        } else {
          value += GET_CHAR(0);
          tok_index++;
        }
        if (GET_CHAR(0) != '\'') {
          shoot_error("Found an unexpected EOF while lexing a 'char'!", Error::Info {
            .highlight = "Unterminated char here.",
            .help = "Make sure to close the char with '\\''.",
            .note = "Chars that start with '\\'' must end with '\\''.",
          });
        }
        tok_index++;
        add_token(Token {
          .value = value,
          .type = Token::Type::ValueChar,
          .location = pos,
        });
        break;
      }
      default: {
        // TODO: 1.2e3 => is a valid float number
        // float value begins with '.'
        if (GET_CHAR(0) == '.' && IS_NUM(GET_CHAR(1))) {
          std::string float_str(1, '.');
          EAT_CHAR(1);
          while (IS_NUM(GET_CHAR(0))) {
            float_str += GET_CHAR(0);
            EAT_CHAR(1);
          }
          add_token(Token {
            .value = float_str,
            .type = Token::Type::ValueFloat,
            .location = std::make_pair(line, column - float_str.size()),
          });
          break;
        }
        // integer/float value
        if (IS_NUM(GET_CHAR(0))) {
          lex_number();
          break;
        }
        // identifier
        if (IS_TEXT(GET_CHAR(0))) {
          lex_identifier();
          break;
        }
        shoot_error("Unknown character ('" + std::string(1, buffer[tok_index]) + "') found!", Error::Info {
          .highlight = "Unknown character here.",
          .help = "Make sure to use a valid character.",
          .note = "The character '" + std::string(1, buffer[tok_index]) + "' is not a valid character.",
        });
        tok_index++;
      }
    }
  }
  if (tokens.size() == 0 || tokens[tokens.size() - 1].type != Token::Type::Eof) {
    add_token(Token {
      .type = Token::Type::Eof,
      .location = std::make_pair(line, column),
    });
  }
  return tokens;
}

void Lexer::lex_number() {
  std::string num(1, GET_CHAR(0));
  enum _ReadMode {
    INT,
    FLOAT,
    BIN,
    HEX,
    OCT
  };
  _ReadMode mode = INT;
  if (GET_CHAR(0) == '0') {
    if (GET_CHAR(1) == 'b' || GET_CHAR(1) == 'B') mode = BIN;
    if (GET_CHAR(1) == 'x' || GET_CHAR(1) == 'X') mode = HEX;
    if (GET_CHAR(1) == 'o' || GET_CHAR(1) == 'O') mode = OCT;
  }
  bool isRange = false;
  EAT_CHAR(1);
  switch (mode) {
    case INT: {
      while (IS_NUM(GET_CHAR(0)) || GET_CHAR(0) == '.') {
        if (GET_CHAR(0) == '.' && mode == FLOAT) {
          mode = INT;
          num.erase(num.size() - 1);
          isRange = true;
          break; // It must be a range, right?
        }
        if (GET_CHAR(0) == '.') mode = FLOAT;
        num += GET_CHAR(0);
        EAT_CHAR(1);
      }
    } break;
    case BIN: {
      num += GET_CHAR(0);
      EAT_CHAR(1); // eat 'b';
      while (GET_CHAR(0) == '0' || GET_CHAR(0) == '1') {
        num += GET_CHAR(0);
        EAT_CHAR(1);
      }
    } break;
    case HEX: {
      num += GET_CHAR(0);
      EAT_CHAR(1); // eat 'x';
      while (IS_HEX_CHAR(GET_CHAR(0))) {
        num += GET_CHAR(0);
        EAT_CHAR(1);
      }
    } break;
    case OCT: {
      num += GET_CHAR(0);
      EAT_CHAR(1); // eat 'o';
      while (GET_CHAR(0) >= '0' && GET_CHAR(0) <= '7') {
        num += GET_CHAR(0);
        EAT_CHAR(1);
      }
    } break;
    default: sn_assert(false, "Invalid mode");
  }
  bool appendDot = false;
  if (num[num.size() - 1] == '.') {
    num.erase(num.size() - 1);
    mode = INT;
    appendDot = true;
  }
  auto tk = Token {
    .value = num,
    .type = mode == FLOAT ? Token::Type::ValueFloat : Token::Type::ValueNumber,
    .location = std::make_pair(line, column - num.size()),
  };
  std::string suffix;
  if (GET_CHAR(0) == 'u' || GET_CHAR(0) == 'U') {
    suffix += "U";
    EAT_CHAR(1);
  } else if (GET_CHAR(0) == 'i' || GET_CHAR(0) == 'I') {
    suffix += "I";
    EAT_CHAR(1);
  }
  if (GET_CHAR(0) == 'l' || GET_CHAR(0) == 'L') {
    suffix += "L";
    EAT_CHAR(1);
  }
  tk.value = tk.value + suffix;
  add_token(tk);
  if (isRange) { // we add '..' if it's a range expr (1..5)
    consume(Token::Type::SymDot);
    consume(Token::Type::SymDot);
    tok_index -= 2;
  }
  if (appendDot) {
    consume(Token::Type::SymDot);
    tok_index--;
  }
}

void Lexer::lex_identifier() {
  std::string identifier(1, GET_CHAR(0));
  EAT_CHAR(1);
  while (IS_TEXT(GET_CHAR(0)) || IS_NUM(GET_CHAR(0))) {
    identifier += GET_CHAR(0);
    EAT_CHAR(1);
  }
  Token tk {
    .value = identifier,
    .type = get_keyword_type(identifier),
    .location = std::make_pair(line, column - identifier.size()),
  };
  if (identifier == "_") {
    shoot_error("Invalid identifier!", Error::Info {
      .highlight = "Invalid identifier here.",
      .note = "The identifier '_' is not a valid identifier. Its reserved for special use.\ne.g. an unknown type or a placeholder.",
    });
  }
  add_token(tk);
}

void Lexer::add_token(const Token& token) {
  tokens.push_back(token);
}

void Lexer::consume(Token::Type type, unsigned int length) {
  add_token(Token {
    .type = type,
    .location = std::make_pair(line, column),
  });
  EAT_CHAR(length);
}

void Lexer::shoot_error(const std::string& message, const Error::Info& info, Error::Type type) {
  add_error(E(message, SourceLocation {line, column, 1, this->file}, info, type));
}

} // namespace frontend
} // namespace snowball

