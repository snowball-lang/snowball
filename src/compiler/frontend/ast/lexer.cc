
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

Lexer::Lexer(const Ctx& ctx) : ctx(ctx) {}

std::vector<Token> Lexer::lex() {
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
                .help = "Make sure to close the comment with '*/'.",
                .note = "Comments that start with '/*' must end with '*/'.",
              });
            }
            tok_index++;
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
          consume(Token::Type::SymCollon);
        break;
      }
      case ',': consume(Token::Type::SymComma); break;
      case ';': consume(Token::Type::SymSemiCollon); break;
      case '#': consume(Token::Type::SymHash); break;
      case '$': consume(Token::Type::SymDollar); break;
      case '?': consume(Token::Type::SymQuestion); break;
      case '@': consume(Token::Type::SymAt); break;
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
        std::string value = "\"";
        auto pos = std::make_pair(line, column);
        EAT_CHAR(1);
        while (GET_CHAR(0) != '"') {
          if (GET_CHAR(0) == '\\') {
            switch (GET_CHAR(1)) {
              case 'n': value += '\n'; break;
              case 't': value += '\t'; break;
              case 'r': value += '\r'; break;
              case '0': value += '\0'; break;
              case '\\': value += '\\'; break;
              case '"': value += '"'; break;
              case '\n': {
                line++;
                column = 1;
                tok_index++;
                break;
              }
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
          } else if (GET_CHAR(0) == '\n') {
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
          .value = value + "\"",
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
          std::string prefix;
          if (GET_CHAR(0) == 'u' || GET_CHAR(0) == 'U') {
            prefix += "u";
            EAT_CHAR(1);
          } else if (GET_CHAR(0) == 'i' || GET_CHAR(0) == 'I') {
            prefix += "i";
            EAT_CHAR(1);
          }
          if (GET_CHAR(0) == 'l' || GET_CHAR(0) == 'L') {
            prefix += "l";
            EAT_CHAR(1);
          }
          tk.value = prefix + tk.value;
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
          break;
        }
        // identifier
        if (IS_TEXT(GET_CHAR(0))) {
          std::string identifier(1, GET_CHAR(0));
          EAT_CHAR(1);
          while (IS_TEXT(GET_CHAR(0)) || IS_NUM(GET_CHAR(0))) {
            identifier += GET_CHAR(0);
            EAT_CHAR(1);
          }
          Token tk {
            .value = identifier,
            .location = std::make_pair(line, column - identifier.size()),
          };
          if (identifier == SN_KEYWORD_NEW) {
            tk.type = Token::KwordNew;
          } else if (identifier == SN_KEYWORD_THROW) {
            tk.type = Token::KwordThrow;
          } else if (identifier == SN_KEYWORD_IF) {
            tk.type = Token::KwordIf;
          } else if (identifier == SN_KEYWORD_VARIABLE) {
            tk.type = Token::KwordVar;
          } else if (identifier == SN_KEYWORD_FOR) {
            tk.type = Token::KwordFor;
          } else if (identifier == SN_KEYWORD_ENUM) {
            tk.type = Token::KwordEnum;
          } else if (identifier == SN_KEYWORD_DECLTYPE) {
            tk.type = Token::KwordDecltype;
          } else if (identifier == SN_KEYWORD_FUNCTION) {
            tk.type = Token::KwordFunc;
          } else if (identifier == SN_KEYWORD_MACRO) {
            tk.type = Token::KwordMacro;
          } else if (identifier == SN_KEYWORD_OPERATOR) {
            tk.type = Token::KwordOperator;
          } else if (identifier == SN_KEYWORD_ELSE) {
            tk.type = Token::KwordElse;
          } else if (identifier == SN_KEYWORD_CLASS) {
            tk.type = Token::KwordClass;
          } else if (identifier == SN_KEYWORD_AS) {
            tk.type = Token::KwordAs;
          } else if (identifier == SN_KEYWORD_CONSTANT) {
            tk.type = Token::KwordConst;
          } else if (identifier == SN_KEYWORD_WHILE) {
            tk.type = Token::KwordWhile;
          } else if (identifier == SN_KEYWORD_BREAK) {
            tk.type = Token::KwordBreak;
          } else if (identifier == SN_KEYWORD_EXTERN) {
            tk.type = Token::KwordExtern;
          } else if (identifier == SN_KEYWORD_SUPER) {
            tk.type = Token::KwordSuper;
          } else if (identifier == SN_KEYWORD_CASE) {
            tk.type = Token::KwordCase;
          } else if (identifier == SN_KEYWORD_SWITCH) {
            tk.type = Token::KwordSwitch;
          } else if (identifier == SN_KEYWORD_STATIC) {
            tk.type = Token::KwordStatic;
          } else if (identifier == SN_KEYWORD_IMPORT) {
            tk.type = Token::KwordImport;
          } else if (identifier == SN_KEYWORD_UNSAFE) {
            tk.type = Token::KwordUnsafe;
          } else if (identifier == SN_KEYWORD_CONSTEXPR) {
            tk.type = Token::KwordConstexpr;
          } else if (identifier == SN_KEYWORD_NAMESPACE) {
            tk.type = Token::KwordNamespace;
          } else if (identifier == SN_KEYWORD_STRUCT) {
            tk.type = Token::KwordStruct;
          } else if (identifier == SN_KEYWORD_TYPEDEF) {
            tk.type = Token::KwordTypedef;
          } else if (identifier == SN_KEYWORD_MUTABLE) {
            tk.type = Token::KwordMutable;
          } else if (identifier == SN_KEYWORD_DO) {
            tk.type = Token::KwordDo;
          } else if (identifier == SN_KEYWORD_PRIVATE) {
            tk.type = Token::KwordPrivate;
          } else if (identifier == SN_KEYWORD_PUBLIC) {
            tk.type = Token::KwordPublic;
          } else if (identifier == SN_KEYWORD_VIRTUAL) {
            tk.type = Token::KwordVirtual;
          } else if (identifier == SN_KEYWORD_OVERRIDE) {
            tk.type = Token::KwordOverride;
          } else if (identifier == SN_KEYWORD_RETURN) {
            tk.type = Token::KwordReturn;
          } else if (identifier == SN_KEYWORD_DEFAULT) {
            tk.type = Token::KwordDefault;
          } else if (identifier == SN_KEYWORD_CONTINUE) {
            tk.type = Token::KwordContinue;
          } else if (identifier == SN_KEYWORD_TRY) {
            tk.type = Token::KwordTry;
          } else if (identifier == SN_KEYWORD_CATCH) {
            tk.type = Token::KwordCatch;
          } else if (identifier == SN_KEYWORD_INTER) {
            tk.type = Token::KwordInter;
          } else if (identifier == SN_KEYWORD_EXTENDS) {
            tk.type = Token::KwordExtends;
          } else if (identifier == SN_KEYWORD_IMPLS) {
            tk.type = Token::KwordImplements;
          } else if (identifier == SN_KEYWORD_TRUE || identifier == SN_KEYWORD_FALSE) {
            tk.type = Token::ValueBool;
          } else {
            tk.type = Token::Identifier;
          }
          add_token(tk);
          break;
        }
        if (GET_CHAR(0) == '.') {
          consume(Token::Type::SymDot);
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
  return tokens;
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
  add_error(E(message, SourceLocation {
    .line = line,
    .column = column,
    .length = 1,
    .file = ctx.input_file,
  }, info, type));
}

} // namespace frontend
} // namespace snowball

