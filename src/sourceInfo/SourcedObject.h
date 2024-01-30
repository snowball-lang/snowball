
#include "SourceInfo.h"
#include "common.h"

#ifndef __SNOWBALL_SRC_OBJECT_H_
#define __SNOWBALL_SRC_OBJECT_H_

namespace snowball {

static const SourceInfo* TEMP_DBG_INFO = new SourceInfo("<error>", "<source>");

/// @brief A class that contains source information
/// @details This class is used to store source information
///          in the AST nodes.
///          It is used to store the file path, the line and column
///          of the source code.
///          It is also used to store the source code itself.
/// @see SrcObject
class SrcObject {
 protected:
  const SourceInfo* m_srci;

 public:
  SrcObject(const SourceInfo* i) : m_srci(i) { }
  SrcObject() : m_srci(TEMP_DBG_INFO) { }

  /// @brief get the instance of the source info
  auto& getSourceInfo() const { return m_srci; }
  /// @brief Declare a new instance of source info
  void setSourceInfo(const SourceInfo* i) { m_srci = i; }
};

} // namespace snowball

#endif // __SNOWBALL_SRC_OBJECT_H_
