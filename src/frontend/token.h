
#pragma once

#include "common/stl.h"
#include "common/location.h"

namespace snowball {
namespace frontend {

enum class TT : u8 {
#define DEFINE_TOKEN(name) name,
#include "frontend/tokens.def"
  Unknown
};

/// @brief Represents a token.
/// A token is a single lexical unit in the source code. We use
/// tokens to represent keywords, identifiers, literals, and other
/// language elements and organize them into a stream.
class Token final : public NonCopyable {
public:
  /// @brief Delete the default constructor.
  Token() = delete;

  /// @brief Default destructor.
  ~Token() = default;

  /// @brief Construct a new token.
  /// @param type The type of the token.
  /// @param location The location of the token.
  /// @param value The value of the token.
  Token(TT type, const SourceLocation& location, const String& value = "")
    : mType(type), mValue(value), mLocation(location) {}

  /// @brief Get the type of the token.
  /// @return The type of the token.
  SNOWBALL_NO_DISCARD inline
  auto GetType() const -> TT { return mType; }

  /// @brief Get the value of the token.
  /// @return The value of the token.
  SNOWBALL_NO_DISCARD inline
  auto GetValue() const -> const String& { return mValue; }

  /// @brief Get the location of the token.
  /// @return The location of the token.
  SNOWBALL_NO_DISCARD inline auto GetLocation() const 
    -> const SourceLocation& { return mLocation; }

  /// @brief Get the length of the token.
  /// @return The length of the token.
  SNOWBALL_NO_DISCARD auto GetLength() const -> u16;
private:
  TT mType{TT::Unknown};
  String mValue{};
  SourceLocation mLocation;
};

// Group: fmt utils
auto SnowballFormat(const Token& token) -> String; 

using TokenStream = Vector<Token>;

}; // namespace frontend
}; // namespace snowball
