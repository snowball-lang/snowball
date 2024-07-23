
#pragma once

#include "common/stl.h"

namespace snowball {

using SourceFile = SharedPtr<fs::Path>;

/// @brief A location represents a position in the source code.
class SourceLocation {
public:
  /// @brief Construct a location with a source file, line, and column.
  /// @param file The source file.
  /// @param line The line number.
  /// @param column The column number.
  /// @param width The width of the location.
  SourceLocation(SourceFile file, u64 line, u64 column, u16 width = 0)
    : mFile(file), mLine(line), mColumn(column), mWidth(width) {}
  /// @brief Get the source file.
  /// @return The source file.
  auto GetFile() const -> const SourceFile& { return mFile; }
  /// @brief Get the line number.
  /// @return The line number.
  auto GetLine() const -> u64 { return mLine; }
  /// @brief Get the column number.
  /// @return The column number.
  auto GetColumn() const -> u64 { return mColumn; }
  /// @brief Get the width of the location.
  /// @return The width of the location.
  auto GetWidth() const -> u16 { return mWidth; }

  ~SourceLocation() = default;
private:
  SourceFile mFile;
  u64 mLine{0};
  u64 mColumn{0};
  u16 mWidth{0};
};

} // namespace snowball