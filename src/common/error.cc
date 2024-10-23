
#include "common/error.h"
#include "common/stl.h"
#include "common/location.h"
#include "common/globals.h"
#include "common/utility/format.h"
#include "common/utility/logger.h"

using namespace snowball::utils;

namespace snowball {

auto FatalError(const Error& error) -> void {
  GetLogger().Error(error.GetMessage());
  std::exit(Failure);
}

auto FatalError(const String& message) -> void {
  FatalError(Error(message));
}

auto CrashError(const String& message) -> void {
  GetLogger().Fatal(message);
  std::exit(Failure);
}

auto UnreachableError(const_ptr_t error) -> void {
  if (error == nullptr) {
    FatalError("Unreachable code reached!");
  }
  FatalError((String)"Unreachable code reached: " + error);
}

auto Reportable::GetErrors() const -> const Vector<SourceError>& {
  return mErrors;
}

auto Reportable::HasErrors() const -> bool {
  return !mErrors.empty();
}

auto Reportable::AppendError(const SourceError& error) -> void {
  if (error.GetType() == SourceError::Error) {
    gContext.mErrorCount++;
  }
  mErrors.push_back(error);
}

auto Reportable::GetErrorCount() const -> usize {
  return mErrors.size();
}

auto Reportable::EndReport() -> void {
  if (HasErrors()) {
    for (const auto& error : GetErrors()) {
      error.Print();
    }
    throw StopCompileError();
  }
}

auto SourceError::GetData() const -> const Vector<SourceErrorData>& {
  return mData;
}

auto SourceError::WithInfo(const String& message, const std::optional<SourceLocation>&
    location) -> SourceError& {
  mData.push_back(SourceErrorData{location, message, Info});
  return *this;
}

auto SourceError::WithNote(const String& message, const std::optional<SourceLocation>&
    location) -> SourceError& {
  mData.push_back(SourceErrorData{location, message, Note});
  return *this;
}

auto SourceError::WithWarning(const String& message, const std::optional<SourceLocation>&
    location) -> SourceError& {
  mData.push_back(SourceErrorData{location, message, Warning});
  return *this;
}

auto SourceError::Print() const -> void {
  GetLogger().LogImpl(SnowballFormat(*this));
}

auto SnowballFormat(const Error& error) -> String {
  return error.GetMessage();
}

auto SourceError::GetLoggerType(Kind kind) -> Logger::Level {
  switch (kind) {
    case Error: return Logger::Level::Error;
    case Info: return Logger::Level::Info;
    case Note: return Logger::Level::Info;
    case Warning: return Logger::Level::Warning;
  }
  UnreachableError("Invalid error kind!");
}

auto SnowballFormat(const SourceError& error) -> String {
  std::stringstream ss;
  for (const auto& data : error.GetData()) {
    GetLogger().Log(SourceError::GetLoggerType(data.mKind), data.mMessage, ss);
    // TODO: Continue here.
  }
  return ss.str();
}

}; // namespace snowball
