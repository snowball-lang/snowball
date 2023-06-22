
#include "common.h"
#include "source_info.h"

#ifndef __SNOWBALL_SRC_OBJECT_H_
#define __SNOWBALL_SRC_OBJECT_H_

namespace snowball {

/**
 * Good old src object. This
 * class is used for all objects that
 * require a source info passed into it.
 */
class SrcObject {
  protected:
    SourceInfo* m_srci;

  public:
    SrcObject() : m_srci(nullptr) { }
    SrcObject(SourceInfo* i) : m_srci(i) { }

    /// @brief get the instance of the source info
    auto
    getSourceInfo() const {
        return m_srci;
    }
    /// @brief Declare a new instance of source info
    void
    setSourceInfo(SourceInfo* i) {
        m_srci = i;
    }
};

} // namespace snowball

#endif // __SNOWBALL_SRC_OBJECT_H_
