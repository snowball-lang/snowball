
#pragma once

#include "common/stl.h"
#include "common/location.h"

#include "frontend/token.h"

namespace snowball {
namespace frontend {

/// @brief A lexer.
/// The lexer is responsible for tokenizing the input source code.
class Lexer final : public NonCopyable {
public:
  /// @brief Create a new lexer instance and tokenize the input source code,
  /// by using a file stream.
  static auto StartStreamLexer(const fs::Path& path) -> TokenStream;

  /// @brief Default destructor.
  ~Lexer() = default;
private:
  /// @brief Construct a new lexer.
  /// @param source The source code.
  explicit Lexer() = default;

  /// @brief Tokenize the input source code.
  /// @param source The source code.
  auto Tokenize(const FileStream& source) -> TokenStream;

  /// @brief It returns the list of tokens.
  /// @return The list of tokens.
  auto GetTokens() const -> const TokenStream& { return mTokens; }

  TokenStream mTokens;
};

}; // namespace frontend
}; // namespace snowball
