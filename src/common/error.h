
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
  auto GetData() const -> const Vector<SourceErrorData>&;

  /// @brief Append a new Info source error.
  auto WithInfo(const String& message, const std::optional<SourceLocation>&
    location = std::nullopt) -> SourceError&;
  /// @brief Append a new Note source error.
  auto WithNote(const String& message, const std::optional<SourceLocation>&
    location = std::nullopt) -> SourceError&;
  /// @brief Append a new Warning source error.
  auto WithWarning(const String& message, const std::optional<SourceLocation>&
    location = std::nullopt) -> SourceError&;
private:
  Vector<SourceErrorData> mData;
};

/// @brief It displays an error message and immediately exits the program.
/// @param error The error to display.
[[noreturn]] auto FatalError(const Error& error) -> void;

// Group: fmt utils
auto format_as(const Error& error) -> String; 
auto format_as(const SourceError& error) -> String;

} // namespace snowball
