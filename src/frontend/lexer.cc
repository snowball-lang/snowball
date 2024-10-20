
#include "frontend/token.h"
#include "frontend/lexer.h"

#include "common/disk.h"

using namespace snowball::utils;

namespace snowball::frontend {

auto Lexer::StartStreamLexer(fs::Path& path) -> Lexer {
  auto stream = ReadFile(path);
  return Lexer::Create(stream);
}

Lexer::Lexer(fs::FileStream& source) : mSource(source) {
  mToken = GetNextToken();
}

auto Lexer::GetCurrentToken() -> Token {
  return mToken;
}

auto Lexer::PeekNextToken(u8 offset) -> Token {
  SNOWBALL_ASSERT(offset < SN_MAX_LEXER_PEEK, "Offset is out of bounds.");
  auto current = mToken;
  auto currentCharIndex = mCharIndex;
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
  mCharIndex = currentCharIndex;
  return mPeekedTokens[offset];
}

auto Lexer::GetNextToken(bool peek) -> Token {
  mHasChanged = true;
  return LexToken();
}

auto Lexer::LexToken() -> Token {
  // TODO: Implement the lexer.
  return Token(TT::Unknown, SourceLocation(nullptr, 0, 0));
}

}; // namespace snowball::frontend

