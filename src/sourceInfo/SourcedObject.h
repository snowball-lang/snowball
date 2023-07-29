
#include "common.h"
#include "SourceInfo.h"

#ifndef __SNOWBALL_SRC_OBJECT_H_
#define __SNOWBALL_SRC_OBJECT_H_

namespace snowball {

/// @brief A class that contains source information
/// @details This class is used to store source information
///          in the AST nodes.
///          It is used to store the file path, the line and column
///          of the source code.
///          It is also used to store the source code itself.
/// @see SrcObject
class SrcObject {
protected:
  SourceInfo* m_srci;

public:
  SrcObject() : m_srci(nullptr) { }
  SrcObject(SourceInfo* i) : m_srci(i) { }

  /// @brief get the instance of the source info
  auto getSourceInfo() const { return m_srci; }
  /// @brief Declare a new instance of source info
  void setSourceInfo(SourceInfo* i) { m_srci = i; }
};

} // namespace snowball

#endif // __SNOWBALL_SRC_OBJECT_H_
