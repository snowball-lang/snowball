
#include "frontend/token.h"
#include "frontend/lexer.h"
#include "common/error.h"

#include "common/disk.h"

#include "frontend/lexer.def"

using namespace snowball::utils;

namespace snowball::frontend {

auto Lexer::StartPathLexer(const fs::Path& path) -> Lexer {
  return StartStreamLexer(ReadFile(path));
}

auto Lexer::StartStringLexer(const String& source) -> Lexer {
  return StartStreamLexer(new std::istringstream(source));
}

auto Lexer::StartStreamLexer(IStream* stream) -> Lexer {
  return Lexer(stream);
}

Lexer::Lexer(IStream* source) : mSource(source) {}

auto Lexer::GetCurrentToken() -> Token {
  return mToken;
}

auto Lexer::PeekNextToken(u8 offset) -> Token {
  SNOWBALL_ASSERT(offset < SN_MAX_LEXER_PEEK, "Offset is out of bounds.");
  auto current = mToken;
  if (mHasChanged) {
    mPeekedTokens.clear();
    mHasChanged = false;
  }
  if (mPeekedTokens.size() <= offset) {
    for (u8 i = mPeekedTokens.size(); i <= offset; i++) {
      mPeekedTokens.push_back(GetNextToken(true));
    }
  }
  mToken = current;
  return mPeekedTokens[offset];
}

inline auto Lexer::GetNextToken(bool peek) -> Token {
  mHasChanged = true;
  return LexToken();
}

inline auto Lexer::ConsumeNewLine() -> void {
  mLine++;
  mColumn = 0;
}

inline auto Lexer::CreateSourceLocation() -> SourceLocation {
  return SourceLocation(nullptr, mLine, mColumn);
}

inline auto Lexer::ConsumeChar(TT type) -> Token {
  mColumn++;
  mSource->get();
  return Token(type, CreateSourceLocation());
}

auto Lexer::LexToken() -> Token {
  while (mSource) {
    auto c = mSource->get();
    mColumn += !IsEof();
    switch (c) {
      case -1: // EOF
        mIsEof = true;
        return Token(TT::Eof, CreateSourceLocation());
      case ' ':
      case '\t':
      case '\r':
        continue;
      case '\n':
        ConsumeNewLine();
        continue;
      
      DEFINE_SINGLE_CHAR_TOKENS(SymComma,        ',')
      DEFINE_SINGLE_CHAR_TOKENS(SymSemiColon,    ';')
      DEFINE_SINGLE_CHAR_TOKENS(SymHash,         '#')
      DEFINE_SINGLE_CHAR_TOKENS(SymDollar,       '$')
      DEFINE_SINGLE_CHAR_TOKENS(SymQuestion,     '?')
      DEFINE_SINGLE_CHAR_TOKENS(SymAt,           '@')
      DEFINE_SINGLE_CHAR_TOKENS(SymDot,          '.')

      DEFINE_SINGLE_CHAR_TOKENS(BracketLparent,  '(')
      DEFINE_SINGLE_CHAR_TOKENS(BracketRparent,  ')')
      DEFINE_SINGLE_CHAR_TOKENS(BracketLcurly,   '{')
      DEFINE_SINGLE_CHAR_TOKENS(BracketRcurly,   '}')
      DEFINE_SINGLE_CHAR_TOKENS(BracketLsquared, '[')
      DEFINE_SINGLE_CHAR_TOKENS(BracketRsquared, ']')

      DEFINE_SINGLE_OR_DOUBLE_CHAR_TOKENS(
        SymColon, ':',
        SymColcol, ':'
      )

      DEFINE_SINGLE_OR_EQUAL_CHAR_TOKENS(OpPlus, '+')
      DEFINE_SINGLE_OR_EQUAL_CHAR_TOKENS(OpMinus,'-')
      DEFINE_SINGLE_OR_EQUAL_CHAR_TOKENS(OpMul,  '*')
      DEFINE_SINGLE_OR_EQUAL_CHAR_TOKENS(OpDiv,  '/')
      DEFINE_SINGLE_OR_EQUAL_CHAR_TOKENS(OpMod,  '%')

      DEFINE_SINGLE_OR_EQUAL_CHAR_TOKENS(OpGt,   '>')
      DEFINE_SINGLE_OR_EQUAL_CHAR_TOKENS(OpNot,  '!')

      DEFINE_SINGLE_OR_DOUBLE_CHAR_TOKENS_2(
        OpEq, '=',
        OpEqeq, '=', 
        OpArrow, '>'
      )
    }
  }
  UnreachableError("What do we do here?");
}

#undef DEFINE_SINGLE_CHAR_TOKENS
#undef DEFINE_SINGLE_OR_DOUBLE_CHAR_TOKENS
#undef DEFINE_SINGLE_OR_DOUBLE_CHAR_TOKENS_2

}; // namespace snowball::frontend

