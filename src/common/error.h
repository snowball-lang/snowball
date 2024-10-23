
#pragma once

#include "common/stl.h"
#include "common/location.h"
#include "common/utility/logger.h"
#include "common/utility/format.h"

namespace snowball {

/// @brief A basic error class that can be used to represent errors in the
/// compiler. This will be shown as a simple error message to the user.
/// To display source information, @see snowball::SourceError.
class [[nodiscard]] Error {
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
class [[nodiscard]] SourceError {
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
    Opt<SourceLocation> mLocation;
    String mMessage{};
    Kind mKind{Error};
  };

  /// @brief Return an equivalent @class Logger type from
  ///  a @class SourceErrorData::Kind.
  static auto GetLoggerType(Kind kind) -> utils::Logger::Level;

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

  /// @brief Print the error message.
  auto Print() const -> void;

  /// @brief Get the underlying error type.
  virtual auto GetType() const -> Kind { return Error; }
private:
  Vector<SourceErrorData> mData;
};

/// @brief A representation of a warning error.
class WarningError : public SourceError {
public:
  WarningError(const Vector<SourceErrorData>& data) : SourceError(data) {}
  auto GetType() const -> Kind override { return Warning; }
};

/// @brief A representation of an info error.
class InfoError : public SourceError {
public:
  InfoError(const Vector<SourceErrorData>& data) : SourceError(data) {}
  auto GetType() const -> Kind override { return Info; }
};

/// @brief A representation of a note error.
class NoteError : public SourceError {
public:
  NoteError(const Vector<SourceErrorData>& data) : SourceError(data) {}
  auto GetType() const -> Kind override { return Note; }
};

/// @brief It displays an error message and immediately exits the program.
/// @param error The error to display.
/// @note This is just a helper function to display an error message and
///  immediately exit the program. For actual fatal errors, use the
///  @see CrashError function.
[[noreturn]] auto FatalError(const Error& error) -> void;
[[noreturn]] auto FatalError(const String& message) -> void;

/// @brief It displays a fatal error message and immediately exits the program.
/// @param error The error to display.
[[noreturn]] auto CrashError(const String& message) -> void;

// Group: fmt utils
auto SnowballFormat(const Error& error) -> String; 
auto SnowballFormat(const SourceError& error) -> String;

/// @brief An unreachable error that is used to indicate that a certain
///  code path should never be reached.
/// @see snowball::CrashError
[[noreturn]] auto UnreachableError(const_ptr_t extra = nullptr) -> void;

/// @brief An error that can be thrown and caught by a class.
class [[nodiscard]] StopCompileError : public std::exception {
public:
  /// @brief Construct a new stop compile error..
  explicit StopCompileError() {}
  /// @brief Get the error message.
  /// @return The error message.
  auto what() const noexcept -> const char* override {
    return "Compilation failed with errors.";
  }
};

/// @brief A representation of a class that can contain/throw errors.
class Reportable {
public:
  /// @brief Get all the errors.
  /// @return All the errors.
  auto GetErrors() const -> const Vector<SourceError>&;
  /// @return Whether there are any errors.
  auto HasErrors() const -> bool;
  /// @brief Append a new error.
  /// @param error The error to append.
  auto AppendError(const SourceError& error) -> void;
  /// @return The error count.
  auto GetErrorCount() const -> usize;
  /// @brief Start spiting out errors if there are any.
  auto EndReport() -> void;
  /// @brief Create and append a new error.
  /// @param message The error message.
  template <typename... Args>
  inline auto Report(const SourceLocation& location, const String& message, Args&&... args) -> void {
    AppendError(SourceError({{location, utils::Format(message, std::forward<Args>(args)...)}}));
  }
  /// @brief Create and append a new error.
  /// @param message The error message.
  template <typename... Args>
  inline auto Report(const String& message, Args&&... args) -> void {
    Report(SourceLocation(nullptr, 0, 0), message, std::forward<Args>(args)...);
  }

  ~Reportable() = default;
protected:
  Vector<SourceError> mErrors;
};

} // namespace snowball
