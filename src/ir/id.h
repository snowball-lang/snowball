
#include <cstdint>
#include <stdio.h>

#ifndef __SNOWBALL_ID_MIXIN_H_
#define __SNOWBALL_ID_MIXIN_H_

namespace snowball {
namespace ir {

using id_t = std::int64_t;

/// Mixin class for IR nodes that need ids.
class IdMixin {
  private:
    /// the global id counter
    static id_t currentId;

  protected:
    /// the instance's id
    id_t id;

  public:
    /// Resets the global id counter.
    static void resetId();

    IdMixin() : id(currentId++) {}
    IdMixin& operator=(const IdMixin&) = delete;

    /// @return the node's id.
    virtual id_t getId() const { return id; }
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_ID_MIXIN_H_
