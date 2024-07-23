
#pragma once

#include "common/stl.h"
#include "common/location.h"

namespace snowball {

/// @brief A basic error class that can be used to represent errors in the
/// compiler. This will be shown as a simple error message to the user.
/// To display source information, @see snowball::SourceError.
class Error {
public:
  /// @brief Construct an error with a message.
  /// @param message The error message.
  explicit Error(const String& message) : mMessage(message) {}
  /// @brief Get the error message.
  /// @return The error message.
  auto GetMessage() const -> const String& { return mMessage; }
private:
  String mMessage;
};

/// @brief A source error class that can be used to represent errors in the
/// compiler. This will be shown as an error message with source information.
/// To display a simple error message, @see snowball::Error.
class SourceError {
public:
  enum Kind : u8 {
    Error,
    Info,
    Note,
    Warning,
  };
  /// @brief A representation of the source error data.
  ///  this is used to create 
  struct SourceErrorData {
    SourceLocation mLocation;
    String mMessage{};
    Kind mKind{Error};
  };

  /// @brief Construct a new source error.
  /// @param data The source error data.
  explicit SourceError(const Vector<SourceErrorData>& data) : mData(data) {}
  /// @brief Get the source error data.
  /// @return The source error data.
  auto GetData() const -> const Vector<SourceErrorData>& { return mData; }
private:
  Vector<SourceErrorData> mData;
};

} // namespace snowball
