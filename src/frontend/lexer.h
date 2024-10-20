
#pragma once

#include "common/stl.h"
#include "common/location.h"

#include "frontend/token.h"

namespace snowball {
namespace frontend {

#define SN_MAX_LEXER_PEEK 4

/// @brief A lexer.
/// The lexer is responsible for tokenizing the input source code.
class Lexer final : public NonCopyable, public Createable<Lexer>, public NonMovable {
  friend class Createable<Lexer>;
public:
  /// @brief Create a new lexer instance and tokenize the input source code,
  /// by using a file stream.
  static auto StartStreamLexer(fs::Path& path) -> Lexer;

  /// @brief Default destructor.
  ~Lexer() = default;
private:
  /// @brief Construct a new lexer.
  /// @param source The source code.
  explicit Lexer(fs::FileStream& source);

  /// @brief It returns the list of tokens.
  /// @return The list of tokens.
  inline auto GetNextToken(bool peek = false) -> Token;

  /// @brief Peek the next token.
  /// @return The next token.
  auto PeekNextToken(u8 offset = 0) -> Token;

  /// @brief Get the current token.
  /// @return The current token.
  auto GetCurrentToken() -> Token;

  /// @brief Get the current line.
  /// @return The current line.
  auto GetCurrentLine() const -> u64;

  /// @brief Get the current column.
  /// @return The current column.
  auto GetCurrentColumn() const -> u64;

  /// @brief If it's the end of the file.
  /// @return Whether it's the end of the file.
  auto IsEof() const -> bool;

  /// @brief Lex the next token.
  /// @return The next token.
  SNOWBALL_NO_DISCARD auto LexToken() -> Token;
private:
  fs::FileStream& mSource;
  u64 mLine{1};
  u64 mColumn{1};

  usize mCharIndex{0};
  
  Token mToken{TT::Unknown, SourceLocation(nullptr, 0, 0)};

  /// Some sort of cache for peeked tokens.
  /// We can peek up to SN_MAX_LEXER_PEEK tokens.
  SmallVector<Token, SN_MAX_LEXER_PEEK> mPeekedTokens;
  bool mHasChanged{false}; // If the token has changed, invalidate the cache.

  bool mIsEof{false};
};

}; // namespace frontend
}; // namespace snowball
