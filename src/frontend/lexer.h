
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
  static auto StartPathLexer(const fs::Path& path) -> Lexer;
  /// @brief Create a new lexer instance and tokenize the input source code,
  /// by using a string value.
  static auto StartStringLexer(const String& source) -> Lexer;
  /// @brief Create a new lexer instance and tokenize the input source code,
  /// by using a file stream.
  static auto StartStreamLexer(IStream* stream) -> Lexer;

  /// @brief Default destructor.
  ~Lexer() = default;
private:
  /// @brief Construct a new lexer.
  /// @param source The source code.
  explicit Lexer(IStream* source);

public:
  /// @brief It returns the list of tokens.
  /// @return The list of tokens.
  auto GetNextToken(bool peek = false) -> Token;

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
  inline auto IsEof() const -> bool { return mIsEof; }

  /// @brief Lex the next token.
  /// @return The next token.
  SNOWBALL_NO_DISCARD auto LexToken() -> Token;
private:
  /// @brief Consume a new line.
  auto ConsumeNewLine() -> void;
  /// @brief Create a source location.
  /// @return The source location.
  auto CreateSourceLocation() -> SourceLocation;
  /// @brief Consume a new character.
  /// @return The new character.
  /// @note This can be used when parsing double characters, like '==', '!=', etc.
  auto ConsumeChar(TT type) -> Token;

private:
  IStream* mSource;
  u64 mLine{1};
  u64 mColumn{1};
  
  Token mToken{TT::Unknown, SourceLocation(nullptr, 0, 0)};

  /// Some sort of cache for peeked tokens.
  /// We can peek up to SN_MAX_LEXER_PEEK tokens.
  SmallVector<Token, SN_MAX_LEXER_PEEK> mPeekedTokens;
  bool mHasChanged{false}; // If the token has changed, invalidate the cache.

  bool mIsEof{false};
};

}; // namespace frontend
}; // namespace snowball
